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

void ft_phone(char *str, char **tel)
{
	(void)str;
	(void)tel;
	
	

}

int main(int argc, char **argv)
{
	int i = 0;
	int j = 0;
	char c = 'a';
	// char tel[9][4];
	char **tel;

	tel = malloc(sizeof(char *) * 9);
	while(i < 8)
	{
		if (i == 5 || i == 7)
			tel[i] = malloc(sizeof(char) * 5);
		else
			tel[i] = malloc(sizeof(char) * 4);
		i++;
	}
	i = 0;

	while (i < 8)
	{
		while ((j < 3 && (i != 5 && i != 7)) || (j < 4 &&( i ==5 || i == 7)))
		{
			tel[i][j] = c;
			c++;
			j++;
		}
		tel[i][j] = '\0';
		j = 0;
		i++;
	}
	tel[i] = 0;
	i = 0;
	while (tel[i])
	{
		printf("%s\n", tel[i]);
		i++;
	}


	if (argc == 2)
	{
		ft_phone(argv[1], tel);
	}
	return 0;
}