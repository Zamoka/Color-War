#include "my.h"
#include <stdio.h>
#include <stdlib.h>

void inputs(sfRenderWindow* window, sfEvent evenement){ // On gère simplement comment fermer la fenêtre (avec scape ou la croix)
  if (evenement.type == sfEvtClosed){
      sfRenderWindow_close(window);
      exit(EXIT_SUCCESS);
    }
  if (evenement.type == sfEvtKeyPressed) {
      if (evenement.key.code == sfKeyEscape) {
          sfRenderWindow_close(window);
          exit(EXIT_SUCCESS);
      }
  }
}

sfSprite* createAndLoadSprite(const char* imagePath) {
    // Créer une image à partir du fichier spécifié
    sfImage* image = sfImage_createFromFile(imagePath);
    if (!image) {
        fprintf(stderr, "Impossible de charger l'image depuis le fichier : %s\n", imagePath);
        return NULL;
    }

    // Créer une texture à partir de l'image
    sfTexture* texture = sfTexture_createFromImage(image, NULL); // Utilisation de NULL pour charger toute l'image
    if (!texture) {
        fprintf(stderr, "Impossible de créer la texture à partir de l'image.\n");
        sfImage_destroy(image);
        return NULL;
    }

    // Créer un sprite et lui attribuer la texture
    sfSprite* sprite = sfSprite_create();
    if (!sprite) {
        fprintf(stderr, "Impossible de créer le sprite.\n");
        sfTexture_destroy(texture);
        sfImage_destroy(image);
        return NULL;
    }
    sfSprite_setTexture(sprite, texture, sfTrue);

    // Libérer la mémoire de l'image car elle n'est plus nécessaire
    sfImage_destroy(image);

    //configuration de la position et taille de l'image
    sfVector2f position = {-100, -200};
    sfSprite_setPosition(sprite , position);
    sfVector2f scale = {7.0f, 7.0f};
    sfSprite_setScale(sprite, scale);
    return sprite;
}

void displayText(sfRenderWindow *window, sfFont *font, char* s) { //Affiche le texte en dessous de la grille
    // Création d'un texte
    sfText *text = sfText_create();
    sfText_setString(text, s);
    sfText_setFont(text, font);
    sfText_setCharacterSize(text, 50);
    sfText_setFillColor(text, sfWhite);
    // Positionner le texte au centre de la fenêtre
    sfVector2u windowSize = sfRenderWindow_getSize(window);
    sfText_setPosition(text, (sfVector2f){0.45*windowSize.x, 0.8*(windowSize.y)}); //On positionne le texte vers le bas
    sfRenderWindow_drawText(window, text, NULL);
}

void play_again(sfRenderWindow *window, sfFont *font) { //Affiche un message qui propose de lancer une nouvelle partie
    // Création d'un texte
    sfText *text = sfText_create();
    sfText_setString(text, "Press S to play again !");
    sfText_setFont(text, font);
    sfText_setCharacterSize(text, 40);
    sfText_setFillColor(text, sfBlack);
    // Positionner le texte au centre de la fenêtre
    sfVector2u windowSize = sfRenderWindow_getSize(window);
    sfText_setPosition(text, (sfVector2f){0.35*windowSize.x, 0.9*(windowSize.y)});
    sfRenderWindow_drawText(window, text, NULL);
}


void createButtons(sfRectangleShape *buttons[], sfText *buttonTexts[], sfRenderWindow *window, sfFont *font) { //Crée les boutons de difficulés
    const char *labels[3] = {"Easy", "Medium", "Hard"};
    const float buttonWidth = 300; // Largeur des boutons
    const float buttonHeight = 0.4*buttonWidth; // Hauteur des boutons
    const float buttonMargin = 70; // Marge entre les boutons

    for (int i = 0; i < 3; i++) {
        buttons[i] = sfRectangleShape_create();
        sfRectangleShape_setSize(buttons[i], (sfVector2f){buttonWidth, buttonHeight});
        sfRectangleShape_setFillColor(buttons[i], sfColor_fromRGB(100, 100, 250));

        // Calcul de la position horizontale centrée
        sfFloatRect buttonRect = sfRectangleShape_getLocalBounds(buttons[i]);
        sfVector2u windowSize = sfRenderWindow_getSize(window);
        float posX = (windowSize.x - buttonRect.width) / 2;

        // Positionnement du bouton
        float posY = (i * (buttonHeight + buttonMargin)) + (windowSize.y - 3 * (buttonHeight + buttonMargin)) / 2;
        sfRectangleShape_setPosition(buttons[i], (sfVector2f){posX, posY});

        buttonTexts[i] = sfText_create();
        sfText_setString(buttonTexts[i], labels[i]);
        sfText_setFont(buttonTexts[i], font);
        sfText_setCharacterSize(buttonTexts[i], 40);
        sfText_setColor(buttonTexts[i], sfWhite);

        sfFloatRect textRect = sfText_getLocalBounds(buttonTexts[i]);
        float textPosX = (windowSize.x - textRect.width) / 2;
        // Positionnement du texte centré
        float textPosY = posY + (buttonHeight - textRect.height) / 2 - 10;
        sfText_setPosition(buttonTexts[i], (sfVector2f){textPosX, textPosY});
    }
}



