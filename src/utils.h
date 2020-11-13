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

#define OHNO ohno(__FILE__, __func__, __LINE__)


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
// FUNCTIONS
//================================

void get_command();
void cleanup();
void add_proc(int, char*);
void del_proc(int);
int has_proc(int pid);
void no_nulls();
void ohno(char*, char*, int);

#endif	// UTILS_H