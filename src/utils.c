#include "utils.h"

//facultative
void citire_lista(FILE *f, Lista **p, Lista **q, int n){
    for(int i=1; i < n; i++){
        *q = (Lista *)malloc(sizeof(Lista));
        //printf("valoarea profitului: ");
        fscanf(f, "%lf", &((*q)->valoare));
        (*p)->next = *q;
        *p = (*p)->next;
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

void Randament_Zi(Lista *p, Lista *q){
    while(q){
        q->randament = (q->valoare - p->valoare)/p->valoare;
        p = q;
        q = q->next;
    }
}

double Sharpe_Ratio(double avg_randament, double std_deviatie){
    return avg_randament/std_deviatie;
}

void task1(FILE *f, FILE *g){
    Lista *head=NULL, *curent=NULL, *urmator=NULL;
    int Nr_obs;
    
    fscanf(f, "%d", &Nr_obs);
    if(Nr_obs > 1){
        curent = malloc(sizeof(Lista));
        fscanf(f, "%lf", &curent->valoare);
        curent->randament = 0;
        curent->next = NULL;
        head = curent;
    }
    else{
        printf("nu se poate calcula Shape ratio!\n");
        exit(1);
    }

    citire_lista(f, &curent, &urmator, Nr_obs);

    curent = head;
    urmator = curent->next;
    Randament_Zi(curent, urmator);
    double avg_randament = Sum_Randament(head->next)/(Nr_obs-1);
    double std_deviatie = sqrt(Sum_Deviatie(head->next, avg_randament)/(Nr_obs-1));
    double sh_ratio = Sharpe_Ratio(avg_randament, std_deviatie);

    if(avg_randament > 0) avg_randament = ((floor)(avg_randament*1000))/1000;
        else avg_randament = ((floor)(avg_randament*1000)+1)/1000;

    if(std_deviatie > 0) std_deviatie = ((floor)(std_deviatie*1000))/1000;
        else std_deviatie = ((floor)(std_deviatie*1000)+1)/1000;
    
    fprintf(g, "%.3lf\n%.3lf\n%.3lf\n", avg_randament, std_deviatie, sh_ratio);
    free_lista(&head);
}
