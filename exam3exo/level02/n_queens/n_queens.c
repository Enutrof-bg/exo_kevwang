
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


// verifie si une reine en position (i, j) est en conflit sur les diagonales
// parametres:
//	- tab: le plateau de jeu
//	- i, j: position de la reine à verifier
//	- size: taille du plateau
// retour: 1 si OK, 0 si conflit detecte
int ft_check_diagonale(char **tab, int i, int j, int size)
{
	int d = 1; // distance depuis la position actuelle
	
	// On verifie toutes les diagonales dans les 4 directions
	while (d < size)
	{
		// diagonale haut-gauche: on recule en ligne ET en colonne
		if (i-d >=0 && i-d <size && j-d>=0 && j-d <size && tab[i-d][j-d] == 'Q')
			return (0);
		
		// diagonale bas-gauche: on avance en ligne mais recule en colonne
		if (i+d >=0 && i+d <size && j-d>=0 && j-d <size && tab[i+d][j-d] == 'Q')
			return (0);
		
		// diagonale haut-droite: on recule en ligne mais avance en colonne
		if (i-d >=0 && i-d <size && j+d>=0 && j+d <size && tab[i-d][j+d] == 'Q')
			return (0);
		
		// diagonale bas-droite: on avance en ligne ET en colonne
		if (i+d >=0 && i+d <size && j+d>=0 && j+d <size && tab[i+d][j+d] == 'Q')
			return (0);
		
		d++; // on augmente la distance
	}
	return (1);
}

// verifie si une reine en position (i, j) est en conflit sur sa ligne et sa colonne
// Pparametres:
//   - tab: le plateau de jeu
//   - i, j: position de la reine à verifier
// retour: 1 si OK, 0 si conflit detecte
int ft_check_ligne(char **tab, int i, int j)
{
	int x = 0;
	int y = 0;
	
	// verification de la ligne i (horizontale)
	while (tab[i][y])
	{
		// S'il y a une autre reine sur la même ligne (mais pas à la même position (avec y != j) )
		if (tab[i][y] == 'Q' && y != j)
			return (0);
		y++;
	}
	
	// Verification de la colonne j (verticale)
	x = 0;
	while (tab[x])
	{
		// S'il y a une autre reine sur la même colonne (mais pas à la même position)
		if (tab[x][j] == 'Q' && x != i)
			return (0);
		x++;
	}
	
	return (1); // Aucun conflit trouve
}

//verifie si toutes les reines sur le plateau sont valides
//(pas de conflits horizontaux, verticaux ou diagonaux)
//parametres:
//	tab: le plateau de jeu
//	size: taille du plateau
//retour: 1 si la configuration est valide, 0 sinon
int ft_check(char **tab, int size)
{
	int i = 0;
	int j = 0;
	
	while (tab[i])
	{
		while (tab[i][j])
		{
			// pour chaque reine trouvee, on verifie les lignes/colonnes
			if (tab[i][j] == 'Q' && ft_check_ligne(tab, i, j) == 0)
				return (0);
			
			// pour chaque reine trouvee, on verifie les diagonales
			if (tab[i][j] == 'Q' && ft_check_diagonale(tab, i, j, size) == 0)
				return (0);
			
			j++;
		}
		j = 0;
		i++;
	}
	
	return (1); // toutes les reines sont bien placees
}

//affiche la solution trouvee
//pour chaque ligne, on affiche le numero de colonne où se trouve la reine
//parametres:
//	tab: le plateau de jeu
//	size: taille du plateau
void ft_print(char **tab, int size)
{
	int i = 0;
	int j = 0;
	
	while (tab[i])
	{
		while (tab[i][j])
		{
			//si on trouve une reine et qu'on n'est pas à la derniere ligne
			if (tab[i][j] == 'Q' && i < size - 1)
				printf("%d ", j); // Affiche avec un espace
			
			//si on trouve une reine à la derniere ligne
			if (tab[i][j] == 'Q' && i >= size - 1)
				printf("%d\n", j); //affiche avec un retour à la ligne
			
			j++;
		}
		j = 0;
		i++;
	}
}

// Fonction recursive qui essaie de placer les reines
// algorithme:
//	- i represente la colonne courante (de 0 à size-1)
//	- Pour chaque colonne, on essaie de placer une reine sur chaque ligne
//	- On passe recursivement à la colonne suivante
//	- À la fin (i == size), on verifie si c'est une solution valide
// 
// parametre:
//	- tab: le plateau de jeu
//	- i: colonne actuelle où placer une reine
//	- size: taille du plateau
void ft_map(char **tab, int i, int size)
{
	// cas de base: on a place une reine dans chaque colonne
	if (i == size)
	{
		// on verifie si c'est une solution valide
		if (ft_check(tab, size) == 1)
			ft_print(tab, size); // Si oui, on l'affiche
		return;
	}
	
	// on essaie de placer une reine sur chaque ligne de la colonne i
	for (int col = 0; col < size; col++)
	{
		tab[col][i] = 'Q';           // on place une reine à la ligne 'col', colonne 'i'
		ft_map(tab, i + 1, size);    // appel recursif pour la colonne suivante
		tab[col][i] = '.';           // backtracking: on retire la reine
	}
}

int main(int argc, char **argv)
{
	if (argc == 2)
	{
		int size = atoi(argv[1]); // Convertit l'argument en nombre
		
		// allocation du tableau 2D (size lignes + NULL à la fin)
		char **tab = malloc(sizeof(char *) * (size + 1));
		
		// allocation de chaque ligne
		int i = 0;
		while (i < size)
		{
			tab[i] = malloc(sizeof(char) * size + 1); // +1 pour le '\0'
			i++;
		}

		// initialisation du plateau avec des '.' (cases vides)
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
		tab[i] = NULL;

		// lance l'algorithme de resolution
		// on commence par la colonne 0
		ft_map(tab, 0, size);
	}
	return (0);
}
