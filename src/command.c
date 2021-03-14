#include "command.h"

/**
 * @brief	Builtin command to change working directory
 * 
 * @details	`tokens[1]` contains path where we want to go
 */
void sh_cd() {
	if(chdir(tokens[1]) != 0) perror("Failed to change directory:");
	free(cwd);
	cwd = getcwd(NULL, 0);
}

/**
 * @brief	Builtin command to print a list of processes being
 *			executed by the shell's children
 * 
 */
void sh_jobs() {
	if (procs[0] == 0) {
		printf("No jobs!\n");
		return;
	}
	printf("pid\tnome\n");
	printf("----------------\n");
	for (int i=0; procs[i] != 0; i++) {
		printf("%d\t%s\n", procs[i], job_names[i]);
	}
}

/**
 * @brief	Runs a program
 * 
 */
void sh_run() {
	int pid;
	int fore = 1;
	int i = last_token();
	if (!strcmp(tokens[i], "&")) {	// last token is '&': backround the program
		fore = 0;
		free(tokens[i]);	// remove the '&'
		tokens[i] = NULL;	// from the list of tokens
	}
	if ((pid = fork()) != 0) {		// we're the parent process
		add_proc(pid, tokens[0]);	// add program being run by child to process list
		if (fore) {
			fore_cycle(pid);
			del_proc(pid);
		}
		else kill(pid, SIGTSTP);
	}
	else {				// we're at the child process
		if (execve(tokens[0], tokens, environ)) {	//TODO: use execvp() instead
			printf("Program not found.\n");
		}
		exit(errno);
	}
}

/**
 * @brief	Waits for child process
 * 
 * @details	Returns 1 if process is finished, 0 if it's stalled.
 *
 * @par pid	PID of foreground process
 */
int fore_cycle(int pid) {
	if (!has_proc(pid)) return -2;
	int status;
	signal(SIGINT, sig_child);	// signal child
	signal(SIGTERM, sig_child);
	signal(SIGTSTP, stop_child);
	waitpid(pid, &status, WUNTRACED);
	signal(SIGINT, SIG_DFL);
	signal(SIGTERM, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	if (WIFEXITED(status)) {		// child exited
		if (WEXITSTATUS(status) != 0) printf("[%d]\n", WEXITSTATUS(status));
		return 1;
	}
	else if (WIFSTOPPED(status)) {	// child stopped
		printf("process %d (%s) stopped.\n", pid, tokens[0]);
		return 0;
	}
	else if (WIFSIGNALED(status)) {	// child was signaled
		printf("process %d (%s) has ended due to signal %d.\n", pid, tokens[0], WSTOPSIG(status));
		return 1;
	}
	else return -1;
}

/**
 * @brief Signals last child process (foreground)
 * 
 * @param sig Signal to be sent
 */
void sig_child(int sig) {
	int status;
	waitpid(0, &status, WUNTRACED);
	signal(SIGINT, SIG_DFL);
	signal(SIGTERM, SIG_DFL);
	return;
}

/**
 * @brief Stops last child process (foreground)
 * 
 * @param sig Signal to be sent
 */
void stop_child(int sig) {
	signal(SIGTSTP, SIG_DFL);
	return;
}

/**
 * @brief	Runs program in the foreground
 * 
 */
void sh_fg() {
	int pid = 0;
	if (tokens[1]) pid = atoi(tokens[1]);
	else pid = procs[last_proc()];
	kill(pid, SIGCONT);
	if (fore_cycle(pid)) del_proc(pid);
}

/**
 * @brief	Runs program in the background
 * 
 */
void sh_bg() {
	printf("Para colocar um programa em background, basta pressionar ctrl+Z enquanto ele está sendo executado.\n");
}

void sh_kill() {
	kill(atoi(tokens[1]), SIGKILL);
	del_proc(atoi(tokens[1]));
}
