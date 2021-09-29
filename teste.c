#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "biblioteca.h"
#include "quebrador-senha.h"

void testa_quebrador_senha(){
    unsigned int backtracking, exaustiva;
    double porcentagem_login;
    double backtracking_tempo, exaustiva_tempo;
    double porcentagem_tempo;

    while(proxima_senha()){
        printf("------------------------------------------\n");
        printf("Testando senha: %s\n",senha_atual());

        printf("Rodando Backtracking: \n");
        zera_contadores();
        inicia_tempo();
        if (!quebrador_senha_backtracking())
	        printf("Erro, senha nao encontrada!\n");
        finaliza_tempo();
        backtracking =  total_login();
        backtracking_tempo = tempo_decorrido();
        printf("\t%u tentativas de login\n",backtracking);
        printf("\tTempo decorrido: %lf s\n",backtracking_tempo);

        printf("Rodando busca exaustiva: \n");
        zera_contadores();
        inicia_tempo();
        if(!quebrador_senha_exaustivo())
	        printf("Erro, senha nao encontrada!\n");
        finaliza_tempo();
        exaustiva = total_login();
        exaustiva_tempo = tempo_decorrido();
        printf("\t%u tentativas de login\n",exaustiva);
        printf("\tTempo decorrido: %lf s\n",exaustiva_tempo);

        porcentagem_login =  (double)backtracking/exaustiva * 100;
        porcentagem_tempo =  backtracking_tempo/exaustiva_tempo * 100;
        printf("\nBacktracking reduziu as tentativas de login para %.2f%% e o tempo para %.2f%%\n", porcentagem_login, porcentagem_tempo );
    }
}

int main(){
    carregar_senhas("senhas.txt");
    testa_quebrador_senha();
    return 0;
}

