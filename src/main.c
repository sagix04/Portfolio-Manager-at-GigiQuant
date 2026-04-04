#include "utils.h"

int main(int argc, char *argv[])
{
    if(argc < 2) return 1;

    FILE *f = fopen(argv[1], "r");
    if(f == NULL) return 1; 

    char *fisier = strrchr(argv[1], '/');
    if (fisier == NULL) fisier = argv[1];

    int data_in = 0;
    char *p = fisier;
    while(*p){
        if( *p >= '0' && *p <= '9'){
            data_in = atoi(p);
            break;
        }
        p++;
    }

    FILE *g = stdout;
    if (argc >= 3) {
        g = fopen(argv[2], "w");
        if (g == NULL) {
            fclose(f);
            return 1;
        }
    }

    if (data_in >= 1 && data_in <= 5)
        task1(f, g);     
    else if(data_in >= 6 && data_in <= 10) 
        task2(f, g);
    else if(data_in >= 11 && data_in <= 15)
        task3(f, g);
    else if(data_in >= 16 && data_in <= 20)
        task4(f, g);

    fclose(f);
    if (g != stdout) fclose(g);    
    return 0;
}