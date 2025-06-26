#include "h.h"

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*newstr;
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	newstr = malloc(sizeof(char) * (strlen(s1) + strlen(s2)) + 1);
	if (newstr == NULL)
		return (NULL);
	while (i < strlen(s1))
	{
		newstr[i] = s1[i];
		i++;
	}
	while (j < strlen(s2))
	{
		newstr[i + j] = s2[j];
		j++;
	}
	newstr[i + j] = '\0';
	return (newstr);
}

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

void ft_map(char *str, char **tel, int i,int j)
{
	(void)str;
	(void)tel;
	// (void)comb;
	/*
	size_t it = (size_t)i;
	size_t y = 0;
	char temp[20];
	// size_t jt = (size_t)j;
	if (it == strlen(str))
	{
		printf("%s\n", comb);
		return ;
	}
	// if (jt == strlen(tel[i]))
	// {
	// 	return ;
	// }
	// printf("%c", tel[str[i] -'0'-2][j]);
	for(y = 0; y < strlen(tel[str[i] -'0'-2]); y++)
	{

		strcpy(temp, comb);
		strncat(comb, &tel[str[i] -'0'-2][y], 1+1);
		ft_map(str, tel, i + 1, temp);
		// ft_map(str, tel, i + 1, memcpy(comb, &tel[str[i] -'0'-2][y], 1 + 1));

	}
	*/



	
	i = 0;
	j = 0;
	int x = 0;
	int y = 0;
	int z = 0;
	// while (str[i])
	// {
		while (tel[str[i] - '0' - 2][j])
		{
			// printf("%c\n", tel[str[i] - '0' - 2][j]);

			while (tel[str[i+1] - '0' - 2][x])
			{
				while (tel[str[i+2] - '0' - 2][y])
				{
					while (tel[str[i+2] - '0' - 2][z])
					{
						printf("%c", tel[str[i] - '0' - 2][j]);
						printf("%c", tel[str[i + 1] - '0' - 2][x]);
						printf("%c", tel[str[i + 2] - '0' - 2][y]);
						printf("%c\n", tel[str[i + 3] - '0' - 2][z]);
						z++;
					}
					// printf("%c", tel[str[i] - '0' - 2][j]);
					// printf("%c", tel[str[i + 1] - '0' - 2][x]);
					// printf("%c\n", tel[str[i + 2] - '0' - 2][y]);
					z = 0;
					y++;
				}
				// printf("%c", tel[str[i] - '0' - 2][j]);
				// printf("%c\n", tel[str[i + 1] - '0' - 2][x]);
				x++;
				y = 0;
			}
			x = 0;
			j++;
		}
		// j = 0;
		// i++;
	// }
	
}

void ft_phone(char *str, char **tel)
{
	(void)str;
	(void)tel;
	int i = 0;
	while (str[i])
	{
		if (!(str[i] >= '2' && str[i] <= '9'))
		{
			printf("num erreur");
			exit(1);
		}
		i++;
	}
	int num = atoi(str);
	printf("%d\n", num);
	// char s[50] = "";
	ft_map(str, tel, 0, 0);
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

	// char *a = "a";
	// char *b = "b";
	// char z[10] = strcat(a, b);
	// printf("%s\n", z);

	if (argc == 2)
	{
		if (strlen(argv[1]) != 4)
		{
			printf("mets 4 numeros stp");
			return (0);
		}
		ft_phone(argv[1], tel);
	}
	return 0;
}