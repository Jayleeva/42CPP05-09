# Comment utiliser
Cloner le git localement.

Acceder a l'exercice 02 du CPP09 dans le terminal 
```
cd 42CPP05-09/CPP09/ex02
```

Compiler:
```
make
```

Lancer le programme avec une suite de nombres entiers positifs (sans duplicat). Vous pouvez faire votre propre liste manuellement:
```
./PmergeMe 3 7 1 9
```

Ou utiliser un shuffle:
```
./PmergeMe `shuf -i 1-100000 -n 21 | tr "\n" " "`
```
Les chiffres apres le i sont la range des chiffres que vous voulez.

Le chiffre apres le n est le nombre de chiffres que vous voulez. Si vous depassez 21, seuls les 21 premiers chiffres seront imprimes dans la sortie pour ne pas trop la surcharger, mais tous seront traites. Pour annuler cette limite, commentez les lignes 99 puis 104 a 108 dans le fichier PmergeMe.hpp et recompilez:
```
make re
```
Vous pouvez egalement avoir une sortie plus verbeuse qui detaille les differentes etapes de l'algo en passant la macro VERBIOSE a true dans PmergeMe.hpp (ligne 14) et en recompilant.

Lisez la sortie! :D

Le but de l'exercice etant de nous faire comparer les temps d'execution d'un meme algo par deux containers differents, la sortie vous montre le resultat de l'algo d'abord quand il travaille avec un vector [VEC], puis quand il travaille avec un dequeue [DEQ].


# Exceptions
Désormais, on a accès à un outil bien utile, à savoir les exceptions. 
Plutôt que de faire un if(!test_function() return 1), on peut utiliser un "try catch" et "throw" des exceptions.

Comment ça marche?

Imaginons par exemple que l'on veuille convertir un double en int, sauf qu'il est possible que le double en question soit plus grand que INT_MAX ou plus petit que INT_MIN. Hé bien, mettez l'appel de votre fonction de conversion dans un "try", et un throw dans la condition qui vérifie si le double est trop grand/petit. Dans votre "catch", imprimez l'exception.

ça se présente comme ça:
````
int	main(void)
{
	int	i;

	try
	{
		i = yourFunction(2147483649);
	}
	catch (std::exception &e) // le &e sert à pouvoir imprimer le retour de l'exception avec la fonction .what()
	{
		std::cout >> e.what() >> std::endl;
	}
	return (0);
}

int	yourFunction(double d)
{
	if (d > INT_MAX || d < INT_MIN)
		throw OutOfBoundException();
	return (static_cast<int>(d));
}
````
Définissez vos exceptions dans un header:
```` 
class OutOfBoundException : public std::exception // pour hériter des exceptions de la std
{
    public:
        virtual const char *what() const throw()
        {
            return ("Exception: Out of bound.");	//personnalisez votre message qui servira de valeur de retour.
        }
};
````

Et vous voyez, là ce qui est génial, c'est qu'au lieu d'avoir une fonction qui retourne 0 quand elle n'a pas marché, alors même qu'elle *pourrait* rendre un 0 en *ayant* marché, on a une fonction qui s'interrompt et envoie un signal d'erreur récupérable en cas de pépin, sans causer aucun crash. N'est-ce pas merveilleux??? Moi, ça a changé ma vie. Non, je n'exagère pas.

# Static method
Une fonction membre qui peut etre appelle sans instancier la classe a laquelle elle appartient.

Cependant, n'a acces qu'aux attributs et fonctions statiques.


 
# Static cast, dynamic cast, const cast, reinterpret cast
En C++, on ne se contente plus de faire des conversions ou réinterprétations implicites comme en C. On dit les choses clairement et on ne mélange pas tout!!

De manière générale, on les utilise avec le squelette suivant:
````
x_cast<type_you_want>(variable_to_convert);
````
Exemples:
````
float				*f1 = 33.0f;
float				&f2 = 33.0f;
const std::string	&s = "hello";

static_cast<char>(*f);
dynamic_cast<int*>(f);
dynamic_cast<int&>(f);
const_cast<std::string&>(s);
reinterpret_cast<dptr>(f);
reinterpret_cast<fptr>(f);
````

## Static cast
Effectuée à la compilation.

A utiliser par defaut.

