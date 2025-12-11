#include "h.h"

/*
 * PROGRAMME: Générateur de permutations
 * ======================================
 * Ce programme génère toutes les permutations uniques d'une chaîne de caractères
 * passée en argument, en utilisant une liste chaînée pour construire chaque permutation.
 */

// Structure de liste chaînée pour stocker les caractères
typedef struct s_list
{
	char val;              // Valeur du caractère
	struct s_list *next;   // Pointeur vers le prochain élément
} t_list;

/*
 * ft_lst : Crée un nouveau noeud de liste
 * ---------------------------------------
 * Paramètres:
 *   - val: le caractère à stocker dans le noeud
 * Retour: un pointeur vers le nouveau noeud alloué
 */
t_list *ft_lst(char val)
{
	t_list *new = malloc(sizeof(t_list));
	
	new->val = val;      // Stocke le caractère
	new->next = NULL;    // Le prochain élément est NULL (fin de liste)

	return new;
}

/*
 * ft_add : Ajoute un élément à la fin de la liste
 * ------------------------------------------------
 * Paramètres:
 *   - lst: pointeur vers le pointeur de tête de liste
 *   - val: le caractère à ajouter
 * 
 * Fonctionnement:
 *   1. Si la liste est vide, crée le premier élément
 *   2. Sinon, parcourt jusqu'à la fin et ajoute le nouvel élément
 */
void ft_add(t_list **lst, char val)
{
	// Si la liste est vide, créer le premier élément
	if (!(*lst))
	{
		(*lst) = ft_lst(val);
		return ;
	}
	
	// Sauvegarder le début de la liste
	t_list *temp = *lst;
	
	// Parcourir jusqu'au dernier élément
	while ((*lst)->next)
	{
		(*lst) = (*lst)->next;
	}
	
	// Ajouter le nouveau noeud à la fin
	(*lst)->next = ft_lst(val);
	
	// Restaurer le pointeur au début de la liste
	(*lst) = temp;
}

/*
 * ft_pop : Supprime le dernier élément de la liste
 * -------------------------------------------------
 * Paramètres:
 *   - lst: pointeur vers le pointeur de tête de liste
 * 
 * Fonctionnement:
 *   1. Si la liste a un seul élément, le met à NULL
 *   2. Sinon, trouve l'avant-dernier élément et supprime le lien vers le dernier
 */
void ft_pop(t_list **lst)
{
	if (*lst)
	{
		// Si c'est le seul élément, vider la liste
		if (!(*lst)->next)
		{
			(*lst) = NULL;
			return ;
		}
		
		// Sauvegarder le début de la liste
		t_list *temp = *lst;
		t_list *test = *lst;

		test = test->next;
		
		// Parcourir jusqu'à l'avant-dernier élément
		while (test->next)
		{
			test = test->next;
			(*lst) = (*lst)->next;
		}
		
		// Supprimer le lien vers le dernier élément
		(*lst)->next = NULL;
		
		// Restaurer le pointeur au début
		(*lst) = temp;
	}
}

/*
 * ft_size : Calcule la taille de la liste
 * ----------------------------------------
 * Paramètres:
 *   - lst: pointeur de tête de liste
 * Retour: le nombre d'éléments dans la liste
 */
int ft_size(t_list *lst)
{
	int size = 0;
	
	// Parcourir toute la liste en comptant les éléments
	while (lst)
	{
		size++;
		lst = lst->next;
	}
	return size;
}

/*
 * ft_print : Affiche tous les caractères de la liste
 * ---------------------------------------------------
 * Paramètres:
 *   - lst: pointeur de tête de liste
 * 
 * Affiche chaque caractère de la liste suivi d'un retour à la ligne
 */
void ft_print(t_list *lst)
{
	if (lst)
	{
		int size = ft_size(lst);
		int i = 0;
		
		// Parcourir et afficher chaque caractère
		while (i < size)
		{
			write(1, &lst->val, 1);
			lst = lst->next;
			i++;
		}
		write(1, "\n", 1);  // Retour à la ligne
	}
}

