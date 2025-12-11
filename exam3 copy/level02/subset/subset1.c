

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

void ft_print_res(int *set, int size)
{
	int i = 0;
	while (i < size - 1)
	{
		if (set[i] == 0)
		{
			printf("\n");
			return ;
		}
		printf("%d ", set[i]);
		i++;
	}
	if (set[i] != 0)
		printf("%d", set[i]);
	printf("\n");
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

int ft_check(int *ret)
{
	int i = 0;
	int result = 0;
	while (ret[i])
	{
		result = result + ret[i];
		i++;
	}
	return (result);
}

void backtrack(int *set, int *ret, int i, int target, int argc)
{

	// if (i == (sizeof(*set) / sizeof(int)))
	if (i == argc -2)
	{
		if (ft_check(ret) == target)
			ft_print_res(ret, argc -2);
		return ;
	}
		ft_add(ret, set[i]);
		
		backtrack(set,ret, i+1, target, argc);
		ft_pop(ret);
		backtrack(set,ret, i+1, target, argc);
	// }
}

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	if (argc >= 2)
	{
		// int set[3] = {1,2,3};
		int *set = malloc(sizeof(int) * (argc - 1));
		int i = 0;
		while (i < argc-1)
		{
			set[i] = atoi(argv[i+1]);
			// printf("%d\n", set[i]);
			i++;
		}
		ft_print_tab(set, argc - 1);
		printf("len:%d\n", ft_len(set));
		// int *ret = malloc(sizeof(int) * (argc - 2));
		// i = 0;
		// while (ret[i])
		// {
		// 	ret[i] = 9999;
		// 	i++;
		// }
		// printf("%d\n",ft_power(2,3));
		// int **tab = malloc(sizeof(int *) * (sizeof(ft_power(2, (sizeof(set) / sizeof(int))))));
		// ft_lst(tab, ret);
		// ft_add(ret, 11);
		// ft_add(ret, 12);
		// ft_print_tab(ret, 4);
		// ft_lst(tab, ret);
		// ft_pop(ret);
		// ft_lst(tab, ret);
		// ft_print_big(tab);
		// int target = atoi(argv[1]);
		// printf("target:%d\n", target);
		// backtrack(set, ret, 0, target, argc);
		// printf("set:%lu int:%lu", sizeof(*set) , sizeof(int));
		// backtrack(set, ret, 3, tab);
		// ft_print_big(tab);
		// printf("%lu\n", sizeof(set) / sizeof(int));
	}
}