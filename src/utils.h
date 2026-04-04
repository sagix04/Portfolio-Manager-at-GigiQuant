#ifndef UTILS_H
#define UTILS_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

typedef struct Node{
    double valoare;
    double randament;
    struct Node* next;
}Lista;


//antet functii

//bonus
void citire_lista(FILE *f, Lista **p, Lista **q, int n);
void free_lista(Lista **p);

//interviu 1
double Sum_Randament(Lista *p);
double Sum_Deviatie(Lista *p, double avg_randament);
void Randament_Zi(Lista *p, Lista *q);
double Sharpe_Ratio(double avg_randament, double std_deviatie);
void task1(FILE *f, FILE *g);
//interviu 2

//API (bonus)

#endif