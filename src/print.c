// print.c
#include "my.h"
#include <stdio.h>
#include <stdlib.h>

// Fonction pour effacer l'écran en affichant plusieurs lignes vides
void clear_screen()
{
    char *str; // Chaîne de caractères pour stocker les sauts de ligne
    str = malloc(sizeof(char) * (CLEAR_NBR + 1)); // Allocation de mémoire pour la chaîne de caractères
    for (int i = 0 ; i < CLEAR_NBR ; i++) // Boucle pour remplir la chaîne de caractères avec des sauts de ligne
        str[i] = '\n'; // Caractère de saut de ligne
    str[CLEAR_NBR] = '\0'; // Caractère de fin de chaîne
    printf("%s", str); // Affichage de la chaîne de caractères pour effacer l'écran
    free(str); // Libération de la mémoire allouée pour la chaîne de caractères
}

void inputs(sfRenderWindow* window, sfEvent evenement){
  if (evenement.type == sfEvtClosed)
      sfRenderWindow_close(window);
  if (evenement.type == sfEvtKeyPressed) {
      if (evenement.key.code == sfKeyEscape) {
          sfRenderWindow_close(window); // Fermer la fenêtre si Escape est pressé
      }
  }
}

void afficher_fenetre(int largeur, int hauteur, const char* titre) {
    // Obtention des dimensions de l'écran
    sfVideoMode mode_ecran = sfVideoMode_getDesktopMode();
    int ecran_largeur = mode_ecran.width;
    int ecran_hauteur = mode_ecran.height;

    // Calcul de la position de la fenêtre pour la centrer
    int position_x = (ecran_largeur - largeur) / 2;
    int position_y = (ecran_hauteur - hauteur) / 2;

    // Création de la fenêtre centrée
    sfVideoMode mode = {largeur, hauteur, 32};
    sfRenderWindow* fenetre = sfRenderWindow_create(mode, titre, sfClose, NULL);
    sfRenderWindow_setPosition(fenetre, (sfVector2i){position_x, position_y}); // Positionner la fenêtre

    while (sfRenderWindow_isOpen(fenetre)) {
        sfEvent event;
        while (sfRenderWindow_pollEvent(fenetre, &event)) {
            inputs(fenetre, event);
        }

        sfRenderWindow_clear(fenetre, sfBlack);
        // Dessiner ici

        sfRenderWindow_display(fenetre);
    }

    sfRenderWindow_destroy(fenetre);
}
