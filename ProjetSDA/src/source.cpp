#include "demineur.h"

void InitPB(unsigned int ligne, unsigned int colonne, unsigned int mine) {


    srand(time(NULL)); // Permet de rendre aléatoire

    int* position = new int[mine];
    int* temp = new int[ligne * colonne];

    cout << ligne << " " << colonne << " " << mine; // Entrée utilisateur

    for (unsigned int i = 0; i < mine; i++) {
        unsigned int postionmine = rand() % (ligne * colonne);

        while (temp[postionmine] == -1) {
            postionmine = rand() % (ligne * colonne);
        }

        position[i] = postionmine;
        temp[postionmine] = -1;
        cout << " " << position[i];
    }
    cout << endl;

    delete[] position;
    delete[] temp;

}


/*
* @brief Fonction permettant d'initialiser le jeu du démineur avec le nombre de lignes, colonnes, le nombre de mines, leur position et l'historique de coups
* @param [in] lignes, colonnes, nombre de mines, nombre de coups
*/

void InitJ(Grille& a, unsigned int ligne, unsigned colonne, unsigned int mine) {

    a.ligne = ligne;
    a.colonne = colonne;
    a.mine = mine;
    //Stockage des données dans la structure Grille pour les fonctions suivantes

    for (unsigned int i = 0; i < mine; ++i) {  //Choix et placement des mines stockées dans le tableau positionMines
        cin >> a.pos_Mine[i];

    }
    cin >> a.coup;
    assert(a.coup < (ligne* colonne) - a.mine);

    for (unsigned int i = 0; i < a.coup; ++i) {  //Historique de coups
        cin >> a.HCoup[i];
        cin >> a.pos_Coup[i];
    }
}
/*
* @brief Fonction triant les positions des mines dans l'ordre croissant
* @param [in] Structure Grille
*/

void triM(Grille& a) {
    //Tri position mine dans l'ordre croissant
    unsigned int t1 = 0;

    for (unsigned int i = 0; i < a.mine; i++) {
        for (unsigned int j = 0; j < a.mine; j++) {
            if (a.pos_Mine[i] < a.pos_Mine[j]) {

                t1 = a.pos_Mine[i];
                a.pos_Mine[i] = a.pos_Mine[j];
                a.pos_Mine[j] = t1;

            }
        }
    }
}

/*
* @brief Fonction triant les positions des mines dans l'ordre croissant dans l'historique de coup.
* @param [in] Structure Grille
*/

void triH(Grille& a) {
    //Tri  mines dans l'ordre croissant dans l'historique

    unsigned int t2 = 0, tl = 0;

    for (unsigned int i = 0; i < a.coup; ++i) {
        for (unsigned int j = 0; j < a.coup; ++j) {
            if (a.pos_Coup[i] < a.pos_Coup[j]) {

                //Permet de Triez les nombres
                t2 = a.pos_Coup[i];
                a.pos_Coup[i] = a.pos_Coup[j];
                a.pos_Coup[j] = t2;

                //Permet de Triez les caractères en fonction des nombres

                tl = a.HCoup[i];
                a.HCoup[i] = a.HCoup[j];
                a.HCoup[j] = tl;

            }
        }
    }
}

/*
* @brief Fonction permettant de crée la grille
* @param [in] Grille& gr, Item** g
*/

void InitGr(Item*** a, Grille& gr) {

    // Initialise la grille

    *a = new Item * [gr.ligne];

    for (unsigned int i = 0; i < gr.colonne; ++i) {

        (*a)[i] = new Item[gr.colonne];
    }

    for (unsigned int l = 0; l < gr.ligne; l++) {

        for (unsigned int c = 0; c < gr.colonne; c++) {

            (*a)[l][c] = '.';
        }
    }
}

/*
* @brief Fonction permettant de poser les mines aléatoires de la fonction "InitPB" dans la grille
* @param [in] Structure Grille, Structure Item
*/

void PoseMine(Grille& gr, Item** a) {
    unsigned int p = 0;
    unsigned int cpt = 0;

    for (unsigned int l = 0; l < gr.ligne; ++l) {
        for (unsigned int c = 0; c < gr.colonne; ++c) {
            if (gr.pos_Mine[cpt] == p) {
                a[l][c] = M;
                cpt++;
                p++;
            }
            else {
                p++;
            }
        }
    }
}

/*
* @brief Fonction permettant de marquer ou démasquer une case
* @param [in] Structure Grille, Strucutre Item
*/

