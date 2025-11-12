#include <stdio.h>
#include <pthread.h>

// Chaque thread comptera TIMES_TO_COUNT fois
#define TIMES_TO_COUNT 21000

//juste pour les couleurs pour les printf
#define NC "\e[0m"
#define YELLOW "\e[33m"
#define BYELLOW "\e[1;33m"
#define RED "\e[31m"
#define GREEN "\e[32m"

void *thread_routine(void *data)
{
 // Chaque thread commence ici
 pthread_t tid;
 unsigned int *count; // pointeur vers la variable dans le main
 unsigned int i;

 tid = pthread_self(); // pour recuperer l'id du thread

 // Lors du pthread_create, on a passe (unsigned int)count en 4e parametre
 // le prototype attend une argument de type (void*)
 // Il faut dont recaste date en (unsigned int *) pour pouvoir l'utilise
 count = (unsigned int *)data;
// Maintenant, les deux thread crees dans le main ont acces a la meme variable count du main
// et le modifieront simultanement

 // On imprime le compte avant que ce thread commence
 // a itérer
 printf("%sThread [%ld]: compte au depart = %u.%s\n",
  YELLOW, tid, *count, NC);
 i = 0;
 while (i < TIMES_TO_COUNT)
 {
  // On itere TIMES_TO_COUNT (21000)fois
  // On incremente le compte a chaque iteration
  (*count)++;
  i++;
 }
 // On imprime le compte final au moment ou ce thread
 // a termine son propre compte
 printf("%sThread [%ld]: Compte final = %u.%s\n",
  BYELLOW, tid, *count, NC);
 return (NULL); // Thread termine ici.
}

// le probleme est que les 2 thread peuvent accede a la variable count en meme temps,
// dans ce cas, les threads vont incrementer count une fois chacun ( on aura count++ deux fois)
// mais parce que ca a ete execute en meme temps, le programme ne sera pas synchroniser correctement
// chaque thread vont acceder a la variable count, en faire une copie, l'incrementer avant de le retourner pour mettre a jour count
// si les thread s'executent en meme temps, les deux thread vont copier count, l'incrementer une fois chacun, et le retourner
// mais le main n'enregistrera que une seul incrementation

// ex: on a count = 10, chaque thread en font une copie et l'incremente (count = 11 alors) et le retournera
// le main aura count=11 (au lieu de count=12) car les thread ont incrementer en meme temps au lieu d'alterner
// on appelle ca le "data race"

// chaque thread va incrementer count 21000 fois, mais le compte final attendu(=42000) ne sera pas tout le temps correct si on execute le programme plusieurs fois


int main(void)
{
    pthread_t tid1;
    pthread_t tid2;


    // Variable pour contenir le compte des deux threads :
    unsigned int count;
    count = 0;


    // Vu que chaque thread va compter TIMES_TO_COUNT fois et qu'on va
    // avoir 2 threads, on s'attend a ce que le compte final soit
    // 2 * TIMES_TO_COUNT :

    printf("Main: Le compte attendu est de %s%u%s\n", GREEN,
     2 * TIMES_TO_COUNT, NC);


    // Creation des threads :
    // Argument 1 : l'adresse d'une variable phtread_t (un peu comme pour donne un nom au thread)
    // Argument 2 : pour le projet, ca sera NULL, utilisable mais avec des fonctions interdites
    // Argument 3 : la fonction que le thread va executer, ici thread_routine()
    // Argument 4 : l'argument qui sera passe en parametre a la fonction en 3e argument
    // On lance donc un thread, qui execute la fonction thread_routine avec count en argument thread_routne(count)
    pthread_create(&tid1, NULL, thread_routine, &count);
    printf("Main: Creation du premier thread [%ld]\n", tid1);
    pthread_create(&tid2, NULL, thread_routine, &count);
    printf("Main: Creation du second thread [%ld]\n", tid2);


    // Recuperation des threads :
    pthread_join(tid1, NULL);
    printf("Main: Union du premier thread [%ld]\n", tid1);
    pthread_join(tid2, NULL);
    printf("Main: Union du second thread [%ld]\n", tid2);


    // Evaluation du compte final :
    if (count != (2 * TIMES_TO_COUNT))
    printf("%sMain: ERREUR ! Le compte est de %u%s\n", RED, count, NC);
    else
    printf("%sMain: OK. Le compte est de %u%s\n", GREEN, count, NC);
    return (0);
}