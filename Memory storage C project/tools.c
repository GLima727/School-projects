/*----------------------------------------------------------------------------------------
Guilherme Gonçalves Gutierrez de Lima ist199077
Este ficheiro terá todas as funções presentes em main_tools.c, 
para facilitar a alteração do programa.
É neste ficheiro onde estarão presentes as funções que representam o núcleo do programa.
----------------------------------------------------------------------------------------*/
#include "tools.h"
#include "language_pack_en.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*  Esta função irá verificar se um caminho recebido não
    foi capaz de ser criado, caso ele não tenha sido, 
    o programa irá imprimir uma mensagem de o programa estar
    sem memória e irá terminá-lo. 
*/
void check_memory_caminho(link test)
{
    if(test == NULL)
    {
    printf(NO_MEMORY);
    exit(EXIT_CODE);
    }
}
/*  Esta função irá verificar se um pointer de uma string recebida não
    foi capaz de ser criado, caso ele não tenha sido, 
    o programa irá imprimir uma mensagem de o programa estar
    sem memória e irá terminá-lo. 
*/
void check_memory_string(char *string)
{
    if(string == NULL)
    {
    printf(NO_MEMORY);
    exit(EXIT_CODE);
    }
}
/*  Esta função irá reservar memória para um novo caminho e para uma string recebida,
    irá também verificar se foi possível reservar esta memória.
    A função será responsável pela criação de todos os caminhos neste programa e os
    seus nomes respetivos. 
*/
link NEW(char *buffer)
{
    link x = (link)malloc(sizeof(struct caminho)); 
    check_memory_caminho(x);
                                                
    x->nome =(char *)malloc(sizeof(char) * (strlen(buffer) + 1)); 
    check_memory_string(x->nome);
    strcpy(x->nome, buffer);
    x->next = NULL;
    return x;
}
/*  Esta função irá reservar memória para um sub-caminho e para uma string recebida,
    irá também verificar se foi possível reservar esta memória.
    A função será responsável pela criação de todos os sub-caminhos neste programa e os
    seus nomes respetivos, e irá retornar o primeiro nó do sub-caminho criado. 
*/
link NEW_SUB(char *buffer)
{
    link x = (link)malloc(sizeof(struct caminho)); 
    check_memory_caminho(x);                                         
    x->nome =(char *)malloc(sizeof(char) * (strlen(buffer) + 1)); 
    check_memory_string(x->nome);
    strcpy(x->nome, buffer);
    x->subcaminho = NULL;
    return x;
}

/*  Esta função irá adicionar um valor a um caminho recebido,
    e irá alocar memória para essa string e verificar se isso é possível.
    Depois de atribuir o valor, irá também atribuir um valor hash 
    para servir de chave e aumentar a eficiência na procura desse mesmo valor.
*/
link Add_Valor(link head, char *buffer)
{                                                
    head->valor =(char *)malloc(sizeof(char) * (strlen(buffer) + 1)); 
    check_memory_string(head->valor);
    strcpy(head->valor, buffer);
    head->hash2 = hash(buffer, HASH_VALUE);
    return head;
}
/*  Esta função irá adicionar um diretório a um caminho recebido,
    e irá alocar memória para essa string e verificar se isso é possível.
*/
link Add_Diretorio(link head, char *buffer)
{                                                
    head->diretorio =(char *)malloc(sizeof(char) * (strlen(buffer) + 1));
    check_memory_string(head->diretorio);
    strcpy(head->diretorio, buffer);
    return head;
}
/*  Esta função irá adicionar um valor hash a um caminho recebido,
    de uma string recebida.
*/
link Add_Hash(link head, char *buffer)
{                                                
    head->hash = hash(buffer, HASH_VALUE);
    return head;
}
/* Esta funcão irá imprimir todos os nomes de uma lista recebida. */
void print(link head)
{
    link t;
    for (t = head; t != NULL; t = t->next)
        printf("%s\n", t->nome);
}

/*  Esta função irá inserir no final de uma lista um novo nó com uma
    string atribuída. 
*/
link insertEnd(link head, char *nome)
{
    link x;
    if (head == NULL)
        return NEW(nome);
    for (x = head; x->next != NULL; x = x->next) 
        ;
    x->next = NEW(nome); 
    return head;
}

