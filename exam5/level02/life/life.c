#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

typedef struct s_game
{
	int i;
	int j;
	int draw;

	char **board;
	char alive;
	char dead;
	int width;
	int height;
	int iter;

}t_game;

void ft_init(t_game *game, char **argv)
{
	game->i = 0;
	game->j = 0;
	game->draw = 0;

	game->alive = 'O';
	game->dead = ' ';
	game->width = atoi(argv[1]);
	game->height = atoi(argv[2]);
	game->iter = atoi(argv[3]);
	game->board = malloc(sizeof(char *) * game->height);
	if (!game->board)
		return ;
	int i = 0;
	int j = 0;
	while (i < game->height)
	{
		game->board[i] = malloc(sizeof(char) * game->width);

		j = 0;
		while (j < game->width)
		{
			game->board[i][j] = ' ';
			j++;
		}
		i++;
	}
}

void ft_input(t_game *game)
{
	// int readfd;
	(void)game;
	char buffer;
	int flag;

	while (read(0, &buffer, 1) == 1)
	{
		flag = 0;
		switch (buffer)
		{
			case 'a':
				if (game->j > 0)
					game->j--;
				break;
				
			case 'd':
				if (game->j < game->width - 1)
					game->j++;
				break;

			case 'w':
				if (game->i > 0)
					game->i--;
				break;

			case 's':
				if (game->i < game->height - 1)
					game->i++;
				break;
			
			case 'x':
				game->draw = !game->draw;
				break;

			default:
				flag = 1;
				break;
			// printf("'%c'", buffer);
		}

		if (game->draw == 1 && flag == 0)
		{
			// if (game->i > 0 && game->j > 0
			// 	&& game->i < game->height
			// 	&& game->j < game->width)
				game->board[game->i][game->j] = game->alive;
		}
		// printf("'%c'", buffer);
	}
}

int ft_count(t_game *game, int x, int y)
{
	int count = 0;
	for (int i =-1; i < 2; i++)
	{
		for( int j = -1; j < 2; j++)
		{
			if (i == 0 && j == 0)
				continue;

			int newx = x + i;
			int newy = y + j;
			if (newx <0 || newy < 0)
				continue;
			if(newx >= game->height || newy >= game->width)
				continue;
			if (game->board[newx][newy] == '0')
				count++;
		}
	}
	return count;
}

void ft_play(t_game *game)
{
	char **temp;
	// for (int i = 0; i < game->height; i++)
	// {
	temp = malloc(sizeof(char *) * game->height);
	for (int j = 0; j < game->width; j++)
	{
		temp[j] = malloc(sizeof(char) * game->width);
	}	


	int count;
	for (int i1 = 0; i1 < game->height; i1++)
	{
		for (int j1 = 0; j1 < game->width; j1++)
		{
			count = ft_count(game,i1,j1);
			// printf("%d %d %d\n", count, i1, j1);
			if (game->board[i1][j1] == game->alive)
			{
				if (count == 3 || count == 2)
					
					temp[i1][j1] = game->alive;
				else
					temp[i1][j1] = game->dead;
			}
			else
			{
				if (count == 3)
					
					temp[i1][j1] = game->alive;
				else
					temp[i1][j1] = game->dead;
			}
		}	
	}	
	game->board = temp;

}

void ft_print(t_game *game)
{
	int i = 0;
	int j = 0;
	while (i < game->height)
	{
		
		while (j < game->width)
		{
			putchar(game->board[i][j]);
			j++;
		}
		j = 0;
		i++;
		putchar('\n');
	}
}

int main(int argc, char **argv)
{
	if (argc == 4)
	{
		t_game game;

		ft_init(&game, argv);
		// ft_print(&game);
		ft_input(&game);

		int i = 0;
		// ft_print(&game);
		while (i < game.iter)
		{
			ft_play(&game);
			i++;
		}
		ft_print(&game);
	}	
	return (1);
}