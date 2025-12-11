#include "h.h"

typedef struct s_list
{
	int val;
	struct s_list *next;
}t_list;

t_list *ft_lst(int val)
{
	t_list  *new;
	new = malloc(sizeof(t_list));

	new->val = val;
	new->next = NULL;
	return (new);
}

void ft_add(t_list **lst, int val)
{
	t_list *temp = *lst;

	if (!(*lst))
	{
		(*lst) = ft_lst(val);
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

	t_list *temp = *lst;
	t_list *test = *lst;

	if (*lst)
	{
		if (!(*lst)->next)
		{
			(*lst) = NULL;
			return ;
		}
		test = test->next;
		while ((test)->next)
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
	t_list *temp = lst;
	int size = 0;

	while(temp != NULL)
	{
		size++;
		temp = temp->next;
	}
	return (size);
}

void ft_print(t_list *node0)
{

	if (node0)
	{
		t_list *test = node0;
		int size = ft_size(node0);

		int i = 0;
		while(i < size - 1)
		{
			printf("%d ", test->val);
			test = test->next;
			i++;
		}
		printf("%d\n", test->val);
	}
}

int ft_count(t_list *lst)
{
	t_list *temp = lst;
	int result = 0;

	while (lst)
	{
		result = result + lst->val;
		lst = lst->next;
	}
	lst = temp;
	return (result);
}

void ft_map(int *tab, t_list **node0, int result, int i, int size)
{
	if (i == size)
	{
		if (ft_count(*node0) == result)
		{
			ft_print(*node0);
		}
		return ;
	}
	ft_add(node0, tab[i]);
	ft_map(tab, node0, result, i+1, size);
	ft_pop(node0);
	ft_map(tab, node0, result, i+1, size);
}

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	if (argc >= 2)
	{
		t_list *node0 = NULL;
		int *tab = malloc(sizeof(int) * (argc-2));
		int i = 0;
		while (i < argc -2)
		{
			tab[i] = atoi(argv[i + 2]);
			//printf("%d\n", tab[i]);
			i++;
		}
		int result = atoi(argv[1]);
		ft_map(tab, &node0, result, 0, argc - 2);
	}
	// t_list *node1 =	ft_lst("node01");
	// t_list *node2 = ft_lst("node02");
	// t_list *node3 = ft_lst("node03");
	// t_list *nodefin = ft_lst("nodefin");

	// ft_add(&node0, 1);
	// ft_add(&node0, 2);
	// ft_add(&node0, 3);
	// ft_add(&node0, 4);
	//test01
	// ft_pop(&node0);
	// ft_pop(&node0);
	// ft_pop(&node0);
	// ft_pop(&node0);
	// ft_pop(&node0);


	// temp = node0;
	// while(temp != NULL)
	// {
	// 	printf("%d\n", temp->val);
	// 	temp = temp->next;
	// }
	return 0;
}