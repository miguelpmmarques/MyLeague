#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "header.h"
#define MAX_NOME 100
#define NOME_EQUIPA 20
#define AUX 10
void menu_jogo(ApontEquipa my_team,ApontClassificacao classi,ApontJornada jornadas,int jor_act)
{
    int exi = 0,choice,conta;
    ApontClassificacao no;
    while (exi != 1)
    {
        classi = atualiza_classificacao(classi);
        classi = atualiza_posicao(classi);
        if (jor_act > 14)
        {
            visualiza_classificacao(classi);
            printf("\n\t----> Chegou ao fim da temporada, ficou em %d lugar, o que significa que vai subir %d rantings! <----\n\n",my_team->posicao,(8-my_team->posicao) / 2);
            my_team->rating+= (8-my_team->posicao)/2;
            ver_equipa(my_team);
            conta=1;
            jor_act=1;
            /*Fazer free da classi e da jornadas*/
            classi = NULL;
            jornadas = NULL;
            classi = le_ficheiro_default(classi,&conta);
            my_team->derrotas = 0;
            my_team->empates = 0;
            my_team->golos_marcados = 0;
            my_team->golos_sofridos = 0;
            my_team->pontos = 0;
            my_team->vitorias = 0;
            my_team->posicao = 0;
            no = (ApontClassificacao)malloc(sizeof(Classificacao));
            no->team = my_team;
            no->next = classi;
            classi = no;
            jornadas = cria_jornadas(jornadas,conta,classi);
            classi = atualiza_classificacao(classi);
            classi = atualiza_posicao(classi);
            system("pause");
            system("@cls||clear");
        }
        printf("\t\t                  __                             \n\t\t  /\\/\\  _   _    / /  ___  __ _  __ _ _   _  ___ \n\t\t /    \\| | | |  / /  / _ \\/ _` |/ _` | | | |/ _ \\\n\t\t/ /\\/\\ \\ |_| | / /__|  __/ (_| | (_| | |_| |  __/\n\t\t\\/    \\/\\__, | \\____/\\___|\\__,_|\\__, |\\__,_|\\___|\n\t\t        |___/                   |___/\n\n");
        printf("\t\t\tJOGAR -----------------------> 1\n\t\t\tCONSULTAR EQUIPAS -----------> 2\n\t\t\tVER CLASSIFICACAO -----------> 3\n\t\t\tCONSULTAR JORNADAS ----------> 4\n\t\t\tCONSULTAR CALENDARIO --------> 5\n\t\t\tMY TEAM ---------------------> 6\n\t\t\tSALVAR ----------------------> 7\n\t\t\tSAIR ------------------------> 8");
        printf("\n>>> ");
        scan_int_prot(&choice);
        while (choice<1 || choice > 8)
        {
            printf("Valor invalido");
            printf("\n>>> ");
            scan_int_prot(&choice);
        }
        if (choice == 1)
        {
            system("@cls||clear");
            letsplay(&classi,&jornadas,&jor_act);
        }
        if (choice == 2)
        {
            system("@cls||clear");
            consulta_equipa(classi);
        }
        if (choice == 3)
        {
            classi = atualiza_classificacao(classi);
            classi = atualiza_posicao(classi);
            system("@cls||clear");
            visualiza_classificacao(classi);
            system("pause");
            system("@cls||clear");
        }
        if (choice == 4)
        {
            consultar_jornadas(jornadas);
        }
        if (choice == 5)
        {
            consultar_calendario(jornadas,my_team);
        }
        if (choice == 6)
        {
            classi = atualiza_classificacao(classi);
            classi = atualiza_posicao(classi);
            system("@cls||clear");
            ver_equipa(my_team);
            system("pause");
            system("@cls||clear");
        }
        if (choice == 7)
        {
             salvar(classi,my_team,jornadas,jor_act);
             system("@cls||clear");
             printf("\t\t\tProgresso salvo com sucesso\n\n");
        }
        if (choice == 8)
        {
            exi = sair();
        }

    }
}
void consultar_calendario(ApontJornada jornadas,ApontEquipa my_team)
{
    ApontJornada j=jornadas;
    ApontJogo move;
    int i=1;
    system("@cls||clear");
    printf("\t\t           _  ____   _____  ____   _____ \n\t\t          | |/ __ \\ / ____|/ __ \\ / ____|\n\t\t          | | |  | | |  __| |  | | (___  \n\t\t      _   | | |  | | | |_ | |  | |\\___ \\ \n\t\t     | |__| | |__| | |__| | |__| |____) |\n\t\t      \\____/ \\____/ \\_____|\\____/|_____/ \n");
    while(j)
    {
        printf("\t\t\t\t   JORNADA %d\n",i);
        move = j->jogos;
        while(move)
        {
            if (move->a == my_team || move->b == my_team)
            {
                if (move->score_a == -1)
                    printf("\t\t%20s   -   %s\n",move->a->nome,move->b->nome);
                else
                    printf("\t\t%20s %d - %d %s\n",move->a->nome,move->score_a,move->score_b,move->b->nome);
            }
            move = move->next;
        }
        printf("\n");
        i++;
        j=j->next;
    }
    printf("\n\n");
    system("pause");
    system("@cls||clear");
}
void consulta_equipa(ApontClassificacao classi)
{
    char n[MAX_NOME];
    ApontEquipa find;
    printf("\t  ______ ____  _    _ _____ _____         _____\n\t |  ____/ __ \\| |  | |_   _|  __ \\ /\\    / ____|\n\t | |__ | |  | | |  | | | | | |__) /  \\  | (___ )\n");
    printf("\t |  __|| |  | | |  | | | | |  ___/ /\\ \\  \\___ \\\n\t | |___| |__| | |__| |_| |_| |  / ____ \\ ____) |\n\t |______\\___\\_\\\\____/|_____|_| /_/    \\_\\_____/");
    visualiza_equipas(classi);
    printf("\n\tIndique o nome da equipa deseja consultar");
    do{
        printf("\n>>> ");
        gets(n);
        find = procura_equipa_por_nome(classi,n);
    }while(!find);
    system("@cls||clear");
    ver_equipa(find);
    system("pause");
    system("@cls||clear");
}
void visualiza_equipas(ApontClassificacao classi)
{
    ApontClassificacao move = classi;
    int i=1;
    printf("\n\n");

    while(move)
    {
        printf("\t\t|%3d|%20s       |\n",i,move->team->nome);
        i++;
        move = move->next;
    }
    printf("\n\n");
}
ApontClassificacao atualiza_posicao(ApontClassificacao l)
{
    int i=1;
    ApontClassificacao act=l;
    while(act)
    {
        act->team->posicao = i;
        act = act->next;
        i++;
    }
    return l;
}
ApontClassificacao atualiza_classificacao(ApontClassificacao l)
{
    ApontClassificacao l2=NULL,act=l;
    while(act)
    {
        l = act->next;
        l2 = insere_ord(l2,act);
        act = l;
    }
    return l2;
}
ApontClassificacao insere_ord(ApontClassificacao l, ApontClassificacao novo)
{
    ApontClassificacao act=l,ant=NULL;
    while (act!=NULL && act->team->pontos > novo->team->pontos )
    {
        ant = act;
        act = act->next;
    }
    while (act!=NULL && act->team->pontos == novo->team->pontos && (act->team->golos_marcados - act->team->golos_sofridos > novo->team->golos_marcados-novo->team->golos_sofridos))
    {
        ant = act;
        act = act->next;
    }
    novo->next = act;
    if (ant==NULL)
        l = novo;
    else
        ant->next=novo;
    return l;
}
void letsplay(ApontClassificacao *classi,ApontJornada * jor,int *n)
{
    ApontJornada move= *jor;
    ApontJogo auxi;
    int choice;
    int i,dif,n_golos,aux;
    printf("\t ____          _  ____   _____          _____      ____\n\t \\ \\ \\        | |/ __ \\ / ____|   /\\   |  __ \\    / / /  \n\t  \\ \\ \\       | | |  | | |  __   /  \\  | |__) |  / / /  \n\t   > > >  _   | | |  | | | |_ | / /\\ \\ |  _  /  < < <    \n\t  / / /  | |__| | |__| | |__| |/ ____ \\| | \\ \\   \\ \\ \\   \n\t /_/_/    \\____/ \\____/ \\_____/_/    \\_\\_|  \\_\\   \\ \\ \\ ");
    printf("\n\n\t\t\tPretende mesmo jogar?");
    printf("\n\t\t\tSIM ---------------> 1\n\t\t\tNAO ---------------> 0\n\n");
    printf(">>> ");
    scan_int_prot(&choice);
    while (choice != 1 && choice != 0)
    {
        printf("Valor invalido");
        printf("\n>>> ");
        scan_int_prot(&choice);
    }
    if (choice == 0)
    {
        system("@cls||clear");
        return;
    }
    else
    {
        for(i=1;i<*n;i++)
            move = move->next;
        auxi = move->jogos;
        srand(time(0));
        while (auxi)
        {
            if (auxi->a->rating == auxi->b->rating)
            {
                auxi->score_a = rand()%4;
                auxi->score_b = rand()%4;
                auxi->a->golos_marcados += auxi->score_a;
                auxi->b->golos_marcados += auxi->score_b;
                auxi->a->golos_sofridos += auxi->score_b;
                auxi->b->golos_sofridos += auxi->score_a;
                if (auxi->score_a == auxi->score_b)
                {
                    auxi->a->empates++;
                    auxi->b->empates++;
                    auxi->a->pontos++;
                    auxi->b->pontos++;
                    auxi->a->progress+=10;
                    auxi->b->progress+=10;
                    if (auxi->a->posicao > auxi->b->posicao)
                    {
                        auxi->a->progress += abs(auxi->a->posicao - auxi->b->posicao)*3;
                    }
                    if (auxi->a->posicao < auxi->b->posicao)
                    {
                        auxi->b->progress += abs(auxi->a->posicao - auxi->b->posicao)*3;
                    }
                    if (auxi->a->progress>99)
                    {
                        auxi->a->rating++;
                        auxi->a->progress = auxi->a->progress % 100;
                    }
                    if (auxi->b->progress>99)
                    {
                        auxi->b->rating++;
                        auxi->b->progress = auxi->b->progress % 100;
                    }
                }
                if (auxi->score_a > auxi->score_b)
                {
                    auxi->a->vitorias++;
                    auxi->b->derrotas++;
                    auxi->a->pontos+=3;
                    auxi->a->progress+=30;
                    if (auxi->a->posicao > auxi->b->posicao)
                    {
                        auxi->a->progress+= abs(auxi->a->posicao - auxi->b->posicao)*7;
                    }
                    if (auxi->a->progress>99)
                    {
                        auxi->a->rating++;
                        auxi->a->progress = auxi->a->progress % 100;
                    }
                }
                if (auxi->score_a < auxi->score_b)
                {
                    auxi->b->vitorias++;
                    auxi->a->derrotas++;
                    auxi->b->pontos+=3;
                    auxi->b->progress+=30;
                    if (auxi->a->posicao > auxi->b->posicao)
                    {
                        auxi->a->progress+= abs(auxi->a->posicao - auxi->b->posicao)*7;
                    }
                    if (auxi->b->progress>99)
                    {
                        auxi->b->rating++;
                        auxi->b->progress = auxi->b->progress % 100;
                    }
                }
                printf("\t\t%20s %d - %d %s\n",auxi->a->nome,auxi->score_a,auxi->score_b,auxi->b->nome);
            }
            else if (auxi->a->rating > auxi->b->rating)
            {
                dif = auxi->a->rating - auxi->b->rating;
                aux = 60+dif;
                n_golos = rand()%7;
                auxi->score_a=0;
                auxi->score_b=0;
                for (i=0;i<n_golos;i++)
                {
                    if (rand()%101 < aux)
                    {
                        auxi->score_a++;
                    }
                    else
                    {
                        auxi->score_b++;
                    }
                }
                auxi->a->golos_marcados += auxi->score_a;
                auxi->b->golos_marcados += auxi->score_b;
                auxi->a->golos_sofridos += auxi->score_b;
                auxi->b->golos_sofridos += auxi->score_a;
                if (auxi->score_a == auxi->score_b)
                {
                    auxi->a->empates++;
                    auxi->b->empates++;
                    auxi->a->pontos++;
                    auxi->b->pontos++;
                    auxi->a->progress+=10;
                    auxi->b->progress+=10 + dif/2 ;
                    if (auxi->a->posicao > auxi->b->posicao)
                    {
                        auxi->a->progress+= abs(auxi->a->posicao - auxi->b->posicao)*3;
                    }
                    if (auxi->a->posicao < auxi->b->posicao)
                    {
                        auxi->b->progress+= abs(auxi->a->posicao - auxi->b->posicao)*3;
                    }
                    if (auxi->a->progress>99)
                    {
                        auxi->a->rating++;
                        auxi->a->progress = auxi->a->progress % 100;
                    }
                    if (auxi->b->progress>99)
                    {
                        auxi->b->rating++;
                        auxi->b->progress = auxi->b->progress % 100;
                    }
                }
                if (auxi->score_a > auxi->score_b)
                {
                    auxi->a->vitorias++;
                    auxi->b->derrotas++;
                    auxi->a->pontos+=3;
                    auxi->a->progress+=30;
                    if (auxi->a->posicao > auxi->b->posicao)
                    {
                        auxi->a->progress+= abs(auxi->a->posicao - auxi->b->posicao)*7;
                    }
                    if (auxi->a->progress>99)
                    {
                        auxi->a->rating++;
                        auxi->a->progress = auxi->a->progress % 100;
                    }
                }
                if (auxi->score_a < auxi->score_b)
                {
                    auxi->b->vitorias++;
                    auxi->a->derrotas++;
                    auxi->b->pontos+=3;
                    auxi->b->progress+=30+dif;
                    if (auxi->a->posicao < auxi->b->posicao)
                    {
                        auxi->b->progress+= abs(auxi->a->posicao - auxi->b->posicao)*7;
                    }
                    if (auxi->b->progress>99)
                    {
                        auxi->b->rating++;
                        auxi->b->progress = auxi->b->progress % 100;
                    }

                }
                printf("\t\t%20s %d - %d %s\n",auxi->a->nome,auxi->score_a,auxi->score_b,auxi->b->nome);
            }
            else if (auxi->a->rating < auxi->b->rating)
            {
                dif = auxi->b->rating - auxi->a->rating;
                aux = 60+dif;
                n_golos = rand()%7;
                auxi->score_a=0;
                auxi->score_b=0;
                for (i=0;i<n_golos;i++)
                {
                    if (rand()%101 < aux)
                    {
                        auxi->score_b++;
                    }
                    else
                    {
                        auxi->score_a++;
                    }
                }
                auxi->a->golos_marcados += auxi->score_a;
                auxi->b->golos_marcados += auxi->score_b;
                auxi->a->golos_sofridos += auxi->score_b;
                auxi->b->golos_sofridos += auxi->score_a;
                if (auxi->score_a == auxi->score_b)
                {
                    auxi->a->empates++;
                    auxi->b->empates++;
                    auxi->a->pontos++;
                    auxi->b->pontos++;
                    auxi->a->progress+=10+dif/2;
                    auxi->b->progress+=10;
                    if (auxi->a->posicao > auxi->b->posicao)
                    {
                        auxi->a->progress+= abs(auxi->a->posicao - auxi->b->posicao)*3;
                    }
                    if (auxi->a->posicao < auxi->b->posicao)
                    {
                        auxi->b->progress+= abs(auxi->a->posicao - auxi->b->posicao)*3;
                    }
                    if (auxi->a->progress>99)
                    {
                        auxi->a->rating++;
                        auxi->a->progress = auxi->a->progress % 100;
                    }
                    if (auxi->b->progress>99)
                    {
                        auxi->b->rating++;
                        auxi->b->progress = auxi->b->progress % 100;
                    }
                }
                if (auxi->score_a > auxi->score_b)
                {
                    auxi->a->vitorias++;
                    auxi->b->derrotas++;
                    auxi->a->pontos+=3;
                    auxi->a->progress+=30+dif;
                    if (auxi->a->posicao > auxi->b->posicao)
                    {
                        auxi->a->progress+= abs(auxi->a->posicao - auxi->b->posicao)*7;
                    }
                    if (auxi->a->progress>99)
                    {
                        auxi->a->rating++;
                        auxi->a->progress = auxi->a->progress % 100;
                    }
                }
                if (auxi->score_a < auxi->score_b)
                {
                    auxi->b->vitorias++;
                    auxi->a->derrotas++;
                    auxi->b->pontos+=3;
                    auxi->b->progress+=30;
                    if (auxi->a->posicao <  auxi->b->posicao)
                    {
                        auxi->b->progress+= abs(auxi->a->posicao - auxi->b->posicao)*7;
                    }
                    if (auxi->b->progress>99)
                    {
                        auxi->b->rating++;
                        auxi->b->progress = auxi->b->progress % 100;
                    }
                }
                printf("\t\t%20s %d - %d %s\n",auxi->a->nome,auxi->score_a,auxi->score_b,auxi->b->nome);
            }
            auxi = auxi->next;
        }
    }
    (*n)++;
    system("pause");
    system("@cls||clear");
}
void consultar_jornadas(ApontJornada jornadas)
{
    ApontJornada j=jornadas;
    ApontJogo move;
    int i=1;
    system("@cls||clear");
    printf("\n\t       _  ____  _____  _   _          _____           _____\n\t      | |/ __ \\|  __ \\| \\ | |   /\\   |  __ \\   /\\    / ____|\n\t      | | |  | | |__) |  \\| |  /  \\  | |  | | /  \\  | (___");
    printf("\n\t  _   | | |  | |  _  /| . ` | / /\\ \\ | |  | |/ /\\ \\  \\___ \\ \n\t | |__| | |__| | | \\ \\| |\\  |/ ____ \\| |__| / ____ \\ ____) |\n\t  \\____/ \\____/|_|  \\_\\_| \\_/_/    \\_\\_____/_/    \\_\\_____/ \n\n");
    while(j)
    {
        printf("\t\t\t\t   JORNADA %d\n",i);
        move = j->jogos;
        while(move)
        {
            if (move->score_a == -1)
                printf("\t\t%20s   -   %s\n",move->a->nome,move->b->nome);
            else
                printf("\t\t%20s %d - %d %s\n",move->a->nome,move->score_a,move->score_b,move->b->nome);
            move = move->next;
        }
        printf("\n");
        i++;
        j=j->next;
    }
    printf("\n\n");
    system("pause");
    system("@cls||clear");
}
/*ApontJornada cria_jornadas(ApontJornada jornadas,int n,ApontClassificacao classi)
{
    int *vetor1;
    int *vetor2;
    int j=0,i,k;
    ApontJornada novo;
    ApontJogo novo_j;
    vetor1 = (int*)malloc(sizeof(int)*n/2);
    vetor2 = (int*)malloc(sizeof(int)*n/2);
    for(i=1;i<=n/2;i++)
    {
        vetor1[j] = i;
        j++;
    }
    j=0;
    for(i=n/2+1;i<=n;i++)
    {
        vetor2[j] = i;
        j++;
    }
    for (i=0;i<2;i++)
    {
        for (j=0;j<n/2;j++)
        {
            novo = (ApontJornada)malloc(sizeof(Jornada));
            novo->next = NULL;
            novo->jogos = NULL;
            for (k=0;k<n/2;k++)
            {
                novo_j = (ApontJogo)malloc(sizeof(Jogo));
                novo_j->next = novo->jogos;
                novo->jogos = novo_j;
                novo_j->a = procura_equipa_por_id(classi,vetor1[k]);
                novo_j->b = procura_equipa_por_id(classi,vetor2[k]);
                roda(vetor1,n);
            }
        }
        for (j=n/2;j<n;j++)
        {
            novo = (ApontJornada)malloc(sizeof(Jornada));
            novo->next = NULL;
            novo->jogos = NULL;
            for (k=0;k<n/2;k++)
            {
                novo_j = (ApontJogo)malloc(sizeof(Jogo));
                novo_j->next = novo->jogos;
                novo->jogos = novo_j;
                novo_j->a = procura_equipa_por_id(classi,vetor1[k]);
                novo_j->b = procura_equipa_por_id(classi,vetor2[k]);
                roda(vetor1,n);
            }
        }
    }
    return jornadas;
}*/
ApontJornada cria_jornadas(ApontJornada jornadas,int n,ApontClassificacao classi) /*   PLANO B   */
{
    int vetor[AUX][AUX] = {{1,5,2,6,3,7,4,8},{4,5,1,6,2,7,3,8},{3,5,4,6,1,7,2,8},{2,5,3,6,4,7,1,8},{2,1,3,4,5,6,7,8},{2,3,4,1,7,6,5,8},{2,4,3,1,5,7,8,6}};
    int j,i,k;
    ApontJornada novo;
    ApontJogo novo_j;
    for (i=1;i<3;i++)
    {
        for (j=0;j<n-1;j++)
        {
            novo = (ApontJornada)malloc(sizeof(Jornada));
            novo->next = NULL;
            novo->jogos = NULL;

            for (k=0;k<7;k+=2)
            {
                novo_j = (ApontJogo)malloc(sizeof(Jogo));
                novo_j->next = novo->jogos;
                novo->jogos = novo_j;
                novo_j->a = procura_equipa_por_id(classi,vetor[j][k]);
                novo_j->b = procura_equipa_por_id(classi,vetor[j][k+1]);
                novo_j->score_a = -1;
                novo_j->score_b = -1;
            }
            jornadas = adiciona_fim(jornadas,novo);
        }
    }
    return jornadas;
}

