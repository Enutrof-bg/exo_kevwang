# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: student <student@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/01 00:00:00 by student           #+#    #+#              #
#    Updated: 2025/01/01 00:00:00 by student          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Nom de l'exécutable
NAME = so_long

# Compilateur et flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Répertoires
MLX_DIR = minilibx-linux
INC_DIR = .

# Bibliothèques
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

# Fichiers sources
SRCS = so_long.c

# Fichiers objets
OBJS = $(SRCS:.c=.o)

# Couleurs pour l'affichage
GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

# Règle principale
all: $(MLX_LIB) $(NAME)

# Compilation de la bibliothèque MLX
$(MLX_LIB):
	@echo "$(GREEN)Compilation de la bibliothèque MLX...$(RESET)"
	@make -C $(MLX_DIR)

# Compilation de l'exécutable
$(NAME): $(OBJS)
	@echo "$(GREEN)Compilation de $(NAME)...$(RESET)"
	$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) compilé avec succès!$(RESET)"

# Compilation des fichiers objets
%.o: %.c
	@echo "Compilation de $<..."
	$(CC) $(CFLAGS) -I$(INC_DIR) -I$(MLX_DIR) -c $< -o $@

# Nettoyage des fichiers objets
clean:
	@echo "$(RED)Nettoyage des fichiers objets...$(RESET)"
	rm -f $(OBJS)
	@make -C $(MLX_DIR) clean

# Nettoyage complet
fclean: clean
	@echo "$(RED)Nettoyage complet...$(RESET)"
	rm -f $(NAME)

# Recompilation complète
re: fclean all

# Test du programme
test: $(NAME)
	@echo "$(GREEN)Lancement du test...$(RESET)"
	./$(NAME)

# Vérification des fichiers d'images
check_images:
	@echo "Vérification des images..."
	@ls -la img/

# Installation des dépendances (Ubuntu/Debian)
install_deps:
	@echo "Installation des dépendances..."
	sudo apt-get update
	sudo apt-get install gcc make xorg libxext-dev libbsd-dev

# Règles qui ne correspondent pas à des fichiers
.PHONY: all clean fclean re test check_images install_deps
