#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "func.h"

char rule[30] = "func(myFunction)"; // sirul care contine regula
char code[N];                       // sirul care se introduce de la tastatura sau se genereaza

int main()
{
    printf("Ce varianta dorti sa alegeti?\n");              // am creat un meniu din care utilizatorul poate
    printf("1. Generarea sirului aleatoriu\n");             // alege daca vrea ca sirul sa se genereze automat
    printf("2. Introducerea sirului de la tastatura\n");    // sau daca vrea sa il introduca de la tastatura
    int raspuns;
    scanf("%d", &raspuns);

    if(raspuns == 1) {
        printf("Ce lungime sa aiba sirul generat?\n");
        scanf("%lld", &length);

        srand(time(0));
        generateString(code);
    } else if (raspuns == 2){
        printf("Ce lungime sa aiba sirul citit?\n");
        scanf("%lld", &length);
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {}
        fgets(code, length, stdin);
        code[strlen(code) - 1] = '\0';
    } else {
        printf("Trebuie sa introduci unul dintre numerele de mai sus!");
        return 0;
    }

    printf("Sirul inainte de corectare: \n%s\n\n", code);
    clock_t begin = clock();
    int distance = getDistance(rule, code);
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Distanta dintre cele doua siruri este: %d\n\n", distance);
    printf("Sirul dupa corectare: \n%s\n\n", code);
    printf("secunde : %llf", time_spent);

    return 0;
}
