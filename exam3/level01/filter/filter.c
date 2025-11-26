#include "h.h"

char *ft_strjoin(char *s1, char *s2)
{
	char *new = malloc(sizeof(char) * (strlen(s1) + strlen(s2) + 1));
	if (!new)
		return (NULL);
	size_t i = 0;
	size_t j = 0;
	while (i < strlen(s1))
	{
		new[i] = s1[i];
		i++;
	}
	while (j < strlen(s2))
	{
		new[i + j] = s2[j];
		j++;
	}
	new[i + j] = '\0';
	return (new);
}

int ft_check(char *str, char *arg)
{
	size_t compteur = 0;
	int i = 0;
	while (arg[i])
	{
		if (str[i] == arg[i])
			compteur++;
		if (compteur == strlen(arg))
			return (1);
		i++;
	}
	return (0);
}

int main(int argc, char **argv)
{

	(void)argv;
	if (argc == 2)
	{
		int readfd = 0;
		char *newread = malloc(sizeof(char) * 70000);
		if (!newread)
			return (perror("Error: "), 1);
		char *str = malloc(sizeof(char) * 70000);
		if (!str)
			return (perror("Error: "), 1);


		readfd = read(0, newread, 5);
		if (readfd == -1)
			return (perror("Error: "), 1);

		while (readfd > 0)
		{
			newread[readfd] = '\0';
			str = ft_strjoin(str, newread);
			if (!str)
				return (perror("Error: "), 1);
			readfd = read(0, newread, 5);
			if (readfd == -1)
				return (perror("Error: "), 1);
		}


		int i = 0;
		size_t j = 0;
		while (str[i])
		{
			if (ft_check(&str[i], argv[1]) == 1)
			{
				while (j < strlen(argv[1]))
				{
					str[i + j] = '*';
					j++;
				}
			}
			j = 0;
			i++;
		}
		printf("%s", str);
	}
	return (0);
}