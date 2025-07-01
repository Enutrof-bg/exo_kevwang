#include <stdio.h>
#include <stdlib.h>

///////test int
void ft_add(int a)
{
	a = a + 5;
}
///////test int
void ft_add_pointeur(int *a)
{
	*a = *a + 5;
}
///////test int
void ft_add_pointeur_2(int *a, int x)
{
	*a = *a + x;
}

int main()
{
	/////////////////////////////test int////////////////////////
	//1
	int test = 10;
	printf("1:%d\n", test); //test affiche bien 10

	ft_add(test); //je veux ajouter 5 a test
	printf("2:%d\n", test); // mais test affiche 10

	ft_add_pointeur(&test);// on ajoute en utilisant un pointeur sur test
	printf("3:%d\n", test); //cette fois ci, test affiche bien 15

	ft_add_pointeur_2(&test, 15);
	printf("4:%d\n", test);
}