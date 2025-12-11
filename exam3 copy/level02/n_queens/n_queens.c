
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


// Vérifie si une reine en position (i, j) est en conflit sur les diagonales
// Paramètres:
//	- tab: le plateau de jeu
//	- i, j: position de la reine à vérifier
//	- size: taille du plateau
// Retour: 1 si OK, 0 si conflit détecté
int ft_check_diagonale(char **tab, int i, int j, int size)
{
	int d = 1; // distance depuis la position actuelle
	
	// On vérifie toutes les diagonales dans les 4 directions
	while (d < size)
	{
		// Diagonale haut-gauche: on recule en ligne ET en colonne
		if (i-d >=0 && i-d <size && j-d>=0 && j-d <size && tab[i-d][j-d] == 'Q')
			return (0);
		
		// Diagonale bas-gauche: on avance en ligne mais recule en colonne
		if (i+d >=0 && i+d <size && j-d>=0 && j-d <size && tab[i+d][j-d] == 'Q')
			return (0);
		
		// Diagonale haut-droite: on recule en ligne mais avance en colonne
		if (i-d >=0 && i-d <size && j+d>=0 && j+d <size && tab[i-d][j+d] == 'Q')
			return (0);
		
		// Diagonale bas-droite: on avance en ligne ET en colonne
		if (i+d >=0 && i+d <size && j+d>=0 && j+d <size && tab[i+d][j+d] == 'Q')
			return (0);
		
		d++; // on augmente la distance
	}
	return (1);
}

// Vérifie si une reine en position (i, j) est en conflit sur sa ligne et sa colonne
// Paramètres:
//   - tab: le plateau de jeu
//   - i, j: position de la reine à vérifier
// Retour: 1 si OK, 0 si conflit détecté
int ft_check_ligne(char **tab, int i, int j)
{
	int x = 0;
	int y = 0;
	
	// Vérification de la ligne i (horizontale)
	while (tab[i][y])
	{
		// S'il y a une autre reine sur la même ligne (mais pas à la même position (avec y != j) )
		if (tab[i][y] == 'Q' && y != j)
			return (0);
		y++;
	}
	
	// Vérification de la colonne j (verticale)
	x = 0;
	while (tab[x])
	{
		// S'il y a une autre reine sur la même colonne (mais pas à la même position)
		if (tab[x][j] == 'Q' && x != i)
			return (0);
		x++;
	}
	
	return (1); // Aucun conflit trouvé
}

// Vérifie si toutes les reines sur le plateau sont valides
// (pas de conflits horizontaux, verticaux ou diagonaux)
// Paramètres:
//	- tab: le plateau de jeu
//	- size: taille du plateau
// Retour: 1 si la configuration est valide, 0 sinon
int ft_check(char **tab, int size)
{
	int i = 0;
	int j = 0;
	
	while (tab[i])
	{
		while (tab[i][j])
		{
			// Pour chaque reine trouvée, on vérifie les lignes/colonnes
			if (tab[i][j] == 'Q' && ft_check_ligne(tab, i, j) == 0)
				return (0);
			
			// Pour chaque reine trouvée, on vérifie les diagonales
			if (tab[i][j] == 'Q' && ft_check_diagonale(tab, i, j, size) == 0)
				return (0);
			
			j++;
		}
		j = 0;
		i++;
	}
	
	return (1); // Toutes les reines sont bien placées
}

// Affiche la solution trouvée
// Pour chaque ligne, on affiche le numéro de colonne où se trouve la reine
// Paramètres:
//	- tab: le plateau de jeu
//	- size: taille du plateau
void ft_print(char **tab, int size)
{
	int i = 0;
	int j = 0;
	
	while (tab[i])
	{
		while (tab[i][j])
		{
			// Si on trouve une reine et qu'on n'est pas à la dernière ligne
			if (tab[i][j] == 'Q' && i < size - 1)
				printf("%d ", j); // Affiche avec un espace
			
			// Si on trouve une reine à la dernière ligne
			if (tab[i][j] == 'Q' && i >= size - 1)
				printf("%d\n", j); // Affiche avec un retour à la ligne
			
			j++;
		}
		j = 0;
		i++;
	}
}

// Fonction récursive qui essaie de placer les reines
// Algorithme:
//	- i représente la colonne courante (de 0 à size-1)
//	- Pour chaque colonne, on essaie de placer une reine sur chaque ligne
//	- On passe récursivement à la colonne suivante
//	- À la fin (i == size), on vérifie si c'est une solution valide
// 
// Paramètres:
//	- tab: le plateau de jeu
//	- i: colonne actuelle où placer une reine
//	- size: taille du plateau
void ft_map(char **tab, int i, int size)
{
	// Cas de base: on a placé une reine dans chaque colonne
	if (i == size)
	{
		// On vérifie si c'est une solution valide
		if (ft_check(tab, size) == 1)
			ft_print(tab, size); // Si oui, on l'affiche
		return;
	}
	
	// On essaie de placer une reine sur chaque ligne de la colonne i
	for (int col = 0; col < size; col++)
	{
		tab[col][i] = 'Q';           // On place une reine à la ligne 'col', colonne 'i'
		ft_map(tab, i + 1, size);    // Appel récursif pour la colonne suivante
		tab[col][i] = '.';           // Backtracking: on retire la reine
	}
}

int main(int argc, char **argv)
{
	if (argc == 2)
	{
		int size = atoi(argv[1]); // Convertit l'argument en nombre
		
		// Allocation du tableau 2D (size lignes + NULL à la fin)
		char **tab = malloc(sizeof(char *) * (size + 1));
		
		// Allocation de chaque ligne
		int i = 0;
		while (i < size)
		{
			tab[i] = malloc(sizeof(char) * size + 1); // +1 pour le '\0'
			i++;
		}

		// Initialisation du plateau avec des '.' (cases vides)
		i = 0;
		int j = 0;
		while (i < size)
		{
			while (j < size)
			{
				tab[i][j] = '.';
				j++;
			}
			tab[i][j] = '\0'; 
			j = 0;
			i++;
		}
		tab[i] = NULL;// Marque la fin du tableau de chaînes

		// Lance l'algorithme de résolution
		// On commence par la colonne 0
		ft_map(tab, 0, size);
	}
	return (0);
}
