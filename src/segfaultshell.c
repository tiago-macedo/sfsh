#include "segfaultshell.h"
#include "command_funcs.c"

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

//================================
// FUNÇÕES
//================================

/**
 * @brief		Lê e interpreta entrada do usuário.
 * 
 * @details		Caso não haja entrada do usuário, esta função não faz nada.
 *				Caso haja entrada, esta função separa a entrada do usuário,
 *				usando espaços como divisores, e coloca os pedaços no array
 *				global tokens. O token seguinte ao último deve ficar nulo.
 */
void get_command() {
	// Vamos ler a entrada do usuário.
	char* input = malloc(sizeof(char) * FULLCMNDSIZE);
    char* token = malloc(sizeof(char) * CMNDSIZE);
	size_t cmndsize = FULLCMNDSIZE;
	getline(&input, &cmndsize, stdin);
	// Agora, vamos dividir a entrada em partes,
	// colocando a primeira em tokens[0] e as se-
	// -guintes em tokens.
	token = strtok(input, DELIMITERS); // primeiro token
	if (!token) {
		free(tokens[1]);
		tokens[1] = NULL;
		return;
	}; // nada foi digitado
	if (!tokens[0]) tokens[0] = malloc(sizeof(char) * CMNDSIZE);
	if (!tokens[0]) {
		perror("get_command: falha ao alocar tokens[0]:");
		free(input);
		free(token);
		exit(errno);
	}
	strcpy(tokens[0], token);
	int i = 1;
	while (i < TOKENSNUM) {
		token = strtok(NULL, DELIMITERS); // proximo token
		if (!token) break; // tokens acabaram
		if (!tokens[i]) tokens[i] = malloc(sizeof(char) * CMNDSIZE);
		if (!tokens[i]) {
			perror("get_command: falha ao alocar tokens[0]:");
			free(input);
			free(token);
			exit(errno);
		}
		strcpy(tokens[i], token); // tokens[i] = token[i+1]
		i++;
	}
	if (tokens[i] && i < TOKENSNUM) free(tokens[i]);
	tokens[i] = NULL;
	free(input);
}

/**
 * @brief	Desaloca a memória dinamicamente alocada
 *			pelo programa.
 * 
 */
void cleanup() {
	if (!cwd) free(cwd);
	for (int i=0; i<TOKENSNUM; i++) {
		if (tokens[i]) free(tokens[i]);
	}
	if (tokens) free(tokens);
	if (job_names) free(job_names);
	return;
}

/**
 * @brief		Adiciona processo à lista de processos (procs)
 * 
 * @param pid	pid do processo a ser adicionado à lista
 * @param name	nome do processo a ser adicionado à lista
 */
void add_proc(int pid, char* name) {
	int i = 0;
	while (procs[i] != 0) i++;
	procs[i] = pid;
	if (name[i]) job_names[i] = malloc(sizeof(char) * CMNDSIZE);
	strcpy(job_names[i], name);
	procs[i+1] = 0;
}

/**
 * @brief		Retira processo da lista de processos (procs)
 * 
 * @param pid	pid do processo a ser retirado da lista
 */
void del_proc(int pid) {
	if (!has_proc(pid)) return;
	int i = 0;
	while (procs[i] != pid) i++;
	procs[i] = 0;
	no_nulls();
}

/**
 * @brief	Checa se pid corresponde a um processo na lista
 * 
 * @param pid	pid a ser verificado
 * @return int	1 se sim, 0 se não
 */
int has_proc(int pid) {
	int i;
	for (i=0; procs[i]; i++) if (procs[i] == pid) return 1;
	return 0;
}

/**
 * @brief Tira buracos da lista de processos
 * 
 */
void no_nulls() {
	for (int i=0; i<PROCSNUM; i++) { // Percorre array
		if (procs[i] == 0) { // Encontrei um buraco
			int j = i + 1;
			for (; procs[j]; j++) {
				procs[j-1] = procs[j]; 		// Todo mundo a frente do buraco...
				if (job_names[j]) {
					strcpy(job_names[j-1], job_names[j]); // ...dá um passo atrás.
				}
			}
			procs[j-1] = 0;
			if (job_names[j-1]) free(job_names[j-1]);
			job_names[j-1] = NULL;
		}
	}
}