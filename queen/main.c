#include "h.h"

int ft_check(char **tab, int i, int j)
{
	(void)tab;
	(void)i;
	(void)j;
	int x = 0;
	int y = 0;
	while (tab[i][y])
	{
		if (tab[i][y] == 'Q' && y != j)
			return (0);
		y++;
	}

	y = 0;
	while (tab[x])
	{
		if (tab[x][j] == 'Q' && x != i)
			return (0);
		x++;
	}

	x = 0;

	return (1);
}

int ft_check_diag(char **tab, int i, int j)
{
	int size = strlen(tab[0]);
	int x = i;
	int y = j;
	int d = 1;
	while (tab[x])
	{
		while (tab[x][y])
		{
			if (tab[x][y] == 'Q')
			{
				while (d < size)
				{
					if ((x - d >= 0) && (x - d < size) && y - d >=0 && (y - d < size) && tab[x - d][y - d] == 'Q')
						return (0);
					if ((x + d >= 0) && (x + d < size) && y - d >=0 && (y - d < size) && tab[x + d][y - d] == 'Q')
						return (0);
					if ((x - d >= 0) && (x - d < size) && y + d >=0 && (y + d < size) && tab[x - d][y + d] == 'Q')
						return (0);
					if ((x + d >= 0) && (x + d < size) && y + d >= 0 &&(y + d < size) && tab[x + d][y + d] == 'Q')
						return (0);
					d++;
				}
				d = 1;
			}
			y++;
		}
		y = 0;
		x++;
	}
	return (1);
}

int ft_check_valid(char **tab)
{
	int i = 0;
	int j = 0;
	while (tab[i])
	{
		while (tab[i][j])
		{
			if (tab[i][j] == 'Q' && ft_check(tab, i, j) == 0)
			{
				return (0);
			}
			if (tab[i][j] == 'Q' && ft_check_diag(tab, i, j) == 0)
			{
				return (0);
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (1);
}

int ft_map(char **tab, int i, int size)
{
	int count = 0;
	// int p = 0;
	if (i == size)
	{
		if (ft_check_valid(tab) == 1)
		{
			// while (tab[p])
			// {
			// 	printf("%s\n", tab[p]);
			// 	p++;
			// }
			// printf("\n");
			return (1);
		}
		return (0);
	}

	for (int col = 0; col < size; col++)
	{
		if (ft_check_valid(tab) == 1)
		{
			tab[i][col] = 'Q';
			count = count + ft_map(tab, i+1, size);
			tab[i][col] = '.';
		}
	}
	return(count);
}

int main(int argc, char **argv)
{
	if (argc == 2)
	{
		int i = 0;
		int j = 0;
		int size = atoi(argv[1]);
		char **tab = malloc(sizeof(char *) * size);
		while (i < size)
		{
			tab[i] = malloc(sizeof(char) * size + 1);
			i++;
		}

		i = 0;

		while (i < size)
		{
			while (j < size)
			{
				tab[i][j] = '.';
				j++;
			}
			tab[i][j] = '\0';
			j = 0;
			i++;
		}
		tab[i] = 0;

		i = 0;
		// tab[0][2] = 'Q';
		// tab[1][0] = 'Q';
		// tab[2][3] = 'Q';
		// tab[3][1] = 'Q';

		// int p = 0;
		// while (tab[p])
		// {
		// 	printf("%s\n", tab[p]);
		// 	p++;
		// }
		// printf("\n");
		int test = ft_map(tab, 0, size);
		printf("count:%d\n", test);
		// while (tab[i])
		// {
		// 	printf("%s\n", tab[i]);
		// 	i++;
		// }
		// ft_map(tab, 0);
		// if (ft_check_valid(tab) == 1)
		// {
		// 	printf("ok\n");
		// }
		// else
		// 	printf("no\n");
	}
}