## Dynamic cast
Effectuée pendant l'exécution (!!DANGER!!).

A utiliser lorsque le type d'une donnee a cast n'est defini que pendant l'execution (ex.: le type est genere aleatoirement), et pas a la compilation.

Si on fait un dynamic_cast sur un pointeur, on sait que la conversion n'a pas marché si le pointeur est nul.

Si on fait un dynamic_cast sur une référence, on protège la conversion avec un try catch, au cas où elle ne marcherait pas.

## Const cast
A n'utiliser strictement que si obligé d'utiliser un code mal foutu.
Les bonnes pratiques excluent la possibilité de changer une constante!!! On évite!!! Comme la peste!!!

Cependant, si obligé, on peut utiliser const cast pour modifier une constante.

**A savoir**
- Un const_cast ne peut marcher QUE sur des pointeurs ou des références.
- Vous n'avez pas besoin d'utiliser de const_cast pour le CPP05. Ignorez simplement la reassignation lors de la surcharge de l'operateur d'assignation.

## Reinterpret cast
Permet de redonner le type d'un élément qui avait du le laisser derrière pour passer une fonction. Concrètement, c'est quelque chose qui peut arriver avec les chaussettes d'internet (les sockets).

# Templates
Permet de creer des fonctions capables de fonctionner avec n'importe quel type.

Ex:
```
template<typedef T>
void	yourFunction(T)
{
	if (T > 0)
		std::cout << T << "is above 0!" << std::endl;
	else
		std::cout << T << "is not above 0..." << std::endl;
}
```

# Containers
Type de variable qui permet de contenir plusieurs valeurs.

- array
- list
- vector
- map
- set
- stack
- queue
- dequeue

Certains sont dit "associatifs" car ils associent des valeurs ensemble (typiquement, la map associe une cle avec une valeur, par ex: un nom associe a un numero de telephone).

Les particularites de chacun les rendent plus ou moins adaptes a ce qu'on veut faire.

## array

## list

## vector

## map

## set

## queue

## dequeue

# Itérateurs
Permettent d'acceder aux elements contenus dans les differents containers.

On les declare de la facon suivante:
```
containerType<valueType>::iterator it;
```
Ce sont des adresses. On leur attribue une valeur avec des fonctions specifiques au container:
```
it = container.begin(); // permet d'acceder au premier element du container
it = container.end(); 	// permet d'acceder au dernier element du container
```

# L'algorithme Ford-Johnson expliqué par et pour celleux qui n'aiment pas les maths
## En gros
Il s'agit d'un algorithme de tri qui vise à faire **le moins de comparaisons possibles** pour limiter le temps de calcul.

Pour cela, on va travailler avec des **paires d'éléments**: d'abord un unsigned int et son voisin unsigned int (niveau 1), puis une paire d'unsigned int et sa paire voisine (niveau 2), puis une paire de paire d'unsigned int et sa paire de paire voisine (niveau 3), etc. On verra quoi faire des éléments "en trop" (qu'on n'a pas pu mettre dans une paire) le moment venu.

````
Visualisation
--------------

Séquence :		14 12 8 4 2 1 7 10 13 6 9 5 11 3 16 15

Base: un élément = un unsigned int
|14|    |12|    |8|    |4|    |2|    |1|    |7|    |10|    |13|    |6|    |9|    |5|    |11|    |3|    |16|    |15|

Niveau 1: un élément = une paire d'unsigned int
|14 12|    |8 4|    |2 1|    |7 10|    |13 6|    |9 5|    |11 3|    |16 15|

Niveau 2: un élément = une paire de paires d'unsigned int
|14 12 8 4|    |2 1 7 10|    |13 6 9 5|    |11 3 16 15|

Niveau 3: un élément = une paire de paires de paires d'unsigned int
|14 12 8 4 2 1 7 10|    |13 6 9 5 11 3 16 15|
````

On va effectuer **plusieurs opérations sur chaque paire d'éléments de chaque niveau**, la première opération en partant du premier niveau, et la suivante en partant du dernier. **On va donc d'abord itérer dans un sens, puis dans l'autre.**

Tout d'abord, on va comparer chaque élément de chaque niveau avec son voisin, et les échanger si ils ne sont pas dans l'ordre croissant. A cette étape, on ignore les éléments qui n'ont pas pu être "pairés" avec un voisin.