/*
 * ft_check : Vérifie qu'il n'y a pas de doublons dans la liste
 * -------------------------------------------------------------
 * Paramètres:
 *   - lst: pointeur de tête de liste
 * Retour: 1 si tous les caractères sont uniques, 0 sinon
 * 
 * Cette fonction évite d'afficher les permutations avec des caractères répétés
 * à la même position (ex: si l'entrée est "aab", on ne veut pas "aab" et "aab")
 */
int ft_check(t_list *lst)
{
	char str[5000];
	int i = 0;

	// Convertir la liste en tableau de caractères
	while (lst)
	{
		str[i] = lst->val;
		i++;
		lst = lst->next;
	}
	str[i] = '\0';

	int x = 0;
	int y = 0;
	
	// Vérifier chaque paire de caractères
	while (x < i)
	{
		while (y < i)
		{
			// Si on trouve deux caractères identiques à des positions différentes
			if (str[y] == str[x] && x != y)
				return (0);  // Pas unique, retourner 0
			y++;
		}
		y = 0;
		x++;
	}
	return (1);  // Tous les caractères sont uniques
}

/*
 * ft_map : Génère récursivement toutes les permutations
 * ------------------------------------------------------
 * Paramètres:
 *   - str: la chaîne de caractères d'origine
 *   - size: la longueur de la chaîne
 *   - node: la liste chaînée en cours de construction
 *   - i: l'index actuel (profondeur de récursion)
 * 
 * Algorithme:
 *   1. Si i == size, nous avons une permutation complète
 *      -> Vérifier l'unicité et afficher si valide
 *   2. Sinon, pour chaque caractère de str:
 *      a. Ajouter le caractère à la liste
 *      b. Appeler récursivement pour la position suivante
 *      c. Retirer le caractère (backtracking)
 * 
 * Exemple avec "abc":
 *   - Ajoute 'a', recurse → Ajoute 'b', recurse → Ajoute 'c' → Affiche "abc"
 *   - Retire 'c', Ajoute 'c' (encore), recurse...
 */
void ft_map(char *str, int size, t_list *node, int i)
{
	// Cas de base: permutation complète
	if (i == size)
	{
		// Vérifier qu'il n'y a pas de doublons avant d'afficher
		if (ft_check(node) == 1)
			ft_print(node);
		return ;
	}
	
	// Pour chaque caractère dans la chaîne
	for (int x = 0; x < size; x++)
	{
		// Ajouter le caractère à la permutation actuelle
		ft_add(&node, str[x]);
		
		// Récursion pour la position suivante
		ft_map(str, size, node, i+1);
		
		// Backtracking: retirer le dernier caractère ajouté
		ft_pop(&node);	
	}
}

/*
 * ft_order : Trie la chaîne de caractères par ordre croissant
 * ------------------------------------------------------------
 * Paramètres:
 *   - str: la chaîne à trier
 * Retour: la chaîne triée
 * 
 * Utilise l'algorithme du tri à bulles (bubble sort)
 * Ceci garantit que les permutations seront affichées dans l'ordre lexicographique
 */
char *ft_order(char *str)
{
	int i = 0;
	int j = 0;
	int len = (int)strlen(str);
	char temp;
	
	// Tri à bulles
	while (i < len)
	{
		while (j < len - 1)
		{
			// Si le caractère actuel est plus grand que le suivant, échanger
			if (str[j] > str[j + 1])
			{
				temp = str[j+1];
				str[j+1] = str[j];
				str[j] = temp;
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (str);
}

/*
 * MAIN : Point d'entrée du programme
 * -----------------------------------
 * Utilisation: ./permutations "abc"
 * 
 * Le programme:
 *   1. Trie la chaîne d'entrée par ordre alphabétique
 *   2. Génère toutes les permutations possibles
 *   3. Affiche uniquement les permutations uniques (sans doublons)
 * 
 * Exemple:
 *   ./permutations "abc"
 *   Affichera: abc, acb, bac, bca, cab, cba (dans cet ordre)
 */
int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	t_list *node = NULL;  // Initialiser la liste vide
	
	// Si un argument est fourni
	if (argc >= 2)
	{
		// Trier la chaîne d'abord (pour ordre lexicographique)
		argv[1] = ft_order(argv[1]);
		
		// Générer toutes les permutations
		ft_map(argv[1], strlen(argv[1]), node, 0);
	}
	// Si aucun argument, le programme ne fait rien
}
