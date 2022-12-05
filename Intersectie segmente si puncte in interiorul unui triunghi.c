#include "graphics.h"
#include <math.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define N 3

typedef struct {
        float x, y;
} punct;

typedef struct {
        punct p1, p2;
}dreapta;

punct P[N + 1];
punct m;
punct m2;

using namespace std;

#define pi 3.14159265359

int gd, gm;
int n, i, j;
double r, x, y, xp, yp, fi;
float x_1, x_2, y_1, y_2; int x_max, y_max;

int xe(float x){
    return((int)floor((x - x_1) / (x_2 - x_1)*x_max));
}

int ye(float y){
    return((int)floor((y_2 - y) / (y_2 - y_1)*y_max));
}

void axe2D(){
    setcolor(0);
    outtextxy(xe(x_2) - 20, ye(0) - 20, "x");
    outtextxy(xe(x_2) - 18, ye(0) - 7, ">");
    outtextxy(xe(0) - 15, ye(y_2) + 15, "y");
    outtextxy(xe(0) - 15, ye(0) - 15, "O");
    outtextxy(xe(0) - 1, ye(y_2), "^");
    line(xe(x_1), ye(0), xe(x_2), ye(0));
    line(xe(0), ye(y_1), xe(0), ye(y_2));
}

void linie2D(float xa, float ya, float xb, float yb){
     line(xe(xa), ye(ya), xe(xb), ye(yb));
}

void grafic(){
    char pct[10];
         for (int i = 0; i < N; i++){
             sprintf(pct, "%d", i + 1);
             outtextxy(xe(P[i].x) + 5, ye(P[i].y) + 5, pct);
             if (i<N - 1)
                linie2D(P[i].x, P[i].y, P[i + 1].x, P[i + 1].y);
                pct[0] = 0;
                }
    linie2D(P[N - 1].x, P[N - 1].y, P[0].x, P[0].y);
    outtextxy(xe(m.x) + 5, ye(m.y) + 5, "M");
    outtextxy(xe(m2.x) + 5, ye(m2.y) + 5, "N");
    circle(xe(m.x) + 1, ye(m.y) + 1, 3);
    circle(xe(m2.x) + 1, ye(m2.y) + 1, 3);
    //linie2D(m.x, m.y, m2.x, m2.y); //dreapta MN
}

int citire_poligon(){
    for (int i = 0;i < N; i++){
        printf("\nP[%d].x=", i+1);
        scanf("%f", &P[i].x);
        printf("\nP[%d].y=", i+1);
        scanf("%f", &P[i].y);
    }
    return 1;
}

void citire_punct(punct& m){
    printf("\nm.x=");
    scanf("%f", &m.x);
    printf("\nm.y=");
    scanf("%f", &m.y);
}

int orientare(punct P, punct Q, punct R){
    float d = (float)(Q.x - P.x)*(R.y - P.y) - (float)(Q.y - P.y)*(R.x - P.x);
    if (d>0) 
       return 1;
    if (d<0) 
       return -1;
    if (d == 0) 
       return 0;
}

int coliniare(punct P, punct Q, punct R){
    if (orientare(P, Q, R) != 0) 
       return 0;
    else 
         return 1;
    }
    
int intre(punct P, punct Q, punct R){
    if (!coliniare(P, Q, R)) 
       return 0;
    if (P.x != R.x) 
       return (((P.x <= Q.x) && (Q.x <= R.x)) || ((P.x >= Q.x) && (Q.x >= R.x)));
    else 
         return(((P.y <= Q.y) && (Q.y <= R.y)) || ((P.y >= Q.y) && (Q.y >= R.y)));
}

int intersectie_proprie(punct P, punct Q, punct R, punct S){
    return ((orientare(P, Q, R) * orientare(P, Q, S)< 0) && (orientare(R, S, P) * orientare(R, S, Q) < 0));
}

int intersectie_improprie(punct P, punct Q, punct R, punct S){
    return ((intre(R, P, S)) || (intre(R, Q, S)) || (intre(P, R, Q)) || (intre(P, S, Q)));
}

int intersectie_segmente(punct A, punct B, punct C, punct D){
    return ((intersectie_proprie(A, B, C, D)) || (intersectie_improprie(A, B, C, D)));
}

int interior(punct& m){
    int nr = 2;
    P[N].x = P[0].x;
    P[N].y = P[0].y;
    dreapta test, lp;
    test.p1.x = m.x;
    test.p1.y = m.y;
    test.p2.x = 32760;
    test.p2.y = m.y;//se construieste o semidreapta orizontala pornind din m
    for (int i = 0;i<N;i++){
        lp.p1 = P[i];
        lp.p2 = P[i + 1];
        if (intersectie_segmente(test.p1, test.p2, lp.p1, lp.p2))
           nr = nr + 1;
    }
    return nr % 2;//daca impar at. in int. poligonului, altfel in ext. polig.
}

int main(){
    printf("Limitele domeniului orizontal:\n");
    printf("x1 = -10\n"); x_1 = -10;//scanf("%f", &x_1); //x_1<0<x_2
    printf("x2 = 10\n"); x_2 = 10;// scanf("%f", &x_2);
    printf("Limitele domeniului vertical:\n");
    printf("y1 = -10\n"); y_1 = -10;//scanf("%f", &y_1); //y_1<0<y_2
    printf("y2 = 10\n"); y_2 = 10;//scanf("%f", &y_2);
    
    citire_poligon();
    citire_punct(m);
    citire_punct(m2);
    
    initwindow(800, 600, "intersectii de segmente", 200, 200);
    x_max = getmaxx(); 
    y_max = getmaxy();
    setbkcolor(15);
    cleardevice();
    axe2D();
    grafic();
    
    /// verificare punct pe aceeasi dreapta
    
    // pct M
    printf("\n\n");
    if (interior(m))
       printf("Punctul M este interior triunghiului.");
    else 
         printf("Punct M este exterior triunghiului.");
       // pct N 
    printf("\n\n");     
    if (interior(m2))
       printf("Punctul N este interior triunghiului.");
    else 
         printf("Punct N este exterior triunghiului.");
         
    printf("\n\nTipul intersectiei laturilor MN si 12 este:");
    //1-2   Tipul intersectiei laturilor MN si 12 este  
    if (intersectie_proprie(P[0], P[1], m, m2))
       printf(" proprie");
    else if (intersectie_improprie(P[0], P[1], m, m2))
         printf(" improprie");
    else 
         printf(" vida");
         
    printf("\n\nTipul intersectiei laturilor MN si 23 este:");     
    if (intersectie_proprie(P[1], P[2], m, m2))
       printf(" proprie");
    else if (intersectie_improprie(P[1], P[2], m, m2))
         printf(" improprie");
    else 
         printf(" vida");
    
    printf("\n\nTipul intersectiei laturilor MN si 13 este:");     
    if (intersectie_proprie(P[0], P[2], m, m2))
       printf(" proprie");
    else if (intersectie_improprie(P[0], P[2], m, m2))
         printf(" improprie");
    else 
         printf(" vida");          
    
    getch(); getch();
    return 1;
}