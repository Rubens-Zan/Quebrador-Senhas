/*
    Feito por Rubens Zandomenighi Laszlo, GRR20206147
    Em 01/08/2021.
    Programa que implementa dois tipos de quebradores de senha,
    Quebrador de senha backtracking com poda de arvore ( backtracking ). 
    Quebrador de senha backtracking sem poda de arvore ( exaustivo ). 
    Ambos devem ser feitos recursivamente. 

    O quebrador de senha exaustivo leva em conta apenas as duas primeiras restricoes e o backtracking
    todas as restricoes. 

    1. Apenas letras minúsculas (códigos da tabela ASCII do 97 ao 122 em decimal) e números
    (códigos da tabela ASCII do 48 ao 57 em decimal) são permitidos
    2. A senha deve conter exatamente 6 caracteres
    3. Repetição de caracteres não é permitida
    4. A senha deve conter pelo menos 2 letras
    5. A senha deve conter pelo menos 2 números

*/

#include "biblioteca.h" 
#include "quebrador-senha.h"

#include <stdio.h> 
 
/*********************************************************************************************************************/

/* Funcoes que ambas utilizam  */
void imprime_senha(char *senha,int n);
void troca(char v[], int a, int b);
int permutar(char senha[], int l, int r); 


/* Funcoes do quebrador de senha Backtracking */
int acha_combin_backtracking(int aceitos[], int n, int r);  
int combinacoes_backtracking(int aceitos[], char senha[], int n, int r, int index, int i, int letras, int numeros);

/* Funcoes do quebrador de senha exaustivo */
int acha_combin_exaustivas(int aceitos[], int n, int r);
int combinacoes_exaustivas(int aceitos[], char senha[], int n, int r, int index, int i);

/**********************************************************************************************************************/

/* Funcoes utilizadas por ambas as implementacoes */

/* Funcao que troca elementos do vetor  */
void troca(char v[], int a, int b)
{
    char aux = v[a];
    v[a] = v[b];
    v[b] = aux;
}

/*Funcao para imprimir a senha, caso tenha sido encontrada*/
void imprime_senha(char *senha, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%c", senha[i]);
    }
    printf("\n");
}

/* 
    Funcao para permutar todas as combinacoes possiveis com os caracteres recebidos 
    Retorna se alguma das permutacoes eh a senha a ser quebrada
*/
int permutar(char senha[], int l, int r)
{
    int i;
    if (l == r && login(senha))         /* Funcao login testa se a combinacao eh a senha atual  */
    {
        printf("Senha encontrada:  ");  /* Caso encontre vai imprimir a senha */
        imprime_senha(senha, r);
        return 1;                       /* e retorna 1 */
    }
    else                
        for (i = l; i < r; i++)
        {
            troca(senha, l, i);
            if (permutar(senha, l + 1, r))
                return 1;
            troca(senha, l, i);         
        }
    return 0;                          /* se nenhuma das permutacoes da combinacao eh a senha */
};


/********************************************************************************************************************/

/* Implementacao recursiva do quebrador de senha, utilizando backtracking com poda de arvore */

/* Retorna 1 caso tenha encontrado a senha e 0 caso contrario */
int quebrador_senha_backtracking()
{
    /* Ascii aceitos vai ser preenchido com os numeros e as letras minusculas da tabela ascii */
    int ascii_aceitos[] = {48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106,
                           107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119,
                           120, 121, 122};
    
    int qntd = 6;                                              /*Qtd de chars que a combinacao deve ter*/
    int n = sizeof(ascii_aceitos) / sizeof(ascii_aceitos[0]); /* Tamanho do vetor de ascii aceitos */  

    if (acha_combin_backtracking(ascii_aceitos, n, qntd)) 
        return 1;
    return 0;
}


int acha_combin_backtracking(int aceitos[], int n, int r) /* aceitos, max_tam, qtd*/
{

    char senha[r];   /*Senha vai possuir n caracteres, pois vai ser preenchida com 0s e 1s*/
    
    if (combinacoes_backtracking(aceitos, senha, n, r, 0, 0, 0, 0)) /*index, i, letras, numeros comecam em zero*/
        return 1;                                                  /*Retorna se achou a senha */
    return 0;
}

