// // ai.c
// #include "my.h"
// #include <stdlib.h>
// #include <stdio.h>
//
// // Fonction pour trouver le score maximum dans un tableau de scores
// int max_score(int scores[COLORS_NBRS])
// {
//     int max_score = 0; // Initialisation du score maximum
//     for (int i = 0 ; i < COLORS_NBRS ; i++) // Parcours de tous les scores
//     {
//         if (scores[i] != SCORE_UNSET && scores[i] > max_score) // Vérifie si le score actuel est supérieur au score maximum
//             max_score = scores[i]; // Met à jour le score maximum si nécessaire
//     }
//     return max_score; // Retourne le score maximum
// }
//
// // Fonction pour trouver le score minimum dans un tableau de scores
// int min_score(int scores[COLORS_NBRS])
// {
//     int min_score = MAP_HEIGHT * MAP_WIDTH + 100; // Initialisation du score minimum avec une valeur élevée
//     for (int i = 0 ; i < COLORS_NBRS ; i++) // Parcours de tous les scores
//     {
//         if (scores[i] != SCORE_UNSET && scores[i] < min_score) // Vérifie si le score actuel est inférieur au score minimum
//             min_score = scores[i]; // Met à jour le score minimum si nécessaire
//     }
//     return min_score; // Retourne le score minimum
// }
//
// // Fonction récursive pour évaluer le score pour l'IA
// int ai_rec(char *map, char color, char player, int rec_count)
// {
//     char *rec_map; // Carte pour la récursion
//     int scores[COLORS_NBRS]; // Tableau pour stocker les scores
//     char other_player; // Autre joueur
//
//     // Condition d'arrêt de la récursion
//     if (rec_count > MAX_REC || is_game_over(map))
//         return count_color(map, map[AI_Y * MAP_WIDTH + AI_X], AI_X, AI_Y); // Retourne le score actuel si la récursion dépasse la limite ou si le jeu est terminé
//     map = copy_map(map); // Copie de la carte actuelle
//     rec_map = generate_empty_map(); // Création d'une nouvelle carte vide pour la récursion
//     if (player == PLAYER)
//         play_color(map, rec_map, PLAYER_X, PLAYER_Y, map[PLAYER_Y * MAP_WIDTH + PLAYER_X], color); // Tour du joueur
//     else
//         play_color(map, rec_map, AI_X, AI_Y, map[AI_Y * MAP_WIDTH + AI_X], color); // Tour de l'IA
//     free(rec_map); // Libère la mémoire de la carte pour la récursion
//     other_player = player == AI ? PLAYER : AI; // Détermine l'autre joueur
//     for (char color = 0 ; color < COLORS_NBRS ; color++) // Parcours de toutes les couleurs possibles
//     {
//         scores[color] = SCORE_UNSET; // Initialise les scores à SCORE_UNSET
//         if (color == map[AI_Y * MAP_WIDTH + AI_X] || color == map[PLAYER_Y * MAP_WIDTH + PLAYER_X]) // Vérifie si la couleur est déjà utilisée par l'IA ou le joueur
//             continue; // Passe à la prochaine couleur si elle est déjà utilisée
//         scores[color] = ai_rec(map, color, other_player, rec_count+1); // Appel récursif pour évaluer le score
//     }
//     free(map); // Libère la mémoire de la carte
//     if (player == AI)
//         return max_score(scores); // Retourne le score maximum si c'est le tour de l'IA
//     return min_score(scores); // Retourne le score minimum si c'est le tour du joueur
// }
//
// // Fonction pour le tour de l'IA
// char ai_play(char *map, char **message)
// {
//     int scores[COLORS_NBRS]; // Tableau pour stocker les scores
//     int max_score; // Score maximum
//     int max_score_color; // Couleur correspondant au score maximum
//     char *colors_name[COLORS_NBRS] = COLORS_NAME; // Noms des couleurs
//
//     for (int color = 0 ; color < COLORS_NBRS ; color++) // Parcours de toutes les couleurs possibles
//     {
//         scores[color] = 0; // Initialise les scores à zéro
//         if (color == map[AI_Y * MAP_WIDTH + AI_X] || color == map[PLAYER_Y * MAP_WIDTH + PLAYER_X]) // Vérifie si la couleur est déjà utilisée par l'IA ou le joueur
//             continue; // Passe à la prochaine couleur si elle est déjà utilisée
//         scores[color] = ai_rec(map, color, AI, 1); // Appel de la fonction récursive pour évaluer le score
//     }
//     max_score = 0; // Initialise le score maximum à zéro
//     for (int color = 0 ; color < COLORS_NBRS ; color++) // Parcours de toutes les couleurs possibles
//     {
//         if (scores[color] > max_score) // Vérifie si le score actuel est supérieur au score maximum
//         {
//             max_score = scores[color]; // Met à jour le score maximum
//             max_score_color = color; // Met à jour la couleur correspondant au score maximum
//         }
//     }
//     *message = malloc(sizeof(char) * 150); // Allocation de mémoire pour le message de l'IA
//     snprintf(*message, 150, "AI played %s\nAI max score is %d", colors_name[max_score_color], max_score); // Crée le message de l'IA
//     return max_score_color; // Retourne la couleur choisie par l'IA
// }


