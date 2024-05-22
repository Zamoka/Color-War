// my.h
#ifndef MY_H
#define MY_H
#include <SFML/Window.h>
#include <SFML/Graphics.h>
#include <SFML/Window/Keyboard.h>

// Game Config
extern int DEPTH;
#define FIRST_TO_PLAY PLAYER // Joueur qui commence la partie
#define MAP_WIDTH 9 // Largeur de la carte
#define MAP_HEIGHT MAP_WIDTH // Hauteur de la carte
#define AI_X (MAP_WIDTH - 1) // Position en X de l'IA
#define AI_Y 0 // Position en Y de l'IA
#define PLAYER_X 0 // Position en X du joueur
#define PLAYER_Y (MAP_HEIGHT - 1) // Position en Y du joueur
#define CLEAR_NBR 4 // Nombre de lignes à effacer pour nettoyer l'écran

// General
#define NULL ((void *)0) // Macro pour la valeur NULL
#define SCORE_UNSET (-1) // Valeur indiquant que le score n'est pas défini

//Colors
#define COLORS_NBRS 6 // Nombre de couleurs disponibles
#define COLOR_RESET "\e[0m" // Code de réinitialisation de la couleur dans le terminal
#define COLORS_CODE {"\e[40m", "\e[43m", "\e[41m", "\e[44m", "\e[42m", "\e[105m"} // Codes de couleur pour chaque couleur
#define COLORS_KEY {'B', 'y', 'r', 'b', 'g', 'p'} // Clés associées à chaque couleur
#define COLORS_NAME {"black", "yellow", "red", "blue", "green", "pink"} // Noms des couleurs

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define GRID_SIZE MAP_WIDTH
#define CELL_SIZE 675/GRID_SIZE

#define BUTTON_WIDTH 300
#define BUTTON_HEIGHT 300
#define BUTTON_MARGIN 50

// Structure représentant une case de la grille
typedef struct {
    sfRectangleShape *shape;
    sfColor color;
} Cell;

// Déclarations externes pour player et bool
extern enum bool // Déclaration d'un type énuméré booléen
{
    FALSE = 0, // Valeur FALSE équivaut à 0
    TRUE // Valeur TRUE équivaut à 1
} bool; // Nom du type énuméré

extern enum player // Déclaration d'un type énuméré pour les joueurs
{
    PLAYER = 1, // Joueur
    AI // Intelligence artificielle
} player; // Nom du type énuméré

// Functions
Cell* creer_grille(sfVector2f position);
void mark_zone(char *map, char *rec_map, int x, int y, char color);
void inputs(sfRenderWindow *window, sfEvent event);
char *generate_random_map(); // Génère une carte aléatoire
char *generate_empty_map(); // Génère une carte vide
void print_grid(char* map, Cell* grid, sfRenderWindow *window); //Affiche la carte dans une fenêtre
char *copy_map(char *map); // Copie la carte
enum bool is_game_over(char *map); // Vérifie si la partie est terminée
void player_turn(char *map, Cell* grid, sfRectangleShape **squares, sfRenderWindow *window, sfEvent event, sfFont* font); // Tour du joueur
void ai_turn(char *map, Cell* grid, sfRenderWindow *window); // Tour de l'IA
char index_of_elem_in_array(char elem, char *array, int array_length); // Trouve l'indice d'un élément dans un tableau
char BestMove(char * map, char player);
int evaluate(char *map, char player);
int count_color(char *map, char color, int x, int y); // Compte le nombre de cases d'une couleur
void play_color(char *map, char *rec_map, int x, int y, char old_color, char new_color); // Joue une couleur et met à jour la carte
void end_game(char *map, Cell* grid, sfRenderWindow *window, sfFont *font); // Affiche le résultat de la partie
void createButtons(sfRectangleShape *buttons[], sfText *buttonTexts[], sfRenderWindow *window, sfFont *font);
sfBool isMouseOverButton(sfRectangleShape *button, sfRenderWindow *window);
int handleEvents(sfRenderWindow *window, sfRectangleShape *buttons[], const char *labels[]);
void updateButtons(sfRectangleShape *buttons[], sfRenderWindow *window);
void drawButtons(sfRenderWindow *window, sfRectangleShape *buttons[], sfText *buttonTexts[]);
void affiche_couleurs(sfRectangleShape **squares, sfRenderWindow *window, sfFont *font);
void displayText(sfRenderWindow *window, sfFont *font, char* s);
sfRectangleShape ** create_squares(sfRenderWindow *window);
void update_squares(sfRectangleShape **squares, int color_player, int color_ia);
void affiche_score(char* map, sfRenderWindow * window, sfFont * font);
void play_again(sfRenderWindow *window, sfFont *font);
int isSPressed();
int isEscPressed();
sfSprite* createAndLoadSprite(const char* imagePath);

#endif /* MY_H */