ApontJornada adiciona_fim(ApontJornada l,ApontJornada novo)
{
    ApontJornada inutil;
    inutil = l;

    novo->next = NULL;
    if (l){
        while(inutil->next)
        {
            inutil = inutil->next;
        }
        inutil->next = novo;
    }
    else
        l = novo;

    return l;
}
ApontJornada adiciona_fim_2(ApontJornada l,ApontJornada novo)
{
    ApontJornada inutil = l;

    novo->next = NULL;
    if (l){
        while((inutil)->next)
        {
            inutil = (inutil)->next;
        }
        (inutil)->next = novo;
    }
    else
        l = novo;

    return l;
}
void roda(int v[], int n)
{
   int x = v[n-1];
   int i;
   for (i=n-1;i>0;i--)
      v[i] = v[i-1];
   v[0] = x;
}
void ver_equipa(ApontEquipa my_team)
{
    int i;

    printf("\n\tNOME DA EQUIPA\n>>> %s",my_team->nome);
    printf("\n\tNOME DO TREINADOR\n>>> %s\n",my_team->treinador);
    printf(" VITORIAS | EMPATES | DERROTAS\n");
    printf("     %2d   |    %2d   |    %d\n",my_team->vitorias,my_team->empates,my_team->derrotas);
    printf(" POSICAO | PONTOS\n");
    printf("    %d    |   %d",my_team->posicao,my_team->vitorias*3+my_team->empates);
    printf("\n\n\t\t\t\t\t\t     ->PROGRESSO<-\n");
    printf("    __");
    for(i=0;i<100;i++)
        printf(" ");
    printf("    __\n");
    printf(" ___\\ \\ ");
    for (i=0;i<my_team->progress;i++)
        printf("|");
    for (i=0;i<100-my_team->progress;i++)
        printf(" ");
    printf(" / /___\n");
    printf("|____> >");
    for (i=0;i<my_team->progress;i++)
        printf("|");
    for (i=0;i<100-my_team->progress;i++)
        printf(" ");
    printf("< <____|\n");
    printf("    /_/ ");
    for (i=0;i<my_team->progress;i++)
        printf("|");
    for (i=0;i<100-my_team->progress;i++)
        printf(" ");
    printf(" \\_\\\n");

    printf("\n\n     RATING\n");
    switch (my_team->rating)
    {
    case (49):  printf("   _  _   ___  \n  | || | / _ \\ \n  | || || (_) |\n  |__   _\\__, |\n     | |   / / \n     |_|  /_/");
                break;
    case (50):  printf("   _____  ___  \n  | ____|/ _ \\ \n  | |__ | | | |\n  |___ \\| | | |\n   ___) | |_| |\n  |____/ \\___/");
                break;
    case (51):  printf("   _____ __ \n  | ____/_ |\n  | |__  | |\n  |___ \\ | |\n   ___) || |\n  |____/ |_|");
                break;
    case (52):  printf("   _____ ___  \n  | ____|__ \\ \n  | |__    ) |\n  |___ \\  / / \n   ___) |/ /_ \n  |____/|____|");
                break;
    case (53):  printf("   _____  ____  \n  | ____||___ \\ \n  | |__    __) |\n  |___ \\  |__ < \n   ___) | ___) |\n  |____/ |____/");
                break;
    case (54):  printf("   _____ _  _   \n  | ____| || |  \n  | |__ | || |_ \n  |___ \\|__   _|\n   ___) |  | |  \n  |____/   |_|");
                break;
    case (55):  printf("   _____   _____ \n  | ____| | ____|\n  | |__   | |__  \n  |___ \\  |___ \\ \n   ___) |  ___) |\n  |____/  |____/");
                break;
    case (56):  printf("   _____   __  \n  | ____| / /  \n  | |__  / /_  \n  |___ \\| '_ \\ \n   ___) | (_) |\n  |____/ \\___/");
                break;
    case (57):  printf("   _____ ______ \n  | ____|____  |\n  | |__     / / \n  |___ \\   / /  \n   ___) | / /   \n  |____/ /_/");
                break;
    case (58):  printf("   _____   ___  \n  | ____| / _ \\ \n  | |__  | (_) |\n\t |___ \\  > _ < \n   ___) || (_) |\n  |____/  \\___/");
                break;
    case (59):  printf("   _____ ___  \n  | ____/ _ \\ \n  | |__| (_) |\n  |___ \\\\__, |\n   ___) | / / \n  |____/ /_/");
                break;
    case (60):  printf("     __   ___  \n    / /  / _ \\ \n   / /_ | | | |\n  | '_ \\| | | |\n  | (_) | |_| |\n   \\___/ \\___/");
                break;
    case (61):  printf("     __  __ \n    / / /_ |\n   / /_  | |\n  | '_ \\ | |\n  | (_)  | |\n   \\___/ |_|");
                break;
    case (62):  printf("     __ ___  \n    / /|__ \\ \n   / /_   ) |\n  | '_ \\ / / \n  | (_) / /_ \n   \\___/____|");
                break;
    case (63):  printf("     __ ____  \n    / /|___ \\ \n   / /_  __) |\n\t | '_ \\|__ < \n  | (_) |__) |\n   \\___/____/");
                break;
    case (64):  printf("     __ _  _   \n    / /| || |  \n   / /_| || |_ \n  | '_ \\__   _|\n  | (_) | | |  \n   \\___/  |_|");
                break;
    case (65):  printf("     __ _____ \n    / /| ____|\n   / /_| |__  \n  | '_ \\___ \\ \n  | (_) |__) |\n   \\___/____/");
                break;
    case (66):  printf("     __    __  \n    / /   / /  \n   / /_  / /_  \n  | '_ \\| '_ \\ \n  | (_) | (_) |\n   \\___/ \\___/ ");
                break;
    case (67):  printf("     __ _____ \n    / /____  |\n   / /_   / / \n  | '_ \\ / /  \n  | (_) / /   \n   \\___/_/");
                break;
    case (68):  printf("     __   ___  \n    / /  / _ \\ \n   / /_ | (_) |\n  | '_ \\ > _ < \n  | (_) | (_) |\n   \\___/ \\___/");
                break;
    case (69):  printf("     __  ____ \n    / / / _  \\ \n   / /| \\ (_) |\n  | '_ \\ \\__,/\n  | (_) | / / \n   \\___/ /_/  ");
                break;
    case (70):  printf("   ______ ___  \n  |____  / _ \\ \n      / / | | |\n     / /| | | |\n    / / | |_| |\n   /_/   \\___/");
                break;
    case (71):  printf("   ______  __ \n  |____  /|_ |\n      / /  | |\n     / /   | |\n    / /    | |\n   /_/     |_|");
                break;
    case (72):  printf("   ______ ___  \n  |____  |__ \\ \n      / /   ) |\n     / /   / / \n    / /   / /_ \n   /_/   |____|");
                break;
    case (73):  printf("   ______ ____  \n  |____  |___ \\ \n      / /  __) |\n     / /  |__ < \n    / /   ___) |\n   /_/   |____/");
                break;
    case (74):  printf("   ______ _  _   \n  |____  | || |  \n      / /| || |_ \n     / / |__   _|\n    / /     | |  \n   /_/      |_|");
                break;
    case (75):  printf("   ______ _____ \n  |____  | ____|\n      / /| |__  \n     / / |___ \\ \n    / /   ___) |\n   /_/   |____/");
                break;
    case (76):  printf("   ______ __  \n  |____  / /  \n      / / /_  \n     / / '_ \\ \n    / /| (_) |\n   /_/  \\___/ ");
                break;
    case (77):  printf("   ______ ______ \n  |____  |____  |\n      / /    / / \n     / /    / /  \n    / /    / /   \n   /_/    /_/");
                break;
    case (78):  printf("   ______ ___  \n  |____  / _ \\ \n      / / (_) |\n     / / > _ < \n    / / | (_) |\n   /_/   \\___/");
                break;
    case (79):  printf("   ______ ___  \n  |____  / _ \\ \n      / / (_) |\n     / / \\__, |\n    / /    / / \n   /_/    /_/");
                break;
    case (80):  printf("    ___   ___  \n   / _ \\ / _ \\ \n  | (_) | | | |\n   > _ <| | | |\n  | (_) | |_| |\n   \\___/ \\___/");
                break;
    case (81):  printf("    ___  __ \n   / _ \\/_ |\n  | (_) || |\n   > _ < | |\n  | (_) || |\n   \\___/ |_|");
                break;
    case (82):  printf("    ___ ___  \n   / _ \\__ \\ \n  | (_) | ) |\n   > _ < / / \n  | (_) / /_ \n   \\___/____|");
                break;
    case (83):  printf("    ___ ____  \n   / _ \\___ \\ \n  | (_) |__) |\n   > _ <|__ < \n  | (_) |__) |\n   \\___/____/ ");
                break;
    case (84):  printf("    ___  _  _\n   / _ \\| || |\n  | (_) | || |_\n   > _ <|__   _|\n  | (_) |  | |\n   \\___/   |_|");
                break;
    case (85):  printf("    ___  _____\n   / _ \\| ____|\n  | (_) | |__\n   > _ <|___ \\ \n  | (_) |___) |\n   \\___/|____/");
                break;
    case (86):  printf("    ___    __\n   / _ \\  / /\n  | (_) |/ /_\n   > _ <| '_ \\ \n  | (_) | (_) |\n   \\___/ \\___/ ");
                break;
    case (87):  printf("    ___  _______ \n   / _ \\ \\____  |\n  | (_) |    / / \n   > _ <    / /  \n  | (_) |  / /   \n   \\___/  /_/");
                break;
    case (88):  printf("    ___   ___  \n   / _ \\ / _ \\ \n  | (_) | (_) |\n   > _ < > _ < \n  | (_) | (_) |\n   \\___/ \\___/ ");
                break;
    case (89):  printf("    ___   ___  \n   / _ \\ / _ \\ \n  | (_) | (_) |\n   > _ < \\__, |\n  | (_) |  / / \n   \\___/  /_/");
                break;
    case (90):  printf("    ___   ___  \n   / _ \\ / _ \\ \n  | (_) | | | |\n   \\__, | | | |\n     / /| |_| |\n    /_/  \\___/ ");
                break;
    }
    printf("\n\n");
}
void visualiza_classificacao(ApontClassificacao classi)
{
    ApontClassificacao move = classi;
    int i=1;
    printf("\n\t   _____ _                _____ _____ _____ ______ _____ _____          _____   /\\/|  ____  \n\t  / ____| |        /\\    / ____/ ____|_   _|  ____|_   _/ ____|   /\\   / ____| |/\\/  / __ \\ \n\t | |    | |       /  \\  | (___| (___   | | | |__    | || |       /  \\ | |       / \\ | |  | |");
    printf("\n\t | |    | |      / /\\ \\  \\___ \\___ \\   | | |  __|   | || |      / /\\ \\| |      / _ \\| |  | |\n\t | |____| |____ / ____ \\ ____) |___) |_| |_| |     _| || |____ / ____ \\ |____ / ___ \\ |__| |\n\t  \\_____|______/_/    \\_\\_____/_____/|_____|_|    |_____\\_____/_/    \\_\\_____/_/   \\_\\____/ \n\t                                                                         )_)");
    printf("\n\n");
    printf("\t\t\t|POS|  EQUIPA                   | P | V | E | D |GM|GS|\n");
    while(move)
    {
        printf("\t\t\t|%3d|%20s       |%2d |%2d |%2d |%2d |%2d|%2d|\n",i,move->team->nome,move->team->pontos,move->team->vitorias,move->team->empates,move->team->derrotas,move->team->golos_marcados,move->team->golos_sofridos);
        i++;
        move = move->next;
    }
    printf("\n\n");
}
ApontClassificacao le_ficheiro_default(ApontClassificacao classi,int * conta)
{
    ApontEquipa novo;
    ApontClassificacao no;
    int flag = 1;
    FILE * fp;
    char n[MAX_NOME];
    printf("\n\tLigas Disponiveis:\n\n\t>>> BBVA\n\n\t>>> PREMIER\n\n\t>>> NOS\n\nEscreva o nome da liga para escolher: ");
    while(flag)
    {
        printf("\n>>> ");
        scanf("%s",n);
        if(!strcmp(n,"BBVA"))
        {
            fp = fopen("BBVA.txt","r");
            flag = 0;
            printf("Bateu");
        }
        if(!strcmp(n,"NOS"))
        {
            fp = fopen("NOS.txt","r");
            flag = 0;
        }
        if(!strcmp(n,"PREMIER"))
        {
            fp = fopen("PREMIER.txt","r");
            flag = 0;
        }
    }
    while(!(feof(fp)))
    {
        novo = (ApontEquipa)malloc(sizeof(Equipa));
        no = (ApontClassificacao)malloc(sizeof(Classificacao));
        no->team = novo;
        fscanf(fp," %[^\n]",no->team->nome);
        fscanf(fp," %[^\n]",no->team->treinador);
        fscanf(fp," %d",&no->team->rating);
        no->next = NULL;
        no->team->derrotas = 0;
        no->team->empates = 0;
        no->team->golos_marcados = 0;
        no->team->golos_sofridos = 0;
        no->team->pontos = 0;
        no->team->vitorias = 0;
        no->team->progress = 50;
        no->team->posicao = 0;
        no->team->id = *conta;
        no->next = classi;
        classi = no;
        (*conta)++;
    }
    fclose(fp);
    return classi;
}

