// // main.c
// #include "my.h"
// #include <stdio.h>
// #include <stdlib.h>
//
// #include <SFML/Graphics.h>
//
// #include <SFML/Graphics.h>
// #include <stdlib.h>
// #include <stdio.h>
// #include <time.h>
// #include <SFML/Graphics.h>
// #include <stdlib.h>
// #include <stdio.h>
// #include <time.h>
// #include <SFML/Graphics.h>
//
//
// // int main() {
// //     // Création de la fenêtre SFML
// //     sfVideoMode mode = {WINDOW_WIDTH, WINDOW_HEIGHT, 32};
// //     sfRenderWindow* window = sfRenderWindow_create(mode, "Grid", sfResize | sfClose, NULL);
// //     Cell* grille = creer_grille();
// //
// //     // Boucle principale
// //     while (sfRenderWindow_isOpen(window)) {
// //         sfEvent event;
// //         while (sfRenderWindow_pollEvent(window, &event)) {
// //             if (event.type == sfEvtClosed)
// //                 sfRenderWindow_close(window);
// //         }
// //
// //         // Effacer la fenêtre
// //         sfRenderWindow_clear(window, sfWhite);
// //
// //         // Dessiner la grille sur la fenêtre
// //         for (int i = 0; i < GRID_SIZE * GRID_SIZE; ++i) {
// //             sfRenderWindow_drawRectangleShape(window, grille[i].shape, NULL);
// //         }
// //
// //         // Afficher la grille
// //         sfRenderWindow_display(window);
// //     }
//
// //     return 0;
// // }
//
//
//
//
// // int main(){
// //   printf("coucou \n");
// //   return 0;
// // }
//
//
// // int main()
// // {
// //   sfVideoMode mode = {WINDOW_WIDTH, WINDOW_HEIGHT, 32};
// //   sfRenderWindow *window = sfRenderWindow_create(mode, "GAMEEEE", sfResize | sfClose, NULL);
// //   Cell* g = creer_grille();
// //   char *map = generate_random_map(); // Génère une carte aléatoire
// //   char turn = FIRST_TO_PLAY; // Définit le joueur qui commence
// //   char *ai_message = NULL; // Message de l'IA (initialisé à NULL)
// //
// //   while (sfRenderWindow_isOpen(window)) {
// //     while (!is_game_over(map)) // Boucle principale du jeu jusqu'à la fin de la partie
// //     {
// //       sfEvent event;
// //               while (sfRenderWindow_pollEvent(window, &event)) {
// //                   if (event.type == sfEvtClosed)
// //                       sfRenderWindow_close(window);
// //               }
// //       sfRenderWindow_clear(window, sfWhite);
// //         if (turn == PLAYER) // Si c'est le tour du joueur
// //             player_turn(map, ai_message, g, window); // Tour du joueur
// //         else // Sinon, c'est le tour de l'IA
// //         {
// //             if (ai_message) // Si un message de l'IA existe
// //                 free(ai_message); // Libère la mémoire
// //             ai_turn(map, &ai_message, g, window); // Tour de l'IA
// //         }
// //         turn = turn == PLAYER ? AI : PLAYER; // Passe au prochain tour (joueur ou IA)
// //         sfRenderWindow_display(window);
// //     }
// //     end_game(map, g, window); // Fin du jeu (affiche le résultat)
// //     if (ai_message) // Si un message de l'IA existe
// //         free(ai_message); // Libère la mémoire
// //     free(map); // Libère la mémoire de la carte
// //   }
// //     return 0; // Termine le programme avec succès
// // }
//
// int main()
// {
//   sfVideoMode mode = {WINDOW_WIDTH, WINDOW_HEIGHT, 32};
//   sfRenderWindow *window = sfRenderWindow_create(mode, "GAMEEEE", sfResize | sfClose, NULL);
//   Cell* g = creer_grille();
//   char *map = generate_random_map(); // Génère une carte aléatoire
//
//   char turn = FIRST_TO_PLAY; // Définit le joueur qui commence
//   char *ai_message = NULL; // Message de l'IA (initialisé à NULL)
//
//       while (sfRenderWindow_isOpen(window)) {
//             sfEvent event;
//                     while (sfRenderWindow_pollEvent(window, &event)) {
//                         if (event.type == sfEvtClosed)
//                             sfRenderWindow_close(window);
//                     }
//
//
//         print_mapu(map, g, window);
//         sfRenderWindow_display(window);
//         if (!is_game_over(map)){
//           if (turn == PLAYER) // Si c'est le tour du joueur
//               player_turn(map, ai_message, g, window); // Tour du joueur
//           else // Sinon, c'est le tour de l'IA
//           {
//               if (ai_message) // Si un message de l'IA existe
//                   free(ai_message); // Libère la mémoire
//               ai_turn(map, &ai_message, g, window); // Tour de l'IA
//           }
//           sfRenderWindow_clear(window, sfWhite);
//           turn = turn == PLAYER ? AI : PLAYER; // Passe au prochain tour (joueur ou IA)
//
//         }
//
//         else{
//           end_game(map, g, window); // Fin du jeu (affiche le résultat)
//         }
//       }
//           if (ai_message) // Si un message de l'IA existe
//               free(ai_message); // Libère la mémoire
//           free(map); // Libère la mémoire de la carte
//
//
//     return 0; // Termine le programme avec succès
// }

