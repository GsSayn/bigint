#include <stdio.h>
#include <stdbool.h>


#define base 10
#define tailleMax 1000



typedef struct {
    int digit[tailleMax];
    int taille;
    bool positif;
} GrandEntier;

//PROTOTYPES

int egal_a(GrandEntier a, GrandEntier b);
int different_de(GrandEntier a, GrandEntier b);
int inferieur_a(GrandEntier a, GrandEntier b);
int inferieur_ou_egal_a(GrandEntier a, GrandEntier b);
void ordre(GrandEntier a, GrandEntier b, GrandEntier c);
void additionner(GrandEntier a, GrandEntier b, GrandEntier c);
void soustraire(GrandEntier a, GrandEntier b, GrandEntier c);



void afficher_grand_entier(GrandEntier entier) {                // Afficher le signe du grand entier

    if (entier.positif) {
        printf("+");
    }
    else {
        printf("-");
    }                                                           // Afficher le premier chiffre sans zéro de remplissage

    printf("%d", entier.digit[entier.taille - 1]);
                                                                // Afficher les chiffres restants du grand entier avec le zéro de remplissage appropri
      
    for (int i = entier.taille - 2; i >= 0; i--) {  
        printf("%d", entier.digit[i]);
    }
    printf("\n");
}

void addition(GrandEntier a, GrandEntier b){

    GrandEntier c = {0};
    c.positif = true;

    if(a.positif == 1 && b.positif == 1){
        additionner(a, b, c);

    }

    else if (a.positif == 0 && b.positif == 0){
        c.positif = false;
        additionner(a, b, c);
    }

    else if (a.positif == 1 && b.positif == 0){
        ordre(a, b, c);
    }

    else if (a.positif == 0 && b.positif == 1){
        ordre(b, a, c);
    }

}

void additionner(GrandEntier a, GrandEntier b, GrandEntier c){


    int retenue = 0;

    if (a.taille < b.taille){
        c.taille = b.taille + 1;
        
    }
    
    else{
        c.taille = a.taille + 1;
    }

    

    for( int i = 0; i < c.taille; i++){
        if ((a.digit[i] + b.digit[i] + retenue) >= 10){

            c.digit[i] = (a.digit[i] + b.digit[i] + retenue) % 10;
            retenue = 1;
        } 

        else{
            
            c.digit[i] = (a.digit[i] + b.digit[i] + retenue);
            retenue = 0;
        }
        
    }

    afficher_grand_entier(c);
}

void ordre(GrandEntier a, GrandEntier b, GrandEntier c){
    if (inferieur_a(a, b) == 1){
        c.positif = false;
        soustraire(b, a, c);

    }

    else if (inferieur_a(a, b) == 0){
        soustraire(a, b, c);
    }
}

void soustraire(GrandEntier a, GrandEntier b, GrandEntier c){

    int retenue = 0;

    if (a.taille < b.taille){
        c.taille = b.taille;
        
    }
    

    else{
        c.taille = a.taille;
    }

    for( int i = 0; i < c.taille; i++){
        if (a.digit[i] < (b.digit[i] + retenue)){

            c.digit[i] = (a.digit[i] + 10 - (b.digit[i] + retenue));
            retenue = 1;

            if (i == c.taille){
                c.positif = false;
            }
        } 

        else{
            
            c.digit[i] = (a.digit[i] - (b.digit[i] + retenue));
            retenue = 0;
        }

    }

    afficher_grand_entier(c);
}

void soustraction(GrandEntier a, GrandEntier b){

    GrandEntier c = {0};
    c.positif = true;

    if(a.positif == 1 && b.positif == 1){
       ordre(a, b, c);
    }

    else if (a.positif == 0 && b.positif == 0){
       ordre(b, a, c);
    }

    else if (a.positif == 1 && b.positif == 0){
        additionner(a, b, c);
    }

    else if (a.positif == 0 && b.positif == 1){
        c.positif = false;
        additionner(a, b, c);
    }

}