/*  Esta função será uma versão de insertEnd que recebe
    o último elemento de uma lista para evitar percorrer a lista
    até o final, e irá devolver o nó criado. 
*/
link insertEnd2(link t, char *nome)
{
    t->next = NEW(nome); 
    return t->next;
}

/*  Esta função será similiar á função insertEnd, mas esta 
    irá percorrer os sub-caminhos de um caminho recebido e 
    inserir mais um sub-caminho no final.
*/
link insertEnd_Sub(link head, char *nome)
{
    link x;
    if (head == NULL)
        return NEW_SUB(nome);
    for (x = head; x->subcaminho != NULL; x = x->subcaminho) 
        ;
    x->subcaminho = NEW_SUB(nome); 
    return head;
}

/*  Esta função procura um caminho com o nome que recebe,
    caso não exista nenhum caminho assim, a função retorna NULL.
    Caso ao percorrer a lista encontre, irá devolver esse mesmo caminho. 
*/
link lookup(link head, char *nome)
{
    link t;
    int l = hash(nome, HASH_VALUE);
    for (t = head; t != NULL; t = t->next)
        if (l == hash(t->nome,HASH_VALUE))
            if(strcmp(t->nome, nome) == 0)
                return t;
            
    return NULL;
}

/*  Esta função irá realizar o mesmo que a função lookup, a grande diferença 
    é que caso não encontre um caminho com o nome recebido, irá devolver o
    último nó da lista recebida. 
*/
link lookup2(link head, char *nome)
{
    link t, prev;
    int l = hash(nome, HASH_VALUE);
    for (t = head; t != NULL;prev=t, t = t->next)
        if (l == t->hash)
            if(strcmp(t->nome, nome) == 0)
                return t;
            
    return prev;
}
/*  Esta função irá adicionar a um nó um diretório e um valor hash 
    relativo do seu nome. 
*/
link Add_Hash_Dir(link head, char diretorio[MAX_INPUT], char sub_nome[MAX_INPUT])
{
    head = Add_Hash(head,sub_nome);
    head = Add_Diretorio(head, diretorio);
    return head;
}

/*  Esta função irá libertar de um nó os seus componentes que estão
    a alocar memória, como o seu nome, valor e diretório. 
*/
void FREEnode(link t)
{
    free(t->nome);
    free(t->valor);
    free(t->diretorio);
    free(t);
}

/*-----------------------HELP---------------------------------*/
/*  Esta função irá imprimir todas as descrições dos comandos disponíveis. */
int print_comandos()
{
    printf(HELP_DESC);
    printf(QUIT_DESC);
    printf(SET_DESC);
    printf(PRINT_DESC);
    printf(FIND_DESC);
    printf(LIST_DESC);
    printf(SEARCH_DESC);
    printf(DELETE_DESC);
    return EXIT_CODE;
}

/*-----------------------SET---------------------------------*/

/*  Esta função irá obter os subnomes de um nome. 
    No exemplo de um nome usr///local/bin, os seus subnomes respetivos seriam
    usr, local e bin.
    Com o contador conseguimos escolher a quantidade de palavras que queremos obter,
    neste caso subnome_calc("usr/local/bin", subnome, 2), subnome seria local.  
*/
int subnome_calc(char nome[MAX_INPUT], char subnome[MAX_INPUT], int contador)
{ 
    char c;
    int i,l = 0, contador_aux = 1;
    subnome[0] = '\0';

    for (i = 0; nome[i] != 0; i++) {
        c = nome[i];
        if(c != '/' && contador_aux == contador){
            subnome[l] = c;
            l++;
        }
        if(c == '/'){
            contador_aux++;
            while(nome[++i] == '/');
            i--;
        }    
    }  
    subnome[l] = '\0';
    return EXIT_CODE;
}
/*  Esta função irá obter os subnomes de um nome. 
    No exemplo de um nome usr///local/bin, os seus subnomes respetivos seriam
    usr, usr/local e usr/local/bin.
    Com o contador conseguimos escolher a quantidade de palavras que queremos obter,
    neste caso subnome_calc("usr/local/bin", subnome, 2), subnome seria usr/local.  
*/
int subnome_calc_diretorio(char nome[MAX_INPUT], char subnome[MAX_INPUT], int contador)
{ 
    char c;
    int i,l = 0, contador_aux = 0;

    for (i = 0; nome[i] != 0; i++) {
        c = nome[i];
        if(c != '/' && c != '\0'){
            subnome[l] = c;
            l++;
        }   
        if(c == '/'){
            contador_aux++;
            if(contador_aux != contador)
                subnome[l++] = '/';
            i--;         
        }
        if(contador_aux == contador)
            break;

        if(c == '/'){
            while(nome[++i] == '/');
            
            i--;}
    }   
    subnome[l] = '\0';
    return EXIT_CODE;
}

