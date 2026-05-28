#include "utils.h"

//task1
void citire_lista(FILE *f, Lista **p, Lista **q, int n){
    for(int i=1; i < n; i++){
        *q = (Lista *)malloc(sizeof(Lista));
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
        curent->randament = 0; //Neutru pentru urmatoarea zi
        curent->next = NULL;
        head = curent;
    }
    else{
        printf("nu se poate calcula Shape ratio!\n");
        exit(1);
    }

    //construirea listei
    citire_lista(f, &curent, &urmator, Nr_obs);

    //reset pointeri
    curent = head;
    urmator = curent->next;

    //calcule + trunchiere
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
        if (strchr("1234567890", linie[0])){ //Alege daca e nume sau valoare
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
        else if(p2->valoare == p1->valoare && p2->valoare != p0->valoare){
            Node *temp = malloc(sizeof(Node));
            strcpy(temp->nume, oras[0].nume);
            temp->diferenta = p2->valoare - p0->valoare;
            if(temp->diferenta < 0)
                temp->diferenta = -temp->diferenta;temp->ziua = i;
            temp->next = NULL;
            if(OK == 0){
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
//nu a fost predat la timp
void BST(TreeNode *nod, char nume[][5], double pret[][10]){
    if(nod == NULL || nod->depth >= 4) return;
    int zi = nod->depth;
    StockList *curr = nod->stocks;
    while(curr != NULL){
        int i = 0;
        //indicele actiunii
        while(i < 10 && strcmp(curr->symbol, nume[i]) != 0) 
            i++;
        
        //fiecare nod se testeaza daca merge pe ramura din stanga sau dreapta
        //se creeaza o lista pentru fiecare nod al arborelui pentru denumirea actiuniilor
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
        //actiune i, oglindit = opusul actiunii i
        TreeNode *oglindit = root;

        //cale pentru oglindit
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
                    //dubla validare, ne asiguram ca nu se adevareste if-ul
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

//initializat matricile si arborele (root-ul)
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
long long cmmdc(long long a, long long b){
    long long r;
    while(b){
        r = a % b;
        a = b;
        b = r;
    }
    return a;
}

void task4(FILE *f, FILE *g){
    int n, k_zile, intervale[1000], stari[200], nr_stari = 0, id_start = -1, id_target = -1, u, v, out[200];
    double d, p_start, p_target, preturi[1000];

    fscanf(f, "%d %lf %d %lf %lf", &n, &d, &k_zile, &p_start, &p_target);
    for(int i = 0; i < n; i++){
        fscanf(f, "%lf", &preturi[i]);
        intervale[i] = (int)(preturi[i] / d);
    }

    for(int i = 0; i < n; i++){
        int ok = 0;
        for(int j = 0; j < nr_stari; j++)
            if(stari[j] == intervale[i])
                ok = 1;
        //stari unice
        if(ok == 0){ 
            stari[nr_stari] = intervale[i];
            nr_stari++;
        }
    }

    Muchie *graf[200];
    for(int i = 0; i < nr_stari; i++){
        if(stari[i] == (int)(p_start / d))
            id_start = i;
        if(stari[i] == (int)(p_target / d))
            id_target = i;
            
        out[i] = 0;
        graf[i] = NULL;
    }
    for(int i = 0; i < n - 1; i++){
        for(int j = 0; j < nr_stari; j++){
            if(stari[j] == intervale[i])
                u = j;
            if(stari[j] == intervale[i+1])
                v = j;
        }
        
        out[u]++;

        //De aici am continuat dupa deadline ul
        //Adaugam muchia u -> v
        int gasit = 0;
        Muchie *crt = graf[u];
        while(crt != NULL){
            if(crt->nod_dest == v){ 
                crt->frecventa++;
                gasit = 1;
                break;
            }
            crt = crt->next;
        }
            
        if(gasit == 0){
            Muchie *nou = malloc(sizeof(Muchie));
            nou->nod_dest = v;
            nou->frecventa = 1;
            nou->next = NULL;
                    
            if(graf[u] == NULL)
                graf[u] = nou;
            else{
                Muchie *temp = graf[u];
                while (temp->next != NULL)
                    temp = temp->next;
                temp->next = nou;
            }
        } 
    }

    long long num[200], den[200]; //calculam probabilitatea
    for(int i = 0; i < nr_stari; i++){
        num[i] = 0;
        den[i] = 1;
    }

    if(id_start != -1)
        num[id_start] = 1; 

    for(int zi = 1; zi <= k_zile; zi++){
        if (id_target != -1){
            if (num[id_target] == 0)
                fprintf(g, "0\n");
            else if (den[id_target] == 1)
                fprintf(g, "%lld\n", num[id_target]);
            else
                if(zi < k_zile)
                    fprintf(g, "%lld/%lld\n", num[id_target], den[id_target]);
                else
                    fprintf(g, "%lld/%lld", num[id_target], den[id_target]);
        }
        else{
            fprintf(g, "0\n");
        }

        long long nn[200], nd[200];
        for(int i = 0; i < nr_stari; i++){
            nn[i] = 0;
            nd[i] = 1;
        }

        for(int i = 0; i < nr_stari; i++){
            if (num[i] > 0){ //Daca exista sanse sa fim in starea i
                Muchie *crt = graf[i];
                
                while (crt != NULL){
                    int dest = crt->nod_dest;
                    
                    //Inmultim probabilitatea starii actuale cu probabilitatea muchiei (frecventa / out)
                    long long n1 = num[i] * crt->frecventa;
                    long long d1 = den[i] * out[i];
                    long long g1 = cmmdc(n1, d1);
                    n1 /= g1;
                    d1 /= g1;

                    //Adunam toate cazurile
                    long long top = nn[dest] * d1 + n1 * nd[dest];
                    long long bot = nd[dest] * d1;
                    long long g2 = cmmdc(top, bot);
                    
                    nn[dest] = top / g2;
                    nd[dest] = bot / g2;

                    crt = crt->next;
                }
            }
        }
        //Modificam vectorii pentru urmatoarea zi
        for(int i = 0; i < nr_stari; i++){
            num[i] = nn[i];
            den[i] = nd[i];
        }
    }

    //free
    for (int i = 0; i < nr_stari; i++){
        Muchie *crt = graf[i];
        while (crt != NULL){
            Muchie *temp = crt;
            crt = crt->next;
            free(temp);
        }
    }
}

//task5 - BONUS
/*
static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp){
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *) userp;
    char *ptr = realloc(mem->memory, mem->size + realsize + 1);
    
    if (!ptr) return 0;
    
    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;
    
    return realsize;
}

double* get_open_prices(const char* symbol, const char* interval, const char* range, int *count_out){
    CURL *curl_handle;
    struct MemoryStruct chunk = {malloc(1), 0};
    char url[256];
    double *prices = NULL;
    
    sprintf(url, "https://query1.finance.yahoo.com/v8/finance/chart/%s?interval=%s&range=%s", symbol, interval, range);
    curl_handle = curl_easy_init();
    
    curl_easy_setopt(curl_handle, CURLOPT_URL, url);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);
    curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");
    
    if (curl_easy_perform(curl_handle) == CURLE_OK) {
        cJSON *json = cJSON_Parse(chunk.memory);
        cJSON *result = cJSON_GetArrayItem(cJSON_GetObjectItem(cJSON_GetObjectItem(json, "chart"), "result"), 0);
        cJSON *quote = cJSON_GetArrayItem(cJSON_GetObjectItem(cJSON_GetObjectItem(result, "indicators"), "quote"), 0);
        cJSON *open_prices = cJSON_GetObjectItem(quote, "open");
        
        *count_out = cJSON_GetArraySize(open_prices);
        prices = malloc((*count_out) * sizeof(double));
        
        for (int i = 0; i < *count_out; i++) {
            cJSON *val = cJSON_GetArrayItem(open_prices, i);
            prices[i] = cJSON_IsNumber(val) ? val->valuedouble : -1.0;
        }
        cJSON_Delete(json);
    }
    
    curl_easy_cleanup(curl_handle);
    free(chunk.memory);
    
    return prices;
}

void citire_lista2(double *pret, Lista **p, Lista **q, int n){
    for(int i=1; i < n; i++){
        *q = (Lista *)malloc(sizeof(Lista));
        (*q)->valoare = pret[i];
        (*p)->next = *q;
        *p = (*p)->next;
    }
    (*p)->next = NULL;
}

void task1_bonus(double *pret, int n){
    Lista *head=NULL, *curent=NULL, *urmator=NULL;
    int Nr_obs = n;
    if(Nr_obs > 1){
        curent = malloc(sizeof(Lista));
        curent->valoare = pret[0];
        curent->randament = 0;
        curent->next = NULL;
        head = curent;
    }

    citire_lista2(pret, &curent, &urmator, n);

    curent = head;
    urmator = curent->next;
    Randament_Zi(curent, urmator);
    double avg_randament = Sum_Randament(head->next)/(Nr_obs-1);
    double std_deviatie = sqrt(Sum_Deviatie(head->next, avg_randament)/(Nr_obs-1));
    double sh_ratio = trunc(Sharpe_Ratio(avg_randament, std_deviatie) *1000) / 1000;

        avg_randament = trunc(avg_randament * 1000)/ 1000;
        std_deviatie = trunc(std_deviatie * 1000)/ 1000;

    printf("randament: %.3lf\n" "deviatie: %.3lf\n" "shape ratio: %.3lf\n", avg_randament, std_deviatie, sh_ratio);
    free_lista(&head);
}

void task5(){
    //parametrii API
    const char *simbol = "AAPL", *interval = "1d", *perioada = "1mo";

    int nr_preturi = 0;
    double *preturi = get_open_prices(simbol, interval, perioada, &nr_preturi);

    printf("Preturile actiunii %s in ultima luna:\n", simbol);
    for (int i = 0; i < nr_preturi; i++)
        printf("Ziua %d: %.2lf\n", i + 1, preturi[i]);

    //implementam task1 pentru task5
    task1_bonus(preturi, nr_preturi);
    free(preturi);
}
*/