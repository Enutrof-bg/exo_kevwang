#include <stdio.h>
#include <stdlib.h>

///////////////////////////////////////////////////////////////////////////////////////
//test char malloc
void ft_char(char *str)
{
	// free(str);
	str = malloc(sizeof(char) * 7);
	int i = 0;
	while (i < 7)
	{
		(str)[i] = 'a' + i;
		i++;
	}
	(str)[i] = '\0';
}


void ft_char0(char **str)
{
	free(*str);

	*str = malloc(sizeof(char) * 7 + 1);
	int i = 0;
	while (i < 7)
	{
		(*str)[i] = 'a' + i;
		i++;
	}
	(*str)[i] = '\0';
}



int main()
{
	char *mot = malloc(sizeof(char) * 26 + 1);
	int i = 0;
	while (i < 26)
	{
		mot[i] = 'a' + i;
		i++;
	}
	mot[i] = '\0';
	printf("1:%s\n", mot);

	// ft_char(mot);
	// printf("%s\n", mot);

	ft_char0(&mot);
	printf("2:%s\n", mot);
	// free(mot);
}