ApontEquipa procura_equipa_por_id(ApontClassificacao l,int n)
{
    ApontClassificacao move = l;
    while (move)
    {
        if (move->team->id == n)
            return move->team;
        move = move->next;
    }
    return NULL;
}
ApontEquipa procura_equipa_por_nome(ApontClassificacao l,char *n)
{
    ApontClassificacao move = l;
    while (move)
    {
        if (!strcmp(move->team->nome,n))
            return move->team;
        move = move->next;
    }
    return NULL;
}
Equipa cria_equipa(Equipa my_team)
{
    int n;
    printf("\n\tNOME DA EQUIPA \n>>> ");
    gets(my_team.nome);
    fflush(stdin);
    printf("\n\tNOME DO TREINADOR \n>>> ");
    gets(my_team.treinador);
    fflush(stdin);
    srand(time(0));
    n = rand()%11;
    n += 65;
    printf("\n\t     RATING DA SUA EQUIPA\n\n");
    switch (n)
    {
    case (49):  printf("\t\t  _  _   ___  \n\t\t | || | / _ \\ \n\t\t | || || (_) |\n\t\t |__   _\\__, |\n\t\t    | |   / / \n\t\t    |_|  /_/");
                break;
    case (50):  printf("  _____  ___  \n\t\t | ____|/ _ \\ \n\t\t | |__ | | | |\n\t\t |___ \\| | | |\n\t\t  ___) | |_| |\n\t\t |____/ \\___/");
                break;
    case (51):  printf("\t\t  _____ __ \n\t\t | ____/_ |\n\t\t | |__  | |\n\t\t |___ \\ | |\n\t\t  ___) || |\n\t\t |____/ |_|");
                break;
    case (52):  printf("  _____ ___  \n\t\t | ____|__ \\ \n\t\t | |__    ) |\n\t\t |___ \\  / / \n\t\t  ___) |/ /_ \n\t\t |____/|____|");
                break;
    case (53):  printf("\t\t  _____  ____  \n\t\t | ____||___ \\ \n\t\t | |__    __) |\n\t\t |___ \\  |__ < \n\t\t  ___) | ___) |\n\t\t |____/ |____/");
                break;
    case (54):  printf("\t\t  _____ _  _   \n\t\t | ____| || |  \n\t\t | |__ | || |_ \n\t\t |___ \\|__   _|\n\t\t  ___) |  | |  \n\t\t |____/   |_|");
                break;
    case (55):  printf("\t\t  _____   _____ \n\t\t | ____| | ____|\n\t\t | |__   | |__  \n\t\t |___ \\  |___ \\ \n\t\t  ___) |  ___) |\n\t\t |____/  |____/");
                break;
    case (56):  printf("  _____   __  \n\t\t | ____| / /  \n\t\t | |__  / /_  \n\t\t |___ \\| '_ \\ \n\t\t  ___) | (_) |\n\t\t |____/ \\___/");
                break;
    case (57):  printf("\t\t  _____ ______ \n\t\t | ____|____  |\n\t\t | |__     / / \n\t\t |___ \\   / /  \n\t\t  ___) | / /   \n\t\t |____/ /_/");
                break;
    case (58):  printf("\t\t  _____   ___  \n\t\t | ____| / _ \\ \n\t\t | |__  | (_) |\n\t |___ \\  > _ < \n\t\t  ___) || (_) |\n\t\t |____/  \\___/");
                break;
    case (59):  printf("\t\t  _____ ___  \n\t\t | ____/ _ \\ \n\t\t | |__| (_) |\n\t\t |___ \\\\__, |\n\t\t  ___) | / / \n\t\t |____/ /_/");
                break;
    case (60):  printf("\t\t    __   ___  \n\t\t   / /  / _ \\ \n\t\t  / /_ | | | |\n\t\t | '_ \\| | | |\n\t\t | (_) | |_| |\n\t\t  \\___/ \\___/");
                break;
    case (61):  printf("\t\t    __  __ \n\t\t   / / /_ |\n\t\t  / /_  | |\n\t\t | '_ \\ | |\n\t\t | (_)  | |\n\t\t  \\___/ |_|");
                break;
    case (62):  printf("\t\t    __ ___  \n\t\t   / /|__ \\ \n\t\t  / /_   ) |\n\t\t | '_ \\ / / \n\t\t | (_) / /_ \n\t\t  \\___/____|");
                break;
    case (63):  printf("\t\t    __ ____  \n\t\t   / /|___ \\ \n\t\t  / /_  __) |\n\t | '_ \\|__ < \n\t\t | (_) |__) |\n\t\t  \\___/____/");
                break;
    case (64):  printf("\t\t    __ _  _   \n\t\t   / /| || |  \n\t\t  / /_| || |_ \n\t\t | '_ \\__   _|\n\t\t | (_) | | |  \n\t\t  \\___/  |_|");
                break;
    case (65):  printf("\t\t    __ _____ \n\t\t   / /| ____|\n\t\t  / /_| |__  \n\t\t | '_ \\___ \\ \n\t\t | (_) |__) |\n\t\t  \\___/____/");
                break;
    case (66):  printf("\t\t    __    __  \n\t\t   / /   / /  \n\t\t  / /_  / /_  \n\t\t | '_ \\| '_ \\ \n\t\t | (_) | (_) |\n\t\t  \\___/ \\___/ ");
                break;
    case (67):  printf("\t\t    __ _____ \n\t\t   / /____  |\n\t\t  / /_   / / \n\t\t | '_ \\ / /  \n\t\t | (_) / /   \n\t\t  \\___/_/");
                break;
    case (68):  printf("\t\t    __   ___  \n\t\t   / /  / _ \\ \n\t\t  / /_ | (_) |\n\t\t | '_ \\ > _ < \n\t\t | (_) | (_) |\n\t\t  \\___/ \\___/");
                break;
    case (69):  printf("\t\t    __  ____ \n\t\t   / / / _  \\ \n\t\t  / /| \\ (_) |\n\t\t | '_ \\ \\__,/\n\t\t | (_) | / / \n\t\t  \\___/ /_/  ");
                break;
    case (70):  printf("\t\t  ______ ___  \n\t\t |____  / _ \\ \n\t\t     / / | | |\n\t\t    / /| | | |\n\t\t   / / | |_| |\n\t\t  /_/   \\___/");
                break;
    case (71):  printf("\t\t  ______  __ \n\t\t |____  /|_ |\n\t\t     / /  | |\n\t\t    / /   | |\n\t\t   / /    | |\n\t\t  /_/     |_|");
                break;
    case (72):  printf("\t\t  ______ ___  \n\t\t |____  |__ \\ \n\t\t     / /   ) |\n\t\t    / /   / / \n\t\t   / /   / /_ \n\t\t  /_/   |____|");
                break;
    case (73):  printf("\t\t  ______ ____  \n\t\t |____  |___ \\ \n\t\t     / /  __) |\n\t\t    / /  |__ < \n\t\t   / /   ___) |\n\t\t  /_/   |____/");
                break;
    case (74):  printf("\t\t  ______ _  _   \n\t\t |____  | || |  \n\t\t     / /| || |_ \n\t\t    / / |__   _|\n\t\t   / /     | |  \n\t\t  /_/      |_|");
                break;
    case (75):  printf("\t\t  ______ _____ \n\t\t |____  | ____|\n\t\t     / /| |__  \n\t\t    / / |___ \\ \n\t\t   / /   ___) |\n\t\t  /_/   |____/");
                break;
    case (76):  printf("\t\t  ______ __  \n\t\t |____  / /  \n\t\t     / / /_  \n\t\t    / / '_ \\ \n\t\t   / /| (_) |\n\t\t  /_/  \\___/ ");
                break;
    case (77):  printf("\t\t  ______ ______ \n\t\t |____  |____  |\n\t\t     / /    / / \n\t\t    / /    / /  \n\t\t   / /    / /   \n\t\t  /_/    /_/");
                break;
    case (78):  printf("\t\t  ______ ___  \n\t\t |____  / _ \\ \n\t\t     / / (_) |\n\t\t    / / > _ < \n\t\t   / / | (_) |\n\t\t  /_/   \\___/");
                break;
    case (79):  printf("\t\t  ______ ___  \n\t\t |____  / _ \\ \n\t\t     / / (_) |\n\t\t    / / \\__, |\n\t\t   / /    / / \n\t\t  /_/    /_/");
                break;
    case (80):  printf("\t\t   ___   ___  \n\t\t  / _ \\ / _ \\ \n\t\t | (_) | | | |\n\t\t  > _ <| | | |\n\t\t | (_) | |_| |\n\t\t  \\___/ \\___/");
                break;
    case (81):  printf("\t\t   ___  __ \n\t\t  / _ \\/_ |\n\t\t | (_) || |\n\t\t  > _ < | |\n\t\t | (_) || |\n\t\t  \\___/ |_|");
                break;
    case (82):  printf("\t\t   ___ ___  \n\t\t  / _ \\__ \\ \n\t\t | (_) | ) |\n\t\t  > _ < / / \n\t\t | (_) / /_ \n\t\t  \\___/____|");
                break;
    case (83):  printf("\t\t   ___ ____  \n\t\t  / _ \\___ \\ \n\t\t | (_) |__) |\n\t\t  > _ <|__ < \n\t\t | (_) |__) |\n\t\t  \\___/____/ ");
                break;
    case (84):  printf("\t\t   ___  _  _\n\t\t  / _ \\| || |\n\t\t | (_) | || |_\n\t\t  > _ <|__   _|\n\t\t | (_) |  | |\n\t\t  \\___/   |_|");
                break;
    case (85):  printf("\t\t   ___  _____\n\t\t  / _ \\| ____|\n\t\t | (_) | |__\n\t\t  > _ <|___ \\ \n\t\t | (_) |___) |\n\t\t  \\___/|____/");
                break;
    case (86):  printf("\t\t   ___    __\n\t\t  / _ \\  / /\n\t\t | (_) |/ /_\n\t\t  > _ <| '_ \\ \n\t\t | (_) | (_) |\n\t\t  \\___/ \\___/ ");
                break;
    case (87):  printf("\t\t   ___  _______ \n\t\t  / _ \\ \\____  |\n\t\t | (_) |    / / \n\t\t  > _ <    / /  \n\t\t | (_) |  / /   \n\t\t  \\___/  /_/");
                break;
    case (88):  printf("\t\t   ___   ___  \n\t\t  / _ \\ / _ \\ \n\t\t | (_) | (_) |\n\t\t  > _ < > _ < \n\t\t | (_) | (_) |\n\t\t  \\___/ \\___/ ");
                break;
    case (89):  printf("\t\t   ___   ___  \n\t\t  / _ \\ / _ \\ \n\t\t | (_) | (_) |\n\t\t  > _ < \\__, |\n\t\t | (_) |  / / \n\t\t  \\___/  /_/");
                break;
    case (90):  printf("\t\t   ___   ___  \n\t\t  / _ \\ / _ \\ \n\t\t | (_) | | | |\n\t\t  \\__, | | | |\n\t\t    / /| |_| |\n\t\t   /_/  \\___/ ");
                break;
    }
    printf("\n\n\n\n");
    my_team.rating = n;
    my_team.derrotas = 0;
    my_team.empates = 0;
    my_team.golos_marcados = 0;
    my_team.golos_sofridos = 0;
    my_team.pontos = 0;
    my_team.vitorias = 0;
    my_team.posicao = 0;
    my_team.progress = 50;
    return my_team;
}

