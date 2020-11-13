#ifndef	MAIN_H
#define MAIN_H

//================================
// INCLUDES
//================================

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

#include "config.h"

//================================
// PROTÓTIPOS
//================================
void get_command();		// Lê comando do usuário
void cleanup();			// Limpa memória dinamicamente alocada
void add_proc(int, char*);	// Adiciona processo da lista de processos
void del_proc(int);		// Deleta processo da lista de processos
int has_proc(int);		// Checa se pid corresponde a um processo na lista
void no_nulls();		// Tira buracos da lista de processos
void ohno(char* file, char* function, int line);	// Shows an error message

//================================
// VARIÁVEIS EXTERNAS
//================================
extern int errno;		// Variável de erro
extern char** environ;	// Array de strings com variáveis de ambiente

//================================
// VARIÁVEIS GLOBAIS
//================================
char ** tokens = NULL;	// Pedaços do que o usuário digitou
char * cwd = NULL;		// Atual diretório de trabalho
int procs[PROCSNUM];	// Array de pids de processos em execução
char** job_names = NULL;

#endif	// MAIN_H