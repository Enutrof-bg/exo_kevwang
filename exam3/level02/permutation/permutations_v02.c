#include <stdio.h>

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_swap(char *a, char *b)
{
	char	c;

	c = *a;
	*a = *b;
	*b = c;
}

char	*sorted_string(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i + 1])
	{
		if (s[i] > s[i + 1])
		{
			ft_swap(&s[i], &s[i + 1]);
			i = 0;
		}
		else
			i++;
	}
	return (s);
}

void	reverse(char *s, int start, int end)
{
	while (start < end)
	{
		ft_swap(&s[start], &s[end]);
		start++;
		end--;
	}
}

int	next_permutations(char *s, int len)
{
	int	i;
	int	j;

	i = len - 2;
	while (i >= 0 && s[i] >= s[i + 1])
		i--;
	if (i < 0)
		return (0);
	j = len - 1;
	while (s[j] <= s[i])
		j--;
	ft_swap(&s[i], &s[j]);
	reverse(s, i + 1, len - 1);
	return (1);
}

int	main(int ac, char *av[])
{
	char	*s;
	int		len;

	if (ac != 2)
		return (1);
	s = sorted_string(av[1]);
	len = ft_strlen(s);
	puts(s);
	while (next_permutations(s, len))
		puts(s);
	return (0);
}
