#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void	write_solutions(int nb)
{
	char	c;

	if (nb >= 10)
		write_solutions(nb / 10);
	c = nb % 10 + '0';
	write(1, &c, 1);
}

void	write_solutions_recursive(int *positions, int n, int index)
{
	if (n == index)
	{
		write(1, "\n", 1);
		return ;
	}
	write_solutions(positions[index]);
	if (index != n - 1)
		write(1, " ", 1);
	write_solutions_recursive(positions, n, index + 1);
}

int	is_valid_positions(int	*positions, int row, int col)
{
	int	c;
	int	prev_row;

	c = 0;
	while (c < col)
	{
		prev_row = positions[c];
		if (prev_row == row)
			return (0);
		if (prev_row + c == row + col)
			return (0);
		if (prev_row - c == row - col)
			return (0);
		c++;
	}
	return (1);
}
void	find_solutions(int *positions, int n, int col)
{
	int	row;

	if (col == n)
	{
		write_solutions_recursive(positions, n, 0);
		return ;
	}
	row = 0;
	while (row < n)
	{
		if (is_valid_positions(positions, row, col))
		{
			positions[col] = row;
			find_solutions(positions, n, col + 1);
		}
		row++;
	}
}
int	main(int ac, char *av[])
{
	int	n;

	if (ac != 2)
		return (1);
	n = atoi(av[1]);
	if (n <= 0)
		return (1);
	int	positions[n];
	find_solutions(positions, n, 0);
	return (0);
}
