#ifndef USER_H
#define USER_H

#include <stdbool.h>

// Taille maximale d'un e-mail
#define EMAIL_LENGTH 256

// Structure de données d'un utilisateur
typedef struct {
    char email[EMAIL_LENGTH];
    int id;
} User;

// Maillon d'une liste chaînée (sert uniquement pour la table de hachage)
typedef struct Node {
    User data;         // Les infos de l'utilisateur
    struct Node *next; // L'adresse du maillon suivant
} Node;


// Recherche séquentielle ---
void seq_insert(const char *email, int id);
bool seq_search(const char *email);
void seq_free(void);

// Table de hachage ---
void hash_insert(const char *email, int id);
bool hash_search(const char *email);
void hash_free(void);

// Recherche dichotomique ---
void sorted_insert(const char *email, int id);
bool sorted_search(const char *email);
void sorted_free(void);

#endif