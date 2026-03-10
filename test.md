
AUTRES ESSAIS
````
Visualisation
--------------

Séquence initiale :								14 12 8 17 4 19 7 1 13 10 2 18 11 5 9 6 16 3 20 15
												12 14 8 17 4 19 1 7 10 13 2 18 5 11 6 9 3 16 15 20
												12 14 8 17 1 7 4 19 10 13 2 18 6 9 5 11 3 16 15 20
												12 14 8 17 1 7 4 19 6 9 5 11 10 13 2 18 3 16 15 20
												6 9 5 11 10 13 2 18 12 14 8 17 1 7 4 19 3 16 15 20

Séquence après la première opération :  		6 9 5 11 10 13 2 18 12 14 8 17 1 7 4 19 3 16 15 20

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

Séquence actuelle : 					 		6 9 5 11 10 13 2 18 12 14 8 17 1 7 4 19 3 16 15 20
A ce stade, un élément = une paire de paires d'unsigned int: assez d'éléments!

Séquence "main":								|6 9 5 11|      |10 13 2 18|    |1 7 4 19|
Séquence "pending":								|12 14 8 17|    |3 16 15 20|

Elément correspondant au max Jacobsthal:		inexistant
=> On insère dans l'ordre normal.

Le dernier élément n'a pas d'ancien voisin :	la zone d'insertion n'est pas restreinte.
=> binary insert sur tout le main.

Le second élément a un ancien voisin :			la zone d'insertion est restreinte.
=> binary insert jusqu'à l'ancien voisin.

Séquence "main" après insertion:				|6 9 5 11|    |12 14 8 17|    |10 13 2 18|    |1 7 4 19|    |3 16 15 20|

=> On baisse d'un niveau.
Paire de Jacobsthal:							3, 5

--------------------------------------------------------------------------------------------------------------

Séquence actuelle : 					 		 6 9 5 11 12 14 8 17 10 13 2 18 1 7 4 19 3 16 15 20
A ce stade, un élément = une paire d'unsigned int: assez d'éléments!

Séquence "main":								|6 9|    |5 11|   |8 17|   |2 18|    |4 19|    |15 20|
Séquence "pending":								|12 14|  |10 13|  |1 7|    |3 16|

Elément correspondant au max Jacobsthal:		|3 16|
=> On insère depuis cet élément.

Les éléments ont d'anciens voisins :			la zone d'insertion est restreinte.
=> binary insert jusqu'à leurs anciens voisins.

Séquence "main" après insertion:				|1 7|    |6 9|    |5 11|   |10 13|    |12 14|    |3 16|    |8 17|   |2 18|    |4 19|    |15 20|

=> On baisse d'un niveau.
Paire de Jacobsthal:							5, 11

--------------------------------------------------------------------------------------------------------------

Séquence actuelle : 					 		1 7 6 9 5 11 10 13 12 14 3 16 8 17 2 18 4 19 15 20
A ce stade, un élément =  un unsigned int: assez d'éléments!

Séquence "main":								|1|    |7|    |9|    |11|   |13|    |14|   |16|    |17|   |18|   |19|    |20|
Séquence "pending":								|6|    |5|    |10|   |12|   |3|     |8|    |2|     |4|    |15|

Elément correspondant au max Jacobsthal:		inexistant
=> On insère dans l'ordre normal.

Les éléments ont d'anciens voisins :			la zone d'insertion est restreinte.
=> binary insert jusqu'à leurs anciens voisins.

Séquence "main" après insertion:				|1|    |2|    |3|    |4|    |5|    |6|    |7|    |8|    |9|    |10|    |11|    |12|    |13|    |14|    |15|    |16|   |17|    |18|   |19|    |20|

Séquence après la 2ème opération:				1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
````


````
Visualisation
--------------

Séquence initiale :								22 14 8 17 19 4 21 7 13 10 2 18 11 5 9 6 24 16 3 20 15 1 23 12
												14 22 8 17 4 19 7 21 10 13 2 18 5 11 6 9 16 24 3 20 1 15 12 23
												8 17 14 22 4 19 7 21 10 13 2 18 6 9 5 11 3 20 16 24 1 15 12 23
												4 19 7 21 8 17 14 22 6 9 5 11 10 13 2 18 1 15 12 23 3 20 16 24
												6 9 5 11 10 13 2 18 4 19 7 21 8 17 14 22 1 15 12 23 3 20 16 24

Séquence après la première opération :  		6 9 5 11 10 13 2 18 4 19 7 21 8 17 14 22 1 15 12 23 3 20 16 24

Paire de Jacobsthal:							0, 1
--------------------------------------------------------------------------------------------------------------
A ce stade, un élément = une paire de paires de paires de paires d'unsigned int: pas assez d'éléments.
=> On baisse d'un niveau.
Paire de Jacobsthal:							1, 1
--------------------------------------------------------------------------------------------------------------
Séquence actuelle : 					 		6 9 5 11 10 13 2 18 4 19 7 21 8 17 14 22 1 15 12 23 3 20 16 24
A ce stade, un élément = une paire de paires de paires d'unsigned int: assez d'éléments!

