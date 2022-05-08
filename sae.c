#include <stdio.h>
#include <stdlib.h>



// Définition des structures
typedef struct{
    int num;
    int den;

}Rationnel;

typedef struct{
    int degre;
    Rationnel * poly;
}Polynome;

//
//
// Ameliorations possibles :
//      -- Utiliser les pointeurs dans les fonctions afin de ne pas créer à chaque appel un nouveau polynome mais plutot modifier celui passe en parametres
//         cela permettrait de mieux gerer la memoire
//
//      -- Si l'utilisateur entre le meme numerateur et denominateur alors afficher directement 1      
//      -- Si l'utilisateur entre un nombre et 1 comme denominateur alors afficher directement le nombre
//
//      -- Faire un "menu" pour que l'utilisateur puisse choisir entre les differentes fonctions
//
//
//

Polynome lecturePolynome();
void afficherPolynome(Polynome p);
Polynome sommePolynome(Polynome p1, Polynome p2);
Polynome produitPolynome(Polynome p1, Polynome p2);
Polynome puissancePolynome(Polynome p, int n);
Polynome deriveePolynome(Polynome p);
Polynome racinePolynome(Polynome p);
Polynome primitivePolynome(Polynome p);
int supprimerPolynome(Polynome p);


int main(){
    printf("Définition des polynomes :\n POLYNOME 1 : \n");


    // ------------ Polynomes entres par l'utilisateur ----------- //
    Polynome p1 = lecturePolynome();
    afficherPolynome(p1);

    printf("POLYNOME 2 : \n");
    Polynome p2 = lecturePolynome();
    afficherPolynome(p2);



    // --------- Calculs effectues sur les polynomes ------- //
    printf("Dérivée de P2 : ");
    Polynome p3 = deriveePolynome(p2);
    afficherPolynome(p3);

    printf("Primitive de la derivee de P2 : ");
    Polynome p4 = primitivePolynome(p3);
    afficherPolynome(p4);

    supprimerPolynome(p3);
    supprimerPolynome(p4);

    printf("Somme de p1 et p2 : ");
    Polynome p5 = sommePolynome(p1, p2);
    afficherPolynome(p5);

    supprimerPolynome(p5);

    printf("Produit de p1 et p2 : ");
    Polynome p6 = produitPolynome(p1, p2);
    afficherPolynome(p6);

    supprimerPolynome(p6);

    printf("Puissance 2 de p1 : ");
    Polynome p7 = puissancePolynome(p1, 2);
    afficherPolynome(p7);

    supprimerPolynome(p7);

    printf("Racine de p1 : ");
    Polynome p8 = racinePolynome(p1);
    afficherPolynome(p8);

    supprimerPolynome(p8);





    return 0;

}


Polynome lecturePolynome(){
    // On demande le degré du polynome à l'utilisateur puis on alloue alors le tableau de rationnels dans la memoire
    // en fonction du degré choisi
    int degre;
    printf("Entrez le degre du polynome : ");
    scanf("%d",&degre);
    Polynome p;
    p.degre = degre;
    p.poly = (Rationnel*)malloc((degre+1)*sizeof(Rationnel));
    for(int i=0;i<=degre;i++){

        printf("Entrer le monome %d: ",i);
        scanf("%d/%d",&p.poly[i].num,&p.poly[i].den);


        // On demande d'abord le numérateur puis le dénominateur
        // printf("Entrez le numerateur %d : ",i);
        // scanf("%d",&p.poly[i].num);
        // printf("\n");

        // printf("Entrez le denominateur %d : ",i);
        // scanf("%d",&p.poly[i].den);

    }
    return p;

}

void afficherPolynome(Polynome p){
    printf(" f(x) = ");
    for(int i=0;i<=p.degre;i++){

        // if(p.poly[i].num == p.poly->den){
        //     // Si le numérateur est égal au dénominateur, on affiche juste le numérateur
        //     printf("%d",p.poly[i].num);
        //     continue;
        // }


        if (i == 0){
            // Si le degré est 0 alors on affiche pas le x mais juste le rationnel
            printf("(%d/%d)",p.poly[i].num,p.poly[i].den);
        }else if ( i == 1){
            // Si le degré est 1 alors on affiche juste le x
            printf("(%d/%d)*x",p.poly[i].num,p.poly[i].den);

        }else{
            // Sinon on affiche le x^i
        printf("(%d/%d)*x^%d",p.poly[i].num,p.poly[i].den,i);
        }

        if(i!=p.degre){
            printf(" + ");
        }
    }
    printf("\n");
}


