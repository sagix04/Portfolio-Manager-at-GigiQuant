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
void BST(TreeNode *nod, char nume[][5], double pret[][10]){
    if(nod == NULL || nod->depth >= 4) return;
    int zi = nod->depth;
    StockList *curr = nod->stocks;
    while(curr != NULL){
        int i = 0;
        while(i < 10 && strcmp(curr->symbol, nume[i]) != 0) 
            i++;
        
        if(i < 10){
            if(pret[zi][i] < pret[zi - 1][i]){
                if(nod->left == NULL){
                    nod->left = malloc(sizeof(TreeNode));
                    nod->left->left = NULL;
                    nod->left->stocks = NULL;
                    nod->left->depth = nod->depth + 1;
                }
                StockList *nou = malloc(sizeof(StockList));
                strcpy(nou->symbol, curr->symbol);
                nou->next = NULL;
                if(nod->left->stocks == NULL)
                    nod->left->stocks = nou;
                else{
                    StockList *t = nod->left->stocks;
                    while(t->next != NULL) 
                        t = t->next;
                    t->next = nou;
                }
            }
            else{
                if(nod->right == NULL){
                    nod->right = malloc(sizeof(TreeNode));
                    nod->right->left = NULL;
                    nod->right->right = NULL;
                    nod->right->stocks = NULL;
                    nod->right->depth = nod->depth + 1;
                }
                StockList *nou = malloc(sizeof(StockList));
                strcpy(nou->symbol, curr->symbol);
                nou->next = NULL;
                if (nod->right->stocks == NULL)
                    nod->right->stocks = nou;
                else{
                    StockList *t = nod->right->stocks;
                    while (t->next != NULL) 
                        t = t->next;
                    t->next = nou;
                }
            }
        }
        curr = curr->next;
    }
    BST(nod->left, nume, pret);
    BST(nod->right, nume, pret);
}

void Comparare_drumuri(TreeNode *root, char nume[][5], double pret[][10], FILE *g){
    int OK = 1;
    for(int i = 0; i < 10; i++){
        TreeNode *oglindit = root;
        for(int zi = 1; zi <= 3; zi++){
            if(pret[zi][i] < pret[zi - 1][i]){
                if(oglindit != NULL) 
                    oglindit = oglindit->right;
            }
            else{
                if(oglindit != NULL) 
                    oglindit = oglindit->left;
            }
        }
    
        if(oglindit != NULL && oglindit->stocks != NULL){
            StockList *temp = oglindit->stocks;
            while(temp != NULL){
                int j = 0;
                while(j < 10 && strcmp(temp->symbol, nume[j]) != 0) j++;
                if(j > i && j < 10){
                    int check = 1;
                    for(int k = 1; k <= 3; k++){
                        if((pret[k][i] < pret[k-1][i]) == (pret[k][j] < pret[k-1][j])){
                            check = 0;
                            break;
                        }
                    }
                    if(check == 1){
                        if(OK == 0) 
                            fprintf(g, "\n");
                        fprintf(g, "%s-%s", nume[i], nume[j]);
                        OK = 0;
                    }
                }
                temp = temp->next;
            }
        }
    }
}

void free_tree(TreeNode *root){
    if(root == NULL) return;
    free_tree(root->left);
    free_tree(root->right);
    
    StockList *curr = root->stocks;
    while(curr != NULL){
        StockList *temp = curr;
        curr = curr->next;
        free(temp);
    }
    free(root);
}

void task3(FILE *f, FILE *g){
    char nume[10][5];
    double pret[4][10];

    for(int i = 0; i < 10; i++){
        fscanf(f, " %4[^,\n\r]", nume[i]);
        fgetc(f);
    }
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 10; j++){
            fscanf(f, "%lf", &pret[i][j]);
            fgetc(f);
        }

    TreeNode *root = malloc(sizeof(TreeNode));
    root->left = root->right = NULL;
    root->stocks = NULL;
    root->depth = 1;
    StockList *p = NULL;
    for (int i = 0; i < 10; i++){
        StockList *q = malloc(sizeof(StockList));
        strcpy(q->symbol, nume[i]);
        q->next = NULL;
        if(root->stocks == NULL){
            root->stocks = q; 
            p = q;
        }
        else{
            p->next = q; 
            p = q;
        }
    }

    BST(root, nume, pret);
    Comparare_drumuri(root, nume, pret, g);
    free_tree(root);
}

//task4
void task4(FILE *f, FILE *g){

}