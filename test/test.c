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
///////////////////////////////////////////////////////////////////////////////////////
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
///////////////////////////////////////////////////////////////////////////////////////
//test char*
void ft_mot(char *str)
{
	str = "abcdef";
}

void ft_mot_pointeur(char **str)
{
	*str = "xyz";//on deference
}

void ft_mot_pointeur_2(char **str, char *new)
{
	*str = new; //modifie str par new
}
///////////////////////////////////////////////////////////////////////////////////////

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



	printf("\n\n\n");
	//////////////////////////////test char**///////////////////////
	//2
	char *mot1;
	mot1 = NULL;//on initialise mot1

	ft_mot(mot1);//on veut que mot1 vaut abcdef
	printf("1:%s\n", mot1);//mais mot1 affiche (null)

	ft_mot_pointeur(&mot1);//on veut que mot1 vaut xyz en utilisant un pointeur cette fois ci
	printf("2:%s\n", mot1);//mot1 affiche bien "xyz" cette fois

	ft_mot_pointeur_2(&mot1, "bonjour"); // on peut remplacer mot1 par ce aue l'on veut
	printf("3:%s\n", mot1);//mot1 affiche "bonjour"

	ft_mot(mot1);//mot1 n'est pas modifie, ft_mot recoit une "copie" de mot1
	printf("4:%s\n", mot1);//mot1 n'est pas modifie et vaut toujours "bonjour"

	printf("\n\n\n");
	//////////////////////////////////test char malloc///////////////////////
	//3
	char *mot = malloc(sizeof(char) * 26 + 1);
	int i = 0;
	while (i < 26)
	{
		mot[i] = 'a' + i;
		i++;
	}
	mot[i] = '\0';
	printf("%s\n", mot);

	// ft_char(mot);
	// printf("%s\n", mot);

	ft_char0(&mot);
	printf("%s\n", mot);
	free(mot);
}