/*  Esta função irá ler um diretório de stdin,
    e irá remover caracteres '/' do início da palavra. 
*/
int read_caminho(char caminho[MAX_INPUT])
{
    int l = 0, i = 0;
    char caminho_aux[MAX_INPUT];
    scanf("%s", caminho_aux);
    if(caminho_aux[0] == '/')
    {
        while(caminho_aux[i++] == '/');
        i--;
    }   
    for(; caminho_aux[i] != '\0'; i++)
        caminho[l++] = caminho_aux[i];
    caminho[l] = '\0';
    return EXIT_CODE;
}

/*  Esta função irá ler o valor de um caminho que consiste 
    em uma cadeias de carateres que não pode conter o caráter NULL ('\0'). 
*/
int read_valor(char valor[MAX_INPUT])
{
    char c;
    int i = 0;

    if((c = getchar()) == '\n')
        return EXIT_CODE;

    else{
        while((c = getchar()) != '\n'){
            valor[i++] = c;
        }
        valor[i] = '\0';
    }

    return EXIT_CODE;
}

/*  Esta função irá entregar o número de componentes em um caminho,
    No caso de ser chamada a funcao num_componentes("usr///local//bin/tests", 1),
    irá retornar 4. 
    Esta função será útil para conseguir aceder a todos os diretórios
    usando recursão. 
*/
int num_componentes(char nome[MAX_INPUT], int contador)
{
    char sub_nome[MAX_INPUT];
    subnome_calc(nome,sub_nome,contador);
    if(sub_nome[0] == '\0')
        return contador-1;
    else
        return num_componentes(nome, contador+1);

    return EXIT_CODE;
}
/*  Esta função irá transformar uma string em um número, que será introduzido
    dentro da estrutura dos caminhos para servir de chave, e aumentar a eficiência 
    da procura de nomes e valores dos caminhos.
    Como a comparação de números é feita de forma mais rápida que a comparação de 
    strings, estas chaves irão aumentar a eficiência do programa.
*/
int hash(char *v, int M)
{
    int h = 0, a = 127;

    for (; *v != '\0'; v++)
        h = (a*h + *v) % M;
    return h;
}
/*  Esta função foi realizada com o objetivo de isolar o caso da implementação 
    do sub-caminho final de um diretório. Exemplo: set user/local (local).
    Foi utilizado um método para melhorar a eficiência que consiste na utilização da função 
    lookup2. lookup2 ao procurar um caminho com o nome desejado poderá devolver 3 casos.
    Ou irá devolver NULL, caso a lista esteja vazia, ou devolverá um nó.
    Este nó poderá ser o caminho desejado ou o último elemento da lista.
    Caso seja o caminho desejado iremos apenas alterar o seu valor.
    Caso seja o último elemento da lista ou o primeiro iremos criar um novo caminho.
*/
int caso_terminal_set(link t,char sub_nome[MAX_INPUT],char valor[MAX_INPUT], char diretorio[MAX_INPUT])
{
    link z;
    /* Se o caminho obtido não tiver um subcaminho iremos inserir um subcaminho.*/
    if(t->subcaminho == NULL){
        insertEnd_Sub(t, sub_nome);
        t->subcaminho = Add_Hash_Dir(t->subcaminho,diretorio,sub_nome);
        t->subcaminho = Add_Valor(t->subcaminho,valor);
        return EXIT_CODE;
        }
    z = lookup2(t->subcaminho, sub_nome);
    /* Se o nó obtido for o último da lista iremos inserir o desejado no seu fim.
        Iremos utilizar a função strcmp para verificar qual nó foi obtido. */
    if(z != NULL && strcmp(z->nome,sub_nome) != 0){   
        z = insertEnd2(z, sub_nome);
        z = Add_Hash_Dir(z,diretorio,sub_nome);
        z = Add_Valor(z, valor);
        return EXIT_CODE;
        }
    /* Se o nó obtido for o desejado iremos alterar o seu valor se necessário.*/
    if(z != NULL && strcmp(z->nome,sub_nome) == 0){     
            z = Add_Valor(z, valor);
            return EXIT_CODE;
    }
    /* Se o nó obtido for o primeiro da lista, iremos inserir diretamente nela.*/
    if(z == NULL){
        t->subcaminho = insertEnd(t->subcaminho, sub_nome);
        z = lookup(t->subcaminho, sub_nome);
        z = Add_Hash_Dir(z,diretorio,sub_nome); }
    
    z = Add_Valor(z, valor);
    return EXIT_CODE;
}
/*  Esta função teve como objetivo isolar o caso de o utilizador estar a implementar
    apenas um caminho. Exemplo: set user (user).
    Através do método previamente utilizado do lookup2, iremos verificar se o caminho
    obtido existe na raiz.
    Caso retorne NULL (primeiro elemento da raiz), ou devolve um nó com nome 
    diferente do caminho desejado (último elemento da raiz), iremos criar o 
    caminho, e no final atribuir ou alterar o seu Valor.
*/
link caso_solo_set(link head, link t, char caminho[MAX_INPUT], char valor[MAX_INPUT])
{  
    t = lookup2(head, caminho);
    if(t != NULL){                          
        if(strcmp(t->nome, caminho) != 0){
            t = insertEnd2(t, caminho);
            t = Add_Hash_Dir(t,caminho,caminho);
        }
    }
    else{                           
        head = insertEnd(head, caminho);
        t = lookup(head, caminho);
        t = Add_Hash_Dir(t,caminho,caminho);   
    }
    t = Add_Valor(t, valor);
    return head;
}

