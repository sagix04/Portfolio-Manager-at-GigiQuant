#include "utils.h"

int main(int argc, char *argv[]){

    //verificare elemente introduse in linia de comanda a terminalului (./test /.../data1.in data1.out => 3 elemente: 0, 1, 2)
    if(argc < 2) return 1;
    FILE *f = fopen(argv[1], "r");

    //extrage numele pentru fisier din calea absoluta
    char *fisier = strrchr(argv[1], '/');

    //sau il poate extrage instant daca nu exista o cale absoluta, ci doar numele fisierului
    if (fisier == NULL) fisier = argv[1];

    int data_in = 0;
    char *p = fisier;
    while(*p){
        if(*p >= '0' && *p <= '9'){
            data_in = atoi(p); //extrage in format int valoarea numerica din sir
            break;
        }
        p++;
    }

    FILE *g;
    g = fopen(argv[2], "w");
    if (g == NULL){
        fclose(f);
        return 1;
    }

    if (data_in >= 1 && data_in <= 5)
        task1(f, g);     
    else if(data_in >= 6 && data_in <= 10) 
        task2(f, g);
    else if(data_in >= 11 && data_in <= 15)
        task3(f, g);
    else if(data_in >= 16 && data_in <= 20)
        task4(f, g);
/*
    else
        task5(f, g);
*/
    fclose(f); fclose(g);    
    return 0;
}