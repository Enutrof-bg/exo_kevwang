/*
 * POWERSET - Programme pour trouver tous les sous-ensembles dont la somme égale une valeur cible
 * 
 * Principe : Utilise le BACKTRACKING (exploration de toutes les possibilités)
 * Pour chaque nombre, on a 2 choix : le prendre OU ne pas le prendre
 * 
 * Exemple : ./powerset 3 1 0 2
 * - Cherche tous les sous-ensembles de [1, 0, 2] dont la somme = 3
 * - Résultats : [3], [0, 3], [1, 2], [1, 0, 2]
 */

#include "h.h"

// Structure de liste chaînée pour stocker dynamiquement les nombres du sous-ensemble actuel
typedef struct s_list
{
	int val;               // La valeur du nœud
	struct s_list *next;   // Pointeur vers le nœud suivant
} t_list;

/*
 * ft_lst - Crée un nouveau nœud de liste
 * @val: La valeur à stocker dans le nœud
 * 
 * Return: Pointeur vers le nouveau nœud alloué
 */
t_list *ft_lst(int val)
{
	t_list *new = malloc(sizeof(t_list));
	
	new->val = val;
	new->next = NULL;
	
	return new;
}

/*
 * ft_add - Ajoute un élément À LA FIN de la liste chaînée
 * @lst: Double pointeur vers le début de la liste
 * @val: La valeur à ajouter
 * 
 * Note: Utilise un pointeur temporaire pour garder la tête de liste
 */
void ft_add(t_list **lst, int val)
{
	// Cas 1: La liste est vide, on crée le premier élément
	if (!(*lst))
	{
		(*lst) = ft_lst(val);
		return ;
	}
	
	// Cas 2: La liste n'est pas vide
	t_list *temp = *lst;  // Sauvegarde de la tête de liste
	
	// Parcourir jusqu'au dernier nœud
	while ((*lst)->next)
	{
		(*lst) = (*lst)->next;
	}
	
	// Ajouter le nouveau nœud à la fin
	(*lst)->next = ft_lst(val);
	
	// Restaurer la tête de liste
	(*lst) = temp;
}

/*
 * ft_pop - Retire le DERNIER élément de la liste
 * @lst: Double pointeur vers le début de la liste
 * 
 * Important: Utilisé dans le backtracking pour "défaire" un choix
 */
void ft_pop(t_list **lst)
{
	if (*lst)
	{
		// Cas spécial: Un seul élément dans la liste
		if (!(*lst)->next)
		{
			(*lst) = NULL;
			return ;
		}
		
		t_list *temp = *lst;  // Sauvegarde de la tête
		t_list *test = *lst;  // Pour trouver l'avant-dernier
		
		test = test->next;
		
		// Avancer jusqu'à l'avant-dernier nœud
		while (test->next)
		{
			test = test->next;
			(*lst) = (*lst)->next;
		}
		
		// Supprimer le lien vers le dernier nœud
		(*lst)->next = NULL;
		
		// Restaurer la tête de liste
		(*lst) = temp;
	}
}

/*
 * ft_size - Calcule la taille de la liste
 * @lst: Pointeur vers le début de la liste
 * 
 * Return: Nombre d'éléments dans la liste
 */
int ft_size(t_list *lst)
{
	int size = 0;
	
	while (lst)
	{
		size++;
		lst = lst->next;
	}
	
	return size;
}

/*
 * ft_print - Affiche tous les éléments de la liste séparés par des espaces
 * @lst: Pointeur vers le début de la liste
 * 
 * Format: "1 2 3\n" (espace entre chaque nombre, retour à la ligne à la fin)
 */
void ft_print(t_list *lst)
{
	if (lst)
	{
		int size = ft_size(lst);
		int i = 0;
		
		// Afficher tous les éléments sauf le dernier avec un espace
		while (i < size - 1)
		{
			printf("%d ", lst->val);
			lst = lst->next;
			i++;
		}
		
		// Afficher le dernier élément sans espace, puis retour à la ligne
		printf("%d\n", lst->val);
	}
}

