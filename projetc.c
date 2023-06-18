#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define BASE 10000
#define FORMATDIGIT "%04d"

#define TAILLEMAX 1000

typedef struct {
    int digit[TAILLEMAX];
    int taille;
    bool positif;
} GrandEntier;

//PROTOTYPES


GrandEntier multiplication(GrandEntier a, GrandEntier b);
GrandEntier soustraction(GrandEntier a, GrandEntier b);
GrandEntier negative(GrandEntier a);
GrandEntier soustraction_sans_signe(GrandEntier a, GrandEntier b);
int maximum(int a, int b);
int egal_a(GrandEntier a, GrandEntier b);
int different_de(GrandEntier a, GrandEntier b);
int inferieur_a(GrandEntier a, GrandEntier b);
int inferieur_ou_egal_a(GrandEntier a, GrandEntier b);

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
                r.taille = 0;
                int longueur = strlen(p);
                int multiplicateur = 1;

                for (int i = 0 ; i < longueur; i++){                      
                        if(multiplicateur == 1){
                            r.taille += 1;
                        }
                        
                        r.digit[r.taille - 1] += (p[longueur - i - 1] - '0') * multiplicateur;
                        
                        multiplicateur *= 10;
                        if(multiplicateur == BASE){
                            multiplicateur = 1;
                        }
                }

        } else {
                r.taille=1;
                r.positif=true;
        }

        return r;
}


void afficher_grand_entier(GrandEntier entier){

    int t = entier.taille - 1;

    while(t > 0 && entier.digit[t] == 0){
        t--;
    }
    
    if (entier.positif){
        printf("+");
    }
    else{
        printf("-");
    }
          
    for (int i = t; i >= 0; i--) {
        if (i == t) {
            printf("%d", entier.digit[i]);
        } else {
            printf(FORMATDIGIT, entier.digit[i]);
        } 
    }
    printf("\n");

}

void normaliser(GrandEntier *p){
    for(int i = p->taille - 1; i >= 1; i--){
        if(p->digit[i] != 0){
            break;
        }
        p->taille--;
    }
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
            if (c.digit[i] >= BASE) {
                c.digit[i] -= BASE;
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
                c.digit[i] += BASE;
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
                c.digit[i] += BASE;
                retenue = 1;
            }
            else retenue = 0;
        }
    }

    normaliser(&c);
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

GrandEntier multiplication(GrandEntier a, GrandEntier b){
    GrandEntier c = {0};
    c.positif = (a.positif == b.positif);

    c.taille = a.taille + b.taille - 1;
    int retenue = 0;

    for(int k = 0; k < c.taille; k++){
        c.digit[k] = retenue;
        retenue = 0;
        for(int i = 0; i <= k;i++){
            int j = k - i;
            c.digit[k] += a.digit[i] * b.digit[j];
            if(c.digit[k] >= BASE){
                retenue += c.digit[k] / BASE;
                c.digit[k] = c.digit[k] % BASE;
            }
        }
    }

    if(retenue > 0){
        c.taille += 1;
        c.digit[c.taille - 1] = retenue;
    }

    return c;
}

GrandEntier puissance(GrandEntier a, int b){
    
    memmove(a.digit + b, a.digit, a.taille * sizeof(int));
    memset(a.digit, 0, b * sizeof(int));

    a.taille = a.taille + b;

    return a;
}

void partage(GrandEntier u, GrandEntier *pGauche, GrandEntier *pDroite, int m){
    pGauche->positif = true;
    pDroite->positif = true;
    pGauche->taille = u.taille - m;
    pDroite->taille = m;

    memcpy(pGauche->digit, u.digit + m, pGauche->taille * sizeof(int));
    memcpy(pDroite->digit, u.digit, pDroite->taille * sizeof(int));
}

GrandEntier karatsuba(GrandEntier u, GrandEntier v){
    GrandEntier a = {0};
    GrandEntier b = {0};
    GrandEntier c = {0};  
    GrandEntier d = {0};   

    int n = maximum(u.taille, v.taille);
    if(n==1){
        return multiplication(u,v);
    }

    int k = n /2;

    u.taille = n;
    v.taille = n;

    partage(u, &a, &b, n/2);
    partage(v, &c, &d, n/2);

    GrandEntier x = karatsuba(addition(a,b), addition(c,d)) ;
    GrandEntier y = multiplication(a,c);
    GrandEntier z = multiplication(b,d);
    GrandEntier r = {0};

    r = puissance(y, 2 * k);
    r = addition(r, puissance(soustraction(x, addition(y,z)), k));
    r = addition(r,z);

    return r;
}