/*  Esta função mais uma vez irá isolar um caso do set, neste caso será o de um
    sub-caminho no "meio" de um diretório. Exemplo: set user/local/bin/test (local e bin).
    O mesmo método será utilizado com a excessão de neste caso não se inserir ou
    alterar valores, dado que seria impossível.
*/
link caso_set_medio(link t, char sub_nome[MAX_INPUT], char diretorio[MAX_INPUT])
{ 
    link z;
    z = lookup2(t->subcaminho,sub_nome);

    if(z != NULL && strcmp(z->nome,sub_nome) != 0){
        z = insertEnd2(z,sub_nome);
        z = Add_Hash_Dir(t,diretorio,sub_nome);
        return z;}
    if(z == NULL ){
        t->subcaminho = insertEnd(t->subcaminho, sub_nome);
        z = lookup(t->subcaminho, sub_nome);
        z = Add_Hash_Dir(z,diretorio,sub_nome);
    }
    return z;
}
/*  Esta será a função principal do comando set, que irá conter os 3 casos 
    demonstrados em cima, (caso solo, médio e terminal) mais o caso solo onde
    o número de componentes do dirétorio seja maior que 1.
    Exemplo: user/local/bin  (user).
    Através do número de componentes do diretório recebido e
    um contador esta função será capaz de criar qualquer caminho e subcaminho
    com recursão.
*/
link cria_caminho(link head, link t, char caminho[MAX_INPUT], char valor[MAX_INPUT], int contador)
{
    int l = num_componentes(caminho, 1);
    char sub_nome[MAX_INPUT], diretorio[MAX_INPUT];

    subnome_calc(caminho, sub_nome, contador);
    subnome_calc_diretorio(caminho,diretorio,contador);
    /* Caso o número de componentes seja 1. */
    if(l == 1) {    
        head = caso_solo_set(head,t,diretorio,valor);    
        return head;
    }
    /*  Caso o número de compontentes não seja 1, mas o contador que
        verifica o caminho em que a função está seja 1. (primeiro caminho) */
    if(contador == 1){  
        t = lookup(head, sub_nome);                             
        if(t == NULL){          
            head = insertEnd(head, sub_nome);          
            t = lookup(head, sub_nome);}
            t = Add_Hash_Dir(t,diretorio,sub_nome);
        
        return cria_caminho(head, t, caminho, valor, contador+1);
    }
    /*  Caso o número de componentes e o contador sejam iguais estaremos
        no caminho final do diretório. */   
    if(l == contador){                                  
        caso_terminal_set(t,sub_nome,valor,diretorio);
        return head;
    }
    /*  Caso o subcaminho de um caminho central não exista, iremos criar
        e avancar no diretório. */
    if(t->subcaminho == NULL){
        insertEnd_Sub(t, sub_nome);
        t->subcaminho = Add_Hash_Dir(t->subcaminho,diretorio,sub_nome);
        return cria_caminho(head,t->subcaminho, caminho, valor, contador+1);
    }
    /*  Caso o caminho já tenha um subcaminho, iremos enviar o caminho 
        para uma função auxiliar. */
    t = caso_set_medio(t, sub_nome, diretorio);
    return cria_caminho(head,t, caminho, valor, contador+1);
}