/*
 * ft_count - Calcule la SOMME de tous les éléments de la liste
 * @lst: Pointeur vers le début de la liste
 * 
 * Return: La somme totale
 */
int ft_count(t_list *lst)
{
	int result = 0;
	
	while (lst)
	{
		result = result + lst->val;
		lst = lst->next;
	}
	
	return result;
}

/*
 * ft_map - FONCTION RÉCURSIVE DE BACKTRACKING
 * 
 * @result: La valeur cible à atteindre
 * @tab: Tableau contenant tous les nombres disponibles
 * @node: Liste chaînée représentant le sous-ensemble actuel
 * @i: Index actuel dans le tableau (position de décision)
 * @size: Taille totale du tableau
 * 
 * PRINCIPE DU BACKTRACKING:
 * 1. CAS DE BASE: Si on a traité tous les nombres (i == size)
 *    - Vérifier si la somme du sous-ensemble actuel == résultat cible
 *    - Si oui, afficher le sous-ensemble
 * 
 * 2. CAS RÉCURSIF: Pour chaque nombre à l'index i, on a 2 choix:
 *    
 *    CHOIX 1: PRENDRE le nombre tab[i]
 *    - Ajouter tab[i] à la liste (ft_add)
 *    - Appel récursif pour traiter le nombre suivant (i+1)
 *    - Retirer tab[i] de la liste (ft_pop) <- BACKTRACK!
 *    
 *    CHOIX 2: NE PAS PRENDRE le nombre tab[i]
 *    - Appel récursif pour traiter le nombre suivant (i+1)
 *    - Sans modifier la liste
 * 
 * Exemple visuel avec [1, 2] pour trouver somme = 3:
 * 
 *                      []
 *                    /    \
 *              prendre 1  ignorer 1
 *                 [1]        []
 *               /    \      /    \
 *         +2      -2    +2     -2
 *        [1,2]   [1]   [2]     []
 *         ✓       ✗     ✗      ✗
 *      (somme=3)
 */
void ft_map(int result, int *tab, t_list *node, int i, int size)
{
	// CAS DE BASE: On a parcouru tous les nombres
	if (i == size)
	{
		// Si la somme du sous-ensemble actuel égale la cible, on l'affiche
		if (ft_count(node) == result)
			ft_print(node);
		return ;
	}
	
	// BRANCHE 1: On PREND le nombre à l'index i
	ft_add(&node, tab[i]);           // Ajouter à la liste
	ft_map(result, tab, node, i+1, size);  // Explorer cette branche
	ft_pop(&node);                   // BACKTRACK: retirer le nombre
	
	// BRANCHE 2: On NE PREND PAS le nombre à l'index i
	ft_map(result, tab, node, i+1, size);  // Continuer sans l'ajouter
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
 * 3. Lancer le backtracking avec ft_map
 */
int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	
	// Initialiser une liste vide pour stocker les sous-ensembles
	t_list *node = NULL;
	
	// Vérifier qu'on a au moins un argument (la cible)
	if (argc >= 2)
	{
		// Convertir le premier argument en nombre (la cible)
		int result = atoi(argv[1]);
		
		// Allouer un tableau pour stocker tous les nombres disponibles
		// argc - 2 car on ignore argv[0] (nom du programme) et argv[1] (la cible)
		int *tab = malloc(sizeof(int) * (argc - 2));
		
		// Remplir le tableau avec les nombres convertis depuis argv
		int i = 0;
		while (i < argc - 2)
		{
			tab[i] = atoi(argv[i + 2]);  // argv[2], argv[3], etc.
			i++;
		}
		
		// Lancer l'algorithme de backtracking
		// Commence à l'index 0 avec une liste vide
		ft_map(result, tab, node, 0, argc - 2);
		
		// Note: On devrait free(tab) ici pour être propre
	}
	
	return 0;
}
