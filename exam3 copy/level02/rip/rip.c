#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int     invalid(char *s);

/*
 * Fonction: invalid
 * -----------------
 * Compte combien de parenthèses sont déséquilibrées dans la chaîne
 * 
 * Principe:
 * - On parcourt la chaîne caractère par caractère
 * - Pour chaque '(': on incrémente le compteur 'opened'
 * - Pour chaque ')': 
 *     - S'il y a des '(' non fermées (opened > 0), on les apparie (opened--)
 *     - Sinon, c'est une ')' en trop, on incrémente 'closed'
 * 
 * Retourne: Le nombre total de parenthèses à corriger (opened + closed)
 *           - 'opened' = nombre de '(' sans ')'
 *           - 'closed' = nombre de ')' sans '('
 */
int	invalid(char *s)
{
	int opened  = 0;  // Compte les '(' non appariées
	int closed = 0;   // Compte les ')' en trop
	
	// Parcourir toute la chaîne
	for(int x = 0; s[x]; x++)
	{
		if(s[x] == '(')
			opened++;  // Nouvelle parenthèse ouvrante
		else if(s[x] == ')')
		{
			if(opened > 0)
				opened--;  // On apparie avec une '(' précédente
			else
				closed++;  // ')' en trop, aucune '(' disponible
		}
	}
	
	// Retourne le nombre total de parenthèses déséquilibrées
	return (closed + opened);
}

/*
 * Fonction: solve
 * ---------------
 * Trouve toutes les solutions en retirant le nombre minimal de parenthèses
 * pour équilibrer l'expression (on remplace par des espaces)
 * 
 * Paramètres:
 * - s: la chaîne à traiter (modifiée pendant la récursion)
 * - must_fix: nombre de parenthèses qu'on DOIT retirer
 * - fixed: nombre de parenthèses qu'on a DÉJÀ retirées
 * - pos: position courante dans la chaîne (pour éviter les doublons)
 * 
 * Principe (backtracking):
 * 1. Cas de base: si on a retiré le bon nombre (must_fix == fixed)
 *    ET que la chaîne est valide, on l'affiche
 * 2. Cas récursif: pour chaque parenthèse à partir de 'pos',
 *    on essaie de la retirer (remplacer par ' '), puis on continue
 *    la recherche, puis on la remet (backtrack)
 */
void	solve(char *s, int must_fix, int fixed, int pos)
{
	// Condition d'arrêt: on a retiré assez de parenthèses ET l'expression est valide
	if(must_fix == fixed && !invalid(s))
	{
		puts(s);  // Afficher cette solution
		return ;
	}
	
	// Essayer de retirer chaque parenthèse à partir de la position 'pos'
	for(int x = pos; s[x]; x++)
	{
		// On ne traite que les parenthèses
		if(s[x] == '(' || s[x] == ')')
		{
			char c = s[x];      // Sauvegarder le caractère original
			s[x] = ' ';         // Retirer la parenthèse (remplacer par espace)
			
			// Récursion: chercher d'autres parenthèses à retirer
			solve(s, must_fix, fixed + 1, x + 1);
			
			s[x] = c;           // Backtrack: remettre la parenthèse
		}
	}
}

/*
 * Fonction: main
 * --------------
 * Point d'entrée du programme
 * 
 * 1. Calcule combien de parenthèses sont déséquilibrées (must_fix)
 * 2. Lance la recherche de toutes les solutions
 */
int main(int ac, char **av)
{
	(void)ac;  // Paramètre non utilisé
	
	// Étape 1: Compter combien de parenthèses doivent être retirées
	int must_fix = invalid(av[1]);
	
	// Étape 2: Trouver et afficher toutes les solutions
	solve(av[1], must_fix, 0, 0);
	
	return (0);
}
