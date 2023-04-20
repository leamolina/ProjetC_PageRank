#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include "Divers.c"


typedef struct page{
    long index;
    char *name;
    struct page* next;
}Page;

typedef struct{
    Page* first;
    //Page* dernier;
    long length;
}PageList;


//Initialisation de ListePage
PageList* PageListInit(){
  PageList* pagelist=malloc(sizeof(pagelist));
  if(pagelist==NULL){
    exit(-1);
  }
  pagelist->first=NULL;
  pagelist->length=0;
  return pagelist;
}


//Recuperation de la page correspondant au i eme element de pagelist
Page* GetPage(PageList* pagelist, long index){
  long i;
  Page *page=pagelist->first;
  if(pagelist==NULL){
    exit(-1);
  }
  //Par convention, quand l'indice n'est pas approprié (trop grand ou trop petit), on renvoie la premier page de listePage
  if(index>=pagelist->length || index<0){
    return pagelist->first;
  }
  for(i=0; i<index; i++){
    page=page->next;
  }
  return page;
}


//Creation d' une case vide de listePage qui contindra le nom et l'indice passe en argument
void PushPageInList(PageList* pagelist, long i, char* str){
  Page* new=malloc(sizeof(Page));
  if(pagelist==NULL || new==NULL){
    exit(-1);
  }
  new->name=malloc((strlen(str)+1)*sizeof(char));
  if(new->name==NULL){
    exit(-1);
  }
  strcpy(new->name,str);
  new->index=i;
  new->next=NULL;
  if(pagelist->length>0){
    Page* last;
    last=GetPage(pagelist, pagelist->length -1);
    last->next=new;
  }
  else{
    pagelist->first=new;
  }
  pagelist->length++;
}


//Recuperation de l'indice associé au nom d'une page
long GetIndex(PageList* pagelist, char* word){
  long i=0;
  while(i<pagelist->length){
    Page* p=GetPage(pagelist,i);
    int x=strcmp(p->name, word);
    if(x==0) return i;
    i++;
  }
  return -1;
}

//Recuperation d'un nom associé à un indice
char* GetName(PageList* pagelist, long i){
  Page* p=GetPage(pagelist,i);
  return(p->name);
}

//Remplissage de listePage
void FillListPage(FILE* f, PageList* pagelist, long NumCharFile){
  long cpt=0;
  char* pipe;
  pipe="|";
  char line[NumCharFile];
  while (fgets(line, sizeof(line), f)) {
    char* word;
    SuppChar(line,10);
    word=strtok(line, pipe);
    PushPageInList(pagelist,cpt,word);
    cpt++;
    }
}

//Affichage de listepage
void DisplayPageList(PageList* pagelist){
  Page* page= pagelist->first;
  while(page!=NULL){
    printf("%ld : %s \n",page->index,page->name);
    page=page->next;
  }
  printf("\n");
}

void DestroyPageList(PageList *pagelist){
  if (pagelist == NULL){
    exit(-1);
  }
  Page *current = pagelist->first;
  Page *tmp = NULL;
  while (current != NULL){
    tmp = current->next;
    free(current->name);
    free(current);
    current = tmp;
  }
  free(pagelist);
}