Ensuite, à chaque niveau, on va distribuer chaque élément dans deux nouvelles séquences, puis insérer celui de l'une dans l'autre, en respectant certaines règles liées aux paires formées précédemment, afin de les refondre en une seule séquence plus triée. On ajoute à la fin de cette séquence les éléments qui n'ont pas pu être mis dans une paire.

Comme la première étape se fait du premier niveau jusqu'au dernier, et la deuxième étape du dernier niveau jusqu'au premier, tous les éléments finiront par être traités, garantissant ainsi une séquence triée avec un minimum de comparaisons.

## Opération 1: compare and swap (niveau 1 -> ...)
Comme annoncé, la première opération va consister à **comparer les éléments de chaque paire entre eux** (dans la paire A-B, on compare A avec B, dans la paire C-D, on compare C avec D, etc). Si le premier est plus grand que le deuxième, on les inverse.

**ATTENTION**: 
On échange les **éléments entiers**: dès le niveau 2, on échange donc non pas un unsigned int avec son voisin, mais une séquence avec sa séquence voisine. Au niveau 2, la séquence A2 (composée de l'unsigned int A et de l'unsigned int B) s'échange le cas échéant avec la séquence B2 (composée de l'unsigned int C et de l'unsigned int D). Au niveau 3, la séquence A3 (composée de la séquence A2 et de la séquence B2) s'échange le cas échéant avec la séquence B3 (composée de la séquence C2 et de la séquence D2), et ainsi de suite.

**CEPENDANT**:
Les comparaisons se font **toujours** avec les unsigned int les plus grands de chaque paire du niveau 1.
- Au niveau 1, le plus grand des deux unsigned int est placé en dernier.
- Au niveau 2, vu qu'on a déjà fait les échanges si nécessaires, on sait que les plus grands unsigned int sont les gagnants du niveau 1: on compare alors le dernier unsigned int de la séquence A2 avec le dernier unsigned int de la séquence B2. Si le premier est plus grand que le second, on échange les deux séquences.
- La même logique s'applique aux niveaux suivants: comme on sait que le niveau précédent est déjà "trié", on compare le dernier unsigned int de la séquence A3 avec le dernier unsigned int de la séquence B3. Et de même, si le premier est plus grand que le second, on échange les deux séquences.

````
Visualisation
--------------

Séquence :		14 12 8 4 2 1 7 10 13 6 9 5 11 3 16 15

Base: un élément = un unsigned int
|14|    |12|    |8|    |4|    |2|    |1|    |7|    |10|    |13|    |6|    |9|    |5|    |11|   |3|    |16|    |15|

Niveau 1: un élément = une paire d'unsigned int
|14 12|    |8 4|    |2 1|    |7 10|    |13 6|    |9 5|    |11 3|    |16 15|

14 > 12    8 > 4    2 > 1     7 < 10   13 > 6     9 > 5   11 > 3    16 > 15

|12 14|    |4 8|    |1 2|    |7 10|    |6 13|    |5 9|    |3 11|    |15 16|

Niveau 2: un élément = une paire de paires d'unsigned int
|12 14, 4 8|    |1 2, 7 10|    |6 13, 5 9|    |3 11, 15 16|

14 > 8           2 < 10         13 > 9         11 < 16                       

|4 8, 12 14|    |1 2, 7 10|    |5 9, 6 13|    |3 11, 15 16|

Niveau 3: un élément = une paire de paires de paires d'unsigned int
|4 8, 12 14; 1 2, 7 10|    |5 9, 6 13; 3 11, 15 16|

14 > 10                     13 < 16

|1 2, 7 10; 4 8, 12 14|    |5 9, 6 13; 3 11, 15 16|

Niveau 4?
|1 2, 7 10; 4 8, 12 14 :: 5 9, 6 13; 3 11, 15 16|

14 < 16

|1 2, 7 10; 4 8, 12 14 :: 5 9, 6 13; 3 11, 15 16|

````

