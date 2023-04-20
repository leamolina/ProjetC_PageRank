#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include <math.h>
#include "matrice.c"



double ReturnPercentMax(double probaFile[], double tmp[], long LengthMatrix){
  long i;
  //Comparaison des supernoeuds
  double resultExact=probaFile[0];
  double resultApprox=tmp[LengthMatrix];
  double result=(fabs(resultApprox-resultExact)/resultExact) * 100;
  double percentMax=result;
  for(i=1; i<LengthMatrix+1; i++){
    double resultExact=probaFile[i];
    double resultApprox=tmp[i-1];
    double result=(fabs(resultApprox-resultExact)/resultExact) * 100;
    if(result>percentMax){
      percentMax=result;
    }
  }
  return percentMax;
}

//Initialisation d'un tableau de probabilite
void ProbaPageInit(List** Adj,double proba[],long n){
  for (long i=0; i<n;i++){
    if (IsSuperNode(Adj, i,n)==1){
      proba[i]=0.0;
    }
    else{
      double m=n-1;
      proba[i]=1/m;
    }
  }
}

//Inialisation des differentes valeurs de proba(u->s)
double probaU(List** Adj, long length, long u, long s, double epsilon){
  double n=length-1;
  int nodeU=IsSuperNode(Adj,u,length);
  int nodeS=IsSuperNode(Adj,s, length);
  if(nodeU==1){
    return 1/n;
  }
  else if (nodeS==1) return epsilon;
  else{
    //On ne compte pas le super noeud ni l identificateur
    double nb=Adj[u]->length-2;
    return (1-epsilon)/nb;
  }
}



//Création de tableau contenant les predecesseur de chaque indice
long TabPredecessor(List** Adj,long* predecessor,long index, long n){
  long i=0;
  for (long j=0; j<n;j++){
    List* list=Adj[j];
    if(IsInList(index, list)==0){
      predecessor[i]=j;
      i++;
    }
  }
  return i;
}


//Calcul des probabilites
void CalculProba(List** Adj,double proba[], double tmp[], long lengthProba, long predecessor[], double epsilon){
  CopyTab(proba,tmp,lengthProba);
  for(long index=0; index<lengthProba; index++){
    long length=TabPredecessor(Adj,predecessor,index,lengthProba);
    double sum=0.0;
    for (long i=0; i<length; i++){
      long u=predecessor[i];
      sum+=probaU(Adj,lengthProba,u,index,epsilon)*tmp[u];
    }
    proba[index]=sum;
  }
}




//Recuperation des x pages les plus importantes
void RecupMax(double proba[],long x, PageList* pagelist, long length){
  long indexMax=0;
  //Une proba est toujours inferieure a 1
  double MaxPred=1.0;
  long cpt=0;
  while(cpt<x){
    double Max=proba[0];
    for(long i=0; i<length; i++){
      if(proba[i]>=Max && proba[i]<=MaxPred){
        indexMax=i;
        Max=proba[i];
      }
    }
    proba[indexMax]=0.0;
    char* name= GetName(pagelist, indexMax);
    printf("numero %ld : %s (page rank = %lf )\n",cpt+1,name,Max);
    MaxPred=Max;
    cpt++;
  }
}

double SumProba(double proba[],long length){
  double sum=0.0;
  for (long i=0;i<length;i++){
    sum+=proba[i];
  }
  return sum;


}
