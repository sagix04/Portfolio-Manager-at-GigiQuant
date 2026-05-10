#include "utils.h"

//task1
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
    double sh_ratio = trunc(Sharpe_Ratio(avg_randament, std_deviatie) *1000) / 1000;

        avg_randament = trunc(avg_randament * 1000)/ 1000;
        std_deviatie = trunc(std_deviatie * 1000)/ 1000;

    fprintf(g, "%.3lf\n%.3lf\n%.3lf\n", avg_randament, std_deviatie, sh_ratio);
    free_lista(&head);
}

//task2
void citire_stiva(FILE *f, Stack **p, char nume[]){
    char linie[101];

    while (fgets(linie, 100, f) != NULL)
        if (strchr("1234567890", linie[0])){
            Stack *q = malloc(sizeof(Stack));
            q->valoare = atof(linie);
            q->next = *p;
            *p = q;
        }
        else{
            strcpy(nume, linie);
            return;
        }
}

void free_stiva(Stack **p){
    while(*p){
        Stack *temp = *p;
        (*p) = (*p)->next;
        free(temp);
    }
}

void print_coada(FILE *g, Oportunitate p){
    while(p.head){
        fprintf(g, "ziua %d - %.2lf - %s", p.head->ziua, p.head->diferenta, p.head->nume);
        p.head = p.head->next;
    }
}

void free_coada(Node **p){
    while(*p){
        Node *temp = *p;
        (*p) = (*p)->next;
        free(temp);
    }
}

void task2(FILE *f, FILE *g){
    City oras[3];
    char nume[101];
    fgets(oras[0].nume, 100, f);
    oras[0].pointer = NULL;

    int i, n=3;
    for (i = 0; i < n; i++){
        oras[i].pointer = NULL;
        if(i < n-1)
            citire_stiva(f, &(oras[i].pointer), oras[i+1].nume);
        else
            citire_stiva(f, &(oras[i].pointer), nume);
    }
    
    i = 1;
    int OK=0;
    Oportunitate coada;
    coada.head = NULL;
    coada.rear = NULL;
    Stack *p0 = oras[0].pointer, *p1 = oras[1].pointer, *p2 = oras[2].pointer;
    while(p0 && p1 && p2){
        if(p0->valoare == p1->valoare && p2->valoare != p0->valoare){
            Node *temp = malloc(sizeof(Node));
            strcpy(temp->nume, oras[2].nume);
            temp->diferenta = p2->valoare - p0->valoare;
            if(temp->diferenta < 0)
                temp->diferenta = -temp->diferenta;
            temp->ziua = i;
            temp->next = NULL;

            if (OK == 0){
                coada.head = temp;
                coada.rear = temp;
                OK++;
            }
            else{
                coada.rear->next = temp;
                coada.rear = temp;
            }
        }
        else if(p0->valoare == p2->valoare && p1->valoare != p0->valoare){
            Node *temp = malloc(sizeof(Node));
            strcpy(temp->nume, oras[1].nume);
            temp->diferenta = p1->valoare - p0->valoare;
            if(temp->diferenta < 0)
                temp->diferenta = -temp->diferenta;
            temp->ziua = i;
            temp->next = NULL;

            if (OK == 0){
                coada.head = temp;
                coada.rear = temp;
                OK++;
            }
            else{
                coada.rear->next = temp;
                coada.rear = temp;
            }
        }
        else if (p2->valoare == p1->valoare && p2->valoare != p0->valoare){
            Node *temp = malloc(sizeof(Node));
            strcpy(temp->nume, oras[0].nume);
            temp->diferenta = p2->valoare - p0->valoare;
            if(temp->diferenta < 0)
                temp->diferenta = -temp->diferenta;temp->ziua = i;
            temp->next = NULL;
            if (OK == 0){
                coada.head = temp;
                coada.rear = temp;
                OK++;
            }
            else{
                coada.rear->next = temp;
                coada.rear = temp;
            }
        }
        p0 = p0->next;
        p1 = p1->next;
        p2 = p2->next;
        i++;
    }

    for(i=0; i < n; i++)
        free_stiva(&(oras[i].pointer));

    print_coada(g, coada);
    free_coada(&(coada.head));
}

//task3
void task3(FILE *f, FILE *g){
    /*
        De creat un arbore cu structurile din interviu, de folosit task ul 1 pt oportunitatile la fiecare 
        actiune, de comparat intr un anume fel fiecare actiune pentru a construi un bst, valoarea nodului va 
        fi media aritmetica a actiunilor
    */
}

void task4(FILE *f, FILE *g){

}