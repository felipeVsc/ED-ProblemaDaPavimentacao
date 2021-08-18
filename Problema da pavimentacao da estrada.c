/* O problema da pavimentação de estrada

    Tertuliano Gonçalves havia prometido casamento a Josefina das Graças. O evento deveria ser realizado, segundo ele, assim que acabasse o contrato de trabalho recém assinado com uma empresa encarregada de pavimentar toda a rede de estradas que ligava Santana do Caixa Prego (cidade onde morava Josefina) às cidades da região. O trabalho iria começar em Santana e prosseguir em continuidade, estada após estrada, terminando, segundo explicou Tertuliano, na própria Santa. A rede de estradas poderia ser representada pela matriz de adjacência que se segue, na qual a cidade de Santana é representada pelo número 1. 

*/

#include <stdio.h>
#include <stdlib.h>

#define False 0
#define True 1

#define VERIFIED_VERTEX 1 //já foi verificada a conexao
#define NOT_VERIFIED_VERTEX 0 // ainda nao foi descoberto ou verificado a conexao
#define END_OF_ARRANGE -1  // está em estado de pai e seus filhos ainda estao sendo verificados

typedef int bool;
typedef int WEIGHT_TYPE; //nesse caso os pesos sao bits(conexao ou ausencia de conexao); porem se a matriz for ponderada, o tipo pode mudar

/* Grafo matriz de adjacência com atributos n_vertex(num. de vertices), city_index (indice da cidade de santana) e matriz de adjacência matriz do tipo WEIGHT_TYPE. Lembrando que no atributo city_index deve-se subtrair 1 unidade na atribuição, pois para o usuario os indices iniciam em 1. */
typedef struct graph{
    int n_vertex;
    int city_index;
    WEIGHT_TYPE **matrix;
} Graph;

/*--- Funçoes da matriz de adjacencia ---*/

/* Na chamada de createGraph, deve-se definir a ordem da matriz (n_vertex) e o indice em que se encontra a cidade do problema(city_index - 1). */
Graph *createGraph(int n_vertex, int city_index){
    /* Cria matriz com n_vertex colunas e linhas */
    int i, j;
    Graph *graph = malloc(sizeof(Graph));

    graph->n_vertex = n_vertex;
    graph->city_index = city_index;
    graph->matrix = malloc(n_vertex * sizeof(WEIGHT_TYPE*));
    
    /* vetor de ponteiros de linhas contíguas */
    graph->matrix[0] = malloc(n_vertex * n_vertex * sizeof(WEIGHT_TYPE));

    for (i = 1; i < n_vertex; i++)
        graph->matrix[i] = graph->matrix[0] + i * n_vertex;

    
    for(i = 0; i < n_vertex; i++)
        for(j = 0; j < n_vertex; j++)
            graph->matrix[i][j] = 0;
    
    return graph;
}

/* Na chamada de CreateEdge deve-se subtrair um indice de origin e destiny, pq para o usuário, as cidades iniciam em 1 */
bool createEdge(Graph *graph, int origin, int destiny, WEIGHT_TYPE weight){

    /* Testes de parâmetro */

    if((destiny < 0) || (destiny >= graph->n_vertex))
        return False;
    
    if((origin < 0) || (origin >= graph->n_vertex))
        return False;    
    
    if(origin == destiny) // o grafo nao admite loop
        return False;

    if(graph->matrix[origin][destiny]){
        printf("Conexão já registrada previamente. ");
        return False;
    }   

    /* Fim dos testes */
          
    graph->matrix[origin][destiny] = weight;
    graph->matrix[destiny][origin] = weight;
    
    return True;    
}

bool removeEdge(Graph *graph, int origin, int destiny){
    /* Testes de parâmetro */

    if((destiny < 0) || (destiny >= graph->n_vertex))
        return False;
    
    if((origin < 0) || (origin >= graph->n_vertex))
        return False; 
    
    if(origin == destiny) // o grafo nao admite loop
        return False;
    
    if(!graph->matrix[origin][destiny]){
        printf("As estradas não possuem conexão. ");
        return False;
    }

    /* Fim dos testes */

    graph->matrix[origin][destiny] = 0;
    graph->matrix[destiny][origin] = 0;

    return True;
}

void printGraph(Graph *graph){
    int i, j;
    for(i = 0; i < graph->n_vertex; i++){
        for(j = 0; j < graph->n_vertex; j++){
            printf("%d ", graph->matrix[i][j]);
        }
        printf("\n");
    }    
}

