# Projet Compilation — Analyseur syntaxique d'expressions arithmétiques

## Présentation

Ce projet a été réalisé dans le cadre du cours de Compilation. Il s'agit d'un analyseur syntaxique pour des expressions arithmétiques simples, implémenté en C++17.

L'analyseur est capable de reconnaitre et d'évaluer des expressions composées d'entiers, des opérateurs `+` et `*`, et de parenthèses. Par exemple, l'expression `(1+34)*123` est correctement analysée et évaluée.

Le principe repose sur une analyse syntaxique ascendante de type **shift-reduce**, avec un automate à pile dont les états implémentent chacun leur logique de transition.

## Architecture du projet

Le projet est décomposé en plusieurs modules :

| Fichier | Rôle |
|--------|------|
| `main.cpp` | Point d'entrée du programme |
| `lexer.h` / `lexer.cpp` | Analyseur lexical : découpe la chaîne d'entrée en tokens |
| `symbole.h` / `symbole.cpp` | Hiérarchie de classes représentant les symboles et les noeuds de l'arbre d'expression |
| `etat.h` | Classe abstraite `Etat` |
| `etats.h` / `etats.cpp` | Les états concrets de l'automate (E0 à E8) |
| `automate.h` / `automate.cpp` | L'automate à pile, qui orchestre les opérations de décalage et de réduction |
| `tests.cpp` | Jeu de tests |

## Grammaire reconnue

La grammaire des expressions arithmétiques que l'on cherche à reconnaître est la suivante :

```
E -> E + E
E -> E * E
E -> ( E )
E -> entier
```

Les priorités opératoires sont gérées au niveau de l'automate via l'ordre des réductions. La grammaire ne supporte volontairement que les opérateurs `+` et `*` (pas de soustraction ni de division).

## Fonctionnement général

1. Le **Lexer** parcourt la chaîne caractère par caractère et produit des objets `Symbole` (tokens).
2. L'**Automate** maintient deux piles : une pile d'états et une pile de symboles.
3. À chaque étape, l'état courant décide soit de **décaler** (empiler le symbole courant et passer à un nouvel état), soit de **réduire** (remplacer plusieurs symboles par un non-terminal).
4. Les réductions construisent un **arbre d'expression** (`ExprPlus`, `ExprMult`, `ExprEntier`) dont on appelle ensuite `eval()` pour obtenir le résultat.

## Compilation et exécution

Le projet utilise un `Makefile`. Les commandes disponibles sont :

```bash
# Compiler le projet principal ET les tests en une seule fois
make

# Compiler uniquement le programme principal
make main

# Compiler uniquement les tests
make tests

# Lancer le programme principal (sans détails de pile)
./bin/main

# Lancer le programme principal avec les détails de pile (verbose)
./bin/main --verbose
# ou
./bin/main -v

# Lancer les tests
./bin/tests

# Nettoyer les fichiers compilés
make clean
```

> Pré-requis : `g++` avec support C++17 (`-std=c++17`). Les flags `-Wall -Wextra` sont activés.

## Tests

Le fichier `tests.cpp` contient un ensemble de cas de tests couvrant :

- **Expressions valides** : `5+7`, `2*5`, `(1+4)*6`, `(4+2)*(6+3)`, `((5)+2)`, etc.
- **Expressions invalides** : `+5`, `5+`, `()`, `(5+7` (parenthèse non fermée), `abc+5` (caractère invalide), `5-4` (opérateur non supporté), chaîne vide, etc.

Chaque test vérifie que l'automate accepte les expressions correctes et rejette bien les expressions erronées en affichant un message d'erreur approprié.

À la fin de l'exécution, un **bilan** est affiché :

```
========== BILAN ==========
Total   : 24
Réussis : 24
Échoués : 0
============================
```

En cas d'échec, les expressions concernées sont listées. Le programme retourne le nombre de tests échoués (utile pour scripts CI).
---

> Ce README a été rédigé avec l'aide d'une IA (Claude Sonnet 4.6).
