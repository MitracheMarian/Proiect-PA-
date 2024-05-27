# Proiect PA

## Descriere

Aceasta este o aplicație care corectează un șir de caractere generat aleatoriu sau introdus de utilizator pentru a se potrivi cu o regulă dată.

## Structura Proiectului

- `main.c`: Conține funcția principală care rulează aplicația.
- `func.c`: Conține implementarea funcțiilor necesare pentru manipularea și corectarea șirurilor.
- `func.h`: Header-ul care declară funcțiile și structurile de date utilizate.
- `Makefile`: Fișierul Makefile pentru automatizarea procesului de compilare.
- `README.md`: Acest fișier, care conține instrucțiuni de compilare și utilizare.

## Cerințe

Pentru a compila și rula acest proiect, veți avea nevoie de:

- Un compilator C (de exemplu, GCC)
- `make` utilitarul pentru a folosi Makefile-ul (opțional, dar recomandat pentru ușurința compilării)

## Instrucțiuni de Compilare

### Utilizând Makefile

1. Asigurați-vă că aveți `make` instalat pe sistemul dvs. Puteți verifica acest lucru rulând:
   ```sh
   make --version

2. Pentru a compila codul, navigați la directorul proiectului și rulați:

make

3. Pentru a curăța fișierele generate (fișierele obiect și executabilul), rulați:
   
make clean

### Compilare Manuală

Dacă nu doriți să utilizați Makefile, puteți compila manual codul utilizând gcc:

Compilați func.c și main.c într-un fișier obiect:

gcc -c func.c -o func.o
gcc -c main.c -o main.o

Linkuiți fișierele obiect pentru a crea executabilul:

gcc func.o main.o -o my_program

## Utilizare

După compilare, puteți rula programul executabil my_program:

./my_program

Programul vă va cere să alegeți una dintre cele două opțiuni:

Generarea unui șir aleatoriu
Introducerea unui șir de la tastatură

Urmați instrucțiunile afișate pentru a introduce lungimea șirului sau șirul dorit.

## Exemplar de Utilizare

Ce varianta dorti sa alegeti?
1. Generarea sirului aleatoriu
2. Introducerea sirului de la tastatura
1
Ce lungime sa aiba sirul generat?
10
Sirul inainte de corectare:
gHf4JxK2Ls

Distanta dintre cele doua siruri este: 8

Sirul dupa corectare:
func(myFunctio)

