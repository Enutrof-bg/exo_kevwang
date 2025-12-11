#include "h.h"

typedef struct s_list
{
	char val;
	struct s_list *next;
}t_list;

t_list *ft_lst(char val)
{
	t_list *new = malloc(sizeof(t_list));
	// struct s_list *new = malloc(sizeof(t_list));
	
	new->val = val;
	new->next = NULL;

	return new;
}

void ft_add(t_list **lst, char val)
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
		int i = 0;
		while (i < size)
		{
			write(1, &lst->val, 1);
			lst = lst->next;
			i++;
		}
		// write(1, &lst->val, 1);
		write(1, "\n", 1);
	}
}

int ft_check(t_list *lst)
{
	char str[5000];
	int i = 0;

	while (lst)
	{
		str[i] = lst->val;
		i++;
		lst = lst->next;
	}
	str[i] = '\0';

	int x = 0;
	int y = 0;
	while (x < i)
	{
		while (y < i)
		{
			if (str[y] == str[x] && x != y)
				return (0);
			y++;
		}
		y = 0;
		x++;
	}
	return (1);
}

void ft_map(char *str, int size, t_list *node, int i)
{
	if (i == size)
	{
		if (ft_check(node) == 1)
			ft_print(node);
		return ;
	}
	for (int x = 0; x < size; x++)
	{
		ft_add(&node, str[x]);
		ft_map(str, size, node, i+1);
		ft_pop(&node);	
	}
}

char *ft_order(char *str)
{
	int i = 0;
	int j = 0;
	int len = (int)strlen(str);
	char temp;
	while (i < len)
	{
		while (j < len - 1)
		{
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
		argv[1] = ft_order(argv[1]);
		ft_map(argv[1], strlen(argv[1]), node, 0);
	}
	
}