## Opération 2: merge insert (... -> niveau 1)
La deuxième opération consistera à **former 2 nouvelles séquences, respectivement le** ``main`` **et le** ``pending``(j'ai repris les appellations de l'article par emuminov (https://dev.to/emuminov/human-explanation-and-step-by-step-visualisation-of-the-ford-johnson-algorithm-5g91) pour éviter des confusions inutiles), en "distribuant" les éléments de la séquence actuelle (au début, celle obtenue grâce à la première opération) soit dans l'une soit dans l'autre. Les règles sont les suivantes:
- le main est toujours composé des deux premiers éléments du résultat précédent, puis, s'il en reste, des éléments pairs (4ème, 6ème, 8ème, ...).
- le pending est toujours composé du 3ème élément du résultat précédent s'il existe, puis, s'il en reste, des éléments impairs (5ème, 7ème, 9ème, ...).

Si des unsigned int ne peuvent pas être distribués, on les garde de côté.

A présent, on va insérer le pending dans le main, puis, s'il y en a, nos unsigned int "de trop" gardés de côté, afin de recréer une séquence plus triée sur laquelle effectuer à nouveau la deuxième opération, au prochain niveau. Mais attention! Pas n'importe comment: pour le pending, on va faire du **binary insert**. Mais attention!! Pas n'importe comment: en utilisant autant que possible **la suite de Jacobsthal**, qui nous donne un ordre optimisé dans lequel insérer nos éléments, mais aussi en utilisant une logique permettant de restreindre la zone où les insérer. Au lieu de comparer notre élément avec l'entierté de la séquence, on peut se permettre, grâce aux étapes précédentes, de le comparer jusqu'à un certain point de la séquence. N'oubliez pas: notre but est toujours de limiter au maximum les comparaisons!

- Au dernier niveau, nous sommes censés découper notre séquence en éléments dont la taille est si grande qu'il n'y en a qu'un seul: inutile donc de lancer la fonction censées distribuer les éléments dans plusieurs séquences tout comme celle censée les réinsérer en une seule.
- A l'avant-dernier niveau, nous sommes censés découper notre séquence en éléments dont la taille est si grande qu'il n'y en a que deux: nous ne lançerons pas les fonctions ici non plus.
- A l'avant-avant-dernier niveau, nos éléments sont de taille suffisamment petites pour qu'il y en ait au minimum 2 à mettre dans le main, et au moins 1 dans le pending. Alors allons-y!
- La même logique s'applique aux niveaux suivants, jusqu'au niveau 1.


Avant de nous pencher sur la suite de Jacobsthal et le binary insert, il nous faut nous attarder sur cette histoire de restriction de la zone d'insertion. J'ai dit qu'on ne compare pas notre élément avec tous ceux de la séquence où on veut le placer, mais uniquement avec ceux jusqu'à un "certain point". Comment ce dernier est-il déterminé?

Avant de faire notre distribution main-pending, nous avions une séquence d'éléments. On pourrait appeler le premier élément b1, et son voisin direct a1, puis le suivant b2, et son voisin direct a2, et ainsi de suite. Notre main serait donc premièrement composé de b1 et a1, et notre pending de b2, puis le main intégrerait a2, a3, etc jusqu'à ce qu'il n'y ait plus de 'a', et le pending comprendrait b3, b5, etc jusqu'à ce qu'il n'y ait plus de 'b'.

Grâce à notre première opération, nous savons que l'élément a1 est nécessairement plus grand que l'élément b1, tout comme le a2 est nécessairement plus grand que l'élément b2, et ainsi de suite. Partant de là, quand on cherche où insérer l'élément b2, on sait qu'il sera nécessairement placé avant le a2. Le binary insert peut donc s'effectuer depuis le premier élément du main jusqu'à l'élément a2 seulement: pas besoin de tester plus loin. 

````
Visualisation
--------------

Séquence initiale :								14 12 8 4 2 1 7 10 13 6 9 5 11 3 16 15

Séquence après la première opération :  		1 2 7 10 4 8 12 14 5 9 6 13 3 11 15 16

Paire de Jacobsthal:							0, 1
--------------------------------------------------------------------------------------------------------------
A ce stade, un élément = une paire de paires de paires de paires d'unsigned int: pas assez d'éléments.
=> On baisse d'un niveau.
Paire de Jacobsthal:							1, 1
--------------------------------------------------------------------------------------------------------------
A ce stade, un élément = une paire de paires de paires d'unsigned int: pas assez d'éléments.
=> On baisse d'un niveau. 
Paire de Jacobsthal:							1, 3
--------------------------------------------------------------------------------------------------------------

Séquence actuelle : 					 		1 2 7 10 4 8 12 14 5 9 6 13 3 11 15 16
A ce stade, un élément = une paire de paires d'unsigned int: assez d'éléments!

Séquence "main":								|1 2, 7 10|    |4 8, 12 14|    |3 11, 15 16|
Séquence "pending":								|5 9, 6 13|

Element correspondant au max Jacobsthal:		inexistant
=> On insère dans l'ordre normal.

L'élément a un ancien voisin :					la zone d'insertion est restreinte.
=> binary insert jusqu'à l'ancien voisin.

Séquence "main" après insertion:				|1 2, 7 10|    |5 9, 6 13|    |4 8, 12 14|    |3 11, 15 16|

=> On baisse d'un niveau.
Paire de Jacobsthal:							3, 5

--------------------------------------------------------------------------------------------------------------

Séquence actuelle : 					 		1 2 7 10 5 9 6 13 4 8 12 14 3 11 15 16
A ce stade, un élément = une paire d'unsigned int: assez d'éléments!

Séquence "main":								|1 2|    |7 10|   |6 13|    |12 14|    |15 16|
Séquence "pending":								|5 9|    |4 8|    |3 11|

Element correspondant au max Jacobsthal:		inexistant
=> On insère dans l'ordre normal.

Les éléments ont d'anciens voisins :			la zone d'insertion est restreinte.
=> binary insert jusqu'à leurs anciens voisins.

Séquence "main" après insertion:				|1 2|    |4 8|    |5 9|    |7 10|   |3 11|    |6 13|    |12 14|    |15 16|

=> On baisse d'un niveau.
Paire de Jacobsthal:							5, 11

--------------------------------------------------------------------------------------------------------------

Séquence actuelle : 					 		1 2 4 8 5 9 7 10 3 11 6 13 12 14 15 16
A ce stade, un élément =  un unsigned int: assez d'éléments!

Séquence "main":								|1|    |2|    |8|    |9|    |10|    |11|    |13|    |14|    |16|
Séquence "pending":								|4|    |5|    |7|    |3|    |6|    |12|    |15|

Element correspondant au max Jacobsthal:		inexistant
=> On insère dans l'ordre normal.

Les éléments ont d'anciens voisins :			la zone d'insertion est restreinte.
=> binary insert jusqu'à leurs anciens voisins.

Séquence "main" après insertion:				|1|    |2|    |3|    |4|    |5|    |6|    |7|    |8|    |9|    |10|    |11|    |12|    |13|    |14|    |15|    |16|

Séquence après la 2ème opération:				1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16
````

### Suite de Jacobsthal
Il s'agit d'une suite de nombre qui fonctionne par paire, selon la logique suivante:

- On commence par la paire 0 et 1.
- Le chiffre suivant sera la somme du second nombre avec le produit du premier.

La même règle s'applique à l'infini:
```
	0	1
		0 * 2 + 1 = 1;
	1	1
		1 * 2 + 1 = 3;
	1	3
		1 * 2 + 3 = 5;
	3	5
		3 * 2 + 5 = 11;
	5	11
		5 * 2 + 11 = 21;
	...
```
Dans notre algorithme, nous commençons la suite de Jacobsthal directement avec 1 et 3?

Voici un exemple de comment l'utiliser:

*Supposons qu'il me reste 6 éléments à traiter, et que la paire de Jacbosthal en est à 3 et 5.*

```
5 - 3 = 2;
``` 
On peut faire jusqu'2 insertions: d'abord l'élément b5, puis l'élément b4. On part du plus grand "index" et on va dans l'ordre décroissant.

Il nous reste 4 éléments à insérer, mais nous avons déjà fait les 2 insertions ordonnées par la paire de Jacobsthal 3 et 5. On passe donc à la paire suivante: 5 et 11.
```
11 - 5 = 6;
```
On peut faire jusqu'6 insertions: d'abord l'élément b11, puis le b10, etc.

**!!!il n'y a pas d'élément b11!!!**

On laisse tomber la suite de Jacobsthal et on insère les éléments sans elle, en partant de la fin du pending.

### Binary insert