//ai.c
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

    rec_map = generate_empty_map(); // Crée une carte de zones explorées

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
    free(rec_map); // Libère la mémoire allouée pour la carte de zones explorées
    return count; // Retourne le score basé sur le nombre de zones explorées
}


// Implémentation de l'algorithme Minimax
int minimax(char *map, int alpha, int beta, int m,char color, char player, int depth) {
    // Si la profondeur maximale est atteinte ou si le jeu est terminé
    if (is_game_over(map) || depth >= DEPTH ) {
        int player_score = evaluate(map,PLAYER);
        int ai_score = evaluate(map,AI);
        int score;

        if (player == PLAYER) {
            score = (player_score - ai_score)-4*depth;

            return (score);
        }
        else {
            score = (ai_score - player_score)-4*depth;


            return (score);
        }
    }

    if (m) {
        int bestScore = INT_MIN;
        for (int i = 0; i < COLORS_NBRS; i++) {
            // Évite de choisir la couleur actuelle de l'IA ou celle du joueur
            if (i == map[AI_Y * MAP_WIDTH + AI_X] || i == map[PLAYER_Y * MAP_WIDTH + PLAYER_X])
                continue;

            char *tmp = copy_map(map); // Copie du plateau
            char *rec_map = generate_empty_map(); // Création d'une carte de zones explorées
            if (player == AI)
                play_color(tmp, rec_map, AI_X, AI_Y, map[AI_Y * MAP_WIDTH + AI_X], i); // Joue la couleur sur une copie du plateau
            else
                play_color(tmp, rec_map, PLAYER_X, PLAYER_Y, map[PLAYER_Y * MAP_WIDTH + PLAYER_X], i); // Joue la couleur sur une copie du plateau

            // Appel récursif minimax pour évaluer les coups possibles du joueur
            int score = minimax(tmp, alpha, beta, 0, i, player, depth + 1);
            bestScore = max(bestScore, score); // Met à jour le meilleur score trouvé jusqu'à présent

            free(rec_map); // Libère la mémoire allouée pour la carte de zones explorées
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
            char *rec_map = generate_empty_map(); // Création d'une carte de zones explorées
            if (player == PLAYER)
                play_color(tmp, rec_map, AI_X, AI_Y, map[AI_Y * MAP_WIDTH + AI_X], i); // Joue la couleur sur une copie du plateau
            else
                play_color(tmp, rec_map, PLAYER_X, PLAYER_Y, map[PLAYER_Y * MAP_WIDTH + PLAYER_X], i); // Joue la couleur sur une copie du plateau

            // Appel récursif minimax pour évaluer les coups possibles du joueur
            int score = minimax(tmp, alpha, beta, 1, i, player, depth + 1);
            bestScore = min(bestScore, score); // Met à jour le meilleur score trouvé jusqu'à présent

            free(rec_map); // Libère la mémoire allouée pour la carte de zones explorées
            free(tmp); // Libère la mémoire allouée pour la copie du plateau
            beta = min(beta,score);
            if (beta <= alpha)
                break;
        }
        return bestScore;
    }
    /*if (player == AI) { // Si c'est le tour de l'IA
        int bestScore = INT_MIN;
        for (int i = 0; i < COLORS_NBRS; i++) {
            // Évite de choisir la couleur actuelle de l'IA ou celle du joueur
            if (i == map[AI_Y * MAP_WIDTH + AI_X] || i == map[PLAYER_Y * MAP_WIDTH + PLAYER_X])
                continue;

            char *tmp = copy_map(map); // Copie du plateau
            char *rec_map = generate_empty_map(); // Création d'une carte de zones explorées
            play_color(tmp, rec_map, AI_X, AI_Y, map[AI_Y * MAP_WIDTH + AI_X], i); // Joue la couleur sur une copie du plateau
            // Appel récursif minimax pour évaluer les coups possibles du joueur
            int score = minimax(tmp, alpha, beta, i, PLAYER, depth + 1);
            bestScore = max(bestScore, score); // Met à jour le meilleur score trouvé jusqu'à présent

            free(rec_map); // Libère la mémoire allouée pour la carte de zones explorées
            free(tmp); // Libère la mémoire allouée pour la copie du plateau

            alpha = max(alpha, score); // Met à jour la valeur alpha
            if (beta <= alpha)
                break; // Coupure alpha-beta
        }
        return bestScore; // Retourne le meilleur score trouvé pour l'IA
    } else { // Si c'est le tour du joueur
        int bestScore = beta;
        for (int i = 0; i < COLORS_NBRS; i++) {
            // Évite de choisir la couleur actuelle de l'IA ou celle du joueur
            if (i == map[AI_Y * MAP_WIDTH + AI_X] || i == map[PLAYER_Y * MAP_WIDTH + PLAYER_X])
                continue;

            char *tmp = copy_map(map); // Copie du plateau
            char *rec_map = generate_empty_map(); // Création d'une carte de zones explorées
            play_color(tmp, rec_map, PLAYER_X, PLAYER_Y, map[PLAYER_Y * MAP_WIDTH + PLAYER_X], i); // Joue la couleur sur une copie du plateau
            // Appel récursif minimax pour évaluer les coups possibles de l'IA
            int score = minimax(tmp, alpha, beta, i, AI, depth + 1);
            bestScore = min(bestScore, score); // Met à jour le meilleur score trouvé jusqu'à présent

            free(rec_map); // Libère la mémoire allouée pour la carte de zones explorées
            free(tmp); // Libère la mémoire allouée pour la copie du plateau

            beta = min(beta, score); // Met à jour la valeur beta
            if (beta <= alpha)
                break; // Coupure alpha-beta
        }
        return bestScore; // Retourne le meilleur score trouvé pour le joueur
    }*/
}

