#include "my.h"
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>


// Fonction pour trouver le minimum parmi deux valeurs
int min(int a, int b) {
    return (a < b) ? a : b;
}

// Fonction pour trouver le maximum parmi deux valeurs
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Fonction d'évaluation (score) pour l'état du jeu
int evaluate(char *map, char player) {
    char *rec_map;
    int count = 0; // Initialise le compteur de zones explorées

    rec_map = generate_empty_map(); // Crée une map de zones explorées

    // Marque la zone explorée par le joueur correspondant
    if (player == AI)
        mark_zone(map, rec_map, AI_X, AI_Y, map[AI_Y * MAP_WIDTH + AI_X]);
    else
        mark_zone(map, rec_map, PLAYER_X, PLAYER_Y, map[PLAYER_Y * MAP_WIDTH + PLAYER_X]);

    // Compte le nombre de zones explorées
    for (int i = 0 ; i < (MAP_HEIGHT * MAP_WIDTH) ; i++)
    {
        if (rec_map[i] == 1)
        {
            count++; // Incrémente le compteur pour chaque zone explorée
        }
    }
    free(rec_map); // Libère la mémoire allouée pour la map de zones explorées
    return count; // Retourne le score basé sur le nombre de zones explorées
}


// Implémentation de l'algorithme Minimax
int minimax(char *map, int alpha, int beta, int maximiser,char color, char player, int depth) {
    // Si la profondeur maximale est atteinte ou si le jeu est terminé
    if (is_game_over(map) || depth >= DEPTH ) {
        int player_score = evaluate(map,PLAYER);
        int ai_score = evaluate(map,AI);
        int score;

        if (player == PLAYER) { // Evaluation du score basé sur la difference de point et de la profondeur
            score = (player_score - ai_score)-4*depth;
            return (score);
        }
        else {
            score = (ai_score - player_score)-4*depth;
            return score;
        }
    }

    if (maximiser) {
        int bestScore = INT_MIN;
        for (int i = 0; i < COLORS_NBRS; i++) {
            // Évite de choisir la couleur actuelle de l'IA ou celle du joueur
            if (i == map[AI_Y * MAP_WIDTH + AI_X] || i == map[PLAYER_Y * MAP_WIDTH + PLAYER_X])
                continue;

            char *tmp = copy_map(map); // Copie du plateau
            char *rec_map = generate_empty_map(); // Création d'une map de zones explorées
            if (player == AI)
                play_color(tmp, rec_map, AI_X, AI_Y, map[AI_Y * MAP_WIDTH + AI_X], i); // Joue la couleur sur une copie du plateau
            else
                play_color(tmp, rec_map, PLAYER_X, PLAYER_Y, map[PLAYER_Y * MAP_WIDTH + PLAYER_X], i); // Joue la couleur sur une copie du plateau

            // Appel récursif minimax pour évaluer les coups possibles du joueur
            int score = minimax(tmp, alpha, beta, 0, i, player, depth + 1);
            bestScore = max(bestScore, score); // Met à jour le meilleur score trouvé jusqu'à présent

            free(rec_map); // Libère la mémoire allouée pour la map de zones explorées
            free(tmp); // Libère la mémoire allouée pour la copie du plateau

            alpha = max(alpha,score);
            if (beta <= alpha)
                break;
        }
        return bestScore;
    }
    else {
        int bestScore = INT_MAX;
        for (int i = 0; i < COLORS_NBRS; i++) {
            // Évite de choisir la couleur actuelle de l'IA ou celle du joueur
            if (i == map[AI_Y * MAP_WIDTH + AI_X] || i == map[PLAYER_Y * MAP_WIDTH + PLAYER_X])
                continue;

            char *tmp = copy_map(map); // Copie du plateau
            char *rec_map = generate_empty_map(); // Création d'une map de zones explorées
            if (player == PLAYER)
                play_color(tmp, rec_map, AI_X, AI_Y, map[AI_Y * MAP_WIDTH + AI_X], i); // Joue la couleur sur une copie du plateau
            else
                play_color(tmp, rec_map, PLAYER_X, PLAYER_Y, map[PLAYER_Y * MAP_WIDTH + PLAYER_X], i); // Joue la couleur sur une copie du plateau

            // Appel récursif minimax pour évaluer les coups possibles du joueur
            int score = minimax(tmp, alpha, beta, 1, i, player, depth + 1);
            bestScore = min(bestScore, score); // Met à jour le meilleur score trouvé jusqu'à présent

            free(rec_map); // Libère la mémoire allouée pour la map de zones explorées
            free(tmp); // Libère la mémoire allouée pour la copie du plateau
            beta = min(beta,score);
            if (beta <= alpha)
                break;
        }
        return bestScore;
    }
}

// Fonction principale de l'IA
char BestMove(char *map, char player) {
    char *tmp;
    char *rec_map;
    int bestscore = INT_MIN;
    int alpha = INT_MIN;
    int beta = INT_MAX;
    int move;

    for (int i = 0; i < COLORS_NBRS; i++) {
        if (i == map[AI_Y * MAP_WIDTH + AI_X] || i == map[PLAYER_Y * MAP_WIDTH + PLAYER_X]) {
            continue; // Éviter de choisir la couleur actuelle du joueur
        }
            tmp = copy_map(map);
            rec_map = generate_empty_map();
            play_color(tmp, rec_map, AI_X, AI_Y, map[AI_Y * MAP_WIDTH + AI_X], i);
            // Évaluation initiale avant la réévaluation
            int score = minimax(tmp, alpha, beta, 0, i, player, 0);
            if (score >= bestscore) {
                bestscore = score;
                move = i;
            }
            // Libération de la mémoire
            free(rec_map);
            free(tmp);
    }
    return move;
}
