#include <stdlib.h>
#include <string.h>
#include "user.h"

// Nombre de cases de la table
#define HASH_SIZE 10007

// Tableau de pointeurs : chaque case pointe vers le début d'une liste chaînée
static Node *hash_table[HASH_SIZE] = {NULL};

// Transforme un e-mail (texte) en un numéro de case entre 0 et HASH_SIZE - 1
static unsigned int hash_func(const char *str) {
    unsigned long hash = 5381;
    int c = 0;
    // Calcule un grand nombre à partir de chaque lettre de l'e-mail
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; // Équivaut à : hash * 33 + c
    }
    return hash % HASH_SIZE; // Modulo pour rester dans les limites du tableau
}

void hash_insert(const char *email, int id) {
    // On calcule la case correspondante et on crée un nouveau maillon
    unsigned int idx = hash_func(email);
    Node *new_node = malloc(sizeof(Node));
    if (!new_node) return; // Sécurité si la mémoire est pleine

    // On remplit le maillon avec les infos de l'utilisateur
    strncpy(new_node->data.email, email, EMAIL_LENGTH - 1);
    new_node->data.email[EMAIL_LENGTH - 1] = '\0';
    new_node->data.id = id;

    // On accroche ce nouveau maillon tout au début de la liste de cette case
    new_node->next = hash_table[idx];
    hash_table[idx] = new_node;
}

bool hash_search(const char *email) {
    // Bloc 1 : On va directement à la bonne case grâce à la fonction de hachage
    unsigned int idx = hash_func(email);
    Node *curr = hash_table[idx];

    // Bloc 2 : On parcourt uniquement la petite liste chaînée de cette case
    while (curr != NULL) {
        if (strcmp(curr->data.email, email) == 0) {
            return true; // Trouvé
        }
        curr = curr->next; // On passe au maillon suivant
    }
    return false; // Absent
}

void hash_free(void) {
    // Bloc 1 : On passe sur chaque case du tableau
    for (int i = 0; i < HASH_SIZE; i++) {
        Node *curr = hash_table[i];
        // Bloc 2 : On libère un par un tous les maillons de la liste chaînée
        while (curr != NULL) {
            Node *tmp = curr;  // On sauvegarde le maillon actuel
            curr = curr->next; // On avance au suivant
            free(tmp);         // On supprime l'ancien
        }
        hash_table[i] = NULL;
    }
}