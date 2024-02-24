#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "../include/grid.h"


// Fonction d'initialisation de la grille
// Paramètres :
//   - grid : la grille de jeu représentée par un tableau à deux dimensions de cellules
//   - difficulty : le niveau de difficulté du jeu
void Initialisation(cell grid[SIZE][SIZE], int difficulty) {
    // Initialisation du générateur de nombres aléatoires
    srand(time(NULL));
    int mine_replaced = 0;
    // Placement des mines sur la grille
    while (mine_replaced < MINES * difficulty) {
        // Génération aléatoire de coordonnées pour placer les mines
        int row = rand() % SIZE;
        int column = rand() % SIZE;
        // Vérification si la case n'est pas déjà une mine
        if (grid[row][column].content != 'm') {
            // La case est inactive et contient une mine
            grid[row][column].is_activate = false;
            grid[row][column].content = 'm';
            mine_replaced++;
        }
    }
    // Remplissage des cases restantes avec des cases vides
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            // Vérification si la case ne contient pas déjà une mine
            if (grid[i][j].content != 'm') {
                // La case est inactive et vide
                grid[i][j].is_activate = false;
                grid[i][j].content = ' ';
            }
        }
    }
}

// Fonction d'affichage de la grille de jeu
// Paramètre :
//   - grid : la grille de jeu représentée par un tableau à deux dimensions de cellules
void Display(cell grid[SIZE][SIZE]){
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            // Vérification si la case est activée
            if (grid[i][j].is_activate == true)
                // Affichage du contenu de la case si elle est activée
                printf("[ %c ] ", grid[i][j].content);
            else
                // Affichage des coordonnées de la case si elle n'est pas activée
                printf("[%d:%d] ", i, j);
        }
        printf("\n");
    }
    printf("\n");
}

// Fonction de mise à jour de l'état d'une cellule spécifique
// Paramètres :
//   - ligne : numéro de ligne de la cellule à mettre à jour
//   - colonne : numéro de colonne de la cellule à mettre à jour
//   - grid : la grille de jeu représentée par un tableau à deux dimensions de cellules
void Update(int ligne, int colonne, cell grid[SIZE][SIZE]){
    // Activation de la cellule spécifiée en utilisant ses coordonnées
    grid[ligne][colonne].is_activate = true;
}

// Fonction de détection de fin de jeu
// Paramètres :
//   - ligne : numéro de ligne de la cellule à vérifier
//   - colonne : numéro de colonne de la cellule à vérifier
//   - grid : la grille de jeu représentée par un tableau à deux dimensions de cellules
// Renvoie :
//   - true si le jeu est terminé (une mine a été touchée), sinon false
bool gameOver(int ligne, int colonne, cell grid[SIZE][SIZE]){
    // Vérification si la cellule spécifiée contient une mine
    if(grid[ligne][colonne].content == 'm'){
        // Remplacement de la mine touchée par un symbole de mine découverte
        grid[ligne][colonne].content = '*';
        // Activation de toutes les mines sur la grille
        for(int i = 0 ; i < SIZE ; i++){
            for(int j = 0 ; j < SIZE ; j++){
                if(grid[i][j].content == 'm') 
                    grid[i][j].is_activate = true;
            }
        }
        // Affichage du message de fin de jeu
        printf("GAME OVER!\n");
        return true;
    }
    // Aucune mine n'a été touchée, le jeu continue
    return false;
}

// Fonction de vérification des voisins d'une cellule spécifique
// Paramètres :
//   - grid : la grille de jeu représentée par un tableau à deux dimensions de cellules
//   - ligne : numéro de ligne de la cellule dont les voisins doivent être vérifiés
//   - colonne : numéro de colonne de la cellule dont les voisins doivent être vérifiés
void checkVoisins(cell grid[SIZE][SIZE], int ligne, int colonne) {
    // Parcours des cellules voisines dans un carré de 3x3 centré sur la cellule spécifiée
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {    
            int new_ligne = ligne + i;
            int new_colonne = colonne + j;
            // Vérification si la cellule voisine est dans les limites de la grille
            if (new_ligne >= 0 && new_ligne < SIZE && new_colonne >= 0 && new_colonne < SIZE) {
                // Vérification si la cellule voisine n'est pas déjà activée
                if (!grid[new_ligne][new_colonne].is_activate) {
                    // Activation de la cellule voisine
                    grid[new_ligne][new_colonne].is_activate = true;
                    // Mise à jour du comptage des mines pour la cellule voisine
                    minesCount(new_ligne, new_colonne, grid);
                }
            }
        }
    }
}

