#include "h.h"

typedef struct s_list
{
	int val;
	struct s_list *next;
}t_list;

t_list *ft_lst(int val)
{
	t_list *new = malloc(sizeof(t_list));

	new->val = val;
	new->next = NULL;

	return (new);
}

void ft_add(t_list **lst, int val)
{
	t_list *temp = *lst;

	if (!(*lst))
	{
		*lst = ft_lst(val);
		return ;
	}
	while ((*lst)->next)
	{
		(*lst) = (*lst)->next;
	}
	(*lst)->next = ft_lst(val);
	(*lst) = temp;
}

void ft_pop(t_list **lst)
{

	if (*lst)
	{
		t_list *temp = *lst;
		t_list *test = *lst;
		if (!(*lst)->next)
		{
			(*lst) = NULL;
			return ;
		}
		test = test->next;
		while (test->next)
		{
			test = test->next;
			(*lst) = (*lst)->next;
		}
		(*lst)->next = NULL;
		(*lst) = temp;		
	}
}

int ft_size(t_list *lst)
{
	int size = 0;
	while (lst)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}

void ft_print(t_list *lst)
{
	int size = ft_size(lst);
	int i = 0;
	while (i < size - 1)
	{
		printf("%d ", lst->val);
		lst = lst->next;
		i++;
	}
	printf("%d\n", lst->val);
}

void ft_map(int max, int sizemax, int i, t_list **node)
{
	if (ft_size(*node) == sizemax)
	{
		ft_print(*node);
		return ;
	}
	// ft_add(node, i);
	// ft_map(max, sizemax, i+1, node);
	// // ft_add(node, n);
	// // ft_map(n, k, i+1, node);
	// ft_pop(node);
	// // size--;
	// ft_map(max, sizemax, i+1, node);
	while (i <= max)
	{
		ft_add(node, i);
		ft_map(max, sizemax, i+1, node);
		ft_pop(node);
		i++;
	}
}

int ft_count(t_list *lst)
{
	int result = 0;
	while (lst)
	{
		result = result + lst->val;
		lst = lst->next;
	}
	return (result);
}

// void ft_map(int result, int *tab, int i, t_list **node, int size)
// {
// 	if (i == size)
// 	{
// 		if (ft_count(*node) == result)
// 			ft_print(*node);
// 		return ;
// 	}
// 	ft_add(node, tab[i]);
// 	ft_map(result, tab, i+1, node, size);
// 	// ft_add(node, n);
// 	// ft_map(n, k, i+1, node);
// 	ft_pop(node);
// 	// size--;
// 	ft_map(result, tab, i+1, node, size);
// }
int main(int argc, char **argv)
{
	(void)argv;
	if (argc == 3)
	{
		t_list *node;
		node = NULL;

		// int *tab = malloc(sizeof(int) * argc-2);
		// int i = 0;
		// while(i < argc-2)
		// {
		// 	tab[i] = atoi(argv[i+2]);
		// 	i++;
		// }
		// int result = atoi(argv[1]);

		// ft_map(result, tab, 0, &node, argc-2);
		// ft_add(&node, 1);
		// ft_add(&node, 2);
		// ft_add(&node, 5);

		// ft_pop(&node);
		// ft_pop(&node);
		// ft_pop(&node);
		// ft_pop(&node);
		// ft_print(node);
		ft_map(atoi(argv[1]), atoi(argv[2]), 1, &node);
	}
	return (0);
}