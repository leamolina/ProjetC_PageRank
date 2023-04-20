#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include <math.h>
#include "proba.c"
#define T_MAX 256

void ModeNormal(char*FileName,long x ){
  //Ouverture du fichier texte et recuperation des donnees(characteres)
  FILE *f= fopen(FileName,"r");
  long NumCharFile=GetNumChar(f);
  rewind(f);

  //Initialisation et allocation de la memoire
  char* answer= malloc(3*sizeof(char)+1);
  if (answer==NULL) return;
  //Remplissage de pagelist
  PageList* pagelist=PageListInit();
  FillListPage(f,pagelist,NumCharFile);
  rewind(f);

  //Affichage (optionnel) de pagelist
  printf("Souhaitez-vous afficher pagelist ? Repondez par Oui/Non: ");
  printf("\n");
  scanf("%s",answer);
  if (strcmp(answer,"Oui")==0){
    printf("Affichage de pagelist \n");
    DisplayPageList(pagelist);
    printf("\n");
  }

  //Remplissage du tableau de liste
  List **Adj= malloc((pagelist->length+1)*sizeof(List*)+1);
  if (Adj==NULL) return;
  FillInTable(Adj,pagelist,f,NumCharFile);
  int fclose(FILE* f);

  //Affichage (optionnel) du tableau de liste
  printf("Souhaitez-vous afficher le tableau de liste ? Repondez par Oui/Non: ");
  printf("\n");
  scanf("%s",answer);
  if (strcmp(answer,"Oui")==0){
    printf("Affichage du tableau de liste \n");
    DisplayTabList(Adj,pagelist->length+1);
    printf("\n");
  }
  //Initialisation du tableau de probabilites
  long* predecessor=(long*)malloc((pagelist->length+1)*sizeof(long)+1);
  if (predecessor==NULL) return;
  double proba[pagelist->length+1];
  ProbaPageInit(Adj,proba,pagelist->length+1);

  //Affichage (optionnel) du tableau de liste
  printf("Souhaitez-vous afficher le tableau de probabilites initialise ? Repondez par Oui/Non: ");
  printf("\n");
  scanf("%s",answer);
  if (strcmp(answer,"Oui")==0){
    printf("Affichage du tableau de probabilites initialise \n");
    for (long j=0; j<pagelist->length+1; j++){
        printf("%lf \t", proba[j]);
    }
    printf("\n");
    printf("\n");
  }

  //Recuperation de epsilon
  double epsilon;
  double n=pagelist->length;
  printf("Souhaitez-vous choisir la valeur pour epsilon? Ou gardez la valeur par defaut? \n");
  printf("Entrez Oui pour le premier choix: " );
  printf("\n");
  scanf("%s",answer);
  if (strcmp(answer,"Oui")==0){
    printf("Entrez la valeur d'epsilon: ");
    scanf("%lf", &epsilon);
  }
  else epsilon= 1/(10*n);

  //Calcul des probabilites

  double tmp[pagelist->length+1];
  for(long l=0; l<20; l++){
    CalculProba(Adj,proba, tmp,pagelist->length+1, predecessor, epsilon);
  }
  printf("Souhaitez-vous afficher le tableau de probabilites ? Repondez par Oui/Non: ");
  printf("\n");
  scanf("%s",answer);
  if (strcmp(answer,"Oui")==0){
    printf("Affichage du tableau de probabilites : \n");
    printf("\n");
    for (long j=0; j<pagelist->length+1; j++){
        printf("%lf \t", tmp[j]);
    }
    printf("\n");
  }
  printf("\n");

  printf("Somme des probas: %lf\n",SumProba(tmp,pagelist->length+1));
  //Affichage des x pages les plus importantes
  RecupMax(tmp,x,pagelist,pagelist->length+1);
  //free
  for(long i=0;i<pagelist->length+1;i++){
    List*list=Adj[i];
    DestroyList(list);
  }
  DestroyPageList(pagelist);
  free(Adj);
  free(answer);
  free(predecessor);
  printf("Fin du programme \n");

}