/*------------------------PRINT-----------------------*/
/*  Esta função irá percorrer todos os caminhos e subcaminhos
    dos componentes da raíz, e irá imprimir aqueles que tenham
    um valor atribuído.
*/
int percorrer_main(link head)
{
    link t;
    for(t = head; t != NULL; t = t->next){
        if(t->subcaminho != NULL){
            if(t->valor != NULL)
                printf("/%s %s\n",t->diretorio, t->valor);
            percorrer_main(t->subcaminho);
        }
        else{
            if(t->valor != NULL)
                printf("/%s %s\n",t->diretorio, t->valor);
                    
        }
    }
    return EXIT_CODE;
}

/*--------------------------LIST-------------------*/
/*  Esta função irá copiar os nomes dos componentes da raíz
    e transferí-los para um vetor de strings.
    Este vetor irá servir para ser ordenado alfabeticamente.
*/
int list_main(link head,char *array[HASH_VALUE], int contador)
{
    link t;
    for(t = head; t != NULL; t = t->next){
        array[contador] =(char *)malloc(sizeof(char) * (strlen(t->nome) + 1)); /*reservar memória para nova string*/
        check_memory_string(t->nome);
        strcpy(array[contador], t->nome);
        contador++;
    }
    return contador;
}
/*  Algoritmo de ordenação para ordenar o vetor de strings
    previamente mencionado. 
*/
int bubble_sort(char *table[HASH_VALUE], int n)
{               
    int j, i;
    char aux[MAX_INPUT];

    for ( j=0; j<n-1; j++)
    {
        for (i=j+1; i<n; i++)
        {
            if (strcmp(table[j], table[i]) > 0)
            {
                strcpy(aux, table[j]);
                strcpy(table[j], table[i]);
                strcpy(table[i], aux);
            }
        }
    }

    return EXIT_CODE;         
}
/*  Esta função irá listar os sub-caminhos diretos de um subcaminho através de um contador,
    e um 'int n' que será o número de componentes do diretório recebido.
    Através da função subnome_calc será possível a procura em profundidade de cada
    caminho e sub-caminho de uma forma mais eficiente, no entanto não tão eficiente
    como seria com uma hashtable.
    Caso o número de componentes seja igual ao contador ou não seja possível encontrar
    o caminho desejado numa lista, irá se imprimir o erro Not found.
    Caso encontremos o caminho desejado ir-se-á imprimir o seu sub-caminho com a função print.
*/
int list_main_caminho(link head, char *table[HASH_VALUE], char caminho[MAX_INPUT], int contador, int n)
{
    link t;
    char subnome[MAX_INPUT];

    subnome_calc(caminho, subnome, contador);
    t = lookup(head, subnome);

    if(t == NULL){
        printf(NOT_FOUND);
        return EXIT_CODE;}
    
    if(t->subcaminho != NULL && n != contador)
    {
        list_main_caminho(t->subcaminho, table, caminho, contador+1, n);
    }
    else if(n == contador)
    {
        print(t->subcaminho);
        return EXIT_CODE;
        }
    
    else if(t->subcaminho == NULL && n != contador){
        printf(NOT_FOUND);
        return EXIT_CODE;
    }
    return EXIT_CODE;
}

