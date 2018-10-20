#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#define MAX_NOME 100
#define NOME_EQUIPA 20
#define AUX 10

    /*ESTRUTURAS*/
typedef struct equipa* ApontEquipa;
typedef struct jogo* ApontJogo;
typedef struct jornada* ApontJornada;
typedef struct classificacao* ApontClassificacao;

typedef struct equipa{
    char nome[MAX_NOME];
    char treinador[NOME_EQUIPA];
    int rating;
    int golos_marcados;
    int golos_sofridos;
    int pontos;
    int vitorias,empates,derrotas;
    int posicao;
    int progress;
    int id;
}Equipa;

typedef struct jogo{
    ApontEquipa a,b;
    int score_a,score_b;
    ApontJogo next;
}Jogo;

typedef struct jornada{
    int n;
    ApontJogo jogos;
    ApontJornada next;
}Jornada;

typedef struct classificacao{
    ApontEquipa team;
    ApontClassificacao next;
}Classificacao;


    /*FUNCOES*/
void menu(void);
void scan_int_prot(int * num);
void ajuda(void);
void novo_jogo(void);
void carrega_jogo(void);
int sair(void);
void menu_jogo(ApontEquipa my_team,ApontClassificacao classi,ApontJornada jornadas,int jor_act);
Equipa cria_equipa(Equipa my_team);
ApontClassificacao le_ficheiro_default(ApontClassificacao classi,int * conta);
void visualiza_classificacao(ApontClassificacao classi);
void ver_equipa(ApontEquipa my_team);
ApontJornada cria_jornadas(ApontJornada jornadas,int n,ApontClassificacao classi);
ApontEquipa procura_equipa_por_id(ApontClassificacao l,int n);
ApontEquipa procura_equipa_por_nome(ApontClassificacao l,char *n);
void roda(int v[], int n);
ApontJornada adiciona_fim(ApontJornada l,ApontJornada novo);
void consultar_jornadas(ApontJornada jornadas);
void letsplay(ApontClassificacao *classi,ApontJornada * jor,int *n);
ApontClassificacao atualiza_classificacao(ApontClassificacao l);
ApontClassificacao insere_ord(ApontClassificacao l, ApontClassificacao novo);
void consulta_equipa(ApontClassificacao classi);
void visualiza_equipas(ApontClassificacao classi);
ApontClassificacao atualiza_posicao(ApontClassificacao l);
void consultar_calendario(ApontJornada jornadas,ApontEquipa my_team);
void salvar(ApontClassificacao classi,ApontEquipa my_team,ApontJornada jorna,int jor_act);
void carrega(ApontClassificacao *classi,Equipa *my_team,ApontJornada *jornadas,char file_name[MAX_NOME],int *jor_act);
ApontEquipa procura_equipa_por_nome(ApontClassificacao l,char n[MAX_NOME]);
