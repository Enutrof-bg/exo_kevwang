#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct  s_point
{
   int           x;
    int           y;
}               t_point;

/*
void  flood_fill(char **tab, t_point size, t_point begin)
{

	int i = 0;
	int j = 0;
	int k = 0;
	printf("%d %d\n", begin.x, begin.y);
	char p = tab[begin.y][begin.x];
	(void)p;
	printf("%c\n", p);
	tab[begin.y][begin.x] = 'F';

	while (k < size.x * size.y)
	{
		while (i < size.y)
		{
			while (j < size.x)
			{
				if (tab[i][j] == 'F' && j+1 < size.x && tab[i][j + 1] == p)
					tab[i][j+1] = 'F';


				if (tab[i][j] == 'F' && j-1 >=0 && tab[i][j - 1] == p)
					tab[i][j-1] = 'F';


				if (tab[i][j] == 'F' && i+1 < size.y && tab[i+1][j] == p)
					tab[i + 1][j] = 'F';


				if (tab[i][j] == 'F' && i-1 >=0 && tab[i - 1][j] == p)
					tab[i - 1][j] = 'F';

				j++;
			}
			j=0;
			i++;
		}
		i = 0;
		k++;
	}
}*/

void fill_tab(char **tab, t_point size, int row, int col, char target)
{
	(void)size;
	
	if (row < 0 || row >= size.y || col < 0 || col >= size.x)
		return ;

	if (tab[row][col] == 'F' || tab[row][col] != target)
		return ;
	
	tab[row][col] = 'F';

	fill_tab(tab, size, row+1, col, target);
	fill_tab(tab, size, row-1, col, target);
	fill_tab(tab, size, row, col+1, target);
	fill_tab(tab, size, row, col-1, target);

}

void  flood_fill(char **tab, t_point size, t_point begin)
{
	char target = tab[begin.y][begin.x];

	fill_tab(tab, size, begin.y, begin.x, target);

}

int main()
{
	t_point size = {8, 5};
	t_point begin = {2,0};
	(void)size;
	(void)begin;

	char *zone[] = {
		"11111111",
		"10001001",
		"10010001",
		"10110001",
		"11100001",
		NULL
	};

	int i = 0;
	while (zone[i])
	{
		printf("%s\n", zone[i]);
		i++;
	}

	char **tab = malloc(sizeof(char *) * (size.y + 1));
	int p = 0;
	while (p < size.y)
	{
		tab[p] = malloc(sizeof(char) * (size.x));
		p++;
	}

	int l = 0;
	int j = 0;
	while (l < 5)
	{
		while (j < size.x)
		{
			tab[l][j] = zone[l][j];
			j++;
			// tab[l][j] = zone[l][j];
		}
		tab[l][j] = 0;
		j = 0;
		l++;
	}
	tab[l] = NULL;

	

	flood_fill(tab, size, begin);


	i = 0;
	while (tab[i])
	{
		printf("%s\n", tab[i]);
		i++;
	}
}