#include "h.h"

void	ft_base(int c, int i, char *newstr)
{
	if (c >= 2)
	{
		ft_base(c / 2, i - 1, newstr);
	}
	newstr[i] = "01"[c % 2];
}

char	*ft_call_bit(unsigned char c)
{	
	char	*bite;
	int		i;

	i = 0;
	bite = malloc(sizeof(char) * (8 + 1));
	if (!bite)
		return (NULL);
	while (i < 8)
	{
		bite[i] = '0';
		i++;
	}
	ft_base(c, 7, bite);
	bite[8] = '\0';
	return (bite);
}

int main()
{
	char *test;

	test = ft_call_bit('4' - '0');
	int i = 0;

	while (test[i] == '0')
		i++;
	while (test[i])
	{
		write(1, &test[i], 1);
		i++;
	}
	// printf("%s\n", test);

}