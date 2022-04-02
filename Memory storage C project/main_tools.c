/*----------------------------------------------------------------------------------------
Guilherme Gonçalves Gutierrez de Lima ist199077
Este ficheiro terá todas as funções principais presentes em main.c, 
para facilitar a alteração do programa.
As descrições das funções utilizadas estão presentes em tools.c
----------------------------------------------------------------------------------------*/
#include "tools.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*  Esta função irá criar os caminhos e os respetivos subcaminhos
    e atribuir um valor, ou alterar caso já exista.
*/
link main_set(link caminhos){

    link t = NULL;
    char caminho[MAX_INPUT], valor[MAX_INPUT];

    read_caminho(caminho);
    read_valor(valor);
    caminhos = cria_caminho(caminhos,t,caminho, valor,1);
    return caminhos;
}

/*  Antes de terminar o programa deverá se apagar toda a 
    sua memória alocada, que devido a complicações do
    programa não foi possível. 
*/
void main_quit(link caminhos){

    if(caminhos != NULL)
        {
        /*delete_aux(caminhos);*/
        }
}

/*  Esta função irá imprimir todas as descrições dos comandos
    uma por linha e por ordem. 
*/
int main_help(){

    print_comandos();
    return EXIT_CODE;
}
/*  Esta função função irá imprimir todos os caminhos que tiverem
    um valor atribuído. Os caminhos serão imprimidos um por linha
    com o valor de seguida. 
*/
int main_print(link caminhos){

    percorrer_main(caminhos); 
    return EXIT_CODE;
}
/*  Esta funcão vai listar todos os componentes imediatos de um sub-caminho
    de um caminho recebido, por ordem alfabética.
    Caso nenhum caminho seja recebido iremos listar todos os caminhos da raiz.
    Para realizar a ordem alfabética os nomes dos componentes foram enviados 
    para um vetor de strings.
    Depois de realizar um bubble sort no vetor e imprimir as strings,
    a memória ocupada por estas strings será libertada.
*/
int main_list(link caminhos){

    char c;
    int i, l, n;
    char caminho[MAX_INPUT], *table[HASH_VALUE];

    if((c = getchar()) == '\n'){
        i = list_main(caminhos, table, 0);

    bubble_sort(table, i);
    for(l = 0; l < i; l++)
        printf("%s\n",table[l]);

    for(l = i; l < 0; l--)
        free(table[l]);
    }
    else
    {    
        read_caminho(caminho);
        n = num_componentes(caminho, 1);
        list_main_caminho(caminhos,table, caminho,1, n);
    }
    return EXIT_CODE;
}

/*  Esta função imprime o valor armazenado de um caminho recebido.
    Irá calcular o número de componentes do caminho para facilitar 
    a procura deste caminho.
*/
int main_find(link caminhos){
    int n;
    char caminho[MAX_INPUT];

    read_caminho(caminho);
    n = num_componentes(caminho, 1);
    find_main(caminhos,caminho,1,n); 

    return EXIT_CODE;
}
/*  Esta função procura o caminho com um valor recebido.
    Irá calcular o valor hash do valor para aumentar a eficiência
    do programa, e irá começar a procura. 
*/
int main_search(link caminhos){

    char valor[MAX_INPUT];
    int h;

    read_valor(valor);
    h = hash(valor,HASH_VALUE);
    search_main(caminhos,valor, h);
    return EXIT_CODE;
}
/*  Esta função apaga todos os caminhos de um sub-caminho.
    Serão calculados os componentes do caminho recebido para
    facilitar a procura do caminho desejado, similar ao método
    utilizado em find_main.
    No entanto não foi possível o bom-funcionamento desta função.
*/
int main_delete(link caminhos){

    char caminho[MAX_INPUT];
    int n;

    read_caminho(caminho);
    n = num_componentes(caminho, 1);
    delete_main(caminhos, caminho, 1, n);

    return EXIT_CODE;
}




