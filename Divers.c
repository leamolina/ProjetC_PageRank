#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>

//Convertion d'un caractere en entier
int Integer(char c){
  int val=c;
  return val-48;
}

//Suppression d'un caractere d'une chaine de caractere
char *SuppChar(char *ch,char c){
  char *p1;
  char *p2;
  if(ch!=NULL){
    p1=ch;
    p2=ch;
    while(*p2){
      if(*p2!=c){
        *p1=*p2;
        p1++;
      }
      p2++;
    }
    *p1=0;
  }
  return(ch);
}

//Copie de tab1 dans  tab2
void CopyTab(double tab1[], double tab2[], long length){
  for(long i=0; i<length; i++){
    tab2[i]=tab1[i];
  }
}

//Recherche de l'indice de la premiere occurence de c dans la chaine line
int FindChar(char* line, char c){
  for(int i=0; line[i]!='\0';i++){
    if(line[i]==c) return i;
  }
  return -1;
}

//Recuperation du nombre de ligne d'un fichier
long GetNumLine(FILE* f){
  long num_ligne = 1;
  char word;
  FILE* f2=f;
  while((word=fgetc(f2)) != EOF){
    if(word=='\n')num_ligne++;
    }
  return num_ligne;
}

//Recuperation du nombre de caracteres d'un fichier
long GetNumChar(FILE* f){
  long cpt=0;
  while(fgetc(f)!=EOF){
    cpt++;
  }
  return cpt;
}
