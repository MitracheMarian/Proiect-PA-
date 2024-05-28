from timeit import default_timer as timer
from functions import generateString, fixTheString

rule = "func(myFunction)"

# functia ce se apeleaza daca este aleasa varianta de generare
def generateVariant():
  n = input("Ce lungime sa aiba sirul generat?\n")
  code = generateString(n)
  start = timer() 
  fixTheString(rule, code)
  end = timer()
  print(str(round(end - start, 4)) + " secunde")

# functia ce se apeleaza daca este aleasa varianta de citire
def readVariant():
  code = input("Introduceti sirul:\n")
  start = timer() 
  fixTheString(rule, code)
  end = timer()
  print(str(round(end - start, 4)) + " secunde")

# un dictionar ce contine functile ce trebuie apelate dupa alegerea variantei de catre utilizator
variants = {
  "1": generateVariant,
  "2": readVariant
}

if __name__ == "__main__":
  print("Ce varianta dorti sa alegeti?")
  print("1. Generarea sirului aleatoriu")
  print("2. Introducerea sirului de la tastatura")
  
  answer = input()
  # se apeleaza functia potrivita in functie de varianta aleasa
  variants[answer]() if answer in variants else print("Trebuie introdus un numar dintre cele de mai sus!")
  
  # to stop the program from closing imediately after finishing
  input("\nPress any key to close the program...")