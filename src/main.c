#include "my.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SFML/Window.h>
#include <SFML/Graphics.h>

int DEPTH = -1; // variable globale pour la profondeur

int main() { //
    // Création de la fenêtre
    sfVideoMode desktopMode = sfVideoMode_getDesktopMode();
    sfVideoMode mode = {desktopMode.width - 50, desktopMode.height - 50, 1};
    sfRenderWindow* window = sfRenderWindow_create(mode, "COLOR WAR", sfResize | sfClose, NULL);
    int posX = (desktopMode.width - mode.width) / 2;
    int posY = (desktopMode.height - mode.height - 50) / 2;
    sfRenderWindow_setPosition(window, (sfVector2i){posX, posY});
    sfVector2u windowSize = sfRenderWindow_getSize(window);

    sfFont* font = sfFont_createFromFile("gaming.ttf"); // Chargement de la police de caractères à partir d'un fichier
    if (!font) return 1; // Vérification si le chargement de la police a échoué

    sfRectangleShape *buttons[3]; // Déclaration du tableau des boutons de difficultés (rectangles contenant le texte)
    sfText *buttonTexts[3]; // Déclaration du tableau des boutons de difficultés (texte)
    createButtons(buttons, buttonTexts, window, font); // Création des boutons de difficultés
    const char *labels[3] = {"Easy", "Medium", "Hard"}; // Définition des étiquettes des boutons

    sfVector2f gridPosition = { // Définition de la position de la grille de jeu
        (sfRenderWindow_getSize(window).x - GRID_SIZE * CELL_SIZE) / 2,
        (sfRenderWindow_getSize(window).y - GRID_SIZE * CELL_SIZE) / 2
    };

    sfSprite* wallpaper = createAndLoadSprite("mosaique.png"); // Chargement de l'image de fond

    Cell* g = creer_grille(gridPosition); // Création de la grille de jeu
    char *map = generate_random_map(); // Génération d'une map aléatoire

    char turn = FIRST_TO_PLAY; // Définition du joueur qui commence
    sfColor gray = sfColor_fromRGB(128, 128, 128); // Définition de la couleur grise (pour le fond d'écran lors de la partie)
    sfRectangleShape** squares = create_squares(window); // Création des carrés qui indiquent les couleurs jouables
    int f = 1; // Initialisation du drapeau servant à relancer une partie

    while (sfRenderWindow_isOpen(window)) { // Boucle principale du jeu
        sfEvent event; // Déclaration d'un événement SFML
        while (sfRenderWindow_pollEvent(window, &event)) { // Gestion des événements de la fenêtre
            inputs(window, event); // Traitement des événements (soit presser la croix soit escape pour fermer)
        }

        while (DEPTH == -1) { // On reste dans l'écran d'accueil tant que la difficulté n'a pas été choisie
            f = 1; // Indique qu'une nouvelle partie a commmencé
            sfRenderWindow_clear(window, gray); // Effacement du contenu de la fenêtre
            sfRenderWindow_drawSprite(window, wallpaper, NULL); // Affichage du fond d'écran
            updateButtons(buttons, window); // Mise à jour des boutons (pour le hovering)
            drawButtons(window, buttons, buttonTexts); // Affichage des boutons de difficulés
            DEPTH = handleEvents(window, buttons, labels); // Gestion des événements des boutons (configuration de la difficulté)
        }

        sfRenderWindow_clear(window, gray); // Effacement du contenu de la fenêtre
        affiche_score(map, window, font); // Affichage du score
        update_squares(squares, map[PLAYER_Y * MAP_WIDTH + PLAYER_X], map[AI_Y * MAP_WIDTH + AI_X]); // Mise à jour des couleurs jouables
        affiche_couleurs(squares, window, font); // Affichage des couleurs jouables
        print_grid(map, g, window); // Affichage de la grille de jeu
        sfRenderWindow_display(window); // Affichage de la fenêtre

        if (!is_game_over(map)) { // Vérification si le jeu n'est pas terminé
            if (turn == PLAYER) { // Si c'est le tour du joueur
                player_turn(map, g, squares, window, event, font); // Tour du joueur
            } else { // Sinon, c'est le tour de l'IA
                ai_turn(map, g, window); // Tour de l'IA
            }
            turn = (turn == PLAYER) ? AI : PLAYER; // Changement de tour (joueur ou IA)
        } else { // Si le jeu est terminé
            while (f) { // Boucle pour gérer la fin du jeu
                while (sfRenderWindow_pollEvent(window, &event)) { // Gestion des événements de la fenêtre
                    inputs(window, event); // Traitement des événements
                }
                end_game(map, g, window, font); // Affichage de l'écran de fin de jeu
                //Pour relancer on appuie sur S : on relance une nouvelle partie en modifiant la valeur de f
                if (isSPressed()) {
                    f = 0; // Sortie de la boucle
                    DEPTH = -1; // Réinitialisation de la profondeur de recherche (pour retourner à l'écran d'accueil)
                    map = generate_random_map(); // On crée une nouvelle map
                }
            }
        }
    }
    return 0;
}
