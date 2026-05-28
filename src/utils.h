#ifndef UTILS_H
#define UTILS_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <curl/curl.h>
#include "cJSON.h"

//Data structures

//task1 - list
typedef struct Lista{
    double valoare;
    double randament;
    struct Lista* next;
}Lista;

//task2
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

//task3 
typedef struct StockList{
    char symbol[5];
    struct StockList *next;
}StockList;

typedef struct TreeNode{
    StockList *stocks; 
    struct TreeNode *left;
    struct TreeNode *right;
    int depth;
}TreeNode;

//task4 - graph
Typedef struct Muchie{
    int nod_dest;
    int frecventa;
    struct Muchie *next;
}Muchie;

//task5
struct MemoryStruct{
    char *memory;
    size_t size;
};


//More Functions
void citire_lista(FILE *f, Lista **p, Lista **q, int n);
void free_lista(Lista **p);
void citire_stiva(FILE *f, Stack **p, char nume[]);
void print_coada(FILE *g, Oportunitate p);
void free_coada(Node **p);
void free_tree(TreeNode *root);

//task1
double Sum_Randament(Lista *p);
double Sum_Deviatie(Lista *p, double avg_randament);
void Randament_Zi(Lista *p, Lista *q);
double Sharpe_Ratio(double avg_randament, double std_deviatie);
void task1(FILE *f, FILE *g);

//task2
void task2(FILE *f, FILE *g);

//task3
void BST(TreeNode *nod, char nume[][5], double pret[][10]);
void Comparare_drumuri(TreeNode *nod, char nume[10][5], double pret[3][10], FILE *g);
void task3(FILE *f, FILE *g);

//task4
void task4(FILE *f, FILE *g);

//task bonus
double* get_open_prices(const char* symbol, const char* interval, const char* range, int *count_out);
static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp);
double* get_open_prices(const char* symbol, const char* interval, const char* range, int *count_out);
void citire_lista2(double *pret, Lista **p, Lista **q, int n);
void task1_bonus(double *preturi, int nr_preturi);
void task5();

#endif