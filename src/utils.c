// utils.c
#include "my.h"

// Fonction pour trouver l'indice d'un élément dans un tableau
char index_of_elem_in_array(char elem, char *array, int array_length)
{
    for (int i = 0 ; i < array_length ; i++) // Parcours de tout le tableau
    {
        if (array[i] == elem) // Vérifie si l'élément actuel correspond à celui recherché
            return i; // Retourne l'indice de l'élément s'il est trouvé
    }
    return -1; // Retourne -1 si l'élément n'est pas trouvé dans le tableau
}
