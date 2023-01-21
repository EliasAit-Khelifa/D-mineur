#include <iostream>
#include <stdlib.h>
#include <random>
#include <assert.h>
using namespace std;

//@brief Strucuture qui �num�re les 3 �tats d'une case: Compos� d'une mine, vide, ou marquer
enum Etat_case { M = 'm', Vide = ' ', Cacher = '.', Marque = 'x' };   //�tat d'une case
//@brief Structure qui �num�re les deux actions que nous pouvons realiser lorsque joue
enum action { Marquer = 'M', Demasquer = 'D' };
/*
* @brief Structure de donn�es char de type Item
*/
typedef char Item;

enum { SIZE = 100 };
/*
* @brief Structure de donn�es de type Grille
*/

typedef struct {

    unsigned int mine; // nombre de mines
    unsigned int colonne; //nombre de colonne 
    unsigned int ligne; // nombre de ligne 
    unsigned int coup; // nombre de coup
    int pos_Mine[SIZE]; // position mine 
    int pos_Coup[SIZE]; // position coup 
    char HCoup[SIZE];
}Grille; //Structure d'une grille 

/* Prototypage des fonctions*/

/*
* @brief Initialise le nombre de ligne, colonnes, mine et les positions des cases min�es
* @param [in] num�ro de l'op�ration "1", lignes, colonnes, nombre de mines et les positions des cases min�es
* @param [in/out] nombre de ligne, colonne, mine et les positions des cases min�s
*/
void InitPB(unsigned int ligne, unsigned int colonne, unsigned int mine);
/*
* @brief Fonction permettant d'initialiser le jeu du d�mineur avec le nombre de lignes, colonnes, le nombre de mines et leurs positions
* @param [in] lignes, colonnes, nombre de mines
*/
void InitJ(Grille& a, unsigned int ligne, unsigned colonne, unsigned int mine);
/*
* @brief Fonction triant les positions des mines dans l'ordre croissant
* @param [in] Structure Grille
*/
void triM(Grille& a);
/*
* @brief Fonction triant les positions des mines dans l'ordre croissant dans l'historique de coup.
* @param [in] Structure Grille
*/
void triH(Grille& a);
/*
* @brief Fonction permettant la cr�ation de la grille
* @param [in] Grille& gr, Item** g
*/
void InitGr(Item*** a, Grille& gr);
/*
* @brief Fonction permettant de poser les mines al�atoires de la fonction "InitPB" dans la grille
* @param [in] Structure Grille, Structure Item
*/
void PoseMine(Grille& gr, Item** a);
/*
* @brief Fonction permettant de marquer ou d�masquer une case
* @param [in] Structure Grille, Strucutre Item
*/
void MarqueOuDemasque(Grille& gr, Item** a);
/*
* @brief Affiche sur une case le nombre de mines plac�es sur ses cases adjacentes
* @param [in] Structure Grille, Structure Item
*/
void numerocase(Grille& gr, Item** a);
/*
* @brief Fonction permettant d'afficher la grille
* @param [in/out] structure grille, structure item
* @param [out] la grille
*/
void AfficherGr(Grille& gr, Item** a);
/*
* @brief Fonction permettant de d�terminer si la partie est gagn�e ou pas
* @param [in] Structure grille
* @return "GAME WON" ou "GAME NOT WON"
*/
void gagner(Grille& gr);
/*
* @brief Fonction permettant de d�terminer si une partie est perdue ou pas
* @param [in] Structure grille
* return "GAME LOST" ou "GAME NOT LOST"
*/
void perdu(Grille& gr);




