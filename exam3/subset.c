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

	return new;
}

void ft_add(t_list **lst, int val)
{
	if (!(*lst))
	{
		(*lst) = ft_lst(val);
		return ;
	}
	t_list *temp = *lst;
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
		if (!(*lst)->next)
		{
			(*lst) = NULL;
			return ;
		}
		t_list *temp = *lst;
		t_list *test = *lst;

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
	return size;
}

void ft_print(t_list *lst)
{
	if (lst)
	{
		int size = ft_size(lst);
		// printf("size:%d\n", size);
		int i = 0;
		while (i < size - 1)
		{
			printf("%d ", lst->val);
			lst = lst->next;
			i++;
		}
		printf("%d\n", lst->val);
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

void ft_map(int result, int *tab, t_list *node, int i, int size)
{
	if (i == size)
	{
		if (ft_count(node) == result)
			ft_print(node);
		return ;
	}
	ft_add(&node, tab[i]);
	ft_map(result, tab, node, i+1, size);
	ft_pop(&node);
	ft_map(result, tab, node, i+1, size);
}

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	t_list *node = NULL;

	// ft_add(&node, 1);
	// ft_add(&node, 2);

	// ft_add(&node, 3);

	// ft_pop(&node);
	// ft_pop(&node);
	// ft_pop(&node);
	// ft_pop(&node);
	// ft_print(node);
	
	if (argc >= 2)
	{
		int result = atoi(argv[1]);

		int *tab = malloc(sizeof(int) * (argc -2));
		int i = 0;
		while (i < argc -2)
		{
			tab[i] = atoi(argv[i+2]);
			// printf("%d\n", tab[i]);
			i++;
		}
		// (void)result;
		ft_map(result, tab, node, 0, argc -2);

	}
	
}