#include <stdlib.h>
#include <string.h>
#include "user.h"

// Variables privées au fichier pour gérer le tableau trié
static User *sorted_tab = NULL; // Tableau dynamique toujours gardé en ordre alphabétique
static int sorted_count = 0;    // Nombre d'utilisateurs actuels
static int sorted_cap = 0;      // Capacité maximale actuelle

void sorted_insert(const char *email, int id) {
    // Bloc 1 : Agrandissement du tableau s'il est plein
    if (sorted_count == sorted_cap) {
        sorted_cap = (sorted_cap == 0) ? 16 : sorted_cap * 2;
        sorted_tab = realloc(sorted_tab, sorted_cap * sizeof(User));
    }

    // Bloc 2 : On part de la fin et on décale vers la droite tous les e-mails
    // qui sont après le nouvel e-mail dans l'ordre alphabétique
    
    int i = sorted_count - 1;
    while (i >= 0 && strcmp(sorted_tab[i].email, email) > 0) {
        sorted_tab[i + 1] = sorted_tab[i];
        i--;
    }

    // Bloc 3 : On insère le nouvel utilisateur dans la case libérée
    strncpy(sorted_tab[i + 1].email, email, EMAIL_LENGTH - 1);
    sorted_tab[i + 1].email[EMAIL_LENGTH - 1] = '\0';
    sorted_tab[i + 1].id = id;
    sorted_count++;
}

bool sorted_search(const char *email) {
    // Bloc 1 : On définit les bornes gauche et droite de la zone de recherche
    int left = 0;
    int right = sorted_count - 1;

    // Bloc 2 : Tant qu'il reste des cases à vérifier, on coupe le tableau en deux
    while (left <= right) {
        int mid = left + (right - left) / 2; // Indice du milieu
        int cmp = strcmp(sorted_tab[mid].email, email);

        if (cmp == 0) return true;   // Trouvé pile au milieu
        if (cmp < 0) left = mid + 1; // L'e-mail est plus grand : on cherche à droite
        else right = mid - 1;        // L'e-mail est plus petit : on cherche à gauche
    }
    return false;
}


void sorted_free(void) {
    // Bloc 1 : Libération de la mémoire et remise à zéro
    free(sorted_tab);
    sorted_tab = NULL;
    sorted_count = 0;
    sorted_cap = 0;
}