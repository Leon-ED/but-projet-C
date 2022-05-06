#include <stdio.h>
#include <stdlib.h>


typedef struct{
    int num;
    int den;

}Rationnel;

typedef struct{
    int degre;
    Rationnel * poly;
}Polynome;


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
    Polynome p = lecturePolynome();
    afficherPolynome(p);

    Polynome p2 = lecturePolynome();
    afficherPolynome(p2);

    printf("Dérivee de p \n");
    Polynome p8 = deriveePolynome(p);
    afficherPolynome(p8);

    printf("Primitive de p2 (p2 etant la derivee de p (ne marche pas totalement)) \n");
    Polynome p3 = primitivePolynome(p2);
    afficherPolynome(p3);

    printf("Racine de p \n");
    Polynome p4 = racinePolynome(p);
    afficherPolynome(p4);
    supprimerPolynome(p4);

    printf("Somme de p et p2 \n");
    Polynome p5 = sommePolynome(p, p2);
    afficherPolynome(p5);
    supprimerPolynome(p5);

    printf("Produit de p et p2 \n");
    Polynome p6 = produitPolynome(p, p2);
    afficherPolynome(p6);
    supprimerPolynome(p6);

    printf("Puissance de p2 \n");
    Polynome p7 = puissancePolynome(p2, 3);
    afficherPolynome(p7);
    supprimerPolynome(p7);



    return 0;

}



Polynome lecturePolynome(){
    int degre;
    printf("Entrez le degre du polynome : ");
    scanf("%d",&degre);
    Polynome p;
    p.degre = degre;
    p.poly = (Rationnel*)malloc((degre+1)*sizeof(Rationnel));
    for(int i=0;i<=degre;i++){
        printf("Entrez le numerateur %d : ",i);
        scanf("%d",&p.poly[i].num);
        printf("Entrez le denominateur %d : ",i);
        scanf("%d",&p.poly[i].den);

    }
    return p;

}

void afficherPolynome(Polynome p){
    printf("Le polynome est : f(x) = ");
    for(int i=0;i<=p.degre;i++){
        if (i == 0){
            printf("(%d/%d)",p.poly[i].num,p.poly[i].den);
        }else if ( i == 1){
            printf("(%d/%d)*x",p.poly[i].num,p.poly[i].den);

        }else{
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
    p3.degre = p1.degre;
    p3.poly = (Rationnel*)malloc((p1.degre+1)*sizeof(Rationnel));
    for(int i=0;i<=p1.degre;i++){
        p3.poly[i].num = p1.poly[i].num + p2.poly[i].num;
        p3.poly[i].den = p1.poly[i].den + p2.poly[i].den;
    }
    return p3;
}

Polynome produitPolynome(Polynome p1, Polynome p2){
    Polynome p3;
    p3.degre = p1.degre + p2.degre;
    p3.poly = (Rationnel*)malloc((p1.degre+p2.degre+1)*sizeof(Rationnel));
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
        p3.poly[i].num = p.poly[i+1].num;
        p3.poly[i].den = p.poly[i+1].den;
    }
    return p3;
}

int supprimerPolynome(Polynome p){
    free(p.poly);
    return 0;
}