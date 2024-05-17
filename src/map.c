// map.c
#include "my.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>



// Fonction pour afficher la carte avec les couleurs
void print_map(char *map)
{
    char *colors_code[] = COLORS_CODE; // Tableau de codes de couleur
    for (int y = 0 ; y < MAP_HEIGHT ; y++) // Parcours des lignes de la carte
    {
        for (int x = 0 ; x < MAP_WIDTH ; x++) // Parcours des colonnes de la carte
            printf("%s  %s", colors_code[map[y * MAP_WIDTH + x]], COLOR_RESET); // Affichage de la couleur de chaque case
        printf("\n"); // Nouvelle ligne pour chaque ligne de la carte
    }
}

void print_mapu(char* map, Cell* grid, sfRenderWindow *window)
{
    char *colors_code[] = COLORS_CODE; // Tableau de codes de couleur
    for (int y = 0 ; y < MAP_HEIGHT ; y++) // Parcours des lignes de la carte
    {
        for (int x = 0 ; x < MAP_WIDTH ; x++){ // Parcours des colonnes de la carte
            int couleur = map[y * MAP_WIDTH + x];
            if (colors_code[couleur] == "\e[40m") sfRectangleShape_setFillColor(grid[y* GRID_SIZE + x].shape, sfBlack);
            if (colors_code[couleur] == "\e[43m") sfRectangleShape_setFillColor(grid[y* GRID_SIZE + x].shape, sfYellow);
            if (colors_code[couleur] == "\e[41m") sfRectangleShape_setFillColor(grid[y* GRID_SIZE + x].shape, sfRed);
            if (colors_code[couleur] == "\e[44m") sfRectangleShape_setFillColor(grid[y* GRID_SIZE + x].shape, sfBlue);
            if (colors_code[couleur] == "\e[42m") sfRectangleShape_setFillColor(grid[y* GRID_SIZE + x].shape, sfGreen);
            if (colors_code[couleur] == "\e[105m") sfRectangleShape_setFillColor(grid[y* GRID_SIZE + x].shape, sfMagenta);
        }
    }
    for (int i = 0; i < GRID_SIZE * GRID_SIZE; ++i) sfRenderWindow_drawRectangleShape(window, grid[i].shape, NULL);

}

// Fonction pour générer une carte aléatoire
void random_map(char *map)
{
    srand(time(NULL)); // Initialisation de la graine pour la génération aléatoire
    for (int i = 0 ; i < (MAP_HEIGHT * MAP_WIDTH) ; i++) // Parcours de toutes les cases de la carte
    {
        while (TRUE) // Boucle infinie
        {
            map[i] = rand() % COLORS_NBRS; // Attribution aléatoire d'une couleur à la case
            if (i - 1 >= 0 && map[i - 1] == map[i]) // Vérification de la case à gauche
                continue; // Continue la boucle si la couleur est la même
            if (i - MAP_WIDTH >= 0 && map[i - MAP_WIDTH] == map[i]) // Vérification de la case au-dessus
                continue; // Continue la boucle si la couleur est la même
            break; // Sort de la boucle si les couleurs sont différentes
        }
    }
    while (map[AI_Y * MAP_WIDTH + AI_X] == map[PLAYER_Y * MAP_WIDTH + PLAYER_X]) // Vérification des couleurs du joueur et de l'IA
        map[AI_Y * MAP_WIDTH + AI_X] = rand() % COLORS_NBRS; // Attribution aléatoire d'une couleur différente à l'IA
}



// Fonction pour générer une carte aléatoire
char *generate_random_map()
{
    char *map;

    map = malloc(sizeof(char) * MAP_HEIGHT * MAP_WIDTH); // Allocation de mémoire pour la carte
    random_map(map); // Génération de la carte aléatoire
    return map; // Retourne la carte générée
}

// Fonction pour générer une carte vide
char *generate_empty_map()
{
    char *map;
    map = malloc(sizeof(char) * MAP_HEIGHT * MAP_WIDTH); // Allocation de mémoire pour la carte
    for (int i = 0 ; i < (MAP_HEIGHT * MAP_WIDTH) ; i++) // Parcours de toutes les cases de la carte
        map[i] = 0; // Initialisation de toutes les cases à zéro
    return map; // Retourne la carte vide
}

// Fonction pour copier une carte
char *copy_map(char *map)
{
    char *new_map;

    new_map = malloc(sizeof(char) * MAP_HEIGHT * MAP_WIDTH); // Allocation de mémoire pour la nouvelle carte
    for (int i = 0 ; i < (MAP_HEIGHT * MAP_WIDTH) ; i++) // Parcours de toutes les cases de la carte
        new_map[i] = map[i]; // Copie de chaque case de la carte originale vers la nouvelle carte
    return new_map; // Retourne la nouvelle carte copiée
}

Cell* creer_grille(){
  Cell* g = malloc(GRID_SIZE * GRID_SIZE * sizeof(Cell));
  for (int i = 0; i < GRID_SIZE * GRID_SIZE; i++){
    g[i].shape = sfRectangleShape_create();
    sfVector2f size = {CELL_SIZE, CELL_SIZE};
    sfRectangleShape_setSize(g[i].shape, size);
    sfVector2f position = {(i % GRID_SIZE) * CELL_SIZE, (i / GRID_SIZE) * CELL_SIZE};
    sfRectangleShape_setPosition(g[i].shape, position);
    g[i].color = sfCyan;
    sfRectangleShape_setFillColor(g[i].shape, g[i].color);
  }
  return g;
}