/* 
   aceitos[]  ---> Vetor com todos os caracteres aceitos
   senha[]    ---> Vetor para armazenar a senha
   n          ---> Tamanho do vetor dos caracteres aceitos(36)
   r          ---> Tamanho que deve ser a senha (6)
   index      ---> Index atual do vetor, vai percorrer todos os elementos dos chars aceitos
   i          ---> Quanto elementos foram adicionados  
*/
int combinacoes_backtracking(int aceitos[], char senha[], int n, int r, int index, int i, int letras, int numeros)
{
    
    if (index == n)                                   /* Se ja percorreu o vetor de caracteres aceitos */
    {
        if (i == r && permutar(senha,0,r)) /* Se a senha possui 6 caracteres, testa a combinacao */
            return 1;
        return 0;            /* Caso nao possua 6 caracteres ou se nenhuma permutacao dos char eh a senha */
    }
   
    
    /* Adicionando elemento do indice */
    
    senha[i] = aceitos[index];
    if (index > 9)                      /*no vetor de char aceitos, do 0 ao 9 sao numeros e do 10 ao 35 sao letras*/
        letras++;                       /* Indice maiores que 9 sao letras */
    else
        numeros++;                      /* Indice <=  9 sao numeros */
    if (numeros < 5 && letras < 5)      /* Podando a arvore, caso nao cumpra requisitos */
        if (combinacoes_backtracking(aceitos, senha, n, r, index + 1, i + 1, letras, numeros)) 
            return 1;
    
    /* Aqui combinacoes sem o elemento do indice */
    senha[i] = 0;
    if (index > 9) /*no vetor de char aceitos, do 0 ao 9 sao numeros e do 10 ao 35 sao letras*/
        letras--;  /*Indice maiores que 9 sao letras*/
    else
        numeros--; /*indice <=  9 sao numeros */    
    if (numeros < 5 && letras < 5)      /* Podando a arvore, caso nao cumpra requisitos */
        if (combinacoes_backtracking(aceitos, senha, n, r, index + 1, i, letras, numeros))
            return 1;
};


/********************************************************************************************************************/

/* Implementacao recursivo do quebrador de senha exaustivo */

/* Retorna 1 caso tenha encontrado a senha e 0 caso contrario */
int quebrador_senha_exaustivo()
{
    /* Ascii aceitos vai ser preenchido com os numeros e as letras minusculas da tabela ascii */
    int ascii_aceitos[] = {48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106,
                            107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119,
                            120, 121, 122};

    int qntd = 6; 
    int n = sizeof(ascii_aceitos) / sizeof(ascii_aceitos[0]); 

    if (acha_combin_exaustivas(ascii_aceitos, n, qntd )){ 
        return 1;
    }

    return 0; 
}

/*Funcao que retorna se a funcao de combinacoes exaustivas retornou verdadeiro*/
int acha_combin_exaustivas(int aceitos[], int n, int r)   /*aceitos,max_tam,qtd*/
{
    char senha[r];

    if (combinacoes_exaustivas(aceitos, senha, n, r, 0, 0))
        return 1;  /* Retorna se achou a senha */
    return 0;
}

/* 
    Efetua todas as permutacoes possiveis de senhas,
    conforme os caracteres permitidos e que contenham 6 caracteres  
*/
int combinacoes_exaustivas(int aceitos[], char senha[], int n, int r, int index, int ini)
{
    if (index == r)
    {
        if (permutar(senha,0,r))
            return 1;
        return 0; 
    }

    for (int i = ini; i < n; i++)
    {
        senha[index] = aceitos[i];   /* a senha vai receber os indices inclusos na combinacao */
        if (combinacoes_exaustivas(aceitos, senha, n, r, index + 1, i))
            return 1;
    }
    return 0; 
}

/********************************************************************************************************************/

/* 
    Quebrador de senha exaustivo sem repeticoes

/* 
   aceitos[]  ---> Vetor com todos os caracteres aceitos
   senha[]    ---> Vetor para armazenar a senha 
   n          ---> Tamanho do vetor dos caracteres aceitos
   r          ---> Tamanho que deve ser a senha, no caso do T2, 6
   index      ---> Index do vetor aceitos[]
   i          ---> Quantos elementos foram adicionados a combinacao, incrementado quando senha[index] = 1 
*
int combinacoes_exaustivas(int aceitos[], char senha[], int n, int r, int index, int i)
{
    if (index == n )  /* Se ja percorreu o vetor de caracteres aceitos *
        {
            if (i == r && permutar(senha,0,r)) /* Se a combinacao possui 6 caracteres e se alguma permutacao eh a senha *
            return 1; 
        return 0; /* Se nao possui 6 chars ou se nao eh a senha *
    }

    /* Aqui vai gerar todas as possiveis combinacoes contendo os elementos do vetor de caracteres aceitos *
    
    senha[i] = 0;           
    if (combinacoes_exaustivas(aceitos, senha, n, r, index + 1, i))
        return 1;
           
    senha[i] = aceitos[index];
    if (combinacoes_exaustivas(aceitos, senha, n, r, index + 1, i + 1)) /*O i eh incrementado apenas quando um elemento eh colocado no vetor*
        return 1;    
}
*/