void MarqueOuDemasque(Grille& gr, Item** a) {
    int cpt = 0;
    int p = 0;
    for (unsigned int l = 0; l < gr.ligne; l++) {
        for (unsigned int c = 0; c < gr.colonne; c++) {
            if (gr.HCoup[cpt] == Marquer && gr.pos_Coup[cpt] == p) {
                a[l][c] = Marque;
                p++;
                cpt++;
            }
            else if (gr.HCoup[cpt] == Demasquer && gr.pos_Coup[cpt] == p) {
                if (a[l][c] == Cacher) {
                    a[l][c] = Vide;
                    p++;
                    cpt++;
                }
            }
            else {
                a[l][c] = Cacher;
                p++;
            }
        }
    }
}

/*
* @brief Affiche sur une case le nombre de mines placées sur ses cases adjacentes
* @param [in] Structure Grille, Structure Item
*/

void numerocase(Grille& gr, Item** a) {
    unsigned int ascii = 48; //  0=48  en ASCII 

    
    for (unsigned int l = 0; l < gr.ligne; ++l) {         //Initialisation des cases des mines à 0.
        for (unsigned int c = 0; c < gr.colonne; ++c) {
            
            if (a[l][c] == M) {
                a[l][c] = M;
                
                if (l >= 1 && l < gr.ligne && c >= 1 && c < gr.colonne) {
                    if (a[l - 1][c + 1] != M) {
                        a[l - 1][c + 1] = ascii;
                    }
                    if (a[l - 1][c - 1] != M) {
                        a[l - 1][c - 1] = ascii;
                    }
                    if (a[l - 1][c] != M) {
                        a[l - 1][c] = ascii;
                    }
                    if (a[l][c - 1] != M) {
                        a[l][c - 1] = ascii;
                    }
                    if (a[l][c + 1] != M) {
                        a[l][c + 1] = ascii;
                    }
                    if (a[l + 1][c - 1] != M) {
                        a[l + 1][c - 1] = ascii;
                    }
                    if (a[l + 1][c] != M) {
                        a[l + 1][c] = ascii;
                    }
                    if (a[l + 1][c + 1] != M) {
                        a[l + 1][c + 1] = ascii;
                    }
                }

                if (l == 0 && c == 0) {
                    if (a[l + 1][c + 1] != M) {
                        a[l + 1][c + 1] = ascii;
                    }
                    if (a[l][c + 1] != M) {
                        a[l][c + 1] = ascii;
                    }
                    if (a[l + 1][c] != M) {
                        a[l + 1][c] = ascii;
                    }
                }

                if (l == 0 && c > 0 && c < gr.colonne) {
                    if (a[l + 1][c + 1] != M) {
                        a[l + 1][c + 1] = ascii;
                    }
                    if (a[l][c + 1] != M) {
                        a[l][c + 1] = ascii;
                    }
                    if (a[l + 1][c] != M) {
                        a[l + 1][c] = ascii;
                    }
                    if (a[l + 1][c - 1] != M) {
                        a[l + 1][c - 1] = ascii;
                    }
                    if (a[l][c - 1] != M) {
                        a[l][c - 1] = ascii;
                    }
                }

                if (l == 0 && c == gr.colonne) {
                    if (a[l][c - 1] != M) {
                        a[l][c - 1] = ascii;
                    }
                    if (a[l + 1][c] != M) {
                        a[l + 1][c] = ascii;
                    }
                    if (a[l - 1][c + 1] != M) {
                        a[l][c + 1] = ascii;
                    }
                }

                if (l > 0 && l < gr.ligne && c == 0) {
                    if (a[l - 1][c] != M) {
                        a[l - 1][c] = ascii;
                    }
                    if (a[l - 1][c + 1] != M) {
                        a[l - 1][c + 1] = ascii;
                    }
                    if (a[l][c + 1] != M) {
                        a[l][c + 1] = ascii;
                    }
                    if (a[l + 1][c + 1] != M) {
                        a[l + 1][c + 1] = ascii;
                    }
                    if (a[l + 1][c] != M) {
                        a[l + 1][c] = ascii;
                    }
                }

                if (l == gr.ligne && c == 0) {
                    if (a[l - 1][c] != M) {
                        a[l - 1][c] = ascii;
                    }
                    if (a[l - 1][c + 1] != M) {
                        a[l - 1][c + 1] = ascii;
                    }
                    if (a[l][c + 1] != M) {
                        a[l][c + 1] = ascii;
                    }
                }

                if (l == gr.ligne && c > 0 && c < gr.colonne) {
                    if (a[l][c - 1] != M) {
                        a[l][c - 1] = ascii;
                    }
                    if (a[l - 1][c - 1] != M) {
                        a[l - 1][c - 1] = ascii;
                    }
                    if (a[l - 1][c] != M) {
                        a[l - 1][c] = ascii;
                    }
                    if (a[l - 1][c + 1] != M) {
                        a[l - 1][c + 1] = ascii;
                    }
                    if (a[l + 1][c + 1] != M) {
                        a[l + 1][c + 1] = ascii;
                    }
                }

                if (l == gr.ligne && c == gr.colonne) {
                    if (a[l][c - 1] != M) {
                        a[l][c - 1] = ascii;
                    }
                    if (a[l - 1][c - 1] != M) {
                        a[l - 1][c - 1] = ascii;
                    }
                    if (a[l - 1][c] != M) {
                        a[l - 1][c] = ascii;
                    }
                }

                if (c == gr.colonne && l > 0 && l < gr.ligne) {
                    if (a[l - 1][c] != M) {
                        a[l - 1][c] = ascii;
                    }
                    if (a[l - 1][c - 1] != M) {
                        a[l - 1][c - 1] = ascii;
                    }
                    if (a[l][c - 1] != M) {
                        a[l][c - 1] = ascii;
                    }
                    if (a[l + 1][c - 1] != M) {
                        a[l + 1][c - 1] = ascii;
                    }
                    if (a[l + 1][c] != M) {
                        a[l + 1][c] = ascii;
                    }
                }
            }
        }
    }
    
    for (unsigned int l = 0; l < gr.ligne; ++l) {      //Incrémentation des cases qui ont une mine autour d'elle. On ajoute un + aux cases se trouvant a proximité de la bombe.

        for (unsigned int c = 0; c < gr.colonne; ++c) {
            if (a[l][c] == M) {
                a[l][c] = M;
                if (l >= 1 && l < gr.ligne && c >= 1 && c < gr.colonne) {
                    if (a[l - 1][c + 1] != M) {
                        a[l - 1][c + 1] += 1;
                    }
                    if (a[l - 1][c - 1] != M) {
                        a[l - 1][c - 1] += 1;
                    }
                    if (a[l - 1][c] != M) {
                        a[l - 1][c] += 1;
                    }
                    if (a[l][c - 1] != M) {
                        a[l][c - 1] += 1;
                    }
                    if (a[l][c + 1] != M) {
                        a[l][c + 1] += 1;
                    }
                    if (a[l + 1][c - 1] != M) {
                        a[l + 1][c - 1] += 1;
                    }
                    if (a[l + 1][c] != M) {
                        a[l + 1][c] += 1;
                    }
                    if (a[l + 1][c + 1] != M)
                        a[l + 1][c + 1] += 1;

                }


                if (l == 0 && c == 0) {
                    if (a[l + 1][c + 1] != M) {
                        a[l + 1][c + 1] += 1;
                    }
                    if (a[l][c + 1] != M) {
                        a[l][c + 1] += 1;
                    }
                    if (a[l + 1][c] != M) {
                        a[l + 1][c] += 1;
                    }
                }

                if (l == 0 && c > 0 && c < gr.colonne) {
                    if (a[l + 1][c + 1] != M) {
                        a[l + 1][c + 1] += 1;
                    }
                    if (a[l][c + 1] != M) {
                        a[l][c + 1] += 1;
                    }
                    if (a[l + 1][c] != M) {
                        a[l + 1][c] += 1;
                    }
                    if (a[l + 1][c - 1] != M) {
                        a[l + 1][c - 1] += 1;
                    }
                    if (a[l][c - 1] != M) {
                        a[l][c - 1] += 1;
                    }
                }

                if (l == 0 && c == gr.colonne) {
                    if (a[l][c - 1] != M) {
                        a[l][c - 1] += 1;
                    }
                    if (a[l + 1][c] != M) {
                        a[l + 1][c] += 1;
                    }
                    if (a[l - 1][c + 1] != M) {
                        a[l][c + 1] += 1;
                    }
                }

                if (l > 0 && l < gr.ligne && c == 0) {
                    if (a[l - 1][c] != M) {
                        a[l - 1][c] += 1;
                    }
                    if (a[l - 1][c + 1] != M) {
                        a[l - 1][c + 1] += 1;
                    }
                    if (a[l][c + 1] != M) {
                        a[l][c + 1] += 1;
                    }
                    if (a[l + 1][c + 1] != M) {
                        a[l + 1][c + 1] += 1;
                    }
                    if (a[l + 1][c] != M) {
                        a[l + 1][c] += 1;
                    }
                }

                if (l == gr.ligne && c == 0) {
                    if (a[l - 1][c] != M) {
                        a[l - 1][c] += 1;
                    }
                    if (a[l - 1][c + 1] != M) {
                        a[l - 1][c + 1] += 1;
                    }
                    if (a[l][c + 1] != M) {
                        a[l][c + 1] += 1;
                    }
                }

                if (l == gr.ligne && c > 0 && c < gr.colonne) {
                    if (a[l][c - 1] != M) {
                        a[l][c - 1] += 1;
                    }
                    if (a[l - 1][c - 1] != M) {
                        a[l - 1][c - 1] += 1;
                    }
                    if (a[l - 1][c] != M) {
                        a[l - 1][c] += 1;
                    }
                    if (a[l - 1][c + 1] != M) {
                        a[l - 1][c + 1] += 1;
                    }
                    if (a[l + 1][c + 1] != M) {
                        a[l + 1][c + 1] += 1;
                    }
                }

                if (l == gr.ligne && c == gr.colonne) {
                    if (a[l][c - 1] != M) {
                        a[l][c - 1] += 1;
                    }
                    if (a[l - 1][c - 1] != M) {
                        a[l - 1][c - 1] += 1;
                    }
                    if (a[l - 1][c] != M) {
                        a[l - 1][c] += 1;
                    }
                }

                if (c == gr.colonne && l > 0 && l < gr.ligne) {
                    if (a[l - 1][c] != M) {
                        a[l - 1][c] += 1;
                    }
                    if (a[l - 1][c - 1] != M) {
                        a[l - 1][c - 1] += 1;
                    }
                    if (a[l][c - 1] != M) {
                        a[l][c - 1] += 1;
                    }
                    if (a[l + 1][c - 1] != M) {
                        a[l + 1][c - 1] += 1;
                    }
                    if (a[l + 1][c] != M) {
                        a[l + 1][c] += 1;
                    }
                }
            }
        }
    }
}

