#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include "ListePage.c"

typedef struct elem{
    long val;
    struct elem* next;
}Elem;

typedef struct{
    Elem* first;
    long length;
}List;


//Initialisation de la liste chainee
List* ListInit(){
  List* list=malloc(sizeof(List*));
  if(list==NULL){
    exit(-1);
  }
  list->first=NULL;
  //liste->dernier=NULL;
  list->length=0;
  return list;

}

//Recuperation de l'elem correspondant au i-eme element de la liste chainee
Elem* GetElem(List* list, long index){
  long i;
  Elem* elem=list->first;
  if(list==NULL) exit(-1);
  //Par convention, quand l'indice n'est pas approprié (trop grand ou trop petit), on renvoie le premier element de la liste chainee
  if(index>=list->length || index<0){
    return list->first;
  }

  for(i=0; i<index; i++){
    elem=elem->next;
  }
  return elem;
}



//Creation d'une case vide de la liste chainee qui contient le nombre entré en argument
void PushIntInList(List* list,long n){
   Elem* new=malloc(sizeof(Elem));
   if(list==NULL || new==NULL){
     exit(-1);
   }
   new->val=n;
   if(list->length>0){
       Elem* last;
       last=GetElem(list, list->length-1);
       last->next=new;
   }
   //Si la liste chainee ne contient aucun element
   else {
       list->first=new;
   }

   list->length++;

}



//Affichage d'une liste
void DisplayList(List* l){
    if(l==NULL){
        exit(-1);
    }
    Elem* m=l->first;
    printf("%ld\t",m->val);
    m=m->next;
    while(m!=NULL){
      printf("->\t");
      printf("%ld\t",m->val);
      m=m->next;
    }
}

//Verifie si n est present dans la liste
int IsInList(long n, List* list){
  Elem* m=list->first;
  // on passe au prochain elem car le premier element de la liste sert d'identificateur
  m=m->next;
  while (m!=NULL){
    if (m->val==n) return 0;
    m=m->next;
  }
  return 1;
}


void DestroyList(List *list){
  if (list == NULL){
    exit(-1);
  }
  Elem *current = list->first;
  Elem *tmp = NULL;
  while (current != NULL){
    tmp = current->next;
    free(current);
    current = tmp;
  }
  free(list);
}

//Affichage d'un tableau de liste
void DisplayTabList(List** Adj, long n){
  for (long i=0;i<n;i++){
    List* list=Adj[i];
    DisplayList(list);
    printf("\n");
  }
  printf("Fin de Affichage de liste\n");
}


//Verification que l'element a l'indice i est un supernoeud
int IsSuperNode(List **Adj, long i, long n){
  List* list= Adj[i];
  long cpt;
  if(Adj[i]->length != n){
    return 0;
  }
  for(cpt=0; cpt<n-1 ; cpt++){
    if (IsInList(cpt,list)==1){
      return 0;
    }
  }
  for(cpt=0; cpt<n-1;cpt++){
    List* list=Adj[cpt];
    if(IsInList(i,list) ==1){
      return 0;
    }
  }
  return 1;
}

//Remplissage d'un tableau
void FillInTable(List** Adj, PageList* pagelist, FILE* f,  long NumCharFile){
  long line_num1=0;
  char* pipeS="|";
  long index;
  char line[NumCharFile];
  //On recupere ligne par ligne le fichier
  while (fgets(line, sizeof(line), f)) {
    SuppChar(line,13);
    SuppChar(line,10);
    List* list=ListInit();
    char* tmp=strtok(line,pipeS);
    index=GetIndex(pagelist,tmp);
    PushIntInList(list,index);
    while(tmp!=NULL){
      index=GetIndex(pagelist,tmp);
      if (index==-1){
        tmp=strtok(NULL,pipeS);
        continue;
      }
      PushIntInList(list,index);
      tmp=strtok(NULL,pipeS);
      SuppChar(tmp,13);
      SuppChar(tmp,10);
    }
    PushIntInList(list,pagelist->length);
    Adj[line_num1]=list;
    line_num1++;
  }
  List* list=ListInit();
  PushIntInList(list,pagelist->length);
  for(long i=0; i<pagelist->length; i++){
    PushIntInList(list,i);
  }
  Adj[pagelist->length]=list;
}
