#ifndef CONFIG_H
#define CONFIG_H


//================================
// MACROS
//================================
#define INPUTSIZE 128	// Tamanho do buffer que recebe input do usuário
#define CMNDSIZE 32 	/*Tamanho máximo que espera-se que um comando ou 								argumento tenha */
#define FULLCMNDSIZE 128	// Tamanho grande de uso geral
#define TOKENSNUM 64	// Número máximo de tokens (comando + argumentos)
#define PROCSNUM 64		// Número máximo de processos
#define PROMPT "segfaush >> "
#define DELIMITERS " \n"

#endif	// CONFIG_H