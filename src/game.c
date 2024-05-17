// // game.c
// #include "my.h" // Inclusion de l'en-tête contenant les déclarations nécessaires
// #include <stdio.h>
// #include <stdlib.h>
//
// // Fonction pour marquer la zone explorée
// void mark_zone(char *map, char *rec_map, int x, int y, char color)
// {
//     int index = y * MAP_WIDTH + x;
//
//     // Vérifie si la case a déjà été explorée ou si elle n'a pas la bonne couleur
//     if (rec_map[index] != 0 || map[index] != color)
//         return; // Quitte la fonction si les conditions ne sont pas remplies
//     rec_map[index] = 1; // Marque la case comme explorée
//     // Appels récursifs pour marquer les cases adjacentes de la même couleur
//     if (x + 1 < MAP_WIDTH)
//         mark_zone(map, rec_map, x+1, y, color);
//     if (y + 1 < MAP_HEIGHT)
//         mark_zone(map, rec_map, x, y+1, color);
//     if (x - 1 >= 0)
//         mark_zone(map, rec_map, x-1, y, color);
//     if (y - 1 >= 0)
//         mark_zone(map, rec_map, x, y-1, color);
// }
//
// // Fonction pour vérifier si la partie est terminée
// enum bool is_game_over(char *map)
// {
//     char *rec_map;
//     char ret;
//
//     rec_map = generate_empty_map(); // Crée une carte de zones explorées
//     mark_zone(map, rec_map, AI_X, AI_Y, map[AI_Y * MAP_WIDTH + AI_X]); // Marque la zone explorée par l'IA
//     mark_zone(map, rec_map, PLAYER_X, PLAYER_Y, map[PLAYER_Y * MAP_WIDTH + PLAYER_X]); // Marque la zone explorée par le joueur
//     ret = TRUE; // Initialise le statut de fin de partie
//     // Vérifie si toutes les cases ont été explorées
//     for (int i = 0 ; i < (MAP_HEIGHT * MAP_WIDTH) ; i++)
//     {
//         if (rec_map[i] != 1)
//         {
//             ret = FALSE; // Met à jour le statut si une case n'a pas été explorée
//             break;
//         }
//     }
//     free(rec_map); // Libère la mémoire allouée pour la carte de zones explorées
//     return ret; // Retourne le statut de fin de partie
// }
//
// // Fonction pour jouer une couleur et mettre à jour la carte
// void play_color(char *map, char *rec_map, int x, int y, char old_color, char new_color)
// {
//     // Vérifie si la case n'a pas la bonne couleur ou si elle a déjà été visitée
//     if (map[y * MAP_WIDTH + x] != old_color || rec_map[y * MAP_WIDTH + x] != 0)
//         return; // Sort de la fonction si les conditions ne sont pas remplies
//     map[y * MAP_WIDTH + x] = new_color; // Met à jour la couleur de la case
//     rec_map[y * MAP_WIDTH + x] = 1; // Marque la case comme visitée
//     // Appels récursifs pour mettre à jour les cases adjacentes
//     if (x + 1 < MAP_WIDTH)
//         play_color(map, rec_map, x+1, y, old_color, new_color);
//     if (x - 1 >= 0)
//         play_color(map, rec_map, x-1, y, old_color, new_color);
//     if (y + 1 < MAP_HEIGHT)
//         play_color(map, rec_map, x, y+1, old_color, new_color);
//     if (y - 1 >= 0)
//         play_color(map, rec_map, x, y-1, old_color, new_color);
// }
//
// // Fonction pour le tour du joueur
// void player_turn(char *map, char *message, Cell* grid, sfRenderWindow *window)
// {
//     char colors_key[] = COLORS_KEY;
//     char *colors_name[] = COLORS_NAME;
//     char user_input;
//     char color_played;
//     char *rec_map;
//
//     clear_screen();
//     if (message)
//         printf("%s\n\n", message);
//     print_mapu(map, grid, window);
//     printf("\n");
//     for (int i = 0 ; i < COLORS_NBRS ; i++)
//         printf("%c => %s  ", colors_key[i], colors_name[i]);
//     // Demande à l'utilisateur de choisir une couleur
//     while (TRUE)
//     {
//         printf("\nYour turn: ");
//         (void)scanf(" %c", &user_input);
//         if ((color_played = index_of_elem_in_array(user_input, colors_key, COLORS_NBRS)) == -1)
//             printf("Invalid color code");
//         else if (color_played == map[PLAYER_Y * MAP_WIDTH + PLAYER_X] || color_played == map[AI_Y * MAP_WIDTH + AI_X])
//             printf("Color played is your color or AI's color");
//         else
//             break;
//     }
//     rec_map = generate_empty_map(); // Crée une carte de zones explorées
//     play_color(map, rec_map, PLAYER_X, PLAYER_Y, map[PLAYER_Y * MAP_WIDTH + PLAYER_X], color_played); // Joue la couleur choisie par le joueur
//     free(rec_map); // Libère la mémoire allouée pour la carte de zones explorées
// }
//
// // Fonction pour le tour de l'IA
// void ai_turn(char *map, char **message, Cell* grid, sfRenderWindow *window)
// {
//     char color_played;
//     char *rec_map;
//
//     clear_screen();
//     print_mapu(map, grid, window);
//     printf("\nAI is playing ...");
//
//     color_played = ai_play(map, message); // L'IA choisit la couleur à jouer
//     rec_map = generate_empty_map(); // Crée une carte de zones explorées
//     play_color(map, rec_map, AI_X, AI_Y, map[AI_Y * MAP_WIDTH + AI_X], color_played); // Joue la couleur choisie par l'IA
//     free(rec_map); // Libère la mémoire allouée pour la carte de zones explorées
// }
//
// // Fonction pour compter le nombre de cases d'une couleur dans la zone explorée
// int count_color(char *map, char color, int x, int y)
// {
//     char *rec_map;
//     int score;
//
//     rec_map = generate_empty_map(); // Crée une carte de zones explorées
//     mark_zone(map, rec_map, x, y, color); // Marque la zone explorée
//     score = 0;
//     // Compte le nombre de cases de la couleur dans la zone explorée
//     for (int i = 0 ; i < (MAP_WIDTH * MAP_HEIGHT) ; i++)
//         score += rec_map[i];
//     free(rec_map); // Libère la mémoire allouée pour la carte de zones explorées
//     return score; // Retourne le nombre de cases de la couleur
// }
//
// // Fonction pour afficher le résultat de la partie
// void end_game(char *map, Cell* grid, sfRenderWindow *window)
// {
//     int ai_score;
//     int player_score;
//
//     clear_screen();
//     print_mapu(map, grid, window);
//     printf("\n");
//     ai_score = count_color(map, map[AI_Y * MAP_WIDTH + AI_X], AI_X, AI_Y); // Compte le nombre de cases explorées par l'IA
//     player_score = (MAP_HEIGHT * MAP_WIDTH) - ai_score; // Calcule le score du joueur
//     printf("AI: %d\n", ai_score);
//     printf("Player: %d\n\n", player_score);
//     // Affiche le résultat de la partie
//     if (ai_score > player_score)
//         printf("AI won !! ;)\n");
//     else if (ai_score < player_score)
//         printf("Player won ... :'(\n");
//     else
//         printf("It's a draw :/\n");
// }

