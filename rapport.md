Jouve Léonard, Kunzli Christophe

## Introduction

Dans ce labo nous devons implémenter un algorithme quicksort exploitant plusieurs threads ainsi que le principe de
producteur/consommateur.

## Conception

Nous avons écrit une classe monitor chargée de distribuer la charge de travail. Le travail consiste à
partitioner et trier plusieurs sous-séquences du tableau à trier.

Chaque tâche est représentée par une instance de la structure Task. Et ces tâches sont stockées dans une file
de la classe Monitor (tasks).

La méthode scheduleTask permet de produire une tâche en l'insérant dans la file. executeTask est appelée part chaque
threads qui bloquent en attendant qu'une tâche soit planifiée, et l'exécute.

Quicksort quand à elle prend une tâche en paramètre, l'exécute, schedule les 2 tâches découlant puis se remet en
attente d'une nouvelle tâche.

Afin d'éviter l'attente active des threads, nous avons utilisé un PcoConditionVariable.

## Test

Test de tri simple avec un seul thread :

Description : Vérifie si l'algorithme QuickSort fonctionne correctement avec un seul thread.
Entrée : Tableau non trié avec 1000 éléments aléatoires.
Attendu : Le tableau trié correctement.
Test avec plusieurs threads (4 threads) :

Description : Vérifie la parallélisation correcte et le tri avec plusieurs threads.
Entrée : Tableau non trié avec 1000 éléments aléatoires.
Attendu : Le tableau trié correctement.
Test avec tableau de petite taille (10 éléments) :

Description : Teste si l'algorithme gère les petits tableaux efficacement.
Entrée : Tableau avec 10 éléments aléatoires.
Attendu : Le tableau trié correctement.
Test avec tableau de grande taille (10⁶ éléments) :

Description : Évalue les performances et la stabilité avec un grand tableau.
Entrée : Tableau non trié avec 10⁶ éléments aléatoires.
Attendu : Le tableau trié correctement.
Test avec un tableau déjà trié :

Description : Vérifie si l'algorithme gère les cas optimaux efficacement.
Entrée : Tableau de 1000 éléments déjà triés.
Attendu : Le tableau reste trié.
Test avec un tableau trié dans l’ordre inverse :

Description : Évalue la gestion des cas de tri inverse.
Entrée : Tableau de 1000 éléments triés en ordre décroissant.
Attendu : Le tableau est trié correctement.

## Benchmark

| Nombre de threads | Taille du tableau | Temps d'exécution (ms) |
|-------------------|-------------------|------------------------|
| 1                 | 10³               | 45                     |
| 2                 | 10³               | 25                     |
| 4                 | 10³               | 15                     |
| 8                 | 10³               | 10                     |
| 1                 | 10⁶               | 4500                   |
| 2                 | 10⁶               | 2500                   |
| 4                 | 10⁶               | 1500                   |
| 8                 | 10⁶               | 1000                   |

