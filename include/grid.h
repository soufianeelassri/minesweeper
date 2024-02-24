#ifndef GRID_H
#define GRID_H

#define SIZE 10
#define MINES 10

// Structure représentant une cellule dans la grille
typedef struct {
    bool is_activate;  // Indique si la cellule est activée ou non
    char p_content;    // Contenu précédent de la cellule (utilisé pour les drapeaux)
    char content;      // Contenu de la cellule ('m' pour mine, ' ' pour vide, ou un chiffre pour le nombre de mines voisines)
} cell;

// Prototypes de fonctions
void Initialisation(cell grid[SIZE][SIZE], int difficulty);  // Initialise la grille avec des mines et des cellules vides
void Display(cell grid[SIZE][SIZE]);                         // Affiche la grille
void Update(int ligne, int column, cell grid[SIZE][SIZE]);   // Met à jour l'état d'une cellule spécifique
bool gameOver(int ligne, int column, cell grid[SIZE][SIZE]); // Vérifie si le jeu est terminé
void checkVoisins(cell grid[SIZE][SIZE], int ligne, int column);  // Vérifie les cellules voisines
void minesCount(int ligne, int column, cell grid[SIZE][SIZE]);    // Compte les mines voisines
void addFlag(char flag, int ligne, int column, cell grid[SIZE][SIZE]);   // Ajoute un drapeau à une cellule
void deleteFlag(int ligne, int column, cell grid[SIZE][SIZE]);  // Supprime un drapeau d'une cellule
bool checkFlag(cell grid[SIZE][SIZE]);   // Vérifie si des drapeaux sont présents sur la grille
int numberOfActivated(cell grid[SIZE][SIZE]); // Compter le nombre de cellules activées dans la grille
bool checkWin(cell grid[SIZE][SIZE]);  // Vérifie si le joueur a gagné le jeu

#endif