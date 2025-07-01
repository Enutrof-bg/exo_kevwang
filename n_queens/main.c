#include "h.h"


void ft_print_2(char **tab)
{
	int i = 0;
	int j = 0;
	int len = strlen(tab[0]);
	while (tab[i])
	{
		while (tab[i][j])
		{
			if (tab[i][j] == 'Q' && i < len -1)
			{
				printf("%d ", j);
			}
			else if (tab[i][j] == 'Q' && i >= len -1)
			{
				printf("%d\n", j);
			}
			j++;
		}
		j= 0;
		i++;
	}
}

void ft_print(char **tab)
{
	int i = 0;
	while (tab[i])
	{
		printf("%s\n", tab[i]);
		i++;
	}
	printf("\n");
}

int ft_check_diag(char **tab, int i, int j)
{
	int d = 1;
	int size = strlen(tab[0]);
	//int x = 0;
	//int y = 0;

	if (tab[i][j] == 'Q')
	{
		while (d < size)
		{
			if (i - d >= 0 && j - d >= 0 && i - d < size && j -d < size && tab[i-d][j-d] == 'Q')
				return (0);
			if (i + d >= 0 && j - d >= 0 && i + d < size && j -d < size && tab[i+d][j-d] == 'Q')
				return (0);
			if (i - d >= 0 && j + d >= 0 && i - d < size && j +d < size && tab[i-d][j+d] == 'Q')
				return (0);
			if (i + d >= 0 && j + d >= 0 && i + d < size && j + d < size && tab[i+d][j+d] == 'Q')
				return (0);

			d++;
		}
	}
	return (1);
}

int ft_check(char **tab, int i, int j)
{
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
				return (0);
			if (tab[i][j] == 'Q' && ft_check_diag(tab, i, j) == 0)
				return (0);
			j++;
		}
		j = 0;
		i++;
	}
	return (1);
}

void ft_map(char **tab, int i, int size)
{
	if (i == size)
	{
		if (ft_check_valid(tab) == 1)
		{
			ft_print_2(tab);
			// ft_print(tab);
		}
		return ;
	}
	for (int col = 0; col < size; col++)
	{
		if (ft_check_valid(tab) == 1)
		{
			tab[col][i] = 'Q';
			ft_map(tab, i+1, size);
			tab[col][i] = '.';
		}
	}


}

int main(int argc, char **argv)
{
	if (argc == 2)
	{
		int size = atoi(argv[1]);
		char **tab = malloc(sizeof(char *) * size + 1);
		int i = 0;
		while (i < size)
		{
			tab[i] = malloc(sizeof(char) * size + 1);
			i++;
		}

		i = 0;
		int j = 0;
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
		tab[i] = NULL;
		// ft_print(tab);

		ft_map(tab, 0, size);

	}

}