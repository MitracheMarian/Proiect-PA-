import random
from timeit import default_timer as timer

chars = {}

# functie de generare a sirului code
def generateString(n):
  characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ()[]{}_-"
  string = ""
  for i in range(int(n)):
    string += random.choice(characters)
  return string

# creeaza un dictionar in care cheia reprezinta literam, iar valoarea reprezinta numarul de aparitii
def createFrequencyArray(rule, code):
  # pentru caracterele din sirul rule se creste valoarea lui in dictionar cu 1
  for ch in rule:
    if ch in chars:
      chars[ch] += 1
    else: chars[ch] = 1
  
  # pentru caracterele din sirul code se scade valoarea lui in dictionar cu 1
  for ch in code:
    if ch in chars:
      chars[ch] -= 1
    else: chars[ch] = -1
  # se urmareste ca la final, literele sa aiba valoarea 0 in dictionar, adica sa apara de acelasi numar de ori in ambele siruri

def getDistance(rule, code):
  createFrequencyArray(rule, code)

  # dictionarul in care o sa transform sirul cod pentru a face stergerea unui caracter in O(1)
  codeDict = {}

  distance = 0

  # transform sirul rule intr-o lista
  rule = list(rule)
  # transform sirul code intr-un dictionar
  for i, val in enumerate(code):
    codeDict[i] = val

  # se sterg caracterele ce nu ar trebui sa se afle in sirul code
  i = 0
  while i < len(code) or i < len(rule):
    ruleCh = rule[i] if i < len(rule) else None
    codeCh = code[i] if i in codeDict else None

    if codeCh != ruleCh:
      if codeCh and chars[codeCh] < 0:
        codeDict.pop(i)
        distance += 1
        chars[codeCh] += 1
      else:
        i += 1
    else: 
      i += 1

  # transform dictionarul code intr-un vector pentru a putea insera caracterele la pozitia potrivita
  code = []
  for key in codeDict:
    code.append(codeDict[key])

  # inserez caracterele ce lipsesc din code
  i = 0
  while i < len(code) or i < len(rule):
    ruleCh = rule[i] if i < len(rule) else None
    codeCh = code[i] if i < len(code) else None

    if codeCh != ruleCh:
      if ruleCh and chars[ruleCh] > 0:
        code = code[:i] + [ruleCh] + code[i:]
        chars[ruleCh] -= 1
        distance += 1
      else:
        i += 1
    else:
      i += 1

  # interschimbam caracterele din code care nu sunt la locul lor
  i = 0
  while i < len(code):
    if code[i] != rule[i]:
      j = i + 1
      while j < len(code):
        if rule[i] == code[j] and code[j] != rule[j]:
          code[i], code[j] = code[j], code[i]
          break
        j += 1
      distance += 1
    else:
      i += 1
  
  # transform vectorii inapoi in siruri de caractere dupa care returnez sirurile si distanta dintre ele
  code = "".join(code)
  rule = "".join(rule)

  return distance, code, rule

def fixTheString(rule, code):
  print()
  print("Before:")
  print("rule: " + rule)
  print("code: " + code)

  distance, code, rule = getDistance(rule, code)

  print()
  print("After:")
  print("rule: " + rule)
  print("code: " + code)
  print("distance = " + str(distance))

