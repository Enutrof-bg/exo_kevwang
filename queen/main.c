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
			j++;
		}
		i++;
	}
	return (1);
}

void ft_map(char **tab, int i)
{
	int p = 0;
	if (i == 4)
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

	for (int col = 0; col< 4; col++)
	{
		if (ft_check_valid(tab) == 1)
		{
			tab[i][col] = 'Q';
			ft_map(tab, i+1);
			tab[i][col] = '.';
		}
	}
}

int main()
{
	int i = 0;
	int j = 0;
	char **tab = malloc(sizeof(char *) * 5);
	while (i< 4)
	{
		tab[i] = malloc(sizeof(char) * 5);
		i++;
	}

	i = 0;

	while (tab[i])
	{
		while (j < 4)
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
	// tab[0][3] = 'Q';
	// tab[2][1] = 'Q';
	ft_map(tab, 0);
	while (tab[i])
	{
		printf("%s\n", tab[i]);
		i++;
	}
	ft_map(tab, 0);
	// if (ft_check_valid(tab) == 1)
	// {
	// 	printf("ok\n");
	// }
	// else
	// 	printf("no\n");
}