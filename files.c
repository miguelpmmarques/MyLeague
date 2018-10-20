#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "header.h"
#include <string.h>
#define MAX_NOME 100
#define NOME_EQUIPA 20
#define AUX 10

void salvar(ApontClassificacao classi,ApontEquipa my_team,ApontJornada jorna,int jor_act)
{
    FILE *fp;
    FILE *fp2;
    char file_name[MAX_NOME];
    char auxi[MAX_NOME];
    int i,check=0;
    ApontJornada jornadas = jorna;
    ApontClassificacao move = classi;
    ApontJogo jog;
    strcpy(file_name,my_team->treinador);
    strcat(file_name,"_DataBase.txt");
    fp = fopen(file_name,"w");
    fprintf(fp,"%d\n",my_team->id);
    fprintf(fp,"%s\n",my_team->nome);
    fprintf(fp,"%s\n",my_team->treinador);
    fprintf(fp,"%d %d %d\n",my_team->vitorias,my_team->empates,my_team->derrotas);
    fprintf(fp,"%d %d %d %d\n",my_team->golos_marcados,my_team->golos_sofridos,my_team->pontos,my_team->posicao);
    fprintf(fp,"%d %d\n",my_team->rating,my_team->progress);
    while(move) /*Falta o rating e o progresso*/
    {
        if (strcmp(move->team->treinador,my_team->treinador))
        {
            fprintf(fp,"%s\n",move->team->nome);
            fprintf(fp,"%s\n",move->team->treinador);
            fprintf(fp,"%d %d %d %d %d %d %d %d %d\n",move->team->id,move->team->pontos,move->team->vitorias,move->team->empates,move->team->derrotas,move->team->golos_marcados,move->team->golos_sofridos,move->team->rating,move->team->progress);
        }
        move = move->next;
    }
    while(jornadas)
        {
            jog = jornadas->jogos;
            for (i=0;i<4;i++)
            {
                fprintf(fp,"%s\n",jog->a->nome);
                fprintf(fp,"%s\n",jog->b->nome);
                fprintf(fp,"%d - %d\n",jog->score_a,jog->score_b);
                jog = jog->next;
            }
            jornadas = jornadas->next;
        }
    fprintf(fp,"%d",jor_act);
    fclose(fp);
    fp2 = fopen("Users_Data.txt","r");
    while(!feof(fp2))
    {
        fscanf(fp2," %[^\n]s",auxi);
        if(!strcmp(auxi,my_team->treinador))
            check = 1;
    }

    fclose(fp2);
    if (check==0)
    {
        fp2 = fopen("Users_Data.txt","a");
        fprintf(fp2,"\n%s",my_team->treinador);
        fclose(fp2);
    }
}
void carrega(ApontClassificacao *classi,Equipa *my_team,ApontJornada *jornadas,char file_name[MAX_NOME],int *jor_act)
{
    FILE *fp;
    int i,j;
    char a[MAX_NOME];
    char b[MAX_NOME];
    ApontClassificacao move;
    ApontEquipa novo;
    ApontJornada jog,inutil;
    ApontJogo novo_j;
    fp = fopen(file_name,"r");
    fscanf(fp,"%d",&((*my_team).id));
    fscanf(fp," %[^\n]s",(*my_team).nome);
    fscanf(fp," %[^\n]s",(*my_team).treinador);
    fscanf(fp,"%d %d %d\n",&((*my_team).vitorias),&((*my_team).empates),&((*my_team).derrotas));
    fscanf(fp,"%d %d %d %d\n",&((*my_team).golos_marcados),&((*my_team).golos_sofridos),&((*my_team).pontos),&((*my_team).posicao));
    fscanf(fp,"%d %d\n",&((*my_team).rating),&((*my_team).progress));
    novo = (ApontEquipa)malloc(sizeof(Equipa));
    move = (ApontClassificacao)malloc(sizeof(Classificacao));
    move->team = my_team;
    move->next = *classi;
    *classi = move;
    for (i=0;i<7;i++)
    {
        novo = (ApontEquipa)malloc(sizeof(Equipa));
        move = (ApontClassificacao)malloc(sizeof(Classificacao));
        move->team = novo;
        fscanf(fp," %[^\n]s",move->team->nome);
        fscanf(fp," %[^\n]s",move->team->treinador);
        fscanf(fp," %d %d %d %d %d %d %d %d %d ",&(novo->id),&(novo->pontos),&(novo->vitorias),&(novo->empates),&(novo->derrotas),&(novo->golos_marcados),&(novo->golos_sofridos),&(novo->rating),&(novo->progress));
        move->next = *classi;
        *classi = move;
    }
    for (i=0;i<14;i++)
    {
        jog = (ApontJornada)malloc(sizeof(Jornada));
        jog->next = NULL;
        jog->jogos = NULL;
        for(j=0;j<4;j++)
        {
            novo_j = (ApontJogo)malloc(sizeof(Jogo));
            novo_j->next = jog->jogos;
            jog->jogos = novo_j;
            fscanf(fp," %[^\n]s",a);
            fscanf(fp," %[^\n]s",b);
            fscanf(fp,"%d - %d\n",&(novo_j->score_a),&(novo_j->score_b));
            novo_j->a = procura_equipa_por_nome(*classi,a);
            novo_j->b = procura_equipa_por_nome(*classi,b);
        }
        inutil = (*jornadas);
        if (*jornadas)
        {
            while(inutil->next)
            {
                inutil = inutil->next;
            }
            inutil->next = jog;
        }
        else
            *jornadas = jog;
    }
    fscanf(fp,"%d",jor_act);
    fclose(fp);
}
