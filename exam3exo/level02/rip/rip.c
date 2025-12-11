#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

//compte combien de parentheses sont desequilibrees dans la chadine
//principe:
//-on parcourt la chadine caractere par caractere
//- pour chaque '(': on incremente le compteur 'opened'
//- pour chaque ')': 
//		-s'il y a des '(' non fermees (opened > 0), on les apparie (opened--)
//		- sinon, c'est une ')' en trop, on incremente 'closed'
//
//retourne: Le nombre total de parentheses à corriger (opened + closed)
//  - 'opened' = nombre de '(' sans ')'
//  - 'closed' = nombre de ')' sans '('
//
int	invalid(char *s)
{
	int opened  = 0;  //Compte les '(' non appariees
	int closed = 0;   //Compte les ')' en trop
	
	//parcourir toute la chadine
	for(int x = 0; s[x]; x++)
	{
		if(s[x] == '(')
			opened++;  //nouvelle parenthese ouvrante
		else if(s[x] == ')')
		{
			if(opened > 0)
				opened--;  //on apparie avec une '(' precedente
			else
				closed++;  //')' en trop, aucune '(' disponible
		}
	}
	
	//Retourne le nombre total de parentheses desequilibrees
	return (closed + opened);
}

//fonction: solve
//trouve toutes les solutions en retirant le nombre minimal de parentheses
//pour equilibrer l'expression (on remplace par des espaces)
//
//parametres:
//- s: la chadine à traiter (modifiee pendant la recursion)
//- must_fix: nombre de parentheses qu'on DOIT retirer
//- fixed: nombre de parentheses qu'on a DeJÀ retirees
//- pos: position courante dans la chadine (pour eviter les doublons)
//
//principe (backtracking):
//1.Cas de base: si on a retire le bon nombre (must_fix == fixed)
//		ET que la chadine est valide, on l'affiche
//2.Cas recursif: pour chaque parenthese à partir de 'pos',
//		on essaie de la retirer (remplacer par ' '), puis on continue
//		la recherche, puis on la remet (backtrack)
//
void	solve(char *s, int must_fix, int fixed, int pos)
{
	//condition d'arrêt: on a retire assez de parentheses ET l'expression est valide
	if(must_fix == fixed && !invalid(s))
	{
		puts(s);  //Afficher cette solution
		return ;
	}
	
	//essayer de retirer chaque parenthese à partir de la position 'pos'
	int x = pos;
	while (s[x])
	{
		//on ne traite que les parentheses
		if(s[x] == '(' || s[x] == ')')
		{
			char c = s[x];      //sauvegarder le caractere original
			s[x] = ' ';         //Retirer la parenthese (remplacer par espace)
			
			//Recursion: chercher d'autres parentheses à retirer
			solve(s, must_fix, fixed + 1, x + 1);
			
			s[x] = c;           //backtrack: remettre la parenthese
		}
		x++;
	}
}

//1. calcule combien de parentheses sont desequilibrees (must_fix)
//2. lance la recherche de toutes les solutions
int main(int ac, char **av)
{
	if (ac != 2)
		return (1);

	//etape 1: compter combien de parentheses doivent être retirees
	int must_fix = invalid(av[1]);
	
	//etape 2: trouver et afficher toutes les solutions
	solve(av[1], must_fix, 0, 0);
	
	return (0);
}
