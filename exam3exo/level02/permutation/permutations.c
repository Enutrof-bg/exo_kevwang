#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>


//ft_print : Affiche tous les caracteres du tableau
//Parametres:
//	- tab: tableau d'indices representant la permutation
//	- str: chaîne de caracteres d'origine
//	- size: taille du tableau
//
//Affiche chaque caractere correspondant aux indices du tableau
void ft_print(int *tab, char *str, int size)
{
	int i = 0;
	
	//Pour chaque indice dans le tableau
	while (i < size)
	{
		//Afficher le caractere correspondant a cet indice
		write(1, &str[tab[i]], 1);
		i++;
	}
	write(1, "\n", 1);	//Retour a la ligne
}

//ft_check : Verifie qu'il n'y a pas de doublons dans le tableau
//parametres:
//	- tab: tableau d'indices
//	- size: taille du tableau
//retour: 1 si tous les indices sont uniques, 0 sinon
//
//cette fonction evite d'afficher les permutations avec des indices repetes
//(pour eviter les permutations invalides comme [0, 0, 1])
int ft_check(int *tab, int size)
{
	int x = 0;
	int y = 0;
	
	//verifier chaque paire d'indices
	while (x < size)
	{
		y = 0;
		while (y < size)
		{
			//si on trouve deux indices identiques a des positions differentes
			if (tab[y] == tab[x] && x != y)
				return (0);	//Pas unique, retourner 0
			y++;
		}
		x++;
	}
	return (1);	//tous les indices sont uniques
}

//ft_map : Genere recursivement toute les permutation
//Parametre:
//	- str: la chaîne de caracteres d'origine
//	- size: la longueur de la chaîne
//	- tab: tableau d'indices en cours de construction
//	- i: l'index actuel (profondeur de recursion)
//
//Algorithme:
//	1. si i == size, nous avons une permutation complete
//		 -> verifier et afficher si valide
//	2. sinon, pour chaque position possible (0 a size-1):
//		 a. placer cet indice dans tab[i]
//		 b. appeler recursivement pour la position suivante
//		 c. nettoyer (backtracking, optionnel ici car on ecrase)
//
//Exemple avec "abc" (size=3):
//	tab[0]=0, recurse → tab[1]=0, recurse → tab[2]=0 → Check fail (doublons)
//	tab[0]=0, recurse → tab[1]=0, recurse → tab[2]=1 → Check fail (doublons)
//	tab[0]=0, recurse → tab[1]=1, recurse → tab[2]=2 → Affiche "abc"
//	etc...
void ft_map(char *str, int size, int *tab, int i)
{
	//Cas de base: permutation complete
	if (i == size)
	{
		//verifier qu'il n'y a pas de doublons d'indices avant d'afficher
		if (ft_check(tab, size) == 1)
			ft_print(tab, str, size);
		return ;
	}
	
	//pour chaque indice possible (de 0 a size-1)
	for (int x = 0; x < size; x++)
	{
		//placer cet indice a la position i
		tab[i] = x;
		
		//rrecursion pour la position suivante
		ft_map(str, size, tab, i + 1);
		
		//pas besoin de backtracking explicite car on ecrase la valeur
		//a la prochaine iteration ou a la sortie de la recursion
	}
}

//ft_order : Trie la chaîne de caracteres par ordre croissant
//parametres:
//	- str: la chaîne a trier
//retour: la chaîne triee
//
//utilise l'algorithme du tri a bulles (bubble sort)
//ceci garantit que les permutations seront affichees dans l'ordre lexicographique
char *ft_order(char *str)
{
	int i = 0;
	int j = 0;
	int len = (int)strlen(str);
	char temp;
	
	//Tri a bulles
	while (i < len)
	{
		j = 0;
		while (j < len - 1)
		{
			//si le caractere actuel est plus grand que le suivant, echanger
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

//le programme:
//	1. trie la chaîne d'entree par ordre alphabetique
//	2. genere toutes les permutations possibles via un tableau d'indices
//	3. affiche uniquement les permutations uniques (sans doublons d'indices)
//
//exemple:
//	./permutations "abc"
//	affichera: abc, acb, bac, bca, cab, cba (dans cet ordre)
//
//avantages de la version avec tableau d'int:
//	- plus simple: pas de gestion de malloc/free pour chaque noeud
//	- plus rapide: acces direct par indice au lieu de parcourir une liste
//	- moins de memoire: un seul tableau reutilise au lieu de noeuds multiples
int main(int argc, char **argv)
{
	if (argc >= 2)
	{
		int size = strlen(argv[1]);
		
		//allocation d'un tableau d'indices (de taille size)
		int *tab = malloc(sizeof(int) * size);
		
		//initialiser le tableau a 0
		int i = 0;
		while (i < size)
		{
			tab[i] = 0;
			i++;
		}
		
		//trier la chaîne d'abord (pour ordre alphabetique)
		argv[1] = ft_order(argv[1]);
		
		//generer toutes les permutations
		ft_map(argv[1], size, tab, 0);
		
		//liberer la memoire
		free(tab);
	}
	return (0);
}