/*
* @brief Fonction permettant d'afficher la grille
* @param [in/out] structure grille, structure item
* @param [out] la grille
*/

void AfficherGr(Grille& gr, Item** a) {

    cout << gr.ligne << " " << gr.colonne << endl;

    for (unsigned int i = 1; i <= gr.colonne; ++i) {
        cout << " ---";
    }
    cout << endl;

    for (unsigned int l = 0; l < gr.ligne; ++l) {
        for (unsigned int c = 0; c < gr.colonne; ++c) {
            cout << "| " << a[l][c] << " ";
        }
        cout << "|" << endl;
        for (unsigned int i = 1; i <= gr.colonne; ++i) {
            cout << " ---";
        }
        cout << endl;
    }
}

/*
* @brief Fonction permettant de déterminer si la partie est gagnée ou pas
* @param [in] Structure grille
* @return "GAME WON" ou "GAME NOT WON"
*/

void gagner(Grille& gr) {

    unsigned int resultat = 0;

    if (gr.coup != (gr.ligne * gr.colonne) - gr.mine) {
        resultat = 0; //game not won
    }
    else {
        for (unsigned int i = 0; i < gr.mine; ++i) {
            for (unsigned int j = 0; j < gr.mine; ++j) {
                if (gr.HCoup[i] == Demasquer && gr.pos_Coup[i] != gr.pos_Mine[j]) {
                    resultat = 1; //game won
                }
                else {
                    resultat = 0; //game not won
                }
            }
        }
    }

    if (resultat == 1) {
        cout << "GAME WON" << endl;
    }
    else {
        cout << "GAME NOT WON" << endl;
    }
}

/*
* @brief Fonction permettant de déterminer si une partie est perdue ou pas
* @param [in] Structure grille
* return "GAME LOST" ou "GAME NOT LOST"
*/
void perdu(Grille& gr) {

    unsigned int resultat = 0;

    for (unsigned int i = 0; i < gr.mine; i++) {
        if (gr.HCoup[gr.coup - 1] == Marquer && gr.pos_Coup[gr.coup - 1] != gr.pos_Mine[i]) {
            resultat = 0; //game lost
        }
        if (gr.HCoup[gr.coup - 1] == Demasquer && gr.pos_Coup[gr.coup - 1] == gr.pos_Mine[i]) {
            resultat = 0; //game lost
        }
        if (gr.HCoup[gr.coup - 1] == Demasquer && gr.pos_Coup[gr.coup - 1] != gr.pos_Mine[i]) {
            resultat = 1; //game not lost
        }
        if (gr.HCoup[gr.coup - 1] == Marquer && gr.pos_Coup[gr.coup - 1] == gr.pos_Mine[i]) {
            resultat = 1; //game not lost 
        }
    }

    if (resultat == 0) {
        cout << "GAME LOST" << endl;
    }
    else {
        cout << "GAME NOT LOST" << endl;
    }
}