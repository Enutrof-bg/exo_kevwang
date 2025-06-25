

#include "h.h"

int ft_power(int nb, int power)
{
	int i = 0;
	int result = 1;

	if (power < 0)
		return (0);
	if (nb == 0 && power == 0)
		return (0);
	while (i < power)
	{
		result = result * nb;
		i++;
	}
	return (result);
}

void ft_print_tab(int *set, int size)
{
	int i = 0;
	while (i < size - 1)
	{
		printf("%d ", set[i]);
		i++;
	}
	printf("%d\n", set[i]);
}

void ft_print_big(int **tab)
{
	int i = 0;
	while (tab[i])
	{
		// ft_print_tab(tab[i], sizeof(*tab[i]) / sizeof(int));
		ft_print_tab(tab[i], 3);
		i++;
	}
}

void ft_add(int *ret, int val)
{
	int i = 0;
	while (ret[i])
	{
		i++;
	}
	ret[i] = val;
}

void ft_pop(int *ret)
{
	int i = 0;
	while (ret[i])
		i++;
	i--;
	ret[i] = 0;
}

void ft_lst(int **tab, int *new)
{
	int i = 0;
	int *temp;

	temp = malloc(sizeof(int) * 3);
	while (new[i])
	{
		temp[i] = new[i];
		i++;
	}
	i = 0;
	while (tab[i])
	{
		i++;
	}
	tab[i] = temp;
}

int ft_len(int *t)
{
	int i = 0;
	while (t[i])
		i++;
	return (i);
}

void backtrack(int *set, int *ret, int i, int **tab)
{
	// if (i == 2)
		// ft_lst(tab, ret);
	if (i == 3)
	{
		ft_lst(tab, ret);
		return ;
	}
	// int x;
	// while (i < 3)
	// {
		// x++;
		// backtrack(set,ret, x, tab);
		// x++;
		ft_add(ret, set[i]);
		
		// i++;
		backtrack(set,ret, i+1, tab);
		ft_pop(ret);
		// i++;
		backtrack(set,ret, i+1, tab);
	// }
}

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	
	int set[3] = {1,2,3};
	// ft_print_tab(set, 3);
	int *ret = malloc(sizeof(int) * (sizeof(set) / sizeof(int)));
	// printf("%d\n",ft_power(2,3));
	int **tab = malloc(sizeof(int *) * (sizeof(ft_power(2, (sizeof(set) / sizeof(int))))));
	// ft_lst(tab, ret);
	// ft_add(ret, 11);
	// ft_add(ret, 12);
	// ft_print_tab(ret, 3);
	// ft_lst(tab, ret);
	// ft_pop(ret);
	// ft_lst(tab, ret);
	// ft_print_big(tab);
	backtrack(set, ret, 0, tab);
	// backtrack(set, ret, 3, tab);
	ft_print_big(tab);
	// printf("%lu\n", sizeof(set) / sizeof(int));

}