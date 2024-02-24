#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../src/grid.c"

int main() {

    cell grid[SIZE][SIZE];  // Déclaration de la grille de jeu

    int difficulty;
    printf("Choisissez un niveau de difficulte :\n");
    printf("1. Facile\n2. Moyenne\n3. Difficile\n");
    scanf("%d", &difficulty);
    switch (difficulty) {  // Vérification du niveau de difficulté saisi
        case 1:
        case 2:
        case 3:
            break;
        default:
            printf("Niveau de difficulté invalide\n");
            return 1;
    }

    Initialisation(grid, difficulty);  // Initialisation de la grille avec le niveau de difficulté choisi

    int ligne;
    int column;

    char flag;
    char delete_option;

    int ligne_d;
    int column_d;

    do {
        Display(grid);  // Affichage de la grille
        if(checkFlag(grid)){  // Vérification s'il y a des drapeaux sur la grille
            getchar();
            printf("Voulez-vous supprimer un drapeau ? (o/n) : \n");
            delete_option = getchar();
            if(delete_option == 'o'){  // Suppression d'un drapeau si l'utilisateur le souhaite
                printf("Entrez les coordonnees du drapeau a supprimer (format : ligne colonne) : ");
                scanf("%d%d", &ligne_d, &column_d);
                deleteFlag(ligne_d, column_d, grid);
                Display(grid);
            }
        }
        printf("Selectionnez une cellule sur la grille (format : ligne colonne) : \n");
        scanf("%d%d", &ligne, &column);
        getchar();
        printf("Souhaitez-vous placer un drapeau sur cette cellule ? (o/n) : \n");
        flag = getchar();  // Demande à l'utilisateur s'il veut placer un drapeau sur la cellule sélectionnée
        Update(ligne, column, grid);  // Mise à jour de l'état de la cellule sélectionnée
        addFlag(flag, ligne, column, grid);  // Ajout d'un drapeau à la cellule si demandé
        minesCount(ligne, column, grid);  // Comptage des mines voisines autour de la cellule sélectionnée
    } while(!gameOver(ligne, column, grid));  // Boucle tant que le jeu n'est pas terminé

    Display(grid);  // Affichage final de la grille

    return 0;
}