// main.c
#include "my.h"
#include <stdio.h>
#include <stdlib.h>

#include <SFML/Graphics.h>

#include <SFML/Graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <SFML/Graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <SFML/Graphics.h>


// int main() {
//     // Création de la fenêtre SFML
//     sfVideoMode mode = {WINDOW_WIDTH, WINDOW_HEIGHT, 32};
//     sfRenderWindow* window = sfRenderWindow_create(mode, "Grid", sfResize | sfClose, NULL);
//     Cell* grille = creer_grille();
//
//     // Boucle principale
//     while (sfRenderWindow_isOpen(window)) {
//         sfEvent event;
//         while (sfRenderWindow_pollEvent(window, &event)) {
//             if (event.type == sfEvtClosed)
//                 sfRenderWindow_close(window);
//         }
//
//         // Effacer la fenêtre
//         sfRenderWindow_clear(window, sfWhite);
//
//         // Dessiner la grille sur la fenêtre
//         for (int i = 0; i < GRID_SIZE * GRID_SIZE; ++i) {
//             sfRenderWindow_drawRectangleShape(window, grille[i].shape, NULL);
//         }
//
//         // Afficher la grille
//         sfRenderWindow_display(window);
//     }

//     return 0;
// }




// int main(){
//   printf("coucou \n");
//   return 0;
// }


// int main()
// {
//   sfVideoMode mode = {WINDOW_WIDTH, WINDOW_HEIGHT, 32};
//   sfRenderWindow *window = sfRenderWindow_create(mode, "GAMEEEE", sfResize | sfClose, NULL);
//   Cell* g = creer_grille();
//   char *map = generate_random_map(); // Génère une carte aléatoire
//   char turn = FIRST_TO_PLAY; // Définit le joueur qui commence
//   char *ai_message = NULL; // Message de l'IA (initialisé à NULL)
//
//   while (sfRenderWindow_isOpen(window)) {
//     while (!is_game_over(map)) // Boucle principale du jeu jusqu'à la fin de la partie
//     {
//       sfEvent event;
//               while (sfRenderWindow_pollEvent(window, &event)) {
//                   if (event.type == sfEvtClosed)
//                       sfRenderWindow_close(window);
//               }
//       sfRenderWindow_clear(window, sfWhite);
//         if (turn == PLAYER) // Si c'est le tour du joueur
//             player_turn(map, ai_message, g, window); // Tour du joueur
//         else // Sinon, c'est le tour de l'IA
//         {
//             if (ai_message) // Si un message de l'IA existe
//                 free(ai_message); // Libère la mémoire
//             ai_turn(map, &ai_message, g, window); // Tour de l'IA
//         }
//         turn = turn == PLAYER ? AI : PLAYER; // Passe au prochain tour (joueur ou IA)
//         sfRenderWindow_display(window);
//     }
//     end_game(map, g, window); // Fin du jeu (affiche le résultat)
//     if (ai_message) // Si un message de l'IA existe
//         free(ai_message); // Libère la mémoire
//     free(map); // Libère la mémoire de la carte
//   }
//     return 0; // Termine le programme avec succès
// }

int main()
{
  sfVideoMode mode = {WINDOW_WIDTH, WINDOW_HEIGHT, 32};
  sfRenderWindow *window = sfRenderWindow_create(mode, "GAMEEEE", sfResize | sfClose, NULL);
  Cell* g = creer_grille();
  char *map = generate_random_map(); // Génère une carte aléatoire

  char turn = FIRST_TO_PLAY; // Définit le joueur qui commence
  //char *ai_message = NULL; // Message de l'IA (initialisé à NULL)

      while (sfRenderWindow_isOpen(window)) {
            sfEvent event;
                    while (sfRenderWindow_pollEvent(window, &event)) {
                        if (event.type == sfEvtClosed)
                            sfRenderWindow_close(window);
                    }
        print_mapu(map, g, window);
        sfRenderWindow_display(window);
        if (!is_game_over(map)){
          if (turn == PLAYER) // Si c'est le tour du joueur
              player_turn(map, g, window); // Tour du joueur
          else // Sinon, c'est le tour de l'IA
          {
              ai_turn(map, g, window); // Tour de l'IA
          }
          sfRenderWindow_clear(window, sfWhite);
          turn = turn == PLAYER ? AI : PLAYER; // Passe au prochain tour (joueur ou IA)

        }

        else{
          end_game(map, g, window); // Fin du jeu (affiche le résultat)
        }
      }
          free(map); // Libère la mémoire de la carte


    return 0; // Termine le programme avec succès
}
