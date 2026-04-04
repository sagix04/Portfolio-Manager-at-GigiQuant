#include "utils.h"

//facultative
void citire_lista(Lista **p, Lista **q, double n){
    for(int i=1; i < n; i++){
        *q = (Lista *)malloc(sizeof(Lista));
        //printf("valoarea profitului: ");
        scanf("%lf", &((*q)->valoare));
        (*p)->next = *q;
        *p = (*p)->next;
    }
}

void printare_lista(Lista *p){
    int i=1;
    while(p){
        printf("\n--------------------ziua %d--------------------\n", i);
        printf("profit: %lf\n", p->valoare);
        printf("randament: %lf\n", p->randament);
        p = p->next;
        i++;
    }
}

void free_lista(Lista **p){
    while(*p){
        Lista *temp = *p;
        (*p) = (*p)->next;
        free(temp);
    }
}

//principale
double Sum_Randament(Lista *p){
    double sum=0;
    while(p){
        sum += p->randament;
        p = p->next;
    }
    return sum;
}

double Sum_Deviatie(Lista *p, double avg_randament){
    double sum=0;
    while(p){
        sum += pow((p->randament - avg_randament), 2);
        p = p->next;
    }
    return sum;
}

void Randament_Zi(Lista **p, Lista **q){
    while(*q){
        (*q)->randament = ((*q)->valoare - (*p)->valoare)/(*p)->valoare;
        *p = *q;
        *q = (*q)->next;
    }
}

double Sharpe_Ratio(double avg_randament, double std_deviatie){
    return avg_randament/std_deviatie;
}


