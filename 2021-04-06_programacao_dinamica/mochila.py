# coding=utf-8
# Solução com Programação Dinâmica para o problema da Mochila 0-1
# Devolve o valor máximo que pode ser colocado na mochila com capacidade C

def Mochila(C, peso, valor, n, S):    
    # Constroi a tabela S[][] com os valores ótimos para os subproblemas
    for i in range(1, n+1): 
        for c in range(1, C+1): 
            if peso[i-1] <= c: 
                S[i][c] = max(valor[i-1] + S[i-1][c-peso[i-1]],  S[i-1][c]) 
            else: 
                S[i][c] = S[i-1][c] 
  
    return S[n][C]
  
  
# Definição do Problema
valor = [10,25,39,10,86,50,43,20,32] # valores dos itens 
peso = [5,12,2,6,7,7,3,9,5]  # pesos dos itens
C = 23 # capacidade da mochila
n = len(valor) 

# matriz com os valores ótimos dos subproblemas
S = [[0 for x in range(C+1)] for x in range(n+1)] 

print(Mochila(C, peso, valor, n, S)) # calcula e imprime o valor da solução ótima
for line in S:
  for item in line:
    print("%4d" % (item), end='')
  print("")
  
# Fonte: https://www.geeksforgeeks.org/0-1-knapsack-problem-dp-10/

