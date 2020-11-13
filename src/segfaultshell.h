//================================
// INCLUDES
//================================
#ifndef STDIO_H
	#define STDIO_H
	#include <stdio.h>
#endif

#ifndef STDLIB_H
	#define STDLIB_H
	#include <stdlib.h>
#endif

#ifndef UNISTD_H
	#define UNISTD_H
	#include <unistd.h>
#endif

#ifndef LIMITS_H
	#define LIMITS_H
	#include <limits.h>
#endif

#ifndef SYS_WAIT_H
	#define SYS_WAIT_H
	#include <sys/wait.h>
#endif

#ifndef ERRNO_H
#define ERRNO_H
#include <errno.h>
#endif

#ifndef STRING_H
	#define STRING_H
	#include <string.h>
#endif

//================================
// MACROS
//================================
#define INPUTSIZE 128 // Tamanho do buffer que recebe input do usuário
#define CMNDSIZE 32 // Tamanho máximo que espera-se que um comando ou argumento tenha
#define FULLCMNDSIZE 128 // Tamanho grande de uso geral
#define TOKENSNUM 64 // Número máximo de tokens (comando + argumentos)
#define PROCSNUM 64 // Número máximo de processos
#define PROMPT "segfaush >> "
#define DELIMITERS " \n"

//================================
// PROTÓTIPOS
//================================
void get_command(); // Lê comando do usuário
void cleanup(); // Limpa memória dinamicamente alocada
void add_proc(int, char*); // Adiciona processo da lista de processos
void del_proc(int); // // Deleta processo da lista de processos
int has_proc(int); // Checa se pid corresponde a um processo na lista
void no_nulls(); // Tira buracos da lista de processos

//================================
// VARIÁVEIS EXTERNAS
//================================
extern int errno; // Variável de erro
extern char** environ; // Array de strings com variáveis de ambiente

//================================
// VARIÁVEIS GLOBAIS
//================================
char ** tokens = NULL; // Pedaços do que o usuário digitou
char * cwd = NULL; // Atual diretório de trabalho
int procs[PROCSNUM]; // Array de pids de processos em execução
char** job_names = NULL;