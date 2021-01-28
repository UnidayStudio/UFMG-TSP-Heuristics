# Problema do Caixeiro Viajante

## Introdução
Esse trabalho consiste em apresentar uma heurística construtiva para resolver o
problema clássico do Caixeiro Viajante, ou Traveling Salesman Problem (TSP). Esse
problema consiste em: dado uma lista de cidades “E” e suas coordenadas (ou
distâncias entre elas), calcular qual a menor rota que o caixeiro viajante pode percorrer,
começando de uma cidade X e terminando no mesmo local, passando apenas uma vez
em cada cidade, para visitar todas as cidades da lista “E”.
Esse é um problema NP-Difícil extremamente conhecido e popular no meio da
computação, exatamente por sua aplicabilidade prática e pela vasta opção de
heurísticas para resolvê-lo.

## Heurística: Nearest Neighbor
A heurística construtiva escolhida para essa implementação foi o Nearest Neighbor, um
algoritmo guloso que, iniciando em uma cidade X aleatória, sempre vai até a próxima
cidade Y mais próxima não visitada, até que todas sejam percorridas. Então ele
finalmente volta para a cidade inicial X e termina o trajeto.
A motivação por trás da escolha deste algoritmo em questão foi sua simplicidade e o
fato de que geralmente é um caso base, um ponto de partida para pensar em
heurísticas melhores. A literatura utilizada para compreender tais questões foi o livro
Local Search in Combinatorial Optimization, capítulo 8 (Arts and Lenstra J. K., John
Wiley and Suns, 1997).

## Implementação
A linguagem de programação utilizada foi o C++14. **Nota:** O código utiliza a biblioteca
nativa std::experimental::filesystem para lidar com os arquivos de entrada. A partir
do C++17, ela não é mais experimental e deve ser usada como “std::filesystem”
apenas. O código também está disponível no github através desse link:
https://github.com/UnidayStudio/UFMG-TSP-Heuristics

**O algoritmo funciona da seguinte forma:**

Ele irá percorrer todas as N cidades da entrada, começando da primeira (poderia ser
qualquer cidade aleatória, mas para manter os resultados da execução determinísticos,
foi fixado na primeira) e para cada uma das cidades, ele irá encontrar a mais próxima
não visitada (percorrendo, verificando se já foi visitada e testando as distâncias de
todas as N-1 outras cidades).

Esta implementação escolhida possui complexidade O(n²). (n=quantidade de cidades).

# Problemas
Apesar de simples e eficiente em termos de performance comparado com outras
heurísticas, essa abordagem possui alguns problemas. Por exemplo, considere o
seguinte mapa de cidades:
![Img1](https://media.discordapp.net/attachments/760282757334695936/804358927813705748/unknown.png)

Considere que o viajante começa na cidade A. Uma solução ótima seria passar pelas
cidades, na ordem: A, B, C, D, E, X, F, G, A. Conforme na imagem abaixo:
![Img2](https://media.discordapp.net/attachments/760282757334695936/804358979261038593/unknown.png)

Entretanto, por ser um algoritmo guloso que sempre considera a cidade mais próxima,
ao chegar em E, ele irá identificar F primeiro e seguirá por esse caminho. Após isso ele
só irá considerar X novamente ao terminar todas as outras cidades não visitadas, ou
seja, depois de passar em G:
![Img3](https://media.discordapp.net/attachments/760282757334695936/804359009145585674/unknown.png)

Perceba que tal decisão acarretará em um aumento considerável na distância
percorrida pelo viajante.

## Resultados
Cada uma das entradas e seus respectivos algoritmos de distâncias foram executadas
mil vezes para obter a média de tempo de execução. Já que o algoritmo usa uma
cidade inicial fixa (sempre a primeira), não houve diferenças no resultados da distância
percorrida.
Abaixo a tabela com os resultados obtidos:

![Table1](https://media.discordapp.net/attachments/760282757334695936/804360609058914345/unknown.png)


## Conclusão
A heurística Nearest Neighbor para o TSP, apenas de gulosa, apresentou um tempo de
execução consideravelmente baixo e uma média de gap entre o resultado ótimo de
cerca de 24%, com gap mínimo encontrado de 5.37% e máximo próximo de 50%. Ou
seja, em média o caixeiro viajante percorrerá um caminho 24% maior do que o ótimo.

Tal heurística pode ser utilizada em ocasiões reais onde a garantia de um resultado
ótimo não é essencial, como no caminho a ser percorrido por um agente de inteligência
artificial em um Jogo (video game) de mundo aberto.

## Referências
- **Local Search in Combinatorial Optimization**. Arts and Lenstra J. K., John
Wiley and Suns, 1997. (Capítulo 8)