Séquence "main":								|6 9 5 11 10 13 2 18|    |4 19 7 21 8 17 14 22|
Séquence "pending":								|1 15 12 23 3 20 16 24|

Elément correspondant au max Jacobsthal:		inexistant
=> On insère dans l'ordre normal.

Le dernier élément n'a pas d'ancien voisin :	la zone d'insertion n'est pas restreinte.
=> binary insert sur tout le main.

Séquence "main" après insertion:				|6 9 5 11 10 13 2 18|    |4 19 7 21 8 17 14 22|   |1 15 12 23 3 20 16 24|

=> On baisse d'un niveau.
Paire de Jacobsthal:							1, 3

--------------------------------------------------------------------------------------------------------------
Séquence actuelle : 					 		6 9 5 11 10 13 2 18 4 19 7 21 8 17 14 22 1 15 12 23 3 20 16 24
A ce stade, un élément = une paire de paires de paires d'unsigned int: assez d'éléments!

Séquence "main":								|6 9 5 11|    |10 13 2 18|    |8 17 14 22|    |3 20 16 24|
Séquence "pending":								|4 19 7 21|   |1 15 12 23|     

Elément correspondant au max Jacobsthal:		|1 15 12 23|
=> On insère depuis cet élément.

Le dernier élément n'a pas d'ancien voisin :	la zone d'insertion n'est pas restreinte.
=> binary insert sur tout le main.

Séquence "main" après insertion:				|6 9 5 11|    |10 13 2 18|    |4 19 7 21|    |8 17 14 22|    |1 15 12 23|    |3 20 16 24|

=> On baisse d'un niveau.
Paire de Jacobsthal:							3, 5

--------------------------------------------------------------------------------------------------------------
Séquence actuelle : 					 		 6 9 5 11 10 13 2 18 4 19 7 21 8 17 14 22 1 15 12 23 3 20 16 24
A ce stade, un élément = une paire de paire d'unsigned int: assez d'éléments!

Séquence "main":								|6 9|    |5 11|   |8 17|   |2 18|    |4 19|    |15 20|
Séquence "pending":								|12 14|  |10 13|  |1 7|    |3 16|

Elément correspondant au max Jacobsthal:		|3 16|
=> On insère depuis cet élément.

Les éléments ont d'anciens voisins :			la zone d'insertion est restreinte.
=> binary insert jusqu'à leurs anciens voisins.

Séquence "main" après insertion:				|1 7|    |6 9|    |5 11|   |10 13|    |12 14|    |3 16|    |8 17|   |2 18|    |4 19|    |15 20|

=> On baisse d'un niveau.
Paire de Jacobsthal:							5, 11

--------------------------------------------------------------------------------------------------------------

Séquence actuelle : 					 		1 7 6 9 5 11 10 13 12 14 3 16 8 17 2 18 4 19 15 20
A ce stade, un élément =  un unsigned int: assez d'éléments!

Séquence "main":								|1|    |7|    |9|    |11|   |13|    |14|   |16|    |17|   |18|   |19|    |20|
Séquence "pending":								|6|    |5|    |10|   |12|   |3|     |8|    |2|     |4|    |15|

Elément correspondant au max Jacobsthal:		inexistant
=> On insère dans l'ordre normal.

Les éléments ont d'anciens voisins :			la zone d'insertion est restreinte.
=> binary insert jusqu'à leurs anciens voisins.

Séquence "main" après insertion:				|1|    |2|    |3|    |4|    |5|    |6|    |7|    |8|    |9|    |10|    |11|    |12|    |13|    |14|    |15|    |16|   |17|    |18|   |19|    |20|

Séquence après la 2ème opération:				1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
````



````
Visualisation
--------------

Séquence initiale :								22 14 8 17 32 25 19 4 21 28 7 31 29 13 10 2 30 18 26 11 5 9 6 24 16 3 20 15 27 1 23 12
												14 22 8 17 25 32 4 19 21 28 7 31 13 29 2 10 18 30 11 26 5 9 6 24 3 16 15 20 1 27 12 23
												8 17 14 22 4 19 25 32 21 28 7 31 2 10 13 29 18 26 5 30 3 9 11 24 1 16 6 20 12 23 15 27
												8 17 14 22 4 19 25 32 2 10 13 29 21 28 7 31 3 9 11 24 18 26 5 30 1 16 6 20 12 23 15 27
												2 10 13 29 21 28 7 31 8 17 14 22 4 19 25 32 1 16 6 20 12 23 15 27 3 9 11 24 18 26 5 30
												1 16 6 20 12 23 15 27 3 9 11 24 18 26 5 30 2 10 13 29 21 28 7 31 8 17 14 22 4 19 25 32

Séquence après la première opération :  		1 16 6 20 12 23 15 27 3 9 11 24 18 26 5 30 2 10 13 29 21 28 7 31 8 17 14 22 4 19 25 32

