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
    (*p)->next = NULL;
}
void free_lista(Lista **p){
    while(*p){
        Lista *temp = *p;
        (*p) = (*p)->next;
        free(temp);
    }
}

//task1
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

        avg_randament = trunc(avg_randament * 1000)/ 1000;
        std_deviatie = trunc(std_deviatie * 1000)/ 1000;
        sh_ratio = trunc(sh_ratio * 1000)/ 1000;

    fprintf(g, "%.3lf\n%.3lf\n%.3lf\n", avg_randament, std_deviatie, sh_ratio);
    free_lista(&head);
}

//task2
void task2(FILE *f, FILE *g){

}

void task3(FILE *f, FILE *g){

}

void task4(FILE *f, FILE *g){

}