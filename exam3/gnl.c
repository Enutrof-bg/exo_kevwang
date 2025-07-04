#include "h.h"

char *ft_strjoin(char *s1, char *s2)
{
	char *new = malloc(sizeof(char) * (strlen(s1) + (strlen(s2) + 1)));
	if (!new)
		return NULL;
	int i = 0;
	int j = 0;
	while (s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		new[i + j] = s2[j];
		j++;
	}
	new[i+j] = 0;
	return (new);
}

int ft_check(char *str, char c)
{
	int i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return 0;
		i++;
	}
	return 1;
}

char *ft_return(char *str)
{
	int i = 0;
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	char *new = malloc(sizeof(char) * i + 1);
	if (!new)
		return NULL;
	int j = 0;
	while (j < i)
	{
		new[j] = str[j];
		j++;
	}
	new[j] = 0;
	return new;
}

char *ft_reste(char *str)
{
	int i = 0;
	int j = 0;
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	while (str[i + j] != '\0')
		j++;
	char *new = malloc(sizeof(char) * j + 1);
	if (!new)
		return NULL;
	int n = 0;
	while (str[i +n])
	{
		new[n] = str[i+n];
		n++;
	}
	new[n] = 0;
	return new;
}

char *get_next_line(int fd)
{
	char buff[BUFFER_SIZE + 1];
	static char *str;
	char *strreturn;
	char *temp;

	if (!str)
	{
		str = malloc(sizeof(char) * 1);
		if (!str)
			return NULL;
		str[0] = '\0';
	}
	int readfd = read(fd, buff, BUFFER_SIZE);
	while (readfd > 0)
	{
		buff[readfd] = 0;
		temp = ft_strjoin(str, buff);
		if (!temp)
			return NULL;
		free(str);
		str = temp;
		if (ft_check(str, '\n') == 0)
			break ;
		readfd = read(fd, buff, BUFFER_SIZE);
	}
	if (readfd == 0 && str[0] == '\0')
	{
		return (free(str), NULL);
	}
	strreturn = ft_return(str);
	if (!strreturn)
			return NULL;
	temp = ft_reste(str);
	if (!temp)
			return NULL;
	free(str);
	str = temp;
	return (strreturn);
}
/*
int main()
{
	int fd = open("text.txt", O_RDONLY);
	char *test = get_next_line(fd);
	while (test)
	{
		printf("'%s'", test);
		free(test);
		test = get_next_line(fd);
	}
}
*/