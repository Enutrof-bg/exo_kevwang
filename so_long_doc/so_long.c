#include "so_long.h"

//cc so_long.c -Lminilibx-linux -lmlx -lXext -lX11
/*
** Fonction principale du programme So Long
** Initialise MLX, crée une fenêtre et affiche une image
*/

int ft_close(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	free(data);
	exit(0);
	return (0);
}

int on_key_press(int keysim, t_data *data)
{
	(void)data;
	printf("key:%d\n", keysim);
	return (1);
}

int main(void)
{
	// ========== ÉTAPE 1: ALLOCATION MÉMOIRE ==========
	// Déclaration du pointeur pour la structure de données
	t_data *data;

	// Allouer la mémoire pour la structure
	data = malloc(sizeof(t_data));
	if (!data)
		return (1);

	// ========== ÉTAPE 2: INITIALISATION MLX ==========
	// Initialiser la bibliothèque mlx
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
	{
		free(data);
		return (1);
	}

	// ========== ÉTAPE 3: CRÉATION DE LA FENÊTRE ==========
	// Créer une nouvelle fenêtre (largeur: 800, hauteur: 600)
	data->win_ptr = mlx_new_window(data->mlx_ptr, 800, 600, "So Long");
	if (!data->win_ptr)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
		free(data);
		return (1);
	}

	// ========== ÉTAPE 4: CHARGEMENT DE L'IMAGE ==========
	// Charger une image et la placer dans la fenêtre
	// Assurez-vous de remplacer le chemin par un chemin d'image valide
	data->img_path = "./img/char_im1.xpm";
	data->img_ptr = mlx_xpm_file_to_image(data->mlx_ptr, data->img_path, &data->img_width, &data->img_height);
	if (!data->img_ptr)
	{
		perror("Échec du chargement de l'image");
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
		free(data);
		return (1);
	}

	// ========== ÉTAPE 5: AFFICHAGE ==========
	// Placer l'image dans la fenêtre (position x: 100, y: 50)
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, 100, 50);

	// Afficher un message dans la fenêtre (position x: 10, y: 10, couleur: blanc)
	mlx_string_put(data->mlx_ptr, data->win_ptr, 10, 10, 0xFFFFFF, "Bienvenue dans So Long!");

	// ========== ÉTAPE 6: GESTION DES ÉVÉNEMENTS ==========
	// Gérer les événements de la fenêtre (fermeture, touches, etc.)
	mlx_hook(data->win_ptr, DestroyNotify, 0, ft_close, data);
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, on_key_press, data);

	// ========== ÉTAPE 7: BOUCLE D'ÉVÉNEMENTS ==========
	// Démarrer la boucle d'événements (le programme reste ouvert)
	mlx_loop(data->mlx_ptr);

	return (0);
}