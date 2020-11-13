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