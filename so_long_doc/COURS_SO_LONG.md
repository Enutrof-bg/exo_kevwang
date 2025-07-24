# Cours So Long - Guide Étudiant

## Structure du Projet

### 1. Fichiers Principaux
- `so_long.c` : Fichier principal avec la fonction main
- `so_long.h` : Header avec les structures et prototypes
- `img/` : Dossier contenant les images XPM
- `minilibx-linux/` : Bibliothèque graphique MLX

### 2. Structure de Données

```c
typedef struct s_data {
    void    *mlx_ptr;      // Pointeur vers l'instance MLX
    void    *win_ptr;      // Pointeur vers la fenêtre
    char    *img_path;     // Chemin vers l'image
    void    *img_ptr;      // Pointeur vers l'image
    int     img_width;     // Largeur de l'image
    int     img_height;    // Hauteur de l'image
} t_data;
```

### 3. Étapes d'Initialisation

#### Étape 1 : Allocation Mémoire
```c
t_data *data = malloc(sizeof(t_data));
```

#### Étape 2 : Initialisation MLX
```c
data->mlx_ptr = mlx_init();
```

#### Étape 3 : Création de la Fenêtre
```c
data->win_ptr = mlx_new_window(data->mlx_ptr, 800, 600, "So Long");
```

#### Étape 4 : Chargement de l'Image
```c
data->img_ptr = mlx_xpm_file_to_image(data->mlx_ptr, data->img_path, 
                                      &data->img_width, &data->img_height);
```

#### Étape 5 : Affichage
```c
mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, x, y);
```

#### Étape 6 : Boucle d'Événements
```c
mlx_loop(data->mlx_ptr);
```

### 4. Gestion des Erreurs

**Toujours vérifier :**
- L'allocation mémoire (`malloc`)
- L'initialisation MLX (`mlx_init`)
- La création de fenêtre (`mlx_new_window`)
- Le chargement d'image (`mlx_xpm_file_to_image`)

**En cas d'erreur :**
- Libérer la mémoire allouée
- Détruire les ressources MLX créées
- Retourner un code d'erreur

### 5. Points Importants

1. **Pointeurs vs Structures directes** : Utiliser `t_data *data` permet plus de flexibilité
2. **Opérateur d'accès** : `->` pour les pointeurs, `.` pour les structures directes
3. **Gestion mémoire** : Toujours libérer ce qui a été alloué
4. **Ordre de nettoyage** : Inverse de l'ordre de création

### 6. Compilation

```bash
gcc -Wall -Wextra -Werror so_long.c -Lminilibx-linux -lmlx -lXext -lX11 -o so_long
```

### 7. Prochaines Étapes

- Ajout de la gestion des événements (clavier, souris)
- Lecture et affichage d'une carte
- Gestion du mouvement du joueur
- Logique de jeu (collectibles, sortie)