Paire de Jacobsthal:							0, 1
--------------------------------------------------------------------------------------------------------------
A ce stade, un élément = une paire de paires de paires de paires de paires d'unsigned int: pas assez d'éléments.
=> On baisse d'un niveau.
Paire de Jacobsthal:							1, 1
--------------------------------------------------------------------------------------------------------------
A ce stade, un élément = une paire de paires de paires de paires d'unsigned int: pas assez d'éléments.
=> On baisse d'un niveau.
Paire de Jacobsthal:							1, 3
--------------------------------------------------------------------------------------------------------------
Séquence actuelle : 					 		1 16 6 20 12 23 15 27 3 9 11 24 18 26 5 30 2 10 13 29 21 28 7 31 8 17 14 22 4 19 25 32
A ce stade, un élément = une paire de paires de paires d'unsigned int: pas assez d'éléments.

Séquence "main":								|1 16 6 20 12 23 15 27|    |3 9 11 24 18 26 5 30|    |8 17 14 22 4 19 25 32|
Séquence "pending":								|2 10 13 29 21 28 7 31|

Elément correspondant au max Jacobsthal:		inexistant
=> On insère dans l'ordre normal.

Le dernier élément n'a pas d'ancien voisin :	la zone d'insertion n'est pas restreinte.
=> binary insert sur tout le main.

Séquence "main" après insertion:				|1 16 6 20 12 23 15 27|    |3 9 11 24 18 26 5 30|    |2 10 13 29 21 28 7 31|    |8 17 14 22 4 19 25 32|

=> On baisse d'un niveau.
Paire de Jacobsthal:							3, 5

--------------------------------------------------------------------------------------------------------------
Séquence actuelle : 					 		1 16 6 20 12 23 15 27 3 9 11 24 18 26 5 30 2 10 13 29 21 28 7 31 8 17 14 22 4 19 25 32
A ce stade, un élément = une paire de paires d'unsigned int: assez d'éléments!

Séquence "main":								|1 16 6 20|    |12 23 15 27|    |18 26 5 30|    |21 28 7 31|    |4 19 25 32|
Séquence "pending":								|3 9 11 24|    |2 10 13 29|     |8 17 14 22|

Elément correspondant au max Jacobsthal:		inexistant.
=> On insère dans l'ordre normal.

Le dernier élément a un ancien voisin :			la zone d'insertion est restreinte.
=> binary insert jusqu'à l'ancien voisin.

Séquence "main" après insertion:				|1 16 6 20|    |8 17 14 22|    |3 9 11 24|    |12 23 15 27|    |2 10 13 29|    |18 26 5 30|    |21 28 7 31|    |4 19 25 32|

=> On baisse d'un niveau.
Paire de Jacobsthal:							5, 11

--------------------------------------------------------------------------------------------------------------
Séquence actuelle : 					 		1 16 6 20 8 17 14 22 3 9 11 24 12 23 15 27 2 10 13 29 18 26 5 30 21 28 7 31 4 19 25 32
A ce stade, un élément = une paire d'unsigned int: assez d'éléments!

Séquence "main":								|1 16|    |6 20|   |14 22|   |11 24|    |15 27|    |13 29|   |5 30|    |7 31|    |25 32|
Séquence "pending":								|8 17|    |3 9|    |12 23|   |2 10|     |18 26|    |21 28|   |4 19|

Elément correspondant au max Jacobsthal:		inexistant.
=> On insère dans l'ordre normal.

Les éléments ont d'anciens voisins :			la zone d'insertion est restreinte.
=> binary insert jusqu'à leurs anciens voisins.

Séquence "main" après insertion:				|3 9|  |2 10|  |1 16|  |8 17|  |4 19|  |6 20| |14 22| |12 23|  |11 24|  |18 26|  |15 27|  |21 28|  |13 29| |5 30|  |7 31|  |25 32|

=> On baisse d'un niveau.
Paire de Jacobsthal:							11, 21

--------------------------------------------------------------------------------------------------------------
 
Séquence actuelle : 					 		3 9 2 10 1 16 8 17 4 19 6 20 14 22 12 23 11 24 18 26 15 27 21 28 13 29 5 30 7 31 25 32
A ce stade, un élément =  un unsigned int: assez d'éléments!

Séquence "main":								|3|    |9|    |10|   |16|  |17|    |19|   |20|    |22|   |23|   |24|  |26| |27| |28| |29| |30| |31| |32|
Séquence "pending":								|2|    |1|    |8|    |4|   |6|     |14|   |12|    |11|   |18|   |15|  |21| |13| |5|  |7|  |25|

Elément correspondant au max Jacobsthal:		inexistant
=> On insère dans l'ordre normal.

Les éléments ont d'anciens voisins :			la zone d'insertion est restreinte.
=> binary insert jusqu'à leurs anciens voisins.

Séquence "main" après insertion:				|1|   |2|   |3|  |4|   |5|  |6|   |7|  |8|   |9|  |10|  |11|   |12|   |13|   |14|   |15|   |16|  |17|  |18|   |19|  |20|  |21|   |22|  |23|  |24|  |25|   |26|  |27|  |28|  |29|  |30|  |31|  |32|

Séquence après la 2ème opération:				1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32
````