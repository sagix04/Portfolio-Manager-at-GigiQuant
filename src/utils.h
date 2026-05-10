#ifndef UTILS_H
#define UTILS_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

//Data structures
typedef struct Lista{
    double valoare;
    double randament;
    struct Lista* next;
}Lista;

typedef struct Stack{
    double valoare;
    struct Stack *next;
}Stack;

typedef struct{
    Stack *pointer;
    char nume[101];
}City;

typedef struct Node{
    char nume[101];
    int ziua;
    double diferenta;
    struct Node *next;
}Node;

typedef struct{
    Node *head, *rear;
}Oportunitate;

typedef struct StockList{
    char symbol[5];
    struct StockList *next;
} StockList;

typedef struct TreeNode{
    StockList *stocks; 
    struct TreeNode *left;
    struct TreeNode *right;
    int depth;
} TreeNode;


//More Functions
void citire_lista(FILE *f, Lista **p, Lista **q, int n);
void free_lista(Lista **p);
void citire_stiva(FILE *f, Stack **p, char nume[]);
void print_coada(FILE *g, Oportunitate p);
void free_coada(Node **p);

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