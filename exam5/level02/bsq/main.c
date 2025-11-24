#include <stdlib.h>
#include <stdio.h>

typedef struct s_map
{
	char **map;
	int nbr_line;
	char empty;
	char obstacle;
	char full;

	int max;
	int posi;
	int posy;

}t_map;

int ft_strlen(char* str)
{
	int i = 0;
	while (str[i])
		i++;
	return i;
}

void ft_print(t_map *mape)
{
printf("\n\n");
	int i2 = 0;
	while (mape->map[i2])
	{
		printf("%s", mape->map[i2]);
		i2++;
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

int main(int argc, char **argv)
{
	if (argc !=2)
		return 1;
	t_map mape;

	FILE* fd = fopen(argv[1], "r");
	char *str;
	size_t len = 0;
	int read;
	read = getline(&str, &len, fd);
	printf("%s\n", str);
	int i = 0;
	int val = 0;
	while (str[i])
	{
		if (str[i] != ' ')
		{
			if (val == 0)
				mape.nbr_line = str[i] - 48;
			if (val == 1)
				mape.empty = str[i];
			if (val == 2)
				mape.obstacle = str[i];
			if (val == 3)
				mape.full = str[i];
			val++;
		}
		i++;
	}
	// printf("%d %c %c %c\n", mape.nbr_line, mape.empty, mape.obstacle, mape.full);
	// map = malloc(sizeof(char *) * )
	int i1 = 0;
	mape.map = malloc(sizeof(char *) * mape.nbr_line + 1);
	while (i1 < mape.nbr_line)
	{
		// mape.map[i] = malloc(sizeof(char) * mape.nbr_line);
		getline(&mape.map[i1], &len, fd);
		i1++;
	}

	ft_print(&mape);

	

	int i3 = 0;
	int i4 = 0;
	while (i3 < mape.nbr_line)
	{
		while (i4 < ft_strlen(mape.map[i3]))
		{
			if (mape.map[i3][i4] != mape.obstacle && mape.map[i3][i4] != '\n')
			{
				if (i3 == 0 || i4 == 0)
					mape.map[i3][i4] = '1';
				else
					mape.map[i3][i4] = 't';
			}
			if (mape.map[i3][i4] == mape.obstacle)
				{
					mape.map[i3][i4] = '0';
				}
			i4++;
		}
		i4 = 0;
		i3++;
	}
	ft_print(&mape);

	int x = 0;
	int y = 0;
	int a1;
	int a2;
	int b1;

	mape.max = 0;
		mape.posi = 0;
			mape.posy = 0;
	while (x < mape.nbr_line)
	{
		while (y < ft_strlen(mape.map[x]))
		{
			if (x > 0 && x < mape.nbr_line
				&& y > 0 && y < ft_strlen(mape.map[x])
				&& mape.map[x][y] != mape.obstacle
			&& mape.map[x][y] != '\n')
				{
					a2 = mape.map[x - 1][y] - 48;
					b1 = mape.map[x][y - 1] - 48;
					a1 = mape.map[x - 1][y - 1] - 48;
					int min = ft_min(a1, a2, b1);
					if (mape.map[x][y] == 't')
					{
						mape.map[x][y] =( min + 1 + 48);
						if (min + 1 > mape.max)
						{	
							mape.max = min + 1;
							mape.posi = x;
							mape.posy = y;
							printf("\n'%d' '%d' '%d'\n", mape.max, mape.posi, mape.posy);
						}
					}
					// if (mape.map[x][y] != '\n')
						// mape.map[x][y] = '9';
				}

			y++;
		}
		y = 0;
		x++;
	}

	ft_print(&mape);

	printf("\n'%d' '%d' '%d'\n", mape.max, mape.posi, mape.posy);

	int x1 = mape.posi;
	int y1 = mape.posy;

	while (x1 > mape.posi - mape.max)
	{
		while (y1 > mape.posy - mape.max)
		{
			mape.map[x1][y1] = mape.full;
			y1--;			
		}
		y1 = mape.posy;
		x1--;
	}


	ft_print(&mape);

	int x2 = 0;
	int y2 = 0;
	while (x2 < mape.nbr_line)
	{
		while (y2 < ft_strlen(mape.map[x2]))
		{
			// mape.map[x2][y2] = mape.full;
 
			if (mape.map[x2][y2] == '0')
				mape.map[x2][y2] = mape.obstacle;
			else if (mape.map[x2][y2] != mape.full && mape.map[x2][y2] != '\n')
				mape.map[x2][y2] = mape.empty;
			y2++;			
		}
		y2 = 0;
		x2++;
	}

	ft_print(&mape);
}