bool cleanGraph(Graph *graph){
    free(graph); 
    //printf("%d\n", graph->n_vertex);
    return True;
}
/* ---- Fim das funções da matriz de adjacencia --- */


/*--- Depth-First Search ---*/

void printAnArrange(int size, int arrange[]){ //função de debug, apagar dps
    int i;

    printf("[");
    for(i = 0; i < size; i++){
        printf("%d,", arrange[i]);
    }


    printf("]\n");
}

int inPathIndex(Graph *graph, int path[], int vertex){
    int i;

    for(i = 0; i < graph->n_vertex; i++){
        if(path[i] == vertex){
           break;
        }
    }
    return i;
}

bool inPath(Graph *graph, int path[], int vertex){
    int i;

    for(i = 0; i < graph->n_vertex; i++){
        if(path[i] == vertex){
            return True;
        }
    }
    return False;
}

int walkThroughPath(Graph *graph, int path[]){
    int i;
    for (i = 0; i < graph->n_vertex; i++){
        if(path[i] == END_OF_ARRANGE){
           break;
        }
    }
    return i;
}

void DFS(Graph *graph, int path[], int *verification_status, int currentVertex, int initialIndex){
    int i, pathindex;

    if(!inPath(graph, path, currentVertex)){
        pathindex = walkThroughPath(graph, path);
        path[pathindex] = currentVertex;
    }
    else{        
        pathindex = inPathIndex(graph, path, currentVertex);
    } 


    for(i = initialIndex; i < graph->n_vertex; i++){
        if((graph->matrix[currentVertex][i] == 1) && (!inPath(graph, path, i))){
            if(verification_status[i] != VERIFIED_VERTEX){
                verification_status[i] = VERIFIED_VERTEX;
                return DFS(graph, path, verification_status, i, 0);
            }           
        }
    }   

    /*//debug
    printAnArrange(graph->n_vertex, verification_status);
    printAnArrange(graph->n_vertex, path);*/

    if(currentVertex == graph->city_index){
        /* a linha da cidade foi toda varrida e nao ha mais conexoes diretas. */
        return;
    }

    /* verificar se todos os vertices estao verificados em verification_status */
    if(walkThroughPath(graph, path)){
        i = currentVertex;
        currentVertex = path[pathindex-1];

        //printf("%d %d\n", currentVertex, i);

        path[pathindex] = END_OF_ARRANGE;

        DFS(graph, path, verification_status, currentVertex, i+1);
    }
    
}

bool defineSearch(Graph *graph){
    int i;
    int verification_status[graph->n_vertex];
    int path[graph->n_vertex]; 

    /* Path sera uma pilha que armazena o caminho percorrido naquele nó, e 
        a utiliza para voltar aos nós anteriores */

    for (i = 0; i < graph->n_vertex; i++){
        verification_status[i] = NOT_VERIFIED_VERTEX;
        path[i] = END_OF_ARRANGE; //lista vazia
    }  


    DFS(graph, path, verification_status, graph->city_index, 0); //a busca inicia pelo nó da cidade

    for(i = 0; i < graph->n_vertex; i++){
        if(verification_status[i] == 0 && i != graph->city_index){
            printf("    Não há caminhos de todas as cidades até Santana(%d).\n", graph->city_index + 1);
            return False;
        }
    }

    printf("    Há caminhos de todas as cidades até Santana(%d).\n", graph->city_index + 1);
    return True;
}

/*--- Fim da Depth-First Search ---*/


/*--- Funções do problema ---*/

void pause(void){
	printf("Pressione Enter para continuar... ");
	char pause[300];
	fgets(pause, 300, stdin);
}

int countEmptyConnections(Graph *graph){
    int i, j, empty = 0;

    for(i = 0; i < graph->n_vertex; i++){
        for (j = 0; j < graph->n_vertex; j++){
            if((i != j) && (!graph->matrix[i][j])){
                empty += 1;
            }
        }
    }
    return (empty/2);
}

