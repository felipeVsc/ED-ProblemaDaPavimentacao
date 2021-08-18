# O problema da pavimentação de estrada

## Projeto AB1 - Estrutura de Dados

### Grupo: Emily Brito de Oliveira e Felipe Ferreira Vasconcelos

**Descrição do problema**

*Tertuliano Gonçalves havia prometido casamento a Josefina das Graças. O evento deveria ser realizado, segundo ele, assim que acabasse o contrato de trabalho recém assinado com uma empresa encarregada de pavimentar toda a rede de estradas que ligava Santana do Caixa Prego (cidade onde morava Josefina)  às cidades da região. O trabalho iria começar em Santana e prosseguir em continuidade, estada após estrada, terminando, segundo explicou Tertuliano, na própria Santa. A rede de estradas poderia ser representada pela matriz de adjacência que se segue, na qual a cidade de Santana é representada pelo número 1.*

![image-20210818182010653](C:\Users\emily\AppData\Roaming\Typora\typora-user-images\image-20210818182010653.png)

1. ***Você que leu esta estória acha que Tertuliano estava sendo sincero com Josefina? Por quê?***

   Podemos responder essa questão fazendo um mapeamento das estradas de todas as cidades e verificar se há um caminho entre elas e Santana.

   | Cidade | Caminho até Santana                                       |
   | ------ | --------------------------------------------------------- |
   | **1**  | -                                                         |
   | **2**  | 2 ↔ 1                                                     |
   | **3**  | 3 ↔ 1                                                     |
   | **4**  | 4 ↔ 2 ↔ 1                                                 |
   | **5**  | 5 ↔ 1                                                     |
   | **6**  | 6 ↔ 3 ↔ 1                                                 |
   | **7**  | 7 ↔ 4 ↔ 2 ↔ 1 *ou*  <br/>7 ↔ 5 ↔ 1 *(caminho mais curto)* |
   | **8**  | 8 ↔ 5 ↔ 1                                                 |
   | **9**  | 9 ↔ 5 ↔ 1                                                 |
   | **10** | 10 ↔ 4 ↔ 2 ↔ 1                                            |

    Logo, concluímos que Tertuliano não estava sendo sincero, visto que havia uma maneira de as pessoas de todas as cidades da região chegarem à Santana do Caixa Prego para o casamento.

2. ***E se o itinerário 1-5-9-10 estivesse a cargo de outra empresa, estaria ele sendo sincero?***

   Nesse caso, refaremos a tabela acima, porém removendo as ligações entre as cidades 5-9-10 e as outras.

   | Cidade | Caminho até Santana        |
   | ------ | -------------------------- |
   | **1**  | -                          |
   | **2**  | 2 ↔ 1                      |
   | **3**  | 3 ↔ 1                      |
   | **4**  | 4 ↔ 2 ↔ 1                  |
   | **5**  | *À cargo de outra empresa* |
   | **6**  | 6 ↔ 3 ↔ 1                  |
   | **7**  | 7 ↔ 4 ↔ 2 ↔ 1              |
   | **8**  | 8 ↔ 6 ↔ 3 ↔ 1              |
   | **9**  | *À cargo de outra empresa* |
   | **10** | *À cargo de outra empresa* |

   Ainda existiram formas de chegar à Santana utilizando outros caminhos. Porém poderiam ainda não haver caminhos das cidades 5, 9, 10.

**Implementação do problema**

O problema implementado na linguagem C, resolve este problema através da estrutura matriz de adjacência. Nesse caso específico, a conexão entre as cidades é representada na matriz de forma binária, 1 para a existência de uma estrada (ou aresta) entre as duas cidades (vértices) da linha e coluna, ou 0 para a não existência.

O fluxo da execução do algoritmo inicia obrigatoriamente pela opção 1 do menu, onde o usuário deve inicializar uma rede de estradas (no caso, a matriz), informando a quantidade de cidades adjacentes à Santana, incluindo a própria Santana, dizendo, em seguida, qual seu índice na matriz.

Em seguida, o usuário deve informar as conexões/estradas existentes entre as cidades na opção 2. Esse registro pode ser feito à qualquer momento durante a execução do programa. E, caso registre algo equivocadamente, pode removê-la na opção 3.

É possível checar a matriz na opção 4, verificando as arestas entre os nós (representadas pelo número 1). Nessa opção também é exibido o resultado da busca no grafo. Foi implementada a busca em profundidade para verificar os caminhos existentes entre Santana e as outras cidades. A busca inicia no índice de Santana e vai percorrendo suas conexões, nó por nó, até que chegue ao final. Em seguida, realiza um backtracking até que não aja mais nós não descobertos para serem explorados. Caso, ao final da busca, algum nó não tenha sido descoberto, então sabemos que não existem caminhos  de Santana até ele, e, portanto, que Tertuliano Gonçalves estava sendo verdadeiro com Josefina das Graças.

Por fim, as opções 5 e 6 possibilitam a limpeza da matriz e o fim da execução do programa, respectivamente.

