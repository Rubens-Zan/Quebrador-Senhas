#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "biblioteca.h"


#define MAX_SENHAS 100

static unsigned int n_login = 0;       /* número de tentativas de login */
static char segredo[MAX_SENHAS][7];    /* matriz com senhas que devem ser quebradas   */
static unsigned int n_senhas = 0;      /* quantidade de senhas lidas do arquivo */
static unsigned int senha_da_vez = -1;  /* qual a senha que estamos testado atualmente */
static struct timespec inicio, fim;    /* contagem de tempo             */


/* -------------------------------------------------------------------------- */
void inicia_tempo(void){
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &inicio);
}
/* -------------------------------------------------------------------------- */
void finaliza_tempo(void){
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &fim);
}
/* -------------------------------------------------------------------------- */
/* devolve o tempo decorrido em segundos                                      */
double tempo_decorrido(void){
	double t_s = (double)(fim.tv_sec - inicio.tv_sec) +
              (double)(fim.tv_nsec - inicio.tv_nsec) / 1.0e9;
	return t_s;
}
/* -------------------------------------------------------------------------- */
void zera_contadores(void) {
  n_login = 0;
}
/* -------------------------------------------------------------------------- */
unsigned int total_login(void) {
  return n_login;
}
/* -------------------------------------------------------------------------- */
unsigned int proxima_senha(void) {
  senha_da_vez++;
  if (senha_da_vez < n_senhas)
      return 1;
  return 0;
}
/* -------------------------------------------------------------------------- */
unsigned int login(char *senha){
    ++n_login;
	if (strcmp(senha, segredo[senha_da_vez]) == 0)
        return 1;
    return 0;
}
/* -------------------------------------------------------------------------- */
void carregar_senhas(char *nome_arquivo){
    char * line = NULL;
    size_t len = 0;
    size_t read;
    
    FILE *fp = fopen(nome_arquivo, "r");

    if (fp == NULL){
         printf("Nao foi possivel ler o arquivo de senhas\n");
         exit(EXIT_FAILURE);
    }

    n_senhas = 0;
    while ((read = getline(&line, &len, fp)) != -1  && (n_senhas < MAX_SENHAS)) {
        line[strlen(line)-1] = '\0';
        strcpy(segredo[n_senhas] , line);
        n_senhas++;
    }
    printf("leitura das senhas completadas, %d senhas lidas\n",n_senhas);

    fclose(fp);
}
/* -------------------------------------------------------------------------- */
char *senha_atual(void){
    return segredo[senha_da_vez];
}