sfBool isMouseOverButton(sfRectangleShape *button, sfRenderWindow *window) { //Détècte si la souris est au dessus des boutons
    sfVector2i mousePos = sfMouse_getPositionRenderWindow(window);
    sfFloatRect buttonBounds = sfRectangleShape_getGlobalBounds(button);
    return sfFloatRect_contains(&buttonBounds, mousePos.x, mousePos.y);
}

int handleEvents(sfRenderWindow *window, sfRectangleShape *buttons[], const char *labels[]) { //Permet de choisir la difficulté de la partie
    sfEvent event;
    while (sfRenderWindow_pollEvent(window, &event)) {
        if (event.type == sfEvtClosed) {
            sfRenderWindow_close(window);
            exit(EXIT_SUCCESS);
        }
        if (isEscPressed()){
          sfRenderWindow_close(window);
          exit(EXIT_SUCCESS);
        }
        if (event.type == sfEvtMouseButtonPressed) {
              if (isMouseOverButton(buttons[0], window)) return 1; //Easy : profondeur = 1;
              if (isMouseOverButton(buttons[1], window)) return 5; //Medium : profondeur = 5;
              if (isMouseOverButton(buttons[2], window)) return 10; //Hard : profondeur = 10;
        }
    }
    return -1;
}

void updateButtons(sfRectangleShape *buttons[], sfRenderWindow *window) { //Un peu d'esthétique avec du hovering
    for (int i = 0; i < 3; i++) {
        if (isMouseOverButton(buttons[i], window)) {
            sfRectangleShape_setFillColor(buttons[i], sfColor_fromRGB(150, 150, 250));
        } else {
            sfRectangleShape_setFillColor(buttons[i], sfColor_fromRGB(100, 100, 250));
        }
    }
}

void drawButtons(sfRenderWindow *window, sfRectangleShape *buttons[], sfText *buttonTexts[]) { //Affiche les boutons et leur difficulté associée
    for (int i = 0; i < 3; i++) {
        sfRenderWindow_drawRectangleShape(window, buttons[i], NULL);
        sfRenderWindow_drawText(window, buttonTexts[i], NULL);
    }
    sfRenderWindow_display(window);
}

sfRectangleShape** create_squares(sfRenderWindow *window) { //Crée et renvoieun tableau dynamique de carrés correspondant aux couleurs jouables
  const sfColor colors[COLORS_NBRS] = {
      sfBlack,
      sfYellow,
      sfRed,
      sfBlue,
      sfGreen,
      sfMagenta
  };

    sfVector2f gridPosition = {
        (sfRenderWindow_getSize(window).x - GRID_SIZE * CELL_SIZE) / 2,
        (sfRenderWindow_getSize(window).y - GRID_SIZE * CELL_SIZE) / 4
    };

    // Allocation d'un tableau de pointeurs vers sfRectangleShape
    sfRectangleShape** squares = malloc(COLORS_NBRS * sizeof(sfRectangleShape*));
    if (!squares) {
        fprintf(stderr, "Erreur d'allocation mémoire pour les carrés.\n");
        return NULL;
    }

    for (int i = 0; i < COLORS_NBRS; i++) {
        sfRectangleShape *rect = sfRectangleShape_create();
        if (!rect) {
            fprintf(stderr, "Erreur de création d'un rectangle.\n");
            // Libérer tous les rectangles déjà alloués en cas d'erreur
            for (int j = 0; j < i; j++) {
                sfRectangleShape_destroy(squares[j]);
            }
            free(squares);
            return NULL;
        }

        sfRectangleShape_setSize(rect, (sfVector2f){50, 50});
        sfRectangleShape_setFillColor(rect, colors[i]);
        sfRectangleShape_setPosition(rect, (sfVector2f){gridPosition.x + MAP_WIDTH * CELL_SIZE + 5 * CELL_SIZE, (4 * gridPosition.y) / 3 + 25 + i * 100});
        squares[i] = rect;
    }

    return squares; //On renvoie le tableau
}

