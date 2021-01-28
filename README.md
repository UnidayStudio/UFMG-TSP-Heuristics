# Problema do Caixeiro Viajante

## Introdu��o
Esse trabalho consiste em apresentar uma heur�stica construtiva para resolver o
problema cl�ssico do Caixeiro Viajante, ou Traveling Salesman Problem (TSP). Esse
problema consiste em: dado uma lista de cidades �E� e suas coordenadas (ou
dist�ncias entre elas), calcular qual a menor rota que o caixeiro viajante pode percorrer,
come�ando de uma cidade X e terminando no mesmo local, passando apenas uma vez
em cada cidade, para visitar todas as cidades da lista �E�.
Esse � um problema NP-Dif�cil extremamente conhecido e popular no meio da
computa��o, exatamente por sua aplicabilidade pr�tica e pela vasta op��o de
heur�sticas para resolv�-lo.

## Heur�stica: Nearest Neighbor
A heur�stica construtiva escolhida para essa implementa��o foi o Nearest Neighbor, um
algoritmo guloso que, iniciando em uma cidade X aleat�ria, sempre vai at� a pr�xima
cidade Y mais pr�xima n�o visitada, at� que todas sejam percorridas. Ent�o ele
finalmente volta para a cidade inicial X e termina o trajeto.
A motiva��o por tr�s da escolha deste algoritmo em quest�o foi sua simplicidade e o
fato de que geralmente � um caso base, um ponto de partida para pensar em
heur�sticas melhores. A literatura utilizada para compreender tais quest�es foi o livro
Local Search in Combinatorial Optimization, cap�tulo 8 (Arts and Lenstra J. K., John
Wiley and Suns, 1997).

## Implementa��o
A linguagem de programa��o utilizada foi o C++14. **Nota:** O c�digo utiliza a biblioteca
nativa std::experimental::filesystem para lidar com os arquivos de entrada. A partir
do C++17, ela n�o � mais experimental e deve ser usada como �std::filesystem�
apenas. O c�digo tamb�m est� dispon�vel no github atrav�s desse link:
https://github.com/UnidayStudio/UFMG-TSP-Heuristics

**O algoritmo funciona da seguinte forma:**

Ele ir� percorrer todas as N cidades da entrada, come�ando da primeira (poderia ser
qualquer cidade aleat�ria, mas para manter os resultados da execu��o determin�sticos,
foi fixado na primeira) e para cada uma das cidades, ele ir� encontrar a mais pr�xima
n�o visitada (percorrendo, verificando se j� foi visitada e testando as dist�ncias de
todas as N-1 outras cidades).

Esta implementa��o escolhida possui complexidade O(n�). (n=quantidade de cidades).

# Problemas
Apesar de simples e eficiente em termos de performance comparado com outras
heur�sticas, essa abordagem possui alguns problemas. Por exemplo, considere o
seguinte mapa de cidades:
![Img1](https://media.discordapp.net/attachments/760282757334695936/804358927813705748/unknown.png)

Considere que o viajante come�a na cidade A. Uma solu��o �tima seria passar pelas
cidades, na ordem: A, B, C, D, E, X, F, G, A. Conforme na imagem abaixo:
![Img2](https://media.discordapp.net/attachments/760282757334695936/804358979261038593/unknown.png)

Entretanto, por ser um algoritmo guloso que sempre considera a cidade mais pr�xima,
ao chegar em E, ele ir� identificar F primeiro e seguir� por esse caminho. Ap�s isso ele
s� ir� considerar X novamente ao terminar todas as outras cidades n�o visitadas, ou
seja, depois de passar em G:
![Img3](https://media.discordapp.net/attachments/760282757334695936/804359009145585674/unknown.png)

Perceba que tal decis�o acarretar� em um aumento consider�vel na dist�ncia
percorrida pelo viajante.

## Resultados
Cada uma das entradas e seus respectivos algoritmos de dist�ncias foram executadas
mil vezes para obter a m�dia de tempo de execu��o. J� que o algoritmo usa uma
cidade inicial fixa (sempre a primeira), n�o houve diferen�as no resultados da dist�ncia
percorrida.
Abaixo a tabela com os resultados obtidos:

![Table1](https://media.discordapp.net/attachments/760282757334695936/804360609058914345/unknown.png)


## Conclus�o
A heur�stica Nearest Neighbor para o TSP, apenas de gulosa, apresentou um tempo de
execu��o consideravelmente baixo e uma m�dia de gap entre o resultado �timo de
cerca de 24%, com gap m�nimo encontrado de 5.37% e m�ximo pr�ximo de 50%. Ou
seja, em m�dia o caixeiro viajante percorrer� um caminho 24% maior do que o �timo.

Tal heur�stica pode ser utilizada em ocasi�es reais onde a garantia de um resultado
�timo n�o � essencial, como no caminho a ser percorrido por um agente de intelig�ncia
artificial em um Jogo (video game) de mundo aberto.

## Refer�ncias
- **Local Search in Combinatorial Optimization**. Arts and Lenstra J. K., John
Wiley and Suns, 1997. (Cap�tulo 8)