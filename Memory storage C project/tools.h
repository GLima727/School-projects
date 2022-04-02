#ifndef _TOOLS_
#define _TOOLS_ 

/*VALUE DEFINES */
#define EXIT_CODE 0
#define MAX_INPUT 65535 
#define HASH_VALUE 40009

/* ESTRUTURA PRINCIPAL */
typedef struct caminho{
  char *valor;
  char *nome;
  char *diretorio;
  struct caminho *next;
  struct caminho *subcaminho; 
  int hash;
  int hash2;

}Caminho;

typedef struct caminho *link;

/* Funções utilizadas em main_tools.c presentes em tools.c.*/
int read_caminho(char caminho[MAX_INPUT]);
int read_valor(char valor[MAX_INPUT]);
link cria_caminho(link head,link t, char caminho[MAX_INPUT], char valor[MAX_INPUT], int contador);
int print_comandos();
int percorrer_main(link head);
int list_main(link head,char *array[HASH_VALUE], int contador);
int bubble_sort(char *ids[HASH_VALUE], int right);
int num_componentes(char nome[MAX_INPUT], int contador);
int list_main_caminho(link head, char *table[HASH_VALUE], char caminho[MAX_INPUT], int contador, int n);
int find_main(link head, char caminho[MAX_INPUT], int contador, int n);
int search_main(link head,char valor[MAX_INPUT],int h);
int delete_main(link head, char caminho[MAX_INPUT], int contador, int n);
int delete_aux(link head);
int hash(char *v, int M);

/* Funções utilizadas em main.c presentes em main_tools.c*/
link main_set(link caminhos);
int main_help();
void main_quit(link caminhos);
int main_print(link caminhos);
int main_list(link caminhos);
int main_find(link caminhos);
int main_search(link caminhos);
int main_delete(link caminhos);

#endif