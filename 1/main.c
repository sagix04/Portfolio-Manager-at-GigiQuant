#include "utils.h"

int main()
{
    Lista *head=NULL, *curent=NULL, *urmator=NULL;
    int Nr_obs;
    
    scanf("%d", &Nr_obs);
    if(Nr_obs > 1){
        curent = malloc(sizeof(Lista));
        scanf("%lf", &curent->valoare);
        curent->randament = 0;
        curent->next = NULL;
        head = curent;
    }
    else{
        printf("nu se poate calcula Shape ratio!\n");
        exit(1);
    }

    citire_lista(&curent, &urmator, Nr_obs);

    curent = head;
    urmator = curent->next;
    Randament_Zi(&curent, &urmator);
    double avg_randament = Sum_Randament(head)/(Nr_obs-1);
    double std_deviatie = sqrt(Sum_Deviatie(head, avg_randament)/(Nr_obs-1));
    double sh_ratio = Sharpe_Ratio(avg_randament, std_deviatie);

    if(avg_randament > 0) avg_randament = ((floor)(avg_randament*1000))/1000;
        else avg_randament = ((floor)(avg_randament*1000)+1)/1000;
    if(std_deviatie > 0) std_deviatie = ((floor)(std_deviatie*1000))/1000;
        else std_deviatie = ((floor)(std_deviatie*1000)+1)/1000;
    
    printf("%.3lf\n%.3lf\n%.3lf\n", avg_randament, std_deviatie, sh_ratio);
    fflush(stdout);

    free_lista(&head);
    return 0;
}