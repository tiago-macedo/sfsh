#include "main.h"
#include "utils.h"
#include "command.h"

//================================
// MAIN
//================================
int main(int argc, char* argv[], char* envp[]) {
	atexit(cleanup);
	tokens = calloc(TOKENSNUM, sizeof(char*));
	if (!tokens) {
		perror("Variável tokens:");
		return errno;
	}
	job_names = calloc(PROCSNUM, sizeof(char*));
	for (int i=0; i<PROCSNUM; i++) procs[i] = 0;
	chdir(getenv("HOME"));
	cwd = malloc(sizeof(char) * FULLCMNDSIZE);
	cwd[0] = '\0';
	getcwd(cwd, sizeof(char) * FULLCMNDSIZE);
	while(1) {
		printf("sfsh @ %s> ", cwd); // Escreve o prompt
		get_command();
		if (!strcmp(tokens[0], "\n")) continue;
		// COMANDOS BUILTINS
		if (!strcmp(tokens[0], "quit")) break;
		else if (!strcmp(tokens[0], "del")) del_proc(atoi(tokens[1]));
		else if (!strcmp(tokens[0], "fg")) sh_fore();
		else if (!strcmp(tokens[0], "bg")) sh_back();
		else if (!strcmp(tokens[0], "jobs")) sh_jobs();
		else if (!strcmp(tokens[0], "cd")) sh_cd();
		else if (!strcmp(tokens[0], "kill")) sh_kill();
		else sh_run();
	}
	return 0;
}