#ifndef COMMAND_H
#define COMMAND_H

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


//================================
// EXTERNAL VARIABLES
//================================

extern char ** tokens;
extern char * cwd;
extern int procs[PROCSNUM];
extern char** job_names;
extern int errno;
extern char** environ;


//================================
// PROTÓTIPOS
//================================

void sh_cd(); // Comando builtin para mudar de diretório
void sh_jobs(); // Mostra uma lista dos processos filhos da shell
void sh_run(); // Executa programa, inciialmente em foreground
void sh_fore(); // Passa um programa para foreground
void sh_back(); // Executa programa em background
void sh_kill(); // Mata um processo
int last_token(); // Retorna posição do ultimo token
int last_proc(); // Retorna posição do processo da lista

int fore_cycle(int pid); // Fica esperando o filho
void sig_child(int); // Passar SIGINT ao filho
void stop_child(int); // Passar filho pro background

#endif	// COMMAND_H