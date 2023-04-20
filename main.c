#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include <math.h>
#include "ModeTest.c"
#define T_MAX 256


int main(int ARGC, char* ARGV[]){
  char ** end=NULL;
  //On verifie si l'utilisateur veut executer le mode Normal ou le mode Test
  if(strcmp(ARGV[1], "-t")==0){
    long k =strtol(ARGV[2],end,10);
    if (k!=0){
      ModeTest(k);
    }
    else{
      printf("Erreur de remplissage de la ligne de commande; veuillez re-compiler svp \n");
    }

  }



  else if(strcmp(ARGV[1], "-n")==0){
    char*FileName=ARGV[2];
    long x =strtol(ARGV[3],end,10);
    if (x!=0){
      ModeNormal(FileName,x);
    }
    else{
      printf("Erreur de remplissage de la ligne de commande; veuillez re-compiler svp \n");
    }

  }

  else{
    printf("Erreur de remplissage de la ligne de commande; veuillez re-compiler svp \n");
  }

  return 0;




}
