#include "command_funcs.h"

/**
 * @brief	Comando builtin para mudar de diretório
 * 
 * @details	Local para onde deve-se desviar encontra-se
 *			em tokens[1].
 */
void sh_cd() {
	if (!strcmp(tokens[1], ".")) return; // Nada acontece

	else if (!strcmp(tokens[1], "..")) { // Vamos subir!
		/*
			Precisamos de um loop que crie um path
			igual ao cwd atual, tirando o último diretório.
			Para isso, vamos usar strtok() para dividir o
			atual cwd em pedaços e colocá-los em temp_path.
		*/
		char * temp_path = malloc(CMNDSIZE * sizeof(char));
		temp_path[0] = '\0';
		strcat(temp_path, "/");
		char * token = strtok(cwd, "/");
		if (!token) return; // Usuário já está na raiz
		char * old_token = token;
		while ( (token = strtok(NULL, "/")) ) {
			strcat(temp_path, old_token);
			strcat(temp_path, "/");
			old_token = token;
		}
		if (chdir(temp_path) != 0) {
			perror("Erro subindo p diretório:");
			exit(errno);
		}
		getcwd(cwd, sizeof(char) * FULLCMNDSIZE);
	}
	else if (tokens[1][0] == '/') {
		if(chdir(tokens[1]) != 0) perror("Falha ao mudar de diretório:");
		getcwd(cwd, sizeof(char) * FULLCMNDSIZE);
	}
}

/**
 * @brief	Comando builtin para imprimir uma lista dos processos
 *			sendo executados por filhos da shell
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
 * @brief	Executa programa em foreground
 * 
 */
void sh_run() {
	int pid;
	int fore = 1;
	int i = last_token();
	if (!strcmp(tokens[i], "&")) { // Ultimo token é &: background!
		fore = 0;
		free(tokens[i]); // Retirar &
		tokens[i] = NULL; // dos argumentos.
	}
	if ((pid = fork()) != 0) { // Pai
		add_proc(pid, tokens[0]);
		if (fore) {
			if (fore_cycle(pid)) del_proc(pid);
		}
		else kill(pid, SIGTSTP);
	}
	else { // Filho
		execve(tokens[0], tokens, environ);
		exit(errno);
	}
}

/**
 * @brief	Fica esperando o filho
 * 
 * @details	Retorna 1 se o processo terminou, 0 se só está parado.
 *
 * @par pid	PID do processo que deve estar no foreground
 *
 */
int fore_cycle(int pid) {
	if (!has_proc(pid)) return -2;
	int status;
	signal(SIGINT, sig_child); // passar sinal ao filho
	signal(SIGTERM, sig_child);
	signal(SIGTSTP, stop_child);
	waitpid(pid, &status, WUNTRACED);
	signal(SIGINT, SIG_DFL);
	signal(SIGTERM, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	if (WIFEXITED(status)) { // filho deu exit
		if (WEXITSTATUS(status) != 0) printf("[%d]\n", WEXITSTATUS(status));
		return 1;
	}
	else if (WIFSTOPPED(status)) { // filho foi parado
		printf("processo %d (%s) parado.\n", pid, tokens[0]);
		return 0;
	}
	else if (WIFSIGNALED(status)) { // filho foi sinalizado
		printf("processo %d (%s) terminou devido a sinal %d.\n", pid, tokens[0], WSTOPSIG(status));
		return 1;
	}
	else return -1;
}

/**
 * @brief Envia sinal pro ultimo filho (foreground)
 * 
 * @param sig Sinal a ser enviado
 */
void sig_child(int sig) {
	int status;
	waitpid(0, &status, WUNTRACED);
	signal(SIGINT, SIG_DFL);
	signal(SIGTERM, SIG_DFL);
	return;
}

/**
 * @brief Para o ultimo filho (foreground)
 * 
 * @param sig Sinal a ser enviado
 */
void stop_child(int sig) {
	signal(SIGTSTP, SIG_DFL);
	return;
}

/**
 * @brief	Executa programa em background
 * 
 */
void sh_fore() {
	int pid = 0;
	if (tokens[1]) pid = atoi(tokens[1]);
	else pid = procs[last_proc()];
	kill(pid, SIGCONT);
	if (fore_cycle(pid)) del_proc(pid);
}

/**
 * @brief	Executa programa em background
 * 
 */
void sh_back() {
	printf("Para colocar um programa em background, basta pressionar ctrl+Z enquanto ele está sendo executado.\n");
}

void sh_kill() {
	kill(atoi(tokens[1]), SIGKILL);
	del_proc(atoi(tokens[1]));
}

int last_token() {
	int i=0;
	while(tokens[i] != NULL){
        i++;
    }
	return i-1;
}

int last_proc() {
	int i=0;
	while(procs[i] != 0){
        i++;
    }
	return i-1;
}