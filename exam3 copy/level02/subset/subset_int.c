
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

//ft_print - affiche tous les elements du tableau separes par des espaces
//subset: tableau contenant les elements du sous-ensemble actuel
//count: nombre d'elements dans le sous-ensemble
//
//format: "1 2 3\n" (espace entre chaque nombre, retour a la ligne a la fin)
//
void ft_print(int *subset, int count)
{
	if (count > 0)
	{
		int i = 0;
		
		//afficher tous les elements sauf le dernier avec un espace
		while (i < count - 1)
		{
			printf("%d ", subset[i]);
			i++;
		}
		
		//afficher le dernier element sans espace, puis retour a la ligne
		printf("%d\n", subset[count - 1]);
	}
}

//ft_count - Calcule la SOMME de tous les elements du tableau
// subset: Tableau contenant les elements
// count: Nombre d'elements dans le tableau
// 
// Return: La somme totale
// 
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

//ft_map - FONCTION ReCURSIVE DE BACKTRACKING
//result: La valeur cible a atteindre
//tab: Tableau contenant tous les nombres disponibles
//subset: Tableau pour stocker le sous-ensemble actuel
//count: Nombre d'elements actuellement dans subset
//i: Index actuel dans le tableau tab (position de decision)
//size: Taille totale du tableau tab
//
//PRINCIPE DU BACKTRACKING:
//1. CAS DE BASE: Si on a traite tous les nombres (i == size)
//  - verifier si la somme du sous-ensemble actuel == resultat cible
//  - si oui, afficher le sous-ensemble
//
//2. CAS RECURSIF: Pour chaque nombre a l'index i, on a 2 choix:
//  
//  CHOIX 1: PRENDRE le nombre tab[i]
//  - ajouter tab[i] au tableau subset a la position count
//  - appel recursif pour traiter le nombre suivant (i+1) avec count+1
//  - pas besoin de retirer explicitement (backtrack automatique)
//  
//  CHOIX 2: NE PAS PRENDRE le nombre tab[i]
//  - appel recursif pour traiter le nombre suivant (i+1)
//  - sans modifier le tableau subset ni count
void ft_map(int result, int *tab, int *subset, int count, int i, int size)
{
	//on a parcouru tous les nombres
	if (i == size)
	{
		//si la somme du sous-ensemble actuel egale la cible, on l'affiche
		if (ft_count(subset, count) == result)
			ft_print(subset, count);
		return ;
	}
	
	//BRANCHE 1: on PREND le nombre a l'index i
	subset[count] = tab[i];          //ajouter a la position count
	ft_map(result, tab, subset, count + 1, i + 1, size);  //explorer avec count+1
	//pas besoin de retirer: le backtracking est automatique
	//car on ne touche plus a subset[count] dans la branche suivante
	
	//BRANCHE 2: On NE PREND PAS le nombre a l'index i
	ft_map(result, tab, subset, count, i + 1, size);  //Continuer sans l'ajouter
}

//Usage: ./powerset <cible> <nombre1> <nombre2> ... <nombreN>
//Exemple: ./powerset 5 1 2 3 4 5
//
//Processus:
//1. lire la cible (argv[1])
//2. lire tous les nombres dans un tableau (argv[2] a argv[argc-1])
//3. allouer un tableau pour stocker les sous-ensembles temporaires
//4. lancer le backtracking avec ft_map
int main(int argc, char **argv)
{
	if (argc >= 2)
	{
		int result = atoi(argv[1]);
		
		//calculer le nombre d'elements disponibles
		int nb_elements = argc - 2;  //On ignore argv[0] et argv[1]
		
		//allouer un tableau pour stocker tous les nombres disponibles
		int *tab = malloc(sizeof(int) * nb_elements);
		
		//allouer un tableau pour stocker le sous-ensemble actuel
		//taille max = nb_elements (si on prend tous les nombres)
		int *subset = malloc(sizeof(int) * nb_elements);
		
		//remplir le tableau tab avec les nombres convertis depuis argv
		int i = 0;
		while (i < nb_elements)
		{
			tab[i] = atoi(argv[i + 2]);  //argv[2], argv[3], etc.
			i++;
		}
		
		//Lancer l'algorithme de backtracking
		//- result: la cible
		//- tab: tous les nombres disponibles
		//- subset: tableau vide pour stocker le sous-ensemble actuel
		//- 0: count initial (0 elements dans subset)
		//- 0: index initial (commence au premier nombre)
		//- nb_elements: taille totale
		ft_map(result, tab, subset, 0, 0, nb_elements);
	}
	
	return 0;
}
