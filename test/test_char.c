#include <stdio.h>
#include <stdlib.h>

#include <stdio.h>
#include <stdlib.h>

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

int main()
{
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
}