// Fonction de comptage des mines voisines pour une cellule spécifique
// Paramètres :
//   - ligne : numéro de ligne de la cellule dont les mines voisines doivent être comptées
//   - colonne : numéro de colonne de la cellule dont les mines voisines doivent être comptées
//   - grid : la grille de jeu représentée par un tableau à deux dimensions de cellules
void minesCount(int ligne, int colonne, cell grid[SIZE][SIZE]) {
    // Vérification si la cellule n'est ni un drapeau ni une mine
    if (grid[ligne][colonne].content != 'd' && grid[ligne][colonne].content != 'm') {
        int somme = 0;
        // Parcours des cellules voisines dans un carré de 3x3 centré sur la cellule spécifiée
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                int new_ligne = ligne + i;
                int new_colonne = colonne + j;
                // Vérification si la cellule voisine est dans les limites de la grille
                if (new_ligne >= 0 && new_ligne < SIZE && new_colonne >= 0 && new_colonne < SIZE) {
                    // Vérification si la cellule voisine contient une mine
                    if (grid[new_ligne][new_colonne].content == 'm') {
                        somme++;
                    }
                }
            }
        }
        // Mise à jour du contenu de la cellule avec le nombre de mines voisines
        if (somme != 0 && grid[ligne][colonne].content != 'm') {
            grid[ligne][colonne].content = somme + '0';
        } else {
            // Si aucune mine n'est voisine, on vérifie les voisins de cette cellule
            checkVoisins(grid, ligne, colonne);
        }
    }
}

// Fonction d'ajout d'un drapeau à une cellule spécifique
// Paramètres :
//   - flag : le caractère représentant la décision d'ajouter ou non un drapeau ('o' pour oui, 'n' pour non)
//   - ligne : numéro de ligne de la cellule à laquelle ajouter le drapeau
//   - colonne : numéro de colonne de la cellule à laquelle ajouter le drapeau
//   - grid : la grille de jeu représentée par un tableau à deux dimensions de cellules
void addFlag(char flag, int ligne, int colonne, cell grid[SIZE][SIZE]){
    // Vérification si la décision d'ajouter un drapeau est 'o'
    if(flag == 'o'){
        // Sauvegarde du contenu précédent de la cellule avant d'ajouter le drapeau
        grid[ligne][colonne].p_content = grid[ligne][colonne].content;
        // Ajout du drapeau à la cellule
        grid[ligne][colonne].content = 'd';
        // Activation de la cellule
        grid[ligne][colonne].is_activate = true;
    }
}

// Fonction de vérification de la présence de drapeaux sur la grille
// Paramètre :
//   - grid : la grille de jeu représentée par un tableau à deux dimensions de cellules
// Renvoie :
//   - true si au moins un drapeau est présent sur la grille, sinon false
bool checkFlag(cell grid[SIZE][SIZE]){
    int cpt = 0;
    // Parcours de toutes les cellules de la grille
    for(int i = 0 ; i < SIZE ; i++){
        for(int j = 0 ; j < SIZE ; j++){
            // Vérification si la cellule contient un drapeau
            if(grid[i][j].content == 'd'){
                cpt++;
            }
        }
    }
    // Renvoie vrai si au moins un drapeau est présent sur la grille, sinon faux
    if(cpt > 0) 
        return true;
    else 
        return false;
}

// Fonction de suppression d'un drapeau d'une cellule spécifique
// Paramètres :
//   - ligne : numéro de ligne de la cellule dont le drapeau doit être supprimé
//   - colonne : numéro de colonne de la cellule dont le drapeau doit être supprimé
//   - grid : la grille de jeu représentée par un tableau à deux dimensions de cellules
void deleteFlag(int ligne, int colonne, cell grid[SIZE][SIZE]){
    // Vérification si la cellule contient un drapeau
    if(grid[ligne][colonne].content == 'd'){
        // Restauration du contenu précédent de la cellule
        grid[ligne][colonne].content = grid[ligne][colonne].p_content;
        // Désactivation de la cellule
        grid[ligne][colonne].is_activate = false;
    } else {
        // Affichage d'un message d'erreur si la cellule ne contient pas de drapeau
        printf("Cellule invalide\n");
    }
}