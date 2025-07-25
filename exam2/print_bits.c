#include <unistd.h>
#include <stdio.h>
// void	print_bits(int c, int i, char *newstr)
// {
// 	if (c >= 2)
// 	{
// 		ft_base(c / 2, i - 1, newstr);
// 	}
// 	newstr[i] = "01"[c % 2];
// }

int ft_power(int nb, int power)
{
	int resultat = 1;
	if (power < 0)
		return (0);
	if (nb == 0 && power == 0)
		return (0);
	while (power >= 1)
	{
		resultat = resultat * nb;
		power--;
	}
	return (resultat);
}

void	print_bits(unsigned char octet)
{
	int i = 7;
	
	while (i >= 0)
	{
		write(1, &"01"[octet / ft_power(2, i) % 2], 1);
		i--;
	}
}

void	print_bits_2(unsigned char octet)
{
	int i = 7;
	
	while (i >= 0)
	{
		// Décaler l'octet de i positions vers la droite et garder seulement le bit de poids faible
		write(1, &"01"[(octet >> i) & 1], 1);
		i--;
	}
}

int main()
{

	// char str[9];
	// printf("%d\n", ft_power(2, 8));
	// printf("%d\n", 54 / 32 % 2);

	print_bits(7);
	write(1, "\n", 1);
	print_bits_2(7);
	// str[8] = 0;

	// write(1, str, 8);
}