#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>


// ft_print : Affiche tous les caractères du tableau
// Paramètres:
//   - tab: tableau d'indices représentant la permutation
//   - str: chaîne de caractères d'origine
//   - size: taille du tableau
// 
// Affiche chaque caractère correspondant aux indices du tableau
void ft_print(int *tab, char *str, int size)
{
	int i = 0;
	
	// Pour chaque indice dans le tableau
	while (i < size)
	{
		// Afficher le caractère correspondant à cet indice
		write(1, &str[tab[i]], 1);
		i++;
	}
	write(1, "\n", 1);  // Retour à la ligne
}

// ft_check : Vérifie qu'il n'y a pas de doublons dans le tableau
// Paramètres:
//   - tab: tableau d'indices
//   - size: taille du tableau
// Retour: 1 si tous les indices sont uniques, 0 sinon
// 
// Cette fonction évite d'afficher les permutations avec des indices répétés
// (pour éviter les permutations invalides comme [0, 0, 1])
int ft_check(int *tab, int size)
{
	int x = 0;
	int y = 0;
	
	// Vérifier chaque paire d'indices
	while (x < size)
	{
		y = 0;
		while (y < size)
		{
			// Si on trouve deux indices identiques à des positions différentes
			if (tab[y] == tab[x] && x != y)
				return (0);  // Pas unique, retourner 0
			y++;
		}
		x++;
	}
	return (1);  // Tous les indices sont uniques
}

// ft_map : Génère récursivement toutes les permutations
// Paramètres:
//   - str: la chaîne de caractères d'origine
//   - size: la longueur de la chaîne
//   - tab: tableau d'indices en cours de construction
//   - i: l'index actuel (profondeur de récursion)
// 
// Algorithme:
//   1. Si i == size, nous avons une permutation complète
//      -> Vérifier et afficher si valide
//   2. Sinon, pour chaque position possible (0 à size-1):
//      a. Placer cet indice dans tab[i]
//      b. Appeler récursivement pour la position suivante
//      c. Nettoyer (backtracking, optionnel ici car on écrase)
// 
// Exemple avec "abc" (size=3):
//   tab[0]=0, recurse → tab[1]=0, recurse → tab[2]=0 → Check fail (doublons)
//   tab[0]=0, recurse → tab[1]=0, recurse → tab[2]=1 → Check fail (doublons)
//   tab[0]=0, recurse → tab[1]=1, recurse → tab[2]=2 → Affiche "abc"
//   etc...
void ft_map(char *str, int size, int *tab, int i)
{
	// Cas de base: permutation complète
	if (i == size)
	{
		// Vérifier qu'il n'y a pas de doublons d'indices avant d'afficher
		if (ft_check(tab, size) == 1)
			ft_print(tab, str, size);
		return ;
	}
	
	// Pour chaque indice possible (de 0 à size-1)
	for (int x = 0; x < size; x++)
	{
		// Placer cet indice à la position i
		tab[i] = x;
		
		// Récursion pour la position suivante
		ft_map(str, size, tab, i + 1);
		
		// Pas besoin de backtracking explicite car on écrase la valeur
		// à la prochaine itération ou à la sortie de la récursion
	}
}

// ft_order : Trie la chaîne de caractères par ordre croissant
// Paramètres:
//   - str: la chaîne à trier
// Retour: la chaîne triée
// 
// Utilise l'algorithme du tri à bulles (bubble sort)
// Ceci garantit que les permutations seront affichées dans l'ordre lexicographique
char *ft_order(char *str)
{
	int i = 0;
	int j = 0;
	int len = (int)strlen(str);
	char temp;
	
	// Tri à bulles
	while (i < len)
	{
		j = 0;
		while (j < len - 1)
		{
			// Si le caractère actuel est plus grand que le suivant, échanger
			if (str[j] > str[j + 1])
			{
				temp = str[j + 1];
				str[j + 1] = str[j];
				str[j] = temp;
			}
			j++;
		}
		i++;
	}
	return (str);
}

// Le programme:
//   1. Trie la chaîne d'entrée par ordre alphabétique
//   2. Génère toutes les permutations possibles via un tableau d'indices
//   3. Affiche uniquement les permutations uniques (sans doublons d'indices)
// 
// Exemple:
//   ./permutations "abc"
//   Affichera: abc, acb, bac, bca, cab, cba (dans cet ordre)
// 
// Avantages de la version avec tableau d'int:
//   - Plus simple: pas de gestion de malloc/free pour chaque noeud
//   - Plus rapide: accès direct par indice au lieu de parcourir une liste
//   - Moins de mémoire: un seul tableau réutilisé au lieu de noeuds multiples
int main(int argc, char **argv)
{
	if (argc >= 2)
	{
		int size = strlen(argv[1]);
		
		// Allocation d'un tableau d'indices (de taille size)
		int *tab = malloc(sizeof(int) * size);
		
		// Initialiser le tableau à 0
		int i = 0;
		while (i < size)
		{
			tab[i] = 0;
			i++;
		}
		
		// Trier la chaîne d'abord (pour ordre alphabétique)
		argv[1] = ft_order(argv[1]);
		
		// Générer toutes les permutations
		ft_map(argv[1], size, tab, 0);
		
		// Libérer la mémoire
		free(tab);
	}
	return (0);
}
