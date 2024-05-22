#include "my.h"
#include <stdio.h>
#include <stdlib.h>

// Fonction pour marquer la zone explorée
void mark_zone(char *map, char *rec_map, int x, int y, char color)
{
    int index = y * MAP_WIDTH + x;

    // Vérifie si la case a déjà été explorée ou si elle n'a pas la bonne couleur
    if (rec_map[index] != 0 || map[index] != color)
        return; // Quitte la fonction si les conditions ne sont pas remplies
    rec_map[index] = 1; // Marque la case comme explorée
    // Appels récursifs pour marquer les cases adjacentes de la même couleur
    if (x + 1 < MAP_WIDTH)
        mark_zone(map, rec_map, x+1, y, color);
    if (y + 1 < MAP_HEIGHT)
        mark_zone(map, rec_map, x, y+1, color);
    if (x - 1 >= 0)
        mark_zone(map, rec_map, x-1, y, color);
    if (y - 1 >= 0)
        mark_zone(map, rec_map, x, y-1, color);
}

// Fonction pour vérifier si la partie est terminée
enum bool is_game_over(char *map)
{
    char *rec_map;
    char ret;

    rec_map = generate_empty_map(); // Crée une map de zones explorées
    mark_zone(map, rec_map, AI_X, AI_Y, map[AI_Y * MAP_WIDTH + AI_X]); // Marque la zone explorée par l'IA
    mark_zone(map, rec_map, PLAYER_X, PLAYER_Y, map[PLAYER_Y * MAP_WIDTH + PLAYER_X]); // Marque la zone explorée par le joueur
    ret = TRUE; // Initialise le statut de fin de partie
    // Vérifie si toutes les cases ont été explorées
    for (int i = 0 ; i < (MAP_HEIGHT * MAP_WIDTH) ; i++)
    {
        if (rec_map[i] != 1)
        {
            ret = FALSE; // Met à jour le statut si une case n'a pas été explorée
            break;
        }
    }
    free(rec_map); // Libère la mémoire allouée pour la map de zones explorées
    return ret; // Renvoie le statut de fin de partie
}

// Fonction pour jouer une couleur et mettre à jour la map
void play_color(char *map, char *rec_map, int x, int y, char old_color, char new_color)
{
    // Vérifie si la case n'a pas la bonne couleur ou si elle a déjà été visitée
    if (map[y * MAP_WIDTH + x] != old_color || rec_map[y * MAP_WIDTH + x] != 0)
        return; // Sort de la fonction si les conditions ne sont pas remplies
    map[y * MAP_WIDTH + x] = new_color; // Met à jour la couleur de la case
    rec_map[y * MAP_WIDTH + x] = 1; // Marque la case comme visitée
    // Appels récursifs pour mettre à jour les cases adjacentes
    if (x + 1 < MAP_WIDTH)
        play_color(map, rec_map, x+1, y, old_color, new_color);
    if (x - 1 >= 0)
        play_color(map, rec_map, x-1, y, old_color, new_color);
    if (y + 1 < MAP_HEIGHT)
        play_color(map, rec_map, x, y+1, old_color, new_color);
    if (y - 1 >= 0)
        play_color(map, rec_map, x, y-1, old_color, new_color);
}


//Simples fonctions pour détecter l'appui sur certaines touches (pourinteragir avec le programme)
int isEscPressed() {return sfKeyboard_isKeyPressed(sfKeyEscape);}

int isSPressed(){return sfKeyboard_isKeyPressed(sfKeyS);}

int isNPressed() {return sfKeyboard_isKeyPressed(sfKeyN);}

int isRPressed(){return sfKeyboard_isKeyPressed(sfKeyR);}

int isBPressed(){return sfKeyboard_isKeyPressed(sfKeyB);}

int isMPressed() {return sfKeyboard_isKeyPressed(sfKeyM);}

int isVPressed() {return sfKeyboard_isKeyPressed(sfKeyV);}

int isJPressed() {return sfKeyboard_isKeyPressed(sfKeyJ);}

char collect(){ //Renvoie la couleur choisie en fonction de la touche pressée
  if (isNPressed()) return 'B';
  if (isMPressed()) return 'p';
  if (isJPressed()) return 'y';
  if (isVPressed()) return 'g';
  if (isRPressed()) return 'r';
  if (isBPressed()) return 'b';
  else{
    return 'z'; //Par défaut, si aucune touche n'est appuyée
  }
}

char index_of_elem_in_array(char elem, char *array, int array_length) //Renvoie l'indice de la couleur passée en argument
{
    for (int i = 0 ; i < array_length ; i++) // Parcours de tout le tableau
    {
        if (array[i] == elem) // Vérifie si l'élément actuel correspond à celui recherché
            return i; // Renvoie l'indice de l'élément s'il est trouvé
    }
    return -1; // Renvoie -1 si l'élément n'est pas trouvé dans le tableau
}

