# ProjetC

1. Introduction

Le but de notre projet est d’afficher les pages internet d’un fichier en les classant en fonction de leur pertinence. 
Ce classement porte le nom de PageRank. 
Durant le projet, deux modes d’exécutions sont proposés :
Le mode Normal classe les meilleures probabilités à partir d’un fichier texte contenant une représentation des pages (graphes de Wikipédia).
Le mode Test prend un fichier texte contenant une matrice adjacente et les probabilités censées émaner de notre programme. Le but de ce mode est d’afficher le pourcentage d’erreur maximal obtenu après avoir calculé, à l’aide de nos fonctions, les PageRank de la matrice.


2. Mode normal :

Si vous souhaitez exécuter un tel programme, entrez dans le terminal :
gcc -Wall main.c -o programme
Puis, entrez (toujours dans le terminal) :
./programme -n graphe.txt x
Avec :
- graphe.txt le nom du fichier Wikipédia à exécuter ; s’il n’est pas dans le dossier, vous
pouvez écrire directement son chemin absolu.
- x le nombre de pages les plus importantes du graphe que vous souhaitez récupérer.

Il suffit ensuite de vous laisser guider par les instructions qui s’afficheront sur votre terminal. Certaines fonctionnalités ont en effet été ajoutées, permettant à l’utilisateur (s’il le souhaite) de :
- Afficher la liste de pages
- Afficher le tableau de listes
- Afficher le tableau de probabilités initialisé
- Choisir une valeur particulière pour epsilon
- Afficher le nouveau tableau de probabilités après les mises à jour
Par défaut, le nombre de mises à jour a été fixé à 20. C’est en effet une valeur qui permet d'avoir un résultat assez précis, et dont le temps d’exécution est raisonnable.
A la fin de l’exécution, l’affichage des x pages ayant le meilleur PageRank, avec la valeur associée, s’affiche.


3. Mode test : 

Si vous souhaitez exécuter un tel programme, entrez dans le terminal :
gcc -Wall main.c -o programme
Puis, entrez (toujours dans le terminal) :
./programme -t k
Avec :
- k le nombre de mises à jour du tableau de probabilités. Nous vous conseillons de
choisir une valeur de k comprise entre 20 et 30.
Au début de l’exécution du programme, vous aurez la possibilité d’entrer le nom du fichier texte contenant la matrice adjacente et les probabilités censées être obtenues. 
Si ce fichier n’est pas dans le dossier, vous pouvez écrire directement son chemin absolu.
Tout comme le mode normal, de nombreuses options vous seront proposées. 
Il suffit de vous laisser guider par les instructions qui s’afficheront. 
Certaines fonctionnalités ont en effet été ajoutées, permettant à l’utilisateur (s’il le souhaite) de :
- Afficher la matrice du fichier modifié et contenant le supernoeud - Afficher le tableau de listes
- Afficher le tableau de probabilités initialisées
- Choisir une valeur particulière pour epsilon
- Afficher le nouveau tableau de probabilités après les mises à jour

Le programme se termine en affichant le pourcentage maximal d’erreurs en comparant les probabilités observées dans le fichier texte avec celles obtenues en étudiant la matrice adjacente.
