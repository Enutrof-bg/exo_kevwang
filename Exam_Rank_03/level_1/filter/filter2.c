/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cscache <cscache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 16:43:06 by hlichten          #+#    #+#             */
/*   Updated: 2025/07/21 10:23:04 by cscache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

ssize_t	realloc_buffer(char *buffer, int bytes_read)
{
	char	c;
	int		buffer_size;
	char	*tmp;

	buffer_size = 0;
	bytes_read = read(STDIN_FILENO, &c, 1);
	while (bytes_read > 0)
	{
		tmp = realloc(buffer, buffer_size + 1);
		if (!tmp)
			return (-1);
		buffer = tmp;
		buffer[buffer_size] = c;
		buffer_size++;
		bytes_read = read(STDIN_FILENO, &c, 1);
	}
	return (bytes_read);
}

void	transformation(char *buffer, char *key)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (buffer[i])
	{
		while (buffer[i + j] == key[j] && buffer[i + j] && key[j])
			j++;
		if (key[j] != '\0')
			j = 0;
		if (j != 0)
		{
			k = 0;
			while (k < j)
			{
				printf("%c", '*');
				k++;
			}
			i += j;
			j = 0;
		}
		else
			printf("%c", buffer[i++]);
	}
}
int	main(int ac, char *av[])
{
	char	*buffer;
	int		bytes_read;

	bytes_read = 0;
	// etape 1 : verification de l entree argument
	if (ac != 2 || av[1][0] == '\0')
		return (1);
	// etape 2 : allocation du buffer, verif et initatilisation a 0
	buffer = malloc(sizeof(char) * 1);
	if (!buffer)
		return (perror("Error"), 1);
	buffer[0] = '\0';
	// etape 3 : reallocation du buffer a chaque iteration jusqua la fin +verif
	bytes_read = realloc_buffer(buffer, bytes_read);
	if (bytes_read < 0)
		return (perror("Error"), free(buffer), 1);
	// etape 4 : remplasser le mot par des ***
	transformation(buffer, av[1]);
	free(buffer);
	return (0);
}

