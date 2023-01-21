#include "demineur.h"




int main() {

    int cdo;
    unsigned int l, c, m;
    cin >> cdo;
    assert(cdo >= 1);
    assert(cdo <= 5);

    Grille grille;
    Item** g;
    cin >> l >> c >> m; //Entrez utilisateur

    if (cdo == 1) {
        InitPB(l, c, m);
    }

    else if (cdo == 2) {

        InitJ(grille, l, c, m);
        triM(grille);
        triH(grille);
        InitGr(&g, grille);
        PoseMine(grille, g);
        MarqueOuDemasque(grille, g);
        numerocase(grille, g);
        AfficherGr(grille, g);
    }

    else if (cdo == 3) {

        InitJ(grille, l, c, m);
        gagner(grille);

    }
    else if (cdo == 4) {

        InitJ(grille, l, c, m);
        perdu(grille);

    }
    else if (cdo == 5) {

        cout << "nous n'avons pas réussi le sprint 5 !" << endl;

    }


}