int egal_a(GrandEntier a, GrandEntier b){

    int compt = 0;

    if (a.positif != b.positif || a.taille != b.taille){
        return 0;
    }

    else{
        for (int i = 0; i < a.taille; i++){
            if (a.digit[i] != b.digit[i]){
                compt++;
            }
        }
        
        if (compt == 0){
            return 1;
        }
        else{
            return 0;
        }
    }

}

int different_de(GrandEntier a, GrandEntier b){
    int k = egal_a(a, b);

    if (k == 0){
        return 1;
    }
    else{
        return 0;
    }
}

int inferieur_a(GrandEntier a, GrandEntier b){

    if (a.positif > b.positif){
        return 0;
    }
    else if(a.positif < b.positif){
        return 1;
    }
    else{
        if (a.taille < b.taille){
            return 1;
        }
        else if (b.taille < a.taille){
            return 0;
        }
        else{
            for (int i = a.taille - 1; i >= 0; i--){
                if (a.digit[i] < b.digit[i]){
                    return 1;
                    break;
                }
                else if (a.digit[i] > b.digit[i]){
                    return 0;
                    break;
                }

                if (i == 0){
                    return 0;
                }

            }
        }
    }
    return 0;
}

int inferieur_ou_egal_a(GrandEntier a, GrandEntier b){

    if (a.positif > b.positif){
        return 0;
    }
    else if(a.positif < b.positif){
        return 1;
    }
    else{
        if (a.taille < b.taille){
            return 1;
        }
        else if (b.taille < a.taille){
            return 0;
        }
        else{
            for (int i = a.taille - 1; i >= 0; i--){
                if (a.digit[i] < b.digit[i]){
                    return 1;
                    break;
                }
                else if (a.digit[i] > b.digit[i]){
                    return 0;
                    break;
                }

                if (i == 0){
                    return 1;
                }

            }
        }
    }
    return 0;
}


int main(){

    GrandEntier test = {0};

    test.digit[0] = 7;
    test.digit[1] = 1;
    test.digit[2] = 1;
    test.digit[3] = 1;
    test.digit[4] = 6;
    test.digit[5] = 3;
    test.digit[6] = 8;
    test.digit[7] = 4;
    test.digit[8] = 9;
    test.digit[9] = 2;
    test.digit[10] = 8;
    test.digit[11] = 8;
    test.digit[12] = 9;
    test.digit[13] = 7;
    test.digit[14] = 8;
    test.digit[15] = 1;

    test.taille = 16;

    test.positif = false;


    printf("Premier entier : \n");
    afficher_grand_entier(test);


    GrandEntier Test2 = {0};        // Initialiser tous les éléments à 0
                                    // Chaque élément du tableau Test.Digit
                                    // est "mis à 0", par sécurité
    Test2.digit[0] = 2;
    Test2.digit[1] = 1;
    Test2.digit[2] = 2;
    Test2.digit[3] = 2;
    Test2.digit[4] = 3;
    Test2.digit[5] = 3;
    Test2.digit[6] = 4;
    Test2.digit[7] = 4;
    Test2.digit[8] = 5;
    Test2.digit[9] = 5;
    Test2.digit[10] = 6;
    Test2.digit[11] = 6;
    Test2.digit[12] = 7;
    Test2.digit[13] = 7;
    Test2.digit[14] = 8;
    Test2.digit[15] = 8;
    Test2.digit[16] = 9;
    Test2.digit[17] = 9;


    Test2.taille = 18;
    Test2.positif = true;

    printf("Deuxième entier : \n");
    afficher_grand_entier(Test2);

    printf("______________________\n");
    printf("addition : \n");
    addition(test, Test2);

    printf("______________________\n");
    printf("soustraction : \n");
    soustraction(test, Test2);
    
    // printf("a inferieur à b :%d\n", inferieur_a(test, Test2));

    // printf("a inferieur ou egal à b :%d\n", inferieur_ou_egal_a(test, Test2));

}