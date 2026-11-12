#include <stdlib.h>
#include <string.h>
#include "user.h"

// Variables pour gérer le tableau dynamique
static User *seq_tab = NULL; // Pointeur vers le tableau d'utilisateurs
static int seq_count = 0;    // Nombre d'utilisateurs actuellement enregistrés
static int seq_cap = 0;      // Taille maximale actuelle du tableau en mémoire

void seq_insert(const char *email, int id) {
    if (seq_count == seq_cap) {
        seq_cap = (seq_cap == 0) ? 16 : seq_cap * 2;
        seq_tab = realloc(seq_tab, seq_cap * sizeof(User));
    }

    // On copie l'e-mail et l'id dans la première case libre à la fin
    strncpy(seq_tab[seq_count].email, email, EMAIL_LENGTH - 1);
    seq_tab[seq_count].email[EMAIL_LENGTH - 1] = '\0';
    seq_tab[seq_count].id = id;
    seq_count++;
}

bool seq_search(const char *email) {
    // Ici, on parcourt tout le tableau case par case depuis le début
    for (int i = 0; i < seq_count; i++) {
        // Si les deux e-mails sont identiques, on a trouvé l'utilisateur
        if (strcmp(seq_tab[i].email, email) == 0) {
            return true;
        }
    }
    // Si vide ou absent du tableau
    return false;
}

void seq_free(void) {
    //On vide la mémoire allouée et on remet tout à zéro
    free(seq_tab);
    seq_tab = NULL;
    seq_count = 0;
    seq_cap = 0;
}