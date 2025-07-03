#include "h.h"

char *ft_strjoin(char *s1, char *s2)
{
	char *new = malloc(sizeof(char) * strlen(s1) + strlen(s2) + 1);
	int i =0;
	while (s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	int j = 0;
	while (s2[j])
	{
		new[i +j] = s2[j];
		j++;
	}
	new[i+j] = 0;
	return new;
}

int ft_check(char *str, char *arg)
{
	int i = 0;
	int compteur = 0;
	int len = strlen(arg);
	while (i < len)
	{
		if (str[i] == arg[i])
			compteur++;
		if (compteur == len)
			return 0;
		i++;
	}
	return 1;
}

int main(int argc, char **argv)
{
	if (argc == 2)
	{
		char *str;
		int readfd;
		char *buff;
		char *temp;
		str = malloc(70000);
		buff = malloc(70000);

		readfd = read(0, buff, 10);
		while (readfd > 0)
		{
			buff[readfd] = 0;
			temp = ft_strjoin(str, buff);
			free(str);
			str = temp;
			readfd = read(0, buff, 10);
		}
		int i  = 0;
		size_t j = 0;
		while (str[i])
		{
			if (ft_check(&str[i], argv[1]) == 0)
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
}