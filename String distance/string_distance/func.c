#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "func.h"

// functia findChar cauta un caracter in lista, iar daca il gaseste il returneaza

Character* findChar(char c) {
    Character* current = charArr.head;  // pointerul current primeste pozitia primului nod al listei
    while(current != NULL){             // cat timp current este diferit de NULL
        if(current->ch == c) {          // daca carcaterul retinut de obiect este acelasi ca cel cautat
            return current;             // se returneaza un pointer catre obiectul respectiv
        }
        current = current->next;        // current primeste trece la urmatorul nod din lista
    }
    return NULL;                        // daca nu se gaseste caracterul cautat se returneaza NULL
}

// functia freePointers elibereaza pointerii

void freePointers() {
    Character* current = charArr.head;      // pointerul current primeste pozitia primului nod al listei
    while(current != NULL){                 // cat timp current este diferit de NULL
        Character* next = current->next;    // pointerul next primeste nodul de dupa nodul curent
        free(current);                      // se elibereaza pointerul curent
        current = next;                     // current tece la nodul salvat in next
    }
}

// functia addToList adauga caractere intr-o lista

void addToList(Character* element) {
    if(charArr.head == NULL) {        // daca capul listei este NULL inseamna ca lista inca nu a fost creata
        charArr.head = element;       // capul listei primeste elementul pe care dorim sa il adaugam in lista
        charArr.tail = element;       // pentru ca in acest caz avem doar primul nod, si tail primeste tot acel element
        charArr.head->next = NULL;    // head->next primeste NULL deoarece acolo se termina lista
    } else {                          // in cazul in care lista a fost deja creata
        charArr.tail->next = element; // tail->next primeste elementul pe care vrem sa il adaugam
        charArr.tail = element;       // apoi il mutam pe tail la elementul nou adaugat
        element->next = NULL;         // pentru ca element este ultimul element->next este NULL
    }
}

// functia createFrequencyArray creaza o lista ce are rolul unui vector de aparitii in care
// creste numarul de aparitii al fiecarui caracter ce apare in sirul rule, dupa care scade numarul
// de aparitii pentru caracterele ce apar in sirul code. se urmareste ca valorile sa ajunga la 0,
// ceea ce inseamna ca acele caractere apar de acelasi numar de ori in ambele siruri

void createFrequencyArray(char* rule, char* code) {
    charArr.head = NULL;
    charArr.tail = NULL;

    for(long long i = 0; i < strlen(rule); i++) {   // se parcurge sirul rule
        Character* element = findChar(rule[i]);     // se cauta caracterul de la pozitia i din rule
        if(element != NULL) {                       // daca sa mai gasit la o alta pozitie anterioara
            element->cnt++;                         // se creste numarul de aparitii al caracterului
        } else {
            element = (Character*)malloc(sizeof(Character));// in cazul in care nu a mai fost gasit anterior
            element->ch = rule[i];                          // caracterul curent va fi egal cu caracterul de la pozitia
            element->cnt = 1;                               // i din sirul rule si se va contoriza in cnt
            element->next = NULL;                           // campul urmator al noului nod va fi NULL
            addToList(element);                             // apelez functia de adaugare in lista a noului element
        }
    }

    for(long long i = 0; i < strlen(code); i++) {   // se parcurge sirul code
        Character* element = findChar(code[i]);     // se cauta caracterul de la pozitia i din code
        if(element != NULL) {                       // daca caracterul s-a mai gasit anterior se scade contorizarea lui
            element->cnt--;
        }
    }
}

//functia generateString genereasa un sir aleatoriu de lungime length

void generateString(char* string) {
    for(long long i = 0; i < length; i++) {
        int max = 255;
        int min = 0;
        int r = rand() % (max - min) + min;
        char ch = (char)r;
        if(ch >= 'A' && ch <= 'Z' || ch >= 'a' && ch <= 'z') {
            string[i] = ch;
        } else {
            i--;
        }
    }
}

// functia getDistance calculeaza distanta dintre sirul rule si code, timp in care corecteaza sirul code
// distanta reprezinta numarul de operatii de adaugare, stergere sau interschimbare intre doua caractere
// care se aplica pe sirul code pentru a ajunge identic cu sirul rule


int getDistance(char* rule, char* code) {
    createFrequencyArray(rule, code);

    long long distance = 0; // variabila in care se va contoriza distanta dintre siruri

    long long i = 0;
    while(i < strlen(rule) || i < strlen(code)) {               // se parcurge pana la finalul celui mai lung sir
        if(code[i] != rule[i]) {                     // daca caracterul de la pozitia i difera in cele doua sruri
            Character* element1 = findChar(rule[i]);           // cautam caracterul de la pozitia i din sirul rule
            Character* element2 = findChar(code[i]);           // cautam caracterul de la pozitia i din sirul code
            if(element1 != NULL && element1->cnt > 0) {        // daca caracterul de la poz i din sirul rule exista in lista de aparitii
                for(long long j = strlen(code); j >= i; j--) { // si cnt este pozitiv, adica se afla de mai multe ori in rule decat in code
                    code[j + 1] = code[j];                     // se muta toate elementele de la dreapta elementului
                }                                              // la dreapta cu o pozitie pentru face loc sa se insereze caracterul potrivit
                element1->cnt--;                               // atunci se scade contorul caracterului
                code[i] = rule[i];                             // se copiaza caracterul
                distance++;                                    // si creste distanta
            } else if(element2 == NULL) {                      // daca un caracter din code nu se afla in lista de aparitii
                for(long long j = i; j < strlen(code); j++) {  // se muta toate caracterele de dupa acesta
                    code[j] = code[j + 1];                     // cu o pozitie la stanga astfel stergandu-l
                }
                distance++;                                    // distanta creste
            } else if(element2->cnt < 0){                      // daca avem nevoie de acel caracter dar este de prea
                for(long long j = i; j < strlen(code) - 1; j++) { // multe ori
                    code[j] = code[j + 1];                     // atunci se muta toate elementele de la acea pozitie
                }                                              // la stanga cu o pozitie
                code[strlen(code) - 1] = '\0';                 // se adauga la sfarsitul sirului NULL
                element2->cnt++;                               // se creste valoare contorului aferent caracterului
                distance++;                                    // creste distanta
            } else {                        // daca caracterul gasit in code nu trebuie sters sau adaugat creste i-ul
                i++;
            }
        } else {
            i++;                           // daca caracterele de la pozitia i din rule si code sunt egale creste i-ul
        }
    }

    i = 0;
    while(i < strlen(code)) {     // in acest while se face interschimbarea a doua caractere daca nu sunt pe pozotia
        if(code[i] != rule[i]) {  // corecta desi ele apar in code de cate ori trebuie
            long long j = i + 1;
            while(j < strlen(code)) { // se cauta caracterul cu care trebuie interschimbat
                if(rule[i] == code[j] && code[j] != rule[j]) {
                    char aux;
                    aux = code[i];
                    code[i] = code[j];
                    code[j] = aux;
                }
                j++;
            }
            distance++;         // distanta creste
        } else {
            i++;                // creste i-ul ca sa mearga mai departe in code
        }
    }

    freePointers();             // eliberez pointerii pe care i-am folosit

    return distance;            // returnez distanta
}
