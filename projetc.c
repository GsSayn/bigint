#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define base 10
#define tailleMax 1000



typedef struct {
    int digit[tailleMax];
    int taille;
    bool positif;
} GrandEntier;

//PROTOTYPES

GrandEntier soustraction(GrandEntier a, GrandEntier b);
GrandEntier negative(GrandEntier a);
GrandEntier soustraction_sans_signe(GrandEntier a, GrandEntier b);
int maximum(int a, int b);
int egal_a(GrandEntier a, GrandEntier b);
int different_de(GrandEntier a, GrandEntier b);
int inferieur_a(GrandEntier a, GrandEntier b);
int inferieur_ou_egal_a(GrandEntier a, GrandEntier b);
void ordre(GrandEntier a, GrandEntier b, GrandEntier c);

GrandEntier lecture_grand_entier(const char* str){
        GrandEntier r = {0};

        const char *p = str;

        r.positif = true;

        if (*p == '+' || *p == '-') {
                if (*p == '-') {
                        r.positif = false;
                }
                p++;
        }
        while (*p != 0 && *p == '0') {
                p++;
        }

        if (*p != 0) {
                r.taille = strlen(p);

                for (int i = 0 ; i < r.taille ; i++) {
                        r.digit[r.taille-1-i] = p[i] - '0';
                }
        } else {
                r.taille=1;
                r.positif=true;
        }

        return r;
}


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

GrandEntier addition(GrandEntier a, GrandEntier b){

    GrandEntier c = {0};

    int n = maximum(a.taille, b.taille);
    int retenue = 0;

    if(a.positif == b.positif){
        c.positif = a.positif;
        c.taille = n;

        for(int i = 0; i < n; i++){
            c.digit[i] = a.digit[i] + b.digit[i] + retenue;
            if (c.digit[i] >= 10) {
                c.digit[i] -= 10;
                retenue = 1;
            }
            else retenue = 0;
        }
        if(retenue == 1){
            c.taille += 1;
            c.digit[c.taille - 1] = 1;
        }
    }
    else{
        if(a.positif){
            b.positif = true;
            return soustraction_sans_signe(a,b);
        }
        else{
            a.positif = true;
            return soustraction_sans_signe(a,b);
        }
    }

    return c;
}

GrandEntier soustraction(GrandEntier a, GrandEntier b){
    GrandEntier c = negative(b);
    return addition(a,c);
}

GrandEntier soustraction_sans_signe(GrandEntier a, GrandEntier b){
    GrandEntier c = {0};
    
    int n = maximum(a.taille, b.taille);
    int retenue = 0;
    c.taille = n;


    if(inferieur_a(a, b)){

        c.positif = false;
        for(int i = 0; i < n; i++){
            c.digit[i] = b.digit[i] - a.digit[i] - retenue;

            if(c.digit[i] < 0){
                c.digit[i] += 10;
                retenue = 1;
            }
            else retenue = 0;
        }
    }
    else{
        c.positif = true;
        for(int i = 0; i < n; i++){
            c.digit[i] = a.digit[i] - b.digit[i] - retenue;
         
            if(c.digit[i] < 0){
                c.digit[i] += 10;
                retenue = 1;
            }
            else retenue = 0;
        }
    }
    return c;
}

int egal_a(GrandEntier a, GrandEntier b){

    int n = maximum(a.taille, b.taille);

    if(a.positif == b.positif){
        for(int i = 0; i < n; i++){
            if(a.digit[i] != b.digit[i]){
                return 0;
            }
        }
        return 1;
    }
    else{
        //Signe différent, il faut vérifier que les entiers ne sont pas égals à 0
        for(int i = 0; i < n; i++){
            if(a.digit[i] != 0 || b.digit[i] != 0){
                return 0;
            }
        }
        return 1;
    }
}


int maximum(int a, int b){
    if(a > b){
        return a;
    }
    else{
        return b;
    }
}


int different_de(GrandEntier a, GrandEntier b){
    return 1 - egal_a(a, b);
}

int inferieur_a(GrandEntier a, GrandEntier b){

    int n = maximum(a.taille ,b.taille);

    if(a.positif && b.positif){
        for(int i = n - 1; i >= 0; i--){
            if (a.digit[i] < b.digit[i]){
                return 1;
            } else if (a.digit[i] > b.digit[i]) {
                return 0;
            }
        }
        return 0;
    }
    else if(!a.positif && b.positif){
        for(int i = 0; i < n; i++){
            if(a.digit[i] != 0 || b.digit[i] != 0){
                return 1;
            }
        }
        return 0;
    }
    else if(a.positif && !b.positif){
        return 0;
    }
    else{
        for(int i = n - 1; i >= 0; i--){
            if (a.digit[i] > b.digit[i]){
                return 1;
            } else if (a.digit[i] < b.digit[i]) {
                return 0;
            }
        }
        return 0;
    }
}

int inferieur_ou_egal_a(GrandEntier a, GrandEntier b){
    if(inferieur_a(a,b) == 1 || egal_a(a,b) == 1){
        return 1;
    }
    else return 0;
}

GrandEntier negative(GrandEntier a){
    GrandEntier c;
    memcpy(&c, &a, sizeof(a));
    c.positif = !a.positif;
    
    return c;
}


int main(){

    GrandEntier a = lecture_grand_entier("1693476934");
    GrandEntier b = lecture_grand_entier("-9000");
        
    
    printf("Premier entier : \n");
    afficher_grand_entier(a);


    
    printf("Deuxième entier : \n");
    afficher_grand_entier(b);

    printf("______________________\n");
    printf("addition : \n");
    GrandEntier c = addition(a, b);
    afficher_grand_entier(c);

    printf("______________________\n");
    printf("soustraction : \n");
 //   soustraction(a, b);
    
    // printf("a inferieur à b :%d\n", inferieur_a(test, Test2));

    // printf("a inferieur ou egal à b :%d\n", inferieur_ou_egal_a(test, Test2));
}
 