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
	int d = 0;
	// while (tab[x])
	// {
	// 	while (tab[x][y])
	// 	{
			if (tab[x][y] == 'Q')
			{
				while (d < size)
				{
					if (tab[x - d][y - d] == 'Q' && x-d >=0 && x-d<=3 && y-d >=0 && y-d <=3)
						return (0);
					if (tab[x + d][y - d] == 'Q' && x+d >=0 && x+d<=3 && y-d >=0 && y-d <=3)
						return (0);
					if (tab[x - d][y + d] == 'Q' && x-d >=0 && x-d<=3 && y+d >=0 && y+d <=3)
						return (0);
					if (tab[x + d][y + d] == 'Q' && x+d >=0 && x+d<=3 && y+d >=0 && y+d <=3)
						return (0);
					d++;
				}
		// 	}
		// 	y++;
		// }
		// x++;
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
			// else if (tab[i][j] == 'Q' && ft_check_diag(tab, i, j) == 0)
			// {
			// 	return (0);
			// }
			j++;
		}
		j = 0;
		i++;
	}
	return (1);
}

void ft_map(char **tab, int i, int size)
{
	int p = 0;
	if (i == size)
	{
		if (ft_check_valid(tab) == 1)
		{
			while (tab[p])
			{
				printf("%s\n", tab[p]);
				p++;
			}
			printf("\n");
		}
		return ;
	}

	for (int col = 0; col < size; col++)
	{
		if (ft_check_valid(tab) == 1)
		{
			tab[i][col] = 'Q';
			ft_map(tab, i+1, size);
			tab[i][col] = '.';
		}
	}
}

int main(int argc, char **argv)
{
	if (argc == 2)
	{
		int i = 0;
		int j = 0;
		int size = atoi(argv[1]);
		char **tab = malloc(sizeof(char *) * size);
		while (i< size)
		{
			tab[i] = malloc(sizeof(char) * size);
			i++;
		}

		i = 0;

		while (tab[i])
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
		// tab[1][2] = 'Q';
		// tab[3][0] = 'Q';
		ft_map(tab, 0, size);
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