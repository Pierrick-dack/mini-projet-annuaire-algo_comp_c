# Algorithmie comparative en C — Gestion d'annuaire

## Auteurs

* **Pierrick KAMELA**
* **Eric DJOU TOUSSE**
* **Arnold JABEA**

## Présentation du projet

Ce mini-projet implémente un annuaire d'utilisateurs (e-mail + identifiant numérique) en langage C selon trois structures de données et algorithmes de recherche distincts, exposant une interface commune (`*_insert`, `*_search`, `*_free`).

Le programme exécute deux phases :
1. **Tests fonctionnels :** vérification du comportement sur un annuaire vide, sur un e-mail existant et sur un e-mail absent.
2. **Protocole de mesure (benchmark) :** après confirmation interactive (`o/n`), mesure du temps moyen d'une recherche dans le pire cas (e-mail absent) pour des annuaires de **100** à **1 000 000** d'utilisateurs.

## Architecture du dépôt

```text
.
├── Makefile        # Automatisation de la compilation et du nettoyage
├── user.h          # Structures (User, Node) et prototypes des trois approches
├── sequential.c    # Approche 1 : tableau dynamique et recherche séquentielle
├── hash.c          # Approche 2 : table de hachage (djb2) avec chaînage
├── sorted.c        # Approche 3 : tableau dynamique trié et recherche dichotomique
└── main.c          # Tests fonctionnels et benchmark comparatif
```

## Approches et complexités théoriques

| Approche | Structure de données | Insertion | Recherche (moyenne) | Recherche (pire cas) |
| :--- | :--- | :---: | :---: | :---: |
| **Séquentielle** (`seq_`) | Tableau dynamique (`realloc`) | $O(1)$ amorti | $O(n)$ | $O(n)$ |
| **Table de hachage** (`hash_`) | Tableau fixe (10 007) de listes chaînées | $O(1)$ | $O(1)$ | $O(n)$ |
| **Dichotomique** (`sorted_`) | Tableau dynamique maintenu trié | $O(n)$ | $O(\log n)$ | $O(\log n)$ |

## Compilation et exécution

Le projet se compile avec `gcc` via le `Makefile` fourni :

```bash
# Compiler le projet
make

# Lancer l'exécutable
./annuaire

# Supprimer l'exécutable généré
make clean
```