// game.c
#include "my.h" // Inclusion de l'en-tête contenant les déclarations nécessaires
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

    rec_map = generate_empty_map(); // Crée une carte de zones explorées
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
    free(rec_map); // Libère la mémoire allouée pour la carte de zones explorées
    return ret; // Retourne le statut de fin de partie
}

// Fonction pour jouer une couleur et mettre à jour la carte
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

// Fonction pour le tour du joueur
void player_turn(char *map, Cell* grid, sfRenderWindow *window)
{
    char colors_key[] = COLORS_KEY;
    char *colors_name[] = COLORS_NAME;
    char user_input;
    char color_played;
    char *rec_map;

    clear_screen();
    print_mapu(map, grid, window);
    printf("\n");
    for (int i = 0 ; i < COLORS_NBRS ; i++)
        printf("%c => %s  ", colors_key[i], colors_name[i]);
    // Demande à l'utilisateur de choisir une couleur
    while (TRUE)
    {
        printf("\nYour turn: ");
        (void)scanf(" %c", &user_input);
        if ((color_played = index_of_elem_in_array(user_input, colors_key, COLORS_NBRS)) == -1)
            printf("Invalid color code");
        else if (color_played == map[PLAYER_Y * MAP_WIDTH + PLAYER_X] || color_played == map[AI_Y * MAP_WIDTH + AI_X])
            printf("Color played is your color or AI's color");
        else
            break;
    }
    rec_map = generate_empty_map(); // Crée une carte de zones explorées
    play_color(map, rec_map, PLAYER_X, PLAYER_Y, map[PLAYER_Y * MAP_WIDTH + PLAYER_X], color_played); // Joue la couleur choisie par le joueur
    free(rec_map); // Libère la mémoire allouée pour la carte de zones explorées
}

// Fonction pour le tour de l'IA
void ai_turn(char *map, Cell* grid, sfRenderWindow *window)
{
    char color_played;
    char *rec_map;

    clear_screen();
    print_mapu(map, grid, window);
    printf("\nAI is playing ...");

    color_played = BestMove(map, AI); // L'IA choisit la couleur à jouer
    rec_map = generate_empty_map(); // Crée une carte de zones explorées
    play_color(map, rec_map, AI_X, AI_Y, map[AI_Y * MAP_WIDTH + AI_X], color_played); // Joue la couleur choisie par l'IA
    free(rec_map); // Libère la mémoire allouée pour la carte de zones explorées
}

// Fonction pour compter le nombre de cases d'une couleur dans la zone explorée
int count_color(char *map, char color, int x, int y)
{
    char *rec_map;
    int score;

    rec_map = generate_empty_map(); // Crée une carte de zones explorées
    mark_zone(map, rec_map, x, y, color); // Marque la zone explorée
    score = 0;
    // Compte le nombre de cases de la couleur dans la zone explorée
    for (int i = 0 ; i < (MAP_WIDTH * MAP_HEIGHT) ; i++)
        score += rec_map[i];
    free(rec_map); // Libère la mémoire allouée pour la carte de zones explorées
    return score; // Retourne le nombre de cases de la couleur
}

// Fonction pour afficher le résultat de la partie
void end_game(char *map, Cell* grid, sfRenderWindow *window)
{
    int ai_score;
    int player_score;

    clear_screen();
    print_mapu(map, grid, window);
    printf("\n");
    ai_score = count_color(map, map[AI_Y * MAP_WIDTH + AI_X], AI_X, AI_Y); // Compte le nombre de cases explorées par l'IA
    player_score = (MAP_HEIGHT * MAP_WIDTH) - ai_score; // Calcule le score du joueur
    printf("AI: %d\n", ai_score);
    printf("Player: %d\n\n", player_score);
    // Affiche le résultat de la partie
    if (ai_score > player_score)
        printf("AI won !! ;)\n");
    else if (ai_score < player_score)
        printf("Player won ... :'(\n");
    else
        printf("It's a draw :/\n");
}
