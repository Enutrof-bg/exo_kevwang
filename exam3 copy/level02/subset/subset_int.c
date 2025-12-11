/*
 * POWERSET - Programme pour trouver tous les sous-ensembles dont la somme égale une valeur cible
 * 
 * VERSION AVEC TABLEAU D'INT
 * 
 * Principe : Utilise le BACKTRACKING (exploration de toutes les possibilités)
 * Pour chaque nombre, on a 2 choix : le prendre OU ne pas le prendre
 * 
 * Exemple : ./powerset 3 1 0 2
 * - Cherche tous les sous-ensembles de [1, 0, 2] dont la somme = 3
 * - Résultats : [3], [0, 3], [1, 2], [1, 0, 2]
 */

#include "h.h"

/*
 * ft_print - Affiche tous les éléments du tableau séparés par des espaces
 * @subset: Tableau contenant les éléments du sous-ensemble actuel
 * @count: Nombre d'éléments dans le sous-ensemble
 * 
 * Format: "1 2 3\n" (espace entre chaque nombre, retour à la ligne à la fin)
 */
void ft_print(int *subset, int count)
{
	if (count > 0)
	{
		int i = 0;
		
		// Afficher tous les éléments sauf le dernier avec un espace
		while (i < count - 1)
		{
			printf("%d ", subset[i]);
			i++;
		}
		
		// Afficher le dernier élément sans espace, puis retour à la ligne
		printf("%d\n", subset[count - 1]);
	}
}

/*
 * ft_count - Calcule la SOMME de tous les éléments du tableau
 * @subset: Tableau contenant les éléments
 * @count: Nombre d'éléments dans le tableau
 * 
 * Return: La somme totale
 */
int ft_count(int *subset, int count)
{
	int result = 0;
	int i = 0;
	
	while (i < count)
	{
		result = result + subset[i];
		i++;
	}
	
	return result;
}

/*
 * ft_map - FONCTION RÉCURSIVE DE BACKTRACKING
 * 
 * @result: La valeur cible à atteindre
 * @tab: Tableau contenant tous les nombres disponibles
 * @subset: Tableau pour stocker le sous-ensemble actuel
 * @count: Nombre d'éléments actuellement dans subset
 * @i: Index actuel dans le tableau tab (position de décision)
 * @size: Taille totale du tableau tab
 * 
 * PRINCIPE DU BACKTRACKING:
 * 1. CAS DE BASE: Si on a traité tous les nombres (i == size)
 *    - Vérifier si la somme du sous-ensemble actuel == résultat cible
 *    - Si oui, afficher le sous-ensemble
 * 
 * 2. CAS RÉCURSIF: Pour chaque nombre à l'index i, on a 2 choix:
 *    
 *    CHOIX 1: PRENDRE le nombre tab[i]
 *    - Ajouter tab[i] au tableau subset à la position count
 *    - Appel récursif pour traiter le nombre suivant (i+1) avec count+1
 *    - Pas besoin de retirer explicitement (backtrack automatique)
 *    
 *    CHOIX 2: NE PAS PRENDRE le nombre tab[i]
 *    - Appel récursif pour traiter le nombre suivant (i+1)
 *    - Sans modifier le tableau subset ni count
 * 
 * Exemple visuel avec [1, 2] pour trouver somme = 3:
 * 
 *                      [] count=0
 *                    /              \
 *              prendre 1          ignorer 1
 *              [1] count=1        [] count=0
 *               /      \            /        \
 *         +2        -2         +2          -2
 *      [1,2]      [1]         [2]          []
 *      count=2   count=1    count=1     count=0
 *         ✓         ✗          ✗           ✗
 *      (somme=3)
 * 
 * AVANTAGES de la version tableau:
 * - Plus simple: pas de malloc/free pour chaque élément
 * - Plus rapide: accès direct par indice
 * - Moins de code: pas de gestion de liste chaînée
 * - Backtracking implicite: on ne modifie pas le tableau en descendant dans l'autre branche
 */
void ft_map(int result, int *tab, int *subset, int count, int i, int size)
{
	// CAS DE BASE: On a parcouru tous les nombres
	if (i == size)
	{
		// Si la somme du sous-ensemble actuel égale la cible, on l'affiche
		if (ft_count(subset, count) == result)
			ft_print(subset, count);
		return ;
	}
	
	// BRANCHE 1: On PREND le nombre à l'index i
	subset[count] = tab[i];          // Ajouter à la position count
	ft_map(result, tab, subset, count + 1, i + 1, size);  // Explorer avec count+1
	// Pas besoin de retirer: le backtracking est automatique
	// car on ne touche plus à subset[count] dans la branche suivante
	
	// BRANCHE 2: On NE PREND PAS le nombre à l'index i
	ft_map(result, tab, subset, count, i + 1, size);  // Continuer sans l'ajouter
}

/*
 * main - Point d'entrée du programme
 * 
 * Usage: ./powerset <cible> <nombre1> <nombre2> ... <nombreN>
 * Exemple: ./powerset 5 1 2 3 4 5
 * 
 * Processus:
 * 1. Lire la cible (argv[1])
 * 2. Lire tous les nombres dans un tableau (argv[2] à argv[argc-1])
 * 3. Allouer un tableau pour stocker les sous-ensembles temporaires
 * 4. Lancer le backtracking avec ft_map
 */
int main(int argc, char **argv)
{
	// Vérifier qu'on a au moins un argument (la cible)
	if (argc >= 2)
	{
		// Convertir le premier argument en nombre (la cible)
		int result = atoi(argv[1]);
		
		// Calculer le nombre d'éléments disponibles
		int nb_elements = argc - 2;  // On ignore argv[0] et argv[1]
		
		// Allouer un tableau pour stocker tous les nombres disponibles
		int *tab = malloc(sizeof(int) * nb_elements);
		
		// Allouer un tableau pour stocker le sous-ensemble actuel
		// Taille max = nb_elements (si on prend tous les nombres)
		int *subset = malloc(sizeof(int) * nb_elements);
		
		// Remplir le tableau tab avec les nombres convertis depuis argv
		int i = 0;
		while (i < nb_elements)
		{
			tab[i] = atoi(argv[i + 2]);  // argv[2], argv[3], etc.
			i++;
		}
		
		// Lancer l'algorithme de backtracking
		// - result: la cible
		// - tab: tous les nombres disponibles
		// - subset: tableau vide pour stocker le sous-ensemble actuel
		// - 0: count initial (0 éléments dans subset)
		// - 0: index initial (commence au premier nombre)
		// - nb_elements: taille totale
		ft_map(result, tab, subset, 0, 0, nb_elements);
		
		// Libérer la mémoire
		free(tab);
		free(subset);
	}
	
	return 0;
}
