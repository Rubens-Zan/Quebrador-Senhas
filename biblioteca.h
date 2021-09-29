#ifndef _BIBLIOTECA_H_
#define _BIBLIOTECA_H_

unsigned int login(char *senha);
void carregar_senhas(char *nome_arquivo);
char *senha_atual(void);
unsigned int proxima_senha(void);

void zera_contadores(void);
unsigned int total_login(void);
void inicia_tempo(void);
void finaliza_tempo(void);
double tempo_decorrido(void);

#endif