// Fonction pour le tour du joueur
void player_turn(char *map, Cell* grid, sfRectangleShape ** squares, sfRenderWindow *window, sfEvent event, sfFont* font)
{
    sfColor gray = sfColor_fromRGB(128, 128, 128); // Définition de la couleur gris

    char colors_key[] = COLORS_KEY; // Tableau des clés des couleurs
    char *colors_name[] = COLORS_NAME; // Tableau des noms des couleurs
    char user_input; // Déclaration de la variable contenant le choix de couleur du joueur
    char color_played; // Indice de la couleur choisie
    char *rec_map; // map de zones explorées


    int f = 1; // Initialisation d'un indicateur de boucle
    while (f) // Boucle pour le tour du joueur
    {
        update_squares(squares, map[PLAYER_Y * MAP_WIDTH + PLAYER_X], map[AI_Y * MAP_WIDTH + AI_X]); // Mise à jour des couleurs jouables

        user_input = collect(); // Collecte de la couleur choisie par le joueur
        while (sfRenderWindow_pollEvent(window, &event)) { // Gestion des événements de la fenêtre
            inputs(window, event); // Traitement des événements
        }

        color_played = index_of_elem_in_array(user_input, colors_key, COLORS_NBRS); // Récupération de l'indice de la couleur choisie
        if (color_played == -1){ // Vérification si la couleur choisie est invalide
            ; // On ne fait rien
          }
        else{
          if (color_played == map[PLAYER_Y * MAP_WIDTH + PLAYER_X] || color_played == map[AI_Y * MAP_WIDTH + AI_X]){ // Vérification si la couleur choisie est déjà celle du joueur ou de l'IA
            sfRenderWindow_clear(window, gray); // Efface le contenu de la fenêtre
            affiche_score(map, window, font); // Affiche le score
            affiche_couleurs(squares, window, font); // Affiche les couleurs jouables
            print_grid(map, grid, window); // Affiche la map de jeu
            sfRenderWindow_display(window); // Affiche la fenêtre
          }
        else{
            f = 0; // Sortie de la boucle si la couleur choisie est valide
          }
        }
    }
    rec_map = generate_empty_map(); // Crée une map de zones explorées
    play_color(map, rec_map, PLAYER_X, PLAYER_Y, map[PLAYER_Y * MAP_WIDTH + PLAYER_X], color_played); // Joue la couleur choisie par le joueur
    free(rec_map); // Libère la mémoire allouée pour la map de zones explorées
}


// Fonction pour le tour de l'IA
void ai_turn(char *map, Cell* grid, sfRenderWindow *window)
{
    char color_played;
    char *rec_map;
    print_grid(map, grid, window); //Affiche la grille de jeu

    color_played = BestMove(map, AI); // L'IA choisit la couleur à jouer
    rec_map = generate_empty_map(); // Crée une map de zones explorées
    play_color(map, rec_map, AI_X, AI_Y, map[AI_Y * MAP_WIDTH + AI_X], color_played); // Joue la couleur choisie par l'IA
    free(rec_map); // Libère la mémoire allouée pour la map de zones explorées
}

// Fonction pour compter le nombre de cases d'une couleur dans la zone explorée
int count_color(char *map, char color, int x, int y)
{
    char *rec_map;
    int score; // On déclare le score

    rec_map = generate_empty_map(); // Crée une map de zones explorées
    mark_zone(map, rec_map, x, y, color); // Marque la zone explorée
    score = 0;
    // Compte le nombre de cases de la couleur dans la zone explorée
    for (int i = 0 ; i < (MAP_WIDTH * MAP_HEIGHT) ; i++)
        score += rec_map[i];
    free(rec_map); // Libère la mémoire allouée pour la map de zones explorées
    return score; // Renvoie le nombre de cases de la couleur
}

// Fonction pour afficher le résultat de la partie
void end_game(char *map, Cell* grid, sfRenderWindow *window, sfFont *font)
{
    sfColor gray = sfColor_fromRGB(128, 128, 128); //On définit la couleur gray

    sfRenderWindow_clear(window, gray); //Clear la fenêtre d'affichage
    print_grid(map, grid, window); //Affiche la grille de jeu
    int ai_score = count_color(map, map[AI_Y * MAP_WIDTH + AI_X], AI_X, AI_Y); // Compte le nombre de cases explorées par l'IA
    int player_score = (MAP_HEIGHT * MAP_WIDTH) - ai_score; // Calcule le score du joueur
    affiche_score(map, window, font); //Affiche le score
    play_again(window, font); //Propose de relancer une partie en appuyant sur S

    if (ai_score > player_score){ //En cas de défaite
      displayText(window, font, "Perdu ...");
    }
    else if (ai_score < player_score){ //En cas de victoire
      displayText(window, font, "Victoire !");
    }
    else //En cas d'égalité
      displayText(window, font, "Egalité :/");

    sfRenderWindow_display(window); //Affiche la fenêtre de jeu
}