Polynome sommePolynome(Polynome p1, Polynome p2){
    Polynome p3;
    // Le nouveau polynome est créé avec le degré du plus grand polynome
    if(p1.degre > p2.degre) {
        p3.poly = p1.degre;
    }else{
        p3.poly = p2.degre;
    }

    // On alloue la memoire pour le tableau de rationnels
    p3.poly = (Rationnel*)malloc((p3.degre+1)*sizeof(Rationnel));

    for (int i = 0; i <= p3.degre; i++) {
        if (i>p1.degre){
            p3.poly[i].num = 0 * p2.poly[i].den + p2.poly[i].num * 1;
            p3.poly[i].den = 1 * p2.poly[i].den;
        } 
        else if (i>p2.degre){
            p3.poly[i].num = p1.poly[i].num * 1 + 0 * p1.poly[i].den;
            p3.poly[i].den = p1.poly[i].den * 1;
        } else {
            p3.poly[i].num = p1.poly[i].num * p2.poly[i].den + p2.poly[i].num * p1.poly[i].den;
            p3.poly[i].den = p1.poly[i].den * p2.poly[i].den;
        }
    }
    return p3;

}

Polynome produitPolynome(Polynome p1, Polynome p2){
    Polynome p3;
    p3.degre = p1.degre + p2.degre;
    p3.poly = (Rationnel*)malloc((p3.degre+1)*sizeof(Rationnel));
    for(int i=0;i<=p1.degre;i++){
        for(int j=0;j<=p2.degre;j++){
            p3.poly[i+j].num = p1.poly[i].num * p2.poly[j].num;
            p3.poly[i+j].den = p1.poly[i].den * p2.poly[j].den;
        }
    }
    return p3;
}




Polynome puissancePolynome(Polynome p, int n){
    Polynome p3;
    p3.degre = p.degre * n;
    p3.poly = (Rationnel*)malloc((p.degre*n+1)*sizeof(Rationnel));
    for(int i=0;i<=p.degre;i++){
        for(int j=0;j<n;j++){
            p3.poly[i+j].num = p.poly[i].num;
            p3.poly[i+j].den = p.poly[i].den;
        }
    }
    return p3;
}

Polynome deriveePolynome(Polynome p){
    Polynome p3;
    p3.degre = p.degre - 1;
    p3.poly = (Rationnel*)malloc((p.degre-1)*sizeof(Rationnel));
    for(int i=0;i<p.degre;i++){
        p3.poly[i].num = p.poly[i+1].num * (i+1);
        p3.poly[i].den = p.poly[i+1].den * (i+1);
    }
    return p3;
}

Polynome racinePolynome(Polynome p){
    Polynome p3;
    p3.degre = p.degre / 2;
    p3.poly = (Rationnel*)malloc((p.degre/2)*sizeof(Rationnel));
    for(int i=0;i<p.degre;i++){
        p3.poly[i].num = p.poly[i].num;
        p3.poly[i].den = p.poly[i].den;
    }
    return p3;
}

Polynome primitivePolynome(Polynome p){
    Polynome p3;
    p3.degre = p.degre - 1;
    p3.poly = (Rationnel*)malloc((p.degre-1)*sizeof(Rationnel));
    for(int i=0;i<p.degre;i++){
        if(i == 0){
            p3.poly[i].num = (p.poly[i+1].num);
            p3.poly[i].den = (p.poly[i+1].den);
        }else
        p3.poly[i].num = (p.poly[i+1].num)/(i+1);
        p3.poly[i].den = (p.poly[i+1].den)/(i+1);
    
    }
    return p3;
}

int supprimerPolynome(Polynome p){
    free(p.poly);
    return 0;
}


