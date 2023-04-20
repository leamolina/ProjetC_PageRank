#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include <math.h>
#include "Liste.c"

//Affichage d'une matrice
void DisplayMatrix(long length, long **T) {
    long i, j;
    for (i = 0; i < length; i++) {
      for (j = 0; j < length; j++){
        printf("%3ld ", T[i][j]);
      }
      printf("\n");
    }
}

//Recuperation de la taille d'une matrice
long GetLengthMatrix(FILE *f){
  //C'est une matrice carré donc recuper le nombre de ligne ---> taille premiere ligne suffisante
  long cpt=0;
  while(fgetc(f)!=10){
    cpt++;
  }
  return cpt/2 + cpt%2; //car on compte les espaces --> 2 fois plus d'éléments
}

//Remplissage du tableau de liste
void FillTabListMatrix(long n, List**Adj,long **T){
  long i=0;
  long j=0;
  while(i<n){
    List* list=ListInit();
    // On ajoute le premier element de la liste qui correspond à l'indice du tableau Adj qui pointera sur tous ses elements
    PushIntInList(list,i);
    for(j=0; j<n; j++){
      if(T[i][j]==1) PushIntInList(list,j);
    }
    Adj[i]=list;
    i++;
  }
}

//Recuperation d'une matrice
void GetMatrix(FILE *f, long **T, long LengthMatrix,double* probaFile){
  long i=0; //ligne
  long j; //colonne
  long cpt;
  char* space=" ";
  char line[22*(LengthMatrix+1)+1];
  while (fgets(line, sizeof(line), f)){
    if((i<LengthMatrix)){ //recupere matrice
      cpt=0;
      j=0;
      while(cpt<2*LengthMatrix){
        long n=Integer(line[cpt]);
        if(n == 0 || n== 1){
          if(i==j)T[i][j]=1;
          else T[i][j]=n;
          j++;
          cpt++;
        }
        cpt++;

      }
      T[i][LengthMatrix]=1;
      for(long k=0; k<LengthMatrix; k++){
        T[LengthMatrix][k]=1;
      }
      T[LengthMatrix][LengthMatrix]=0;
      //On ajoute le super noeud (derniere ligne)

    }

    else{
      //On saute une ligne = ligne vide pour pouvoir acceder directement a la ligne contenant les probas
      fgets(line, sizeof(line), f);
      //line contient la ligne de proba; il suffit de la parcourir pour remplir probaFile
      //On separe la ligne en tokens separes par l espace
      char* token=malloc(22*sizeof(char));
      if (token==NULL) return;
      token=strtok(line,space);
      //On supprime la virgule du nombre
      SuppChar(token,44);
      long a=0;
      while(token!=NULL){
        //On converti cette chaine de caractere en double, et on l'ajoute  au tableau probaFichier
        char* next=NULL;
        double tmp=strtod(token, &next) ;
        probaFile[a]=tmp;
        a++;
        token=strtok(NULL,space);
      }
      SuppChar(token,44);
      free(token);
    }
    i++;

  }
}
