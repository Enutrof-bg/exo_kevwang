#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void find_subsets(int *a_int, int *a_choices, int len, int result, int sum, int i)
{
	if (i == len)
	{
		if (sum == result)
		{
			write_subset(a_int, a_choices, len);
			write(1, "\n", 1);
		}
		return ;
	}
	a_choices[i] = 0;
	find_subsets(a_int, a_choices, len, result, sum, i + 1);
	a_choices[i] = 1;
	find_subsets(a_int, a_choices, len, result, sum + a_int[i], i + 1);
}

int	main(int ac, char *av[])
{
	int	*a_int;
	int	*a_choices;
	int	i;
	int	len;

	if (ac < 2)
		return (1);
	len = ac - 2;
	i = 2;
	a_int = malloc(sizeof(int) * len);
	a_choices = malloc(sizeof(int) * len);
	if (!a_int || !a_choices)
		return (1);
	while (av[i])
	{
		if (is_valid(av[i]))
		{
			a_int[i - 2] = atoi(av[i]);
			i++;
		}
		else
			return (1);
	}
	find_subsets(a_int, a_choices, len, atoi(av[1]), 0, 0);
	free(a_int);
	free(a_choices);
	return (0);
}
