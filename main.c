#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "header.h"
#define MAX_NOME 100
#define NOME_EQUIPA 20
#define AUX 10
int main()
{
    menu();
    return 0;
}
void menu(void)
{
    int choice,exi=0;
    while(exi != 1)
    {
        printf("\n\t\t  /\\/\\   __ _(_)_ __     /\\/\\   ___ _ __  _   _ \n\t\t /    \\ / _' | | '_ \\   /    \\ / _ \\ '_ \\| | | |\n\t\t/ /\\/\\ \\ (_| | | | | | / /\\/\\ \\  __/ | | | |_| |\n\t\t\\/    \\/\\__,_|_|_| |_| \\/    \\/\\___|_| |_|\\__,_|\n\n\n");
        printf("\t\t\tNOVO JOGO -------------------> 1\n\t\t\tCARREGAR JOGO ---------------> 2\n\t\t\tAJUDA -----------------------> 3\n\t\t\tSAIR ------------------------> 4");
        printf("\n\n>>> ");
        scan_int_prot(&choice);
        while (choice<1 || choice > 4)
        {
            printf("Valor invalido");
            printf("\n>>> ");
            scan_int_prot(&choice);
        }
        if (choice == 1)
            novo_jogo();
        if (choice == 2)
            carrega_jogo();
        if (choice == 3)
            ajuda();
        if (choice == 4)
            exi = sair();
    }

}
void novo_jogo(void)
{
    int conta = 1,jor_act = 1;
    Equipa my_team;
    ApontClassificacao classi = NULL,no;
    ApontJornada jornadas=NULL;
    system("@cls||clear");
    my_team = cria_equipa(my_team);
    classi = le_ficheiro_default(classi,&conta);
    my_team.id = conta;
    no = (ApontClassificacao)malloc(sizeof(Classificacao));
    no->team = &my_team;
    no->next = classi;
    classi = no;
    jornadas = cria_jornadas(jornadas,conta,classi);
    system("@cls||clear");
    menu_jogo(&my_team,classi,jornadas,jor_act);
}
void carrega_jogo(void)
{
    int flag = 0,choice,conta=0,jor_act = 1;
    char trei[MAX_NOME],nome[MAX_NOME];
    FILE *fp;
    FILE *fp2;
    int i=0;
    char linha[MAX_NOME];
    char ** matriz;
    Equipa my_team;
    ApontClassificacao classi = NULL;
    ApontJornada jornadas=NULL;
    system("@cls||clear");
    printf("\n\tEscreva o nome do trienador da equipa que deseja carregar\n\n\tJogos disponiveis:");
    fp = fopen("Users_Data.txt","r");
    fgets(trei,MAX_NOME,fp);
    while(!feof(fp))
    {
        fscanf(fp," %[^\n]s",trei);
        printf("\n\t>>> %s",trei);
    }
    if (!strcmp(trei,"0"))
        printf("Empty file");
    fclose(fp);
    printf("\n\n");
    while (!flag)
    {
        printf(">>> ");
        scanf(" %[^\n]s",nome);
        fp = fopen("Users_Data.txt","r");
        while(!feof(fp))
        {
            fscanf(fp," %[^\n]s",trei);
            if(!strcmp(trei,nome))
            {
                flag = 1;
                break;
            }
        }
        fclose(fp);
    }
    printf("\n\tDeseja carregar ou eliminar os dados guardados em %s ?\nCarregar -> 1\nEliminar -> 0\n>>> ",nome);
    scan_int_prot(&choice);
    while (choice != 1 && choice != 0)
    {
        printf("Valor invalido");
        printf("\n>>> ");
        scan_int_prot(&choice);
    }
    if (choice)
    {
        system("@cls||clear");
        printf("\n\t\t\tDados de %s carregados com sucesso!\n",nome);
        strcat(nome,"_DataBase.txt");
        carrega(&classi,&my_team,&jornadas,nome,&jor_act);
        menu_jogo(&my_team,classi,jornadas,jor_act);
    }
    else
    {
        strcat(nome,"_DataBase.txt");
        remove(nome);
        fp = fopen("Users_Data.txt","r");
        while(!feof(fp))
        {
            fgets(linha,MAX_NOME,fp);
            conta ++;
        }
        fclose(fp);
        matriz = malloc(sizeof(int)*conta);
        fp = fopen("Users_Data.txt","r");
        while(!feof(fp))
        {
            matriz[i] = malloc(sizeof(char)*MAX_NOME);
            fscanf(fp," %[^\n]s",matriz[i]);
            i++;
        }
        fclose(fp);
        fp2 = fopen("Users_Data.txt","w");
        i=0;
        fprintf(fp,"%s",matriz[i]);
        for (i=1;i<conta;i++)
        {
            fflush(stdin);
            if((strcmp(matriz[i],trei)))
                fprintf(fp,"\n%s",matriz[i]);

        }
        fclose(fp2);
    }
    printf("bateu");
    system("@cls||clear");
}
void ajuda(void)
{
    system("@cls||clear");
    printf("bla bla bla\n");
    system("pause");
}
int sair(void)
{
    int choice;
    system("@cls||clear");
    printf("\n\n\t\tPretende mesmo sair?");
    printf("\n\t\tSIM ---------------> 1\n\t\tNAO ---------------> 0\n\n");
    printf(">>> ");
    scan_int_prot(&choice);
    while (choice != 1 && choice != 0)
    {
        printf("Valor invalido");
        printf("\n>>> ");
        scan_int_prot(&choice);
    }
    system("@cls||clear");
    return choice;
}
void scan_int_prot(int * num){
    char o;
    do
        {
            fflush(stdin);
            scanf("%d%c",num,&o);
            if( o!='\n')
                printf("Valor invalido\n>>> ");
        }while ( o!='\n');
}
