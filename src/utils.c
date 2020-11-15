#include "utils.h"


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
	char* input = smalloc(sizeof(char) * FULLCMNDSIZE, WHERE);
    char* token = smalloc(sizeof(char) * CMNDSIZE, WHERE);
	size_t cmndsize = FULLCMNDSIZE;
	if (	getline(&input, &cmndsize, stdin) == -1 &&
			!feof(stdin)	) OHNO;
	// Now, lets divide the input into tokens,
	// putting the first one in tokens[0], and
	// use a loop for the remaining ones.
	token = strtok(input, DELIMITERS);	// First token
	if (!token) {	// Nothing was typed
		if (tokens[0]) {
			free(tokens[0]);
			tokens[0] = NULL;
		}
		return;
	}
	if (!tokens[0]) tokens[0] = smalloc(sizeof(char) * CMNDSIZE, WHERE);
	strcpy(tokens[0], token);
	int i = 1;
	while (i < TOKENSNUM) {
		token = strtok(NULL, DELIMITERS);	// Next token
		if (!token) break;	// We're all out of tokens
		if (!tokens[i]) tokens[i] = smalloc(sizeof(char) * CMNDSIZE, WHERE);
		strcpy(tokens[i], token);
		i++;
	}
	if (tokens[i] && i < TOKENSNUM) {
		free(tokens[i]);
		tokens[i] = NULL;
	}
	free(input);
	free(token);
}

/**
 * @brief	Frees memory that has been dinamically
 *			allocated by the program.
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
	if (!job_names[i]) job_names[i] = smalloc(sizeof(char) * CMNDSIZE, WHERE);
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


/**
 * @brief		Wrapper for malloc with error handling
 *
 * @details		Calls malloc, uses function panic() if something
 *				goes wrong.
 * 
 * @param size		Size in bytes of memory to be allocated
 * @param file		File that called this function
 * @param function	Function that called this function
 * @param line		Code line that called this function
 * @return void*	Pointer to allocated memory space
 */
void* smalloc(size_t size, char* file, char* function, int line) {
	void* ptr = malloc(size);
	if (!ptr) panic(file, function, line);
	return ptr;
}

/**
 * @brief		Wrapper for calloc with error handling
 * 
* @details		Calls calloc, uses function panic() if something
 *				goes wrong.
 * @param nitems	Number of elements to be allocated
 * @param size		Size in bytes of elements to be allocated
 * @param file		File that called this function
 * @param function	Function that called this function
 * @param line		Code line that called this function
 * @return void*	Pointer to allocated memory space
 */
void* scalloc(size_t nitems, size_t size, char* file, char* function, int line) {
	void* ptr = calloc(nitems, size);
	if (!ptr) panic(file, function, line);
	return ptr;
}

/**
 * @brief			Shows an error message
 *
 * @details			The macro "OHNO" is expanded into
 *					"ohno(__FILE__, __func__, __LINE__)".
 * 
 * @param file		File where error occurred
 * @param function	Function where error occurred
 * @param line		Number of line which called the function
 */
void ohno(char* file, char* function, int line) {
	printf(
		"Error!\n"
		"File: %s\n"
		"Function: %s\n"
		"Line: %d\n"
		"errno: %d\n",
		file, function, line, errno);
	perror("");
}


/**
 * @brief			Shows an error message and exits
 *
 * @details			The macro "OHNO" is expanded into
 *					"ohno(__FILE__, __func__, __LINE__)".
 * 
 * @param file		File where error occurred
 * @param function	Function where error occurred
 * @param line		Number of line which called the function
 */
void panic(char* file, char* function, int line) {
		printf(
		"Error!\n"
		"File: %s\n"
		"Function: %s\n"
		"Line: %d\n"
		"errno: %d\n",
		file, function, line, errno);
	perror("");
}