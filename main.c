#include <stdio.h>
#include <time.h>
#include "user.h"

#define REPS 10000

int main(void) {
    // =========================================================================
    // PARTIE 1 : TESTS FONCTIONNELS (Vide, Existant, Absent)
    // =========================================================================
    printf("=== 1. VERIFICATION DES TROIS APPROCHES ===\n");

    // Bloc 1 : Test sur un annuaire vide (ne doit pas planter et doit renvoyer 0)
    printf("Annuaire vide (attendu 0)  -> Seq: %d | Hash: %d | Dicho: %d\n",
           seq_search("alice@mail.com"),
           hash_search("alice@mail.com"),
           sorted_search("alice@mail.com"));

    // Bloc 2 : Insertion de 3 utilisateurs dans le désordre (pour tester le tri)
    seq_insert("charlie@mail.com", 1);
    hash_insert("charlie@mail.com", 1);
    sorted_insert("charlie@mail.com", 1);

    seq_insert("alice@mail.com", 2);
    hash_insert("alice@mail.com", 2);
    sorted_insert("alice@mail.com", 2);

    seq_insert("bob@mail.com", 3);
    hash_insert("bob@mail.com", 3);
    sorted_insert("bob@mail.com", 3);

    // Bloc 3 : Recherche d'un e-mail existant (doit renvoyer 1 partout)
    printf("Email existant (attendu 1) -> Seq: %d | Hash: %d | Dicho: %d\n",
           seq_search("bob@mail.com"),
           hash_search("bob@mail.com"),
           sorted_search("bob@mail.com"));

    // Bloc 4 : Recherche d'un e-mail absent (doit renvoyer 0 partout)
    printf("Email absent (attendu 0)   -> Seq: %d | Hash: %d | Dicho: %d\n\n",
           seq_search("inconnu@mail.com"),
           hash_search("inconnu@mail.com"),
           sorted_search("inconnu@mail.com"));

    // Bloc 5 : Vidage complet des 3 structures (toujours fait avant de quitter ou continuer)
    seq_free();
    hash_free();
    sorted_free();

    // =========================================================================
    // PAUSE INTERACTIVE : CONFIRMATION AVANT LE TABLEAU DE MESURE
    // =========================================================================
    char choix;
    printf("Voulez-vous continuer sur le tableau de mesure ? (o/n) : ");
    if (scanf(" %c", &choix) != 1 || (choix != 'o' && choix != 'O')) {
        printf("Fin du programme.\n");
        return 0;
    }
    printf("\n");

    // =========================================================================
    // PARTIE 2 : PROTOCOLE DE MESURE
    // =========================================================================
    printf("=== 2. MESURE DES PERFORMANCES (PIRE CAS) ===\n");

    // Bloc 1 : Configuration des tailles d'annuaires à tester
    int tailles[] = {100, 1000, 10000, 100000, 1000000};
    const char *labels[] = {"100", "1 000", "10 000", "100 000", "1 000 000"};
    int nb_tailles = 5;

    char email[64];
    const char *cible_inexistante = "zzzzzzz@inexistant.com"; // Pire cas : absent
    volatile bool trouve = false; // Empêche le compilateur d'ignorer la recherche

    // Bloc 2 : Affichage de l'en-tête du tableau
    printf("+----------------------+------------------+----------------------+------------------+\n");
    printf("| Taille de l'annuaire | Sequentielle (s) | Table de hachage (s) | Dichotomique (s) |\n");
    printf("+----------------------+------------------+----------------------+------------------+\n");

    // Bloc 3 : Boucle principale sur chaque taille d'annuaire
    for (int t = 0; t < nb_tailles; t++) {
        int n = tailles[t];

        // Remplissage des 3 annuaires avec n e-mails générés automatiquement
        for (int i = 0; i < n; i++) {
            sprintf(email, "user%07d@mail.com", i);
            seq_insert(email, i);
            hash_insert(email, i);
            sorted_insert(email, i);
        }

        // Mesure 1 : Recherche séquentielle
        clock_t start = clock();
        for (int r = 0; r < REPS; r++) trouve = seq_search(cible_inexistante);
        clock_t end = clock();
        double t_seq = ((double)(end - start) / CLOCKS_PER_SEC) / REPS;

        // Mesure 2 : Table de hachage
        start = clock();
        for (int r = 0; r < REPS; r++) trouve = hash_search(cible_inexistante);
        end = clock();
        double t_hash = ((double)(end - start) / CLOCKS_PER_SEC) / REPS;

        // Mesure 3 : Recherche dichotomique
        start = clock();
        for (int r = 0; r < REPS; r++) trouve = sorted_search(cible_inexistante);
        end = clock();
        double t_sorted = ((double)(end - start) / CLOCKS_PER_SEC) / REPS;

        // Affichage de la ligne de résultats
        printf("| %-20s | %-16.8f | %-20.8f | %-16.8f |\n",
               labels[t], t_seq, t_hash, t_sorted);
        printf("+----------------------+------------------+----------------------+------------------+\n");

        // Nettoyage complet de la mémoire avant de passer à la taille suivante
        seq_free();
        hash_free();
        sorted_free();
    }

    (void)trouve;
    return 0;
}