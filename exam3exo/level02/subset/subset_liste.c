
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

//structure de liste chaînee pour stocker dynamiquement les nombres du sous-ensemble actuel
typedef struct s_list
{
	int val;               //la valeur du nœud
	struct s_list *next;   //pointeur vers le nœud suivant
} t_list;

//ft_lst - cree un nouveau nœud de liste
//val: la valeur à stocker dans le nœud
//Return: pointeur vers le nouveau nœud alloue
t_list *ft_lst(int val)
{
	t_list *new = malloc(sizeof(t_list));
	
	new->val = val;
	new->next = NULL;
	
	return new;
}

//ft_add - ajoute un element À LA FIN de la liste chaînee
//lst: double pointeur vers le debut de la liste
//val: la valeur à ajouter
//Note: utilise un pointeur temporaire pour garder la tête de liste
void ft_add(t_list **lst, int val)
{
	//cas 1: la liste est vide, on cree le premier element
	if (!(*lst))
	{
		(*lst) = ft_lst(val);
		return ;
	}
	
	//cas 2: la liste n'est pas vide
	t_list *temp = *lst;  //sauvegarde de la tête de liste
	
	//parcourir jusqu'au dernier nœud
	while ((*lst)->next)
	{
		(*lst) = (*lst)->next;
	}
	
	//ajouter le nouveau nœud à la fin
	(*lst)->next = ft_lst(val);
	
	//restaurer la tête de liste
	(*lst) = temp;
}

//ft_pop - retire le DERNIER element de la liste
//lst: double pointeur vers le debut de la liste
//Important: Utilise dans le backtracking pour "defaire" un choix
void ft_pop(t_list **lst)
{
	if (*lst)
	{
		//cas special: Un seul element dans la liste
		if (!(*lst)->next)
		{
			(*lst) = NULL;
			return ;
		}
		
		t_list *temp = *lst;  //sauvegarde de la tête
		t_list *test = *lst;  //pour trouver l'avant-dernier
		
		test = test->next;
		
		//avancer jusqu'à l'avant-dernier nœud
		while (test->next)
		{
			test = test->next;
			(*lst) = (*lst)->next;
		}
		
		//supprimer le lien vers le dernier nœud
		(*lst)->next = NULL;
		
		//restaurer la tête de liste
		(*lst) = temp;
	}
}

//ft_size - calcule la taille de la liste
//lst: pointeur vers le debut de la liste
//Return: nombre d'elements dans la liste
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

//ft_print - affiche tous les elements de la liste separes par des espaces
//lst: pointeur vers le debut de la liste
//Format: "1 2 3\n" (espace entre chaque nombre, retour à la ligne à la fin)
void ft_print(t_list *lst)
{
	if (lst)
	{
		int size = ft_size(lst);
		int i = 0;
		
		//afficher tous les elements sauf le dernier avec un espace
		while (i < size - 1)
		{
			printf("%d ", lst->val);
			lst = lst->next;
			i++;
		}
		
		//afficher le dernier element sans espace, puis retour à la ligne
		printf("%d\n", lst->val);
	}
}

//ft_count - calcule la SOMME de tous les elements de la liste
//lst: pointeur vers le debut de la liste
//Return: la somme totale
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

//ft_map - FONCTION ReCURSIVE DE BACKTRACKING
//
//result: La valeur cible à atteindre
//tab: Tableau contenant tous les nombres disponibles
//node: Liste chaînee representant le sous-ensemble actuel
//i: Index actuel dans le tableau (position de decision)
//size: Taille totale du tableau
//
//PRINCIPE DU BACKTRACKING:
//1. CAS DE BASE: si on a traite tous les nombres (i == size)
//   - verifier si la somme du sous-ensemble actuel == resultat cible
//   - si oui, afficher le sous-ensemble
//
//2. CAS ReCURSIF: pour chaque nombre à l'index i, on a 2 choix:
//   
//   CHOIX 1: PRENDRE le nombre tab[i]
//   - ajouter tab[i] à la liste (ft_add)
//   - appel recursif pour traiter le nombre suivant (i+1)
//   - retirer tab[i] de la liste (ft_pop) <- BACKTRACK!
//   
//   CHOIX 2: NE PAS PRENDRE le nombre tab[i]
//   - appel recursif pour traiter le nombre suivant (i+1)
//   - sans modifier la liste
void ft_map(int result, int *tab, t_list *node, int i, int size)
{
	//CAS DE BASE: on a parcouru tous les nombres
	if (i == size)
	{
		//si la somme du sous-ensemble actuel egale la cible, on l'affiche
		if (ft_count(node) == result)
			ft_print(node);
		return ;
	}
	
	//BRANCHE 1: on PREND le nombre à l'index i
	ft_add(&node, tab[i]);           //ajouter à la liste
	ft_map(result, tab, node, i+1, size);  //explorer cette branche
	ft_pop(&node);                   //BACKTRACK: retirer le nombre
	
	//BRANCHE 2: on NE PREND PAS le nombre à l'index i
	ft_map(result, tab, node, i+1, size);  //continuer sans l'ajouter
}

//./powerset <cible> <nombre1> <nombre2> ... <nombreN>
//exemple: ./powerset 5 1 2 3 4 5
//processus:
//1. lire la cible (argv[1])
//2. lire tous les nombres dans un tableau (argv[2] à argv[argc-1])
//3. lancer le backtracking avec ft_map
int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	
	//initialiser une liste vide pour stocker les sous-ensembles
	t_list *node = NULL;
	
	//verifier qu'on a au moins un argument (la cible)
	if (argc >= 2)
	{
		//convertir le premier argument en nombre (la cible)
		int result = atoi(argv[1]);
		
		//allouer un tableau pour stocker tous les nombres disponibles
		//argc - 2 car on ignore argv[0] (nom du programme) et argv[1] (la cible)
		int *tab = malloc(sizeof(int) * (argc - 2));
		
		//remplir le tableau avec les nombres convertis depuis argv
		int i = 0;
		while (i < argc - 2)
		{
			tab[i] = atoi(argv[i + 2]);  //argv[2], argv[3], etc.
			i++;
		}
		
		//lancer l'algorithme de backtracking
		//commence à l'index 0 avec une liste vide
		ft_map(result, tab, node, 0, argc - 2);
	}
	
	return 0;
}
