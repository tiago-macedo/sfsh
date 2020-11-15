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
#include "utils.h"
#include "command.h"


//================================
// VARIÁVEIS EXTERNAS
//================================
extern int errno;		// Variável de erro
extern char** environ;	// Array de strings com variáveis de ambiente

//================================
// VARIÁVEIS GLOBAIS
//================================
char** tokens = NULL;		// Pedaços do que o usuário digitou
char* cwd = NULL;			// Atual diretório de trabalho
int procs[PROCSNUM];		// Array de pids de processos em execução
char** job_names = NULL;	// Pointeiro para cadeira de nomes de processos

#endif	// MAIN_H