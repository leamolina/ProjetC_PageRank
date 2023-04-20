#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include <math.h>
#include "ModeNormal.c"
#define T_MAX 256

void ModeTest(long k){

  //Recuperation du fichier
  char FileName[T_MAX];
  printf("Entrez le nom du fichier:");
  scanf("%s", FileName );
  FILE *f= fopen(FileName,"r");

  //Initialisation et allocation de la memoire
  long LengthMatrix= GetLengthMatrix(f);
  rewind(f);
  long **T = malloc(sizeof(*T) * LengthMatrix+1);
  if (T==NULL) return;
  for (int i=0; i<LengthMatrix+1 ; i++){
    T[i]= malloc(sizeof(**T)*LengthMatrix+1);
    if (T[i]==NULL) return;
  }
  double* probaFile = malloc((LengthMatrix+1)*sizeof(double));
  if (probaFile==NULL) return;
  List **Adj= malloc((LengthMatrix+1)*sizeof(List*)+1);
  if (Adj==NULL) return;
  long* predecessor=(long*)malloc((LengthMatrix+1)*sizeof(long)+1);
  if (predecessor==NULL) return;
  char* answer= malloc(3*sizeof(char)+1);
  if (answer==NULL) return;

  //Recuperation de la matrice et du tableau de probabilites du fichier
  GetMatrix(f,T,LengthMatrix,probaFile);
  rewind(f);
  int fclose(FILE *f);

  //Affichage (optionnel) de la matrice

  printf("Souhaitez-vous afficher la matrice adjacente ? Repondez par Oui/Non: ");
  printf("\n");
  scanf("%s",answer);
  if (strcmp(answer,"Oui")==0){
    printf("Affichage de la matrice \n");
    DisplayMatrix(LengthMatrix+1,T);
    printf("\n");
  }

  FillTabListMatrix(LengthMatrix+1,Adj,T);

  //Affichage (optionnel) du tableau de liste

  printf("Souhaitez-vous afficher le tableau de liste ? Repondez par Oui/Non: ");
  printf("\n");
  scanf("%s",answer);
  if (strcmp(answer,"Oui")==0){
    printf("Affichage du tableau de liste \n");
    DisplayTabList(Adj, LengthMatrix+1);
    printf("\n");
  }

  //Initialisation du tableau de proba initial

  double proba[LengthMatrix+1];
  ProbaPageInit(Adj,proba,LengthMatrix+1);

  //Affichage (optionnel) du tableau de probabilites initialise

  printf("Souhaitez-vous afficher le tableau de probabilites initialise ? Repondez par Oui/Non: ");
  printf("\n");
  scanf("%s",answer);
  if (strcmp(answer,"Oui")==0){
    printf("Affichage du tableau de probabilites initialise \n");
    for (long j=0; j<LengthMatrix+1; j++){
        printf("%lf \t", proba[j]);
    }
    printf("\n");
    printf("\n");
  }

  //Recuperation de epsilon
  double epsilon;
  double n=LengthMatrix;
  printf("Souhaitez-vous choisir la valeur pour epsilon? Ou gardez la valeur par defaut? \n");
  printf("Entrez Oui pour le premier choix: " );
  scanf("%s",answer);
  printf("\n");
  if (strcmp(answer,"Oui")==0){
    printf("Entrez la valeur d'epsilon: ");
    scanf("%lf", &epsilon);
  }
  else epsilon= 1/(10*n);

  //Calcul des probabilites

  double tmp[LengthMatrix+1];
  for(long l=0; l<k; l++){
    CalculProba(Adj,proba, tmp,LengthMatrix+1, predecessor, epsilon);
  }
  printf("Souhaitez-vous afficher le tableau de probabilites mis a jour ? Repondez par Oui/Non: ");
  printf("\n");
  scanf("%s",answer);
  if (strcmp(answer,"Oui")==0){
    printf("Affichage du tableau de probabilites mis a jour : \n");
    printf("\n");
    printf("%lf \t", tmp[LengthMatrix]);
    for (long j=0; j<LengthMatrix; j++){
      printf("%lf \t", tmp[j]);
    }
    printf("\n");
  }


  //Comparaison des tableaux de probabilites et pourcentage d'erreur

  double percentMax=ReturnPercentMax(probaFile,tmp,LengthMatrix);
  printf("Pourcentage d'erreur maximal: %lf %% \n", percentMax);
  printf("\n");
  printf("Fin du programme \n");
  for(long i=0;i<LengthMatrix+1;i++){
    List*list=Adj[i];
    DestroyList(list);
  }
  for(long j=0;j<LengthMatrix+1;j++){
    free(T[j]);
  }
  free(T);
  free(answer);
  free(Adj);
  free(probaFile);
  free(predecessor);

}
