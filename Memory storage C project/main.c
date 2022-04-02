/*----------------------------------------------------------------------------------------
Guilherme Gonçalves Gutierrez de Lima ist199077
O objetivo do projeto é ter um sistema de armazenamento hierárquico em memória,
que contém caminhos com um valor associado. 
----------------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tools.h"
#include "language_pack_en.h"

int main(){

    link caminhos = NULL;
    char comando[MAX_INPUT];
    while(scanf("%s", comando) == 1){

        /*COMANDO HELP- Imprime os comandos disponíveis:
        Formato de entrada: help
        Formato de saída: Imprime a lista de comandos disponíveis,
        um por linha, com <comando>: <descrição>.
        */
        if(strcmp(comando, HELP) == 0)
        {
            main_help();
        }
        /*COMANDO QUIT - Termina o programa:
        Formato de entrada: quit
        Formato de saída: NADA 
        */
        if(strcmp(comando, QUIT) == 0)
        {   
            main_quit(caminhos);
            return EXIT_CODE; 
        }   
        /* COMANDO SET - Adiciona ou modifica o valor a armazenar:
        Formato de entrada: set <caminho> <valor>
        Formato de saída: NADA 
        */
        else if(strcmp(comando, SET) == 0)
        {
            caminhos = main_set(caminhos);
        }
        /*PRINT - Imprime todos os caminhos e valores:
        Formato de entrada: print
        Formato de saída: Imprime Apenas os caminhos com
        valor associado e os seus valores, em profundidade e pela ordem de criação.
        */
        else if(strcmp(comando, PRINT) == 0)
        {
            main_print(caminhos); 
        }
        /*FIND- Imprime o valor armazenado de um caminho:
        Formato de entrada: find <caminho>
        Formato de saída: Imprime o valor associado ao <caminho>.
        Erros:
        not found: no caso de não existir o caminho.
        no data: no caso de o caminho não ter valor associado.
        */        
        else if(strcmp(comando, FIND) == 0)
        {
            main_find(caminhos);
        }
        /*LIST - Lista todos os componentes imediatos de um sub-caminho:
        Formato de entrada: list <caminho>
        Formato de saída: Imprime o diretório de um <caminho> por ordem alfabética. 
        Se o comando for invocado sem argumentos, lista os componentes da raiz.
        Erros:
        not found: no caso de não existir o caminho.
        */
        else if(strcmp(comando, LIST) == 0)
        {        
            main_list(caminhos);
        }
        /*SEARCH - Procura o caminho dado um valor:
        Formato de entrada: search <valor>
        Formato de saída: Imprime o primeiro caminho, pela ordem de criação,
        encontrado que contém o <valor> indicado.
        Erros:
        not found: no caso de não existir nenhum caminho com o valor indicado.
        */
        else if(strcmp(comando, SEARCH) == 0)
        {
            main_search(caminhos);
        }
        /*DELETE - Apaga todos os caminhos de um sub-caminho:
        Formato de entrada: delete <caminho>
        Formato de saída: Apaga o <caminho> indicado e todos os seus sub-caminhos. 
        Se for invocado sem argumentos apaga todos os caminhos armazenados.
        Erros:
        not found no caso de não existir o caminho.
        */
        else if(strcmp(comando, DELETE) == 0)
        {
            main_delete(caminhos);
        }
    }
    return EXIT_CODE;
}











