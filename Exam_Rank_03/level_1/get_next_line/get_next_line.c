#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

//FONCTIONNE EN EXAM!!

#define BUFFER_SIZE 42

char	*ft_strdup(char *s)
{
	char	*dup;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
		i++;
	dup = malloc(i + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*get_next_line(int fd)
{
	static char	buff[BUFFER_SIZE];
	char		line[70000];
	static int	x = 0;
	static int	r = 0;
	int			y;

	if (fd < 0)
		return (NULL);
	y = 0;
	while (1)
	{
		if (x >= r)
		{
			r = read(fd, buff, BUFFER_SIZE);
			x = 0;
			if (r <= 0)
				break ;
		}
		line[y++] = buff[x++];
		if (buff[x - 1] == '\n')
			break ;
	}
	line[y] = '\0';
	if (y == 0)
		return (NULL);
	return (ft_strdup(line));
}

// #include <stdio.h>

// int	main(int ac, char *av[])
// {
// 	int		fd;
// 	char	*line;

// 	if (ac != 2)
// 		return (1);
// 	fd = open(av[1], O_RDONLY);
// 	while ((line = get_next_line(fd)))
// 	{
// 		printf("%s", line);
// 		free(line);
// 	}
// 	return (0);
// }

