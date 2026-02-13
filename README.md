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

# L'algorithme Ford-Johnson
Il s'agit d'un algorithme de tri qui vise à faire le moins de comparaisons possibles pour limiter le temps de calcul.

Je pensais d'abord expliquer l'approche mathématique puis l'implémentation en code, mais j'ai peur que ça ne crée plus de confusion que nécessaire (comme ça a été le cas pour moi).

En gros, l'algorithme fonctionne de manière récursive, en 3 étapes: 
1. On lance la fonction récursive. Si on peut diviser la taille de la séquence par 2 et obtenir un résultat plus grand que 1, on relance la fonction récursive avec taille / 2. Si cette condition n'est pas remplie, on exécute l'étape suivante. Cela permet de d'abord arriver au plus petit niveau de paire (deux unsigned int) et d'exécuter l'étape suivante sur ce niveau, puis sur le niveau au-dessus (deux paires d'unsigned int), puis le suivant (deux paires de paires d'unsigned int, etc.).
2. On compare chaque élément de la séquence actuelle avec son suivant (paires) et on les répartit en éléments forts (max de chaque paire) et en éléments faibles (min de chaque paire). Au total, nous avons donc 3 séquences: celle actuelle, celle des éléments forts, et celle des éléments faibles. A la première itération, la séquence "actuelle" est celle reçue par l'algorithme. Ensuite, elle est d'abord nettoyée (.clear()) puis copie la séquence des éléments forts. Ainsi, on sépare d'abord les éléments forts et faibles de chaque paire, puis de chaque paire de paire, puis de chaque paire de paire de paire, etc. **ATTENTION:** la séquence des éléments faibles doit être remplie avec un **binary insert**, afin qu'elle soit triée au fur et à mesure. Les éventuels éléments "de trop" (en cas de taille impaire) sont également insérés, de la même manière, dans la séquence des éléments faibles.
3. On sort de la fonction récursive. Il nous reste à combiner notre séquence d'éléments forts restant avec celle des éléments faibles déjà triée. Pour ce faire, nous allons également utiliser le binary insert, avec une couche supplémentaire: la suite de Jacobsthal.