GrandEntier modulo(GrandEntier a, GrandEntier b){
    GrandEntier r = {0};
    r.positif = true;

    if(egal_a(a,b) != 0){
        r.taille = 1;
        return r;
    }
    else if(inferieur_a(a,b) != 0){
        return a;
    }
    
    GrandEntier c = b;
    
    for(;;){
        r = c;
        c = addition(c,c);
        if(inferieur_a(a,c) != 0){
            break;
        }
    }
    return modulo(soustraction(a,r),b);
}


GrandEntier expMod(GrandEntier g, unsigned int e, GrandEntier n){
    int m = 1;
    GrandEntier r0 = lecture_grand_entier("1");
    GrandEntier r1 = g;

    for(int i = 0; i < sizeof(e) * 8; i++){
        if(e % 2 == 1){ // e & m différent de 0 si le bit de poids i est différent de 0
            r0 = modulo(karatsuba(r0,r1), n);
        }
        r1 = modulo(karatsuba(r1,r1), n);
        m*=2;
        e = e / 2;
    }

    return r0;
}

GrandEntier cryptage(GrandEntier m, int e, GrandEntier N){
    return expMod(m, e, N);
}

GrandEntier decryptage(GrandEntier c, int D, GrandEntier N){
    return expMod(c, D, N);
}

