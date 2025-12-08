#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct s_map
{
	/* data */
	int nbr_line;
	char empty;
	char obastacle;
	char full;

	char** board;
	int i;
	int j;
	int min;


}t_map;

void ft_print(t_map *map)
{
	int i = 0;
	while (map->board[i])
	{
		printf("%s", map->board[i]);
		i++;
	}
}
int ft_min(int a, int b, int c)
{
	int min = a;
	if (min > b)
		min = b;
	if (min > c)
		min = c;
	return min;
}


int getElem(FILE *fd, t_map *map)
{
	int ret = fscanf(fd, "%d%c%c%c",
		&(map->nbr_line), &(map->empty), &(map->obastacle), &(map->full));
	(void)ret;
	if (ret != 4)
		return -1;
	if (map->nbr_line <= 0)
		return -1;
	if (map->empty < 26 || map->empty > 126)
		return -1;
	if (map->full < 26 || map->full > 126)
		return -1;
	if (map->obastacle < 26 || map->obastacle > 126)
		return -1;
	if (map->empty == map->obastacle || map->obastacle == map->full || map->obastacle == map->empty)
		return -1;
	// printf("%d %c %c %c", map->nbr_line, map->empty, map->obastacle, map->full);

	map->board = malloc(sizeof(char *) * map->nbr_line + 1);
	map->board[map->nbr_line] = NULL;

	// char *line = NULL;
	size_t len;

	ret = getline(&map->board[0], &len, fd);
	// printf("'%s {%zu}'\n", map->board[0], len);
	int ret2 = 0;
	for(int i = 0; i < map->nbr_line; i++)
	{
		ret2 = getline(&map->board[i], &len, fd);
		if (map->board[i][ret2 - 1] == '\n')
			ret2--;
		if ( i == 0)
			ret = ret2;
		else
		{
			if (ret2 != ret)
				return (printf("errroasd\n"),-1);
		}
		// if (ret != ret2)
			// return (printf("%d %d\n", ret, ret2),-1);
		// printf("'%s {%zu}'", line, len);
	}

	for (int i = 0; i < map->nbr_line; i++)
	{
		for (int j = 0; j < ret; j++)
		{
			if (map->board[i][j] != map->empty
				&& map->board[i][j] != map->obastacle)
				return -1;
		}
	}
	// ft_print(map);

	int matrix[map->nbr_line][ret];
	for (int i = 0; i < map->nbr_line; i++)
	{
		for (int j = 0; j  < ret; j++)
		{
			matrix[i][j] = 0;
		}
	}
	map->min = 0;
	map->i = 0;
	map->j = 0;

	int min;
	for (int i1 = 0; i1 < map->nbr_line; i1++)
	{
		for (int j1 = 0; j1  < ret; j1++)
		{
			if (map->board[i1][j1] == map->obastacle)
				matrix[i1][j1] = 0;
			else if (i1 == 0 || j1 == 0)
			{
				matrix[i1][j1] = 1;
			}
			else
			{
				int a1 = matrix[i1-1][j1];
				int a2 = matrix[i1-1][j1-1];
				int b1 = matrix[i1][j1-1];
				min = ft_min(a1, a2, b1);
				matrix[i1][j1] = min + 1;
				// map->board[i1][j1] = min + 1;
			}

			if (min+1 > map->min)
			{
				map->min = min+1;
				map->i = i1;
				map->j = j1;
			}
			// matrix[i1][j1] = 0;
			// map->board[i1][j1] = min + 1;
		}
	}
	printf("%d %d %d\n", map->min, map->i, map->j);
	for (int i = map->i - map->min + 1; i < map->i + 1; i++)
	{
		for (int j = map->j - map->min + 1; j < map->j + 1; j++)
		{
			if (i < map->nbr_line && j < ret && i >= 0 && j >= 0)
				map->board[i][j] = map->full;
		}
	}

	ft_print(map);
	return 1;
}

int main(int argc, char **argv){

	(void)argv;
	if (argc == 1)
	{
		int ret;
		(void)ret;
		t_map mape;
		if (getElem(stdin, &mape) == -1)
			return (printf("error1"),-1);
	}
	else if (argc == 2)
	{
		t_map mape;
		FILE *file = fopen(argv[1], "r");
		if (!file )
			return -1;
		if (getElem(file, &mape) == -1)
			return (printf("error2"),-1);
	}
	return (0);
}