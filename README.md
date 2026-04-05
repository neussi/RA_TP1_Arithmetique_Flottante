# IEEE 754 & Arithmétique Flottante

## Description
Ce projet explore la représentation binaire des nombres flottants selon la norme IEEE 754, ainsi que les méthodes pour pallier les erreurs d'arrondi (Kahan) et assurer la stabilité numérique (Welford).

Ce projet fait partie du cursus de Réalité Augmentée From Scratch (Semestre 1). L'implémentation est réalisée entièrement en C++17 sans bibliothèque tierce (Zero STL), en suivant les directives de développement moteur Jenga/Nkentseu.

## Fonctionnalités implémentées
- Extraction des champs signe, exposant et mantisse.
- Sommation de Kahan pour la réduction d'erreurs d'arrondi.
- Algorithme de Welford pour un calcul de variance stable.
- Mesure de l'epsilon machine.

## Installation et Compilation
Le projet utilise le système de build **Jenga**.

1. Assurez-vous d'avoir Jenga installé sur votre système.
2. Clonez le dépôt :
   ```bash
   git clone git@github.com:neussi/RA_TP1_Arithmetique_Flottante.git
   cd RA_TP1_Arithmetique_Flottante
   ```
3. Compilez le projet :
   ```bash
   jenga build
   ```
4. Exécutez le programme :
   ```bash
   jenga run TP1
   ```

## Résultats
Le programme génère des sorties dans la console et, le cas échéant, des fichiers images (.ppm) illustrant les concepts mathématiques et graphiques abordés.

## Auteur
**NEUSSI NJIETCHEU PATRICE EUGNE**
Matricule : 24P820