/*--------------------------FIND-------------------*/
/*  Esta função irá procurar um caminho específico através de um contador, e um
    'int n' que será o número de componentes do diretório recebido.
    Através da função subnome_calc será possível a procura em profundidade de cada
    caminho e sub-caminho de uma forma mais eficiente, no entanto não tão eficiente
    como seria com uma hashtable.
    Caso o número de componentes seja igual ao contador ou não seja possível encontrar
    o caminho desejado numa lista, ir-se-á se imprimir o erro Not found.
    Caso o caminho desejado seja encontrado ir-se-á verificar se este tem um valor 
    associado. Caso não tenha ir-se-á imprimir um erro de No data.
    Caso tenha irá se imprimir o seu valor.
*/
int find_main(link head, char caminho[MAX_INPUT], int contador, int n)
{ 
    link t;
    char subnome[MAX_INPUT];

    subnome_calc(caminho, subnome, contador);
    t = lookup(head, subnome);

    if(t == NULL)
    {
        printf(NOT_FOUND);
        return EXIT_CODE;
    }
    if(t->subcaminho != NULL && n != contador)
    {
        find_main(t->subcaminho, caminho, contador+1, n);
    }
    else if(n == contador)
    {
        if(t->valor != NULL){
            printf("%s\n",t->valor);
            return EXIT_CODE;
        }
        else{
            printf(NO_DATA);
            return EXIT_CODE;
        }
    }

    else if(t->subcaminho == NULL && n != contador){
        printf(NOT_FOUND);
        return EXIT_CODE;
    }
    return EXIT_CODE;
}

/*--------------------------SEARCH-------------------*/
/*  Esta função irá procurar em uma lista um caminho com um valor
    correspondente ao valor recebido. Caso encontre um caminho 
    com esse valor, a função irá retornar 1, caso não retornará 0.
*/
int search(link head,char valor[MAX_INPUT], int h)
{
    link t;
    for(t = head; t != NULL; t = t->next){
        if(t->valor != NULL)
            if(h == t->hash2)
                if(strcmp(t->valor, valor) == 0)
                    {
                    printf("/%s\n",t->diretorio);
                    return 1;
                    }

    }
    return EXIT_CODE;
}
/*  Esta será a função principal do search que irá procurar em
    todos os caminhos e subcaminhos por um caminho com o valor 
    correspondente ao valor recebido.
    A função search será utilizada para caso devolva 1, 
    indicando que um valor igual foi encontrado, se possa
    sair do ciclo e terminar a função para que apenas um 
    caminho seja imprimido pelo uso do break.
*/
int search_main(link head, char valor[MAX_INPUT], int h)
{
    link t;
    for(t = head; t != NULL; t = t->next){
        if(t->valor != NULL)
            if(h == t->hash2)
                if(strcmp(t->valor, valor) == 0)
                    {
                    printf("/%s\n",t->diretorio);
                    break;
                    }
        if(t->subcaminho != NULL)
            {
                if(search(t->subcaminho, valor, h) == 1)
                    break;
            search_main(t->subcaminho, valor, h);}
    }
    return EXIT_CODE;
}

/*--------------------------DELETE-------------------*/
/*  Esta função tinha como objetivo eliminar toda a memória 
    alocada de todos os sub-caminhos de um caminho.
*/
int delete_aux(link head)
{
    link t;
    for(t = head; t != NULL; t = t->next){

        if(t->subcaminho != NULL)
            delete_aux(t->subcaminho);

        else
            FREEnode(t);   
    }
    return EXIT_CODE;

}
/*  Esta função irá utilizar o método usado no comando search, list e find
    de forma a encontrar o caminho desejado, e depois irá apagar a memória
    alocada do caminho e todos os seus sub-caminhos.
*/
int delete_main(link head, char caminho[MAX_INPUT], int contador, int n)
{ 
    link t;
    char subnome[MAX_INPUT];

    subnome_calc(caminho, subnome, contador);
    t = lookup(head, subnome);

    if(t == NULL)
    {
        printf(NOT_FOUND);
        return EXIT_CODE;
    } 
    if(t->subcaminho != NULL && n != contador)
        delete_main(t->subcaminho, caminho, contador+1, n);

    else if(n == contador)
    {
        if(t->subcaminho != NULL)
        {
            FREEnode(t);
            delete_aux(t->subcaminho); 
        }
        else
            FREEnode(t);
    }
    else if(t->subcaminho == NULL && n != contador)
    {
        printf(NOT_FOUND);
        return EXIT_CODE;
    }
    return EXIT_CODE;
}


