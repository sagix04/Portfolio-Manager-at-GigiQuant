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

//task1
double Sum_Randament(Lista *p);
double Sum_Deviatie(Lista *p, double avg_randament);
void Randament_Zi(Lista *p, Lista *q);
double Sharpe_Ratio(double avg_randament, double std_deviatie);
void task1(FILE *f, FILE *g);

//task2
void task2(FILE *f, FILE *g);

//taskk3
void task3(FILE *f, FILE *g);

//task4 - API (bonus)
void task4(FILE *f, FILE *g);

#endif