void affiche_couleurs(sfRectangleShape **squares, sfRenderWindow *window, sfFont *font) { //Affiche sur le côté droit les couleurs jouables
    // Définition des couleurs SFML pour chaque couleur du jeu.
    const sfColor colors[COLORS_NBRS] = {
        sfBlack,
        sfYellow,
        sfRed,
        sfBlue,
        sfGreen,
        sfMagenta
    };
    // Initialisation des initiales pour chaque couleur
    const char *initials[COLORS_NBRS] = {"N", "J", "R", "B", "V", "M"};
    // Position de départ pour afficher les couleurs.
    sfVector2f gridPosition = {
        (sfRenderWindow_getSize(window).x - GRID_SIZE * CELL_SIZE) / 2,
        (sfRenderWindow_getSize(window).y - GRID_SIZE * CELL_SIZE) / 4
    };

    for (int i = 0; i < COLORS_NBRS; i++) { // Parcours de chaque couleur
        sfRenderWindow_drawRectangleShape(window, squares[i], NULL); // Dessine un carré représentant la couleur

        sfText *text = sfText_create(); // Crée un texte pour afficher l'initiale de la couleur
        sfText_setString(text, initials[i]); // Définit le contenu du texte
        sfText_setFont(text, font); // Définit la police du texte
        sfText_setCharacterSize(text, 20); // Définit la taille des caractères
        sfText_setColor(text, sfWhite); // Définit la couleur du texte

        sfFloatRect textRect = sfText_getLocalBounds(text); // Récupère les dimensions du texte
        // Positionne le texte à côté du carré de couleur
        sfText_setPosition(text, (sfVector2f){
            gridPosition.x + MAP_WIDTH*CELL_SIZE + 4*CELL_SIZE + 20 ,
            (4*gridPosition.y)/3 + 35 + i * 100
        });

        sfRenderWindow_drawText(window, text, NULL); // Affiche le texte
        sfText_destroy(text); // Détruit l'objet texte pour libérer la mémoire
    }
}


void update_squares(sfRectangleShape **squares, int color_player, int color_ia){ //Rétablis la taille des carrés et rapetisse ceux dont les couleurs associées sont injouables
  for (int i = 0; i < COLORS_NBRS; i++){
    sfRectangleShape_setSize(squares[i], (sfVector2f){50, 50});
  }
  sfRectangleShape_setSize(squares[color_player], (sfVector2f){20, 20}); //Réduction de la taille
  sfRectangleShape_setSize(squares[color_ia], (sfVector2f){20, 20}); //Réduction de la taille
}

void affiche_score(char* map, sfRenderWindow * window, sfFont * font){ //Affiche le score actuel
  int ai_score = count_color(map, map[AI_Y * MAP_WIDTH + AI_X], AI_X, AI_Y); // Compte le nombre de cases explorées par l'IA
  int player_score = count_color(map, map[PLAYER_Y * MAP_WIDTH + PLAYER_X], PLAYER_X, PLAYER_Y); // Compte le nombre de cases explorées par l'IA

  //Allocation de la mémoire
  char *str_player = malloc(12 * sizeof(char));
  char *str_ai = malloc(12 * sizeof(char));

  //Conversion des scores qui sont des entiers en chaîne de caractère afin de pouvoir les afficher
  sprintf(str_player, "Joueur : %d", player_score);
  sprintf(str_ai, "IA : %d", ai_score);

  //Création des textes à afficher
  sfText *text_player = sfText_create();
  sfText *text_ai = sfText_create();

  //configuration des textes (police, taille, couleur, position)
  sfText_setString(text_player, str_player);
  sfText_setString(text_ai, str_ai);
  sfText_setFont(text_player, font);
  sfText_setFont(text_ai, font);
  sfText_setCharacterSize(text_player, 30);
  sfText_setCharacterSize(text_ai, 30);
  sfText_setFillColor(text_player, sfBlack);
  sfText_setFillColor(text_ai, sfBlack);
  sfVector2u windowSize = sfRenderWindow_getSize(window);
  sfText_setPosition(text_player, (sfVector2f){0.05*windowSize.x, 0.55*(windowSize.y)});
  sfText_setPosition(text_ai, (sfVector2f){0.05*windowSize.x, 0.45*(windowSize.y)});

  //Affichage des textes
  sfRenderWindow_drawText(window, text_player, NULL);
  sfRenderWindow_drawText(window, text_ai, NULL);

  //Libération de la mémoire
  free(str_player);
  free(str_ai);
}
