#ifndef UTILS_H
#define UTILS_H


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
// MACROS
//================================

#define WHERE __FILE__, (char*) __func__, __LINE__
#define OHNO ohno(WHERE)
#define PANIC panic(WHERE)
// #define malloc(s) smalloc(s, WHERE)	// Can't figure out why this fails
// #define calloc(n, s) scalloc((size_t) n, s, WHERE)	// Or this


//================================
// EXTERNAL VARIABLES
//================================

extern char** tokens;
extern char* cwd;
extern int procs[PROCSNUM];
extern char** job_names;
extern int errno;
extern char** environ;


//================================
// PROTOTYPES
//================================

void get_command();		// Lê comando do usuário
void cleanup();			// Limpa memória dinamicamente alocada
void add_proc(int, char*);	// Adiciona processo da lista de processos
void del_proc(int);		// Deleta processo da lista de processos
int has_proc(int);		// Checa se pid corresponde a um processo na lista
void no_nulls();		// Tira buracos da lista de processos
int last_token(); // Retorna posição do ultimo token
int last_proc(); // Retorna posição do processo da lista

void* smalloc(size_t, char*, char*, int);	/* Wrapper for malloc with error
											   handling */
void* scalloc(size_t, size_t, char*, char*, int);	/* Wrapper for calloc with
													   error handling */
void ohno(char*, char*, int);	// Shows an error message
void panic(char*, char*, int);	// Shows an error message and exits

#endif	// UTILS_H
