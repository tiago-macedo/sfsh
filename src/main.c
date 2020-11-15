#include "main.h"

//================================
// MAIN
//================================
int main(int argc, char* argv[], char* envp[]) {
	if ( atexit(cleanup) ) PANIC;
	tokens = scalloc(TOKENSNUM, sizeof(char*), WHERE);
	job_names = scalloc(PROCSNUM, sizeof(char*), WHERE);
	for (int i=0; i<PROCSNUM; i++) procs[i] = 0;
	if ( chdir(getenv("HOME")) ) OHNO;
	if (!( cwd = getcwd(NULL, 0) )) OHNO;
	while(1) {
		printf("sfsh | %s >> ", cwd); // Escreve o prompt
		get_command();
		if (!strcmp(tokens[0], "\n")) continue;
		// COMANDOS BUILTINS
		if (!strcmp(tokens[0], "exit")) break;
		else if (!strcmp(tokens[0], "del")) del_proc(atoi(tokens[1]));
		else if (!strcmp(tokens[0], "fg")) sh_fg();
		else if (!strcmp(tokens[0], "bg")) sh_bg();
		else if (!strcmp(tokens[0], "jobs")) sh_jobs();
		else if (!strcmp(tokens[0], "cd")) sh_cd();
		else if (!strcmp(tokens[0], "kill")) sh_kill();
		else sh_run();
	}
	return 0;
}