int main(){

    /*GrandEntier a = lecture_grand_entier("9999");
    GrandEntier b = lecture_grand_entier("99");

    GrandEntier c = {0};
    GrandEntier d = {0};
    
    printf("Premier entier : \n");
    afficher_grand_entier(a);


    
    printf("Deuxième entier : \n");
    afficher_grand_entier(b);

    printf("______________________\n");
    printf("Opération : \n");
    GrandEntier c = addition(a, b);
    afficher_grand_entier(c);
    

    printf("______________________\n\n");
    printf("multiplication : \n");


    afficher_grand_entier(multiplication(a,b));

    printf("puissance : \n");
    afficher_grand_entier(puissance(a,3)); 

    printf("partage : \n");
    partage(a, &c, &d, 2);
    afficher_grand_entier(c);
    afficher_grand_entier(d);

    printf("_______________\n\n");
    printf("Multiplication de Karatsuba \n");
    afficher_grand_entier(karatsuba(a,b));
    
    printf("a inferieur à b :%d\n", inferieur_a(test, Test2));

    printf("a inferieur ou egal à b :%d\n", inferieur_ou_egal_a(test, Test2));*/

    GrandEntier A1 = lecture_grand_entier("99999999999999999999999999999999999999999999999999999999999999999999999999999999");
    printf("A1="); afficher_grand_entier(A1);
    GrandEntier B1 = lecture_grand_entier("1234567890123456789012345678901234567890");
    printf("B1="); afficher_grand_entier(B1); 
    printf("ADDITION="); afficher_grand_entier(addition(A1, B1)); printf("\n");

    GrandEntier A2 = lecture_grand_entier("199999999999999999999999999999999999999999999999999999999999999999999999999999999");
    printf("A2="); afficher_grand_entier(A2);
    GrandEntier B2 = lecture_grand_entier("11234567890123456789012345678901234567890");
    printf("B2="); afficher_grand_entier(B2); 
    printf("SOUSTRACTION="); afficher_grand_entier(soustraction(A2, B2)); printf("\n");

    GrandEntier A3 = lecture_grand_entier("199999999999999999999999999999999999999999999999999999999999999999999999999999999");
    printf("A3="); afficher_grand_entier(A3);
    GrandEntier B3 = lecture_grand_entier("199999999999999999999999999999999999999999999999999999999999999999999999999999991");
    printf("B3="); afficher_grand_entier(B3); 
    printf("PLUSGRANDQUE:"); 
    int x = inferieur_a(A3, B3);
    (x == 1) ? printf("0") : printf("1");
    printf("\n\n");

    GrandEntier A4 = lecture_grand_entier("12345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890");
    printf("A4="); afficher_grand_entier(A4);
    GrandEntier B4 = lecture_grand_entier("99999999999999999999999999999999999999999999999999999999999999");
    printf("B4="); afficher_grand_entier(B4); 
    printf("MULTIPLICATIONNAIVE="); afficher_grand_entier(multiplication(A4, B4)); 
    printf("MULTIPLICATIONKARAT="); afficher_grand_entier(karatsuba(A4, B4)); printf("\n");

    GrandEntier A5 = lecture_grand_entier("12345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890");
    printf("A5="); afficher_grand_entier(A5);
    printf("MULTIPLICATIONNAIVE="); afficher_grand_entier(multiplication(A5, A5)); 
    printf("MULTIPLICATIONKARAT="); afficher_grand_entier(karatsuba(A5, A5)); printf("\n");

    GrandEntier N1 = lecture_grand_entier("12345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890");
    printf("N="); afficher_grand_entier(N1);
    unsigned int E1 = 123456789;
    printf("E=%d\n", E1);
    printf("A5^EMODULON="); afficher_grand_entier(expMod(A5, E1, N1)); printf("\n");

    GrandEntier N2 = lecture_grand_entier("12345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890");
    printf("N="); afficher_grand_entier(N2);
    unsigned int E2 = 987654321;
    printf("E=%d\n", E2);
    GrandEntier deux = lecture_grand_entier("2");
    printf("2^EMODULON=");  afficher_grand_entier(expMod(deux, E2, N2)); printf("\n");

    GrandEntier N3 = lecture_grand_entier("10000000000000000189723687123897624600000000000000130909344115489356213");
    printf("N="); afficher_grand_entier(N3);
    GrandEntier A6 = lecture_grand_entier("8686485663426759224407888859770678805723738354159785676572400332226014");
    printf("A="); afficher_grand_entier(A6);
    unsigned int E3 = 17;
    printf("E=%d\n", E3);
    printf("A^EMODULON="); afficher_grand_entier(expMod(A6, E3, N3)); printf("\n");

    GrandEntier N4 = lecture_grand_entier("10000000000000000189723687123897624600000000000000130909344115489356213");
    printf("N="); afficher_grand_entier(N4);
    GrandEntier B6 = lecture_grand_entier("1114879505571279227970284372445165131110680858963525298678652733320689");
    printf("B="); afficher_grand_entier(B6);
    unsigned int E4 = 1009;
    printf("E=%d\n", E4);
    printf("B^EMODULON="); afficher_grand_entier(expMod(B6, E4, N4)); printf("\n");

    GrandEntier N5 = lecture_grand_entier("10000000000000000189723687123897624600000000000000130909344115489356213");
    printf("N="); afficher_grand_entier(N5);
    GrandEntier M = lecture_grand_entier("1114879505571279227970284372445165131110680858963525298678652733320689");
    printf("M="); afficher_grand_entier(M);
    unsigned int E5 = 1009;
    printf("E=%d\n", E5);
    printf("B^EMODULON="); afficher_grand_entier(expMod(B6, E5, N5)); printf("\n");

    GrandEntier N6 = lecture_grand_entier("100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000012160000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000253383");
    printf("N="); afficher_grand_entier(N6);
    GrandEntier E6 = lecture_grand_entier("26491372460098638396330243727363668286317542677949618538027887477497099825349193306847666543548485163139087985459003998682524099556579043532908249083765604229295493584603683988172823034576084437663807");
    printf("E="); afficher_grand_entier(E6);
    printf("2^EMODULON=XXX\n");  printf("\n");

    GrandEntier E7 = lecture_grand_entier("36491372460098638396330243727363668286317542677949618538027887477497099825349193306847666543548485163139087985459003998682524099556579043532908249083765604229295493584603683988172823034576084437663807");
    printf("E="); afficher_grand_entier(E7);
    printf("2^EMODULON=XXX\n"); printf("\n");

    GrandEntier E8 = lecture_grand_entier("426491372460098638396330243727363668286317542677949618538027887477497099825349193306847666543548485163139087985459003998682524099556579043532908249083765604229295493584603683988172823034576084437663807");
    printf("E="); afficher_grand_entier(E8);
    printf("2^EMODULON=XXX\n"); printf("\n");

    GrandEntier E9 = lecture_grand_entier("426491372460098638396330243727363668286317542677949618538027887477497099825349193306847666543548485163139087985459003998682524099556579043532908249083765604229295493584603683988172823034576084437663807");
    printf("E="); afficher_grand_entier(E9);
    printf("2^EMODULON=XXX\n"); printf("\n");

    GrandEntier E10 = lecture_grand_entier("526491372460098638396330243727363668286317542677949618538027887477497099825349193306847666543548485163139087985459003998682524099556579043532908249083765604229295493584603683988172823034576084437663807");
    printf("E="); afficher_grand_entier(E10);
    printf("2^EMODULON=XXX\n"); printf("\n");
}
 