# 42CPP05-09
Projet du 6ème cercle du cursus 42


## L'algorithme Ford-Johnson
Il s'agit d'un algorithme de tri qui vise à faire le moins de comparaisons possibles pour limiter le temps de calcul.

En gros, il fonctionne de manière récursive, en 3 étapes: 
- on forme des paires et on en compare et trie les éléments; les éléments forts (max de chaque paire) seront les seuls importants pour la suite.
- 

# Etape 1: les paires de paires de paires de...

On forme et compare des paires, puis des paires de paires, puis des paires de paires de paires, ... Jusqu'à ce qu'une "paire de paire de..." englobe en réalité toute la séquence. 

Par exemple, sur la séquence suivante:
````
21 4 56 92 3 15 47 8 39 16 2 73 45 19 12 24
````
On forme les premières paires suivantes:
````
21 4 | 56 92 | 3 15 | 47 8 | 39 16 | 2 73 | 45 19 | 12 24
````
A l'intérieur de chaque paire, on compare et trie les éléments: si l'élément A est plus grand que l'élément B, on les inverse.
Dans notre exemple, on obtiendrait alors:
````
4 21 | 56 92 | 3 15 | 8 47 | 16 39 | 2 73 | 19 45 | 12 24
````
Nous savons désormais quels sont les éléments forts de la suite:
4 **21** 56 **92** 3 **15** 8 **47** 16 **39** 2 **73** 19 **45** 12 **24**

En réalité, dans notre code, nous n'allons pas nous embêter à faire des swap: on crée deux nouvelles séquences, l'une qui contient les éléments faibles, et l'autre qui contient les éléments forts.

Puis on forme les paires de paires suivantes:
````
4 21 56 92 | 3 15 8 47 | 16 39 2 73 | 19 45 12 24
````

Puis on forme les paires de paires de paires suivantes:
````
21 4 56 92 3 15 47 8 | 39 16 2 73 45 19 12 24
````
On s'arrête là, car le prochain niveau reviendrait à regrouper toute la séquence.


