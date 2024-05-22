#include "my.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

void print_grid(char* map, Cell* grid, sfRenderWindow *window)
{
    char *colors_code[] = COLORS_CODE; // Tableau de codes de couleur
    for (int y = 0 ; y < MAP_HEIGHT ; y++) // Parcours des lignes de la map
    {
        for (int x = 0 ; x < MAP_WIDTH ; x++){ // Parcours des colonnes de la map
            //Remplissage des cellules de la grille
            int couleur = map[y * MAP_WIDTH + x];
            if (colors_code[couleur] == "\e[40m") sfRectangleShape_setFillColor(grid[y* GRID_SIZE + x].shape, sfBlack);
            if (colors_code[couleur] == "\e[43m") sfRectangleShape_setFillColor(grid[y* GRID_SIZE + x].shape, sfYellow);
            if (colors_code[couleur] == "\e[41m") sfRectangleShape_setFillColor(grid[y* GRID_SIZE + x].shape, sfRed);
            if (colors_code[couleur] == "\e[44m") sfRectangleShape_setFillColor(grid[y* GRID_SIZE + x].shape, sfBlue);
            if (colors_code[couleur] == "\e[42m") sfRectangleShape_setFillColor(grid[y* GRID_SIZE + x].shape, sfGreen);
            if (colors_code[couleur] == "\e[105m") sfRectangleShape_setFillColor(grid[y* GRID_SIZE + x].shape, sfMagenta);
        }
    }
    //Affichage de la grille
    for (int i = 0; i < GRID_SIZE * GRID_SIZE; ++i) sfRenderWindow_drawRectangleShape(window, grid[i].shape, NULL);
}

// Fonction pour générer une map aléatoire
void random_map(char *map)
{
    srand(time(NULL)); // Initialisation de la graine pour la génération aléatoire
    for (int i = 0 ; i < (MAP_HEIGHT * MAP_WIDTH) ; i++) // Parcours de toutes les cases de la map
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



// Fonction pour générer une map aléatoire
char *generate_random_map()
{
    char *map; //Déclaration de la map

    map = malloc(sizeof(char) * MAP_HEIGHT * MAP_WIDTH); // Allocation de mémoire pour la map
    random_map(map); // Génération de la map aléatoire
    return map; // Renvoie la map générée
}

// Fonction pour générer une map vide
char *generate_empty_map()
{
    char *map;
    map = malloc(sizeof(char) * MAP_HEIGHT * MAP_WIDTH); // Allocation de mémoire pour la map
    for (int i = 0 ; i < (MAP_HEIGHT * MAP_WIDTH) ; i++) // Parcours de toutes les cases de la map
        map[i] = 0; // Initialisation de toutes les cases à zéro
    return map; // Retourne la map vide
}

// Fonction pour copier une map
char *copy_map(char *map)
{
    char *new_map; //Déclaration de la nouvelle map
    new_map = malloc(sizeof(char) * MAP_HEIGHT * MAP_WIDTH); // Allocation de mémoire pour la nouvelle map
    for (int i = 0 ; i < (MAP_HEIGHT * MAP_WIDTH) ; i++) // Parcours de toutes les cases de la map
        new_map[i] = map[i]; // Copie de chaque case de la map originale vers la nouvelle map
    return new_map; // Renvoie la nouvelle map
}


//Renvoie une nouvelle grille de jeu
Cell* creer_grille(sfVector2f position) {
    Cell* g = malloc(GRID_SIZE * GRID_SIZE * sizeof(Cell)); //Allocation de la mémoire pour la grille
    for (int i = 0; i < GRID_SIZE * GRID_SIZE; i++) { //Parcours de la grille
        g[i].shape = sfRectangleShape_create(); //Chaque cellule est un rectangle
        sfVector2f size = {CELL_SIZE, CELL_SIZE}; //On définit leur taille de sorte à les rendre carrées
        sfRectangleShape_setSize(g[i].shape, size);
        sfVector2f cellPosition = { //On place les cases en fonction de la taille de la grille
            position.x + (i % GRID_SIZE) * CELL_SIZE,
            (position.y)/2 + (i / GRID_SIZE) * CELL_SIZE
        };
        sfRectangleShape_setPosition(g[i].shape, cellPosition);
        g[i].color = sfCyan; //Pour les cases non initialisées (si tout se passe bien aucune case ne sera de couleur cyan)
        sfRectangleShape_setFillColor(g[i].shape, g[i].color);
    }
    return g; //Renvoie la grille
}