void menu(Graph *graph){
    char operation;
    int verificado = 0;

    printf(" ------------------------------------------\n");
    printf("|        Pavimentação das estradas         |\n");
    printf("|------------------------------------------|\n");
    printf("|                                          |\n");
    printf("|           Escolha uma opção:             |\n");
    printf("|                                          |\n");
    printf("|        1 Inicializar uma rede            |\n");
    printf("|        2 Registrar estrada(s)            |\n");
    printf("|        3 Deletar uma estrada             |\n");
    printf("|        4 Mostrar rede                    |\n"); 
    printf("|        5 Limpar rede                     |\n");
    printf("|        6 Sair do programa                |\n");
    printf("|                                          |\n");
    printf(" ------------------------------------------\n");

    operation = getchar();
    getchar();

    switch (operation)
    {
        case 49:
            if(graph->n_vertex)
                printf("A rede ja existe.\n");

            else{
                int n_vertex = 0, city_index = 0;

                while(!verificado){
                    printf("Digite a quantidade de cidades: ");
                    scanf("%d", &n_vertex);

                    if(n_vertex <= 1){
                        printf("Valor inválido.\n");                        
                    }                        
                    else{
                        verificado = 1;
                    }
                    
                }

                verificado = 0;

                while(!verificado){
                    printf("Digite o número(indice) da cidade Santana do Caixa Prego: ");
                    scanf("%d", &city_index);

                    if(city_index <= 0 || city_index > n_vertex){
                        printf("Valor inválido.\n");                        
                    }                        
                    else{
                        verificado = 1;
                    }
                    
                }             

                         
                getchar();

                graph = createGraph(n_vertex, city_index-1);

                if(graph->n_vertex)
                    printf("Rede criada!\n");                     
            }
            break;
        
        case 50:  
            if(!graph->n_vertex)
                printf("Você precisa inicializar uma rede antes!\n");

            else{
                int n, i = 1;
                int c1, c2;
                verificado = 0;

                while(!verificado){
                    printf("Digite -1 para cancelar a operação.\n");
                    printf("Quantas estradas você quer registrar?: ");                
                    scanf("%d", &n);
                    getchar();

                    if (n >= countEmptyConnections(graph)){
                        printf("Essa quantidade excede o número de espaços vazios.\n");
                    }
                    else if(n == -1){
                        printf("Operação cancelada.\n");
                        verificado = 1;
                        break;
                    }
                    else if(n <= 0){
                        printf("Valor inválido.\n");
                    }                    
                    else{                        
                        verificado = 1;
                        printf("\nDigite '-1 -1' para cancelar a operação.\n");
                    }
                }                                      
                while(i <= n){
                    printf("Digite os números das duas cidades que a %dª estrada conecta no formato C1 C2: ", i);     
                    scanf("%d%d", &c1, &c2); 
                    printf("%d %d\n", c1, c2);                               
                    getchar();

                    if(c1 != -1){
                        if(!createEdge(graph, c1-1, c2-1, 1)) 
                            printf("Valores inválidos.\n");
                        else {
                            printf("Estrada registrada com sucesso!\n\n");
                            i++;
                        }                       
                            
                    }
                    else{
                        printf("Operação cancelada.\n");
                        break; 
                    }
                         
                }                
            }
            break;
        
        case 51:
            if(!graph->n_vertex)
                printf("Você precisa inicializar uma rede antes!\n");

            else{
                int c1, c2;
                verificado = 0;
                printf("Digite '-1 -1' para cancelar a operação a qualquer momento.\n");
                while(!verificado){                    
                    printf("Digite as cidades cuja estrada será removida no formato C1 C2: ");
                    scanf("%d%d", &c1, &c2);
                    printf("%d %d\n", c1, c2);   
                    getchar();

                    if(c1 != -1){
                        if(!removeEdge(graph, c1-1, c2-1)){
                            printf("Valores inválidos.\n");
                        }
                        else{
                            printf("Conexão removida.\n");
                            verificado = 1;
                        }
                    }
                    else{
                        printf("Operação cancelada.\n");                        
                        break;
                    }
                    
                }
            }
            break;
        
        case 52:
            if(graph->n_vertex){
                printGraph(graph);
                printf("\nCom os dados inseridos até então...\n");
                defineSearch(graph);
            }
            else{
                printf("Rede não criada.\n");
            }           
            break;
        
        case 53:  
            if(!graph->n_vertex)
                printf("Não há rede criada para limpar.\n");

            else{
                printf("Deseja mesmo limpar a rede de estradas criada? Esta ação é irreversível. Y/N\n");
                operation = getchar();
                getchar();
                if(operation == 121 || operation == 89){                    
                    cleanGraph(graph); 
                    printf("A rede foi limpa.\n");
                }                  
                    
                else if(operation == 110 || operation == 78)
                    break;
                else
                    printf("Operação inválida.\n");
            }            
            break;

        case 54:
            return;

        default:
            printf("Operação inválida.\n");           
    }

    pause();
    system("clear||cls");
    menu(graph);    
}
/* Fim das funções do problema */

int main(){
    Graph *graph;
    graph->n_vertex = 0;
    system("clear||cls");
    menu(graph);
    return 0;
}