// Fonction pour vérifier si le joueur est sur le point de gagner
int is_winning_condition(char *map, char player1, char player2, int advantage) {
    int player1_zone_size = evaluate(map, player1);
    int player2_zone_siez = evaluate(map,player2);

    // Vérifie si le joueur 1 est sur le point de gagner
    return ((player1_zone_size-advantage) > player2_zone_siez);
}

//renvoie 1 si aucun changement de couleur augment le score du joueur
int IsMoveImpossible(char *map)
{
    int verif = 0;
    int verif2 = 0;
    int chek = 0;

    for (int i = 0; i < COLORS_NBRS; i++) {
        char *tmp = copy_map(map); // Copie du plateau
        char *rec_map = generate_empty_map(); // Création d'une carte de zones explorées
        play_color(tmp, rec_map, PLAYER_X, PLAYER_Y, map[PLAYER_Y * MAP_WIDTH + PLAYER_X], i); // Joue la couleur sur une copie du plateau
        //printf("verif : %d  verif2 : %d     player : %d     Ia : %d     color : %d\n",verif,verif2,evaluate(tmp,PLAYER),evaluate(tmp,AI),i);

        verif = evaluate(tmp, PLAYER); // Évaluation de la taille de la zone explorée par le joueur

        if (verif2 == verif)
        {
            chek++;
        }

        verif2 = verif;
        free(rec_map); // Libération de la mémoire allouée pour la carte de zones explorées
        free(tmp); // Libération de la mémoire allouée pour la copie du plateau
    }
    //printf("chek : %d\n",chek);
    return (chek == COLORS_NBRS - 2); // Retourne vrai si la valeur évaluée est la même pour chaque couleur
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
        //if (is_winning_condition(map, AI, PLAYER,(MAP_WIDTH*MAP_HEIGHT*5%100))) {
        /*if (IsMoveImpossible(map) || is_winning_condition(map, AI, PLAYER,(MAP_WIDTH*MAP_HEIGHT*5/100))) {
            tmp = copy_map(map);
            rec_map = generate_empty_map();
            play_color(tmp, rec_map, AI_X, AI_Y, map[AI_Y * MAP_WIDTH + AI_X], i);
            int score = evaluate(tmp, AI); // Évalue la taille de la zone explorée par l'IA
            //printf("pas de minmax ici\n");
            // Priorise les coups qui augmentent la taille de la zone contrôlée par l'IA
            if (score >= bestscore) {
                bestscore = score;
                move = i;
            }
            free(rec_map);
            free(tmp);
        }
        else {*/
            tmp = copy_map(map);
            rec_map = generate_empty_map();
            play_color(tmp, rec_map, AI_X, AI_Y, map[AI_Y * MAP_WIDTH + AI_X], i);
            // Évaluation initiale avant la réévaluation
            int score = minimax(tmp, alpha, beta, 0, i, player, 0);
            //printf("minmax ici\n");
            if (score >= bestscore) {
                bestscore = score;
                move = i;
            }
            // Libération de la mémoire
            free(rec_map);
            free(tmp);
        //}
    }
    return move;
}
