#ifndef _FUNCOES_BIB_H 
#define _FUNCOES_BIB_H 

#define DISPONIVEL 1
#define EMPRESTADO 0
#define SUCESSO 1
#define ERRO 0
#define SIM 1
#define NAO 0
#define CONFIRMADO 1
#define CANCELADO 0

extern int proximo_id;

typedef struct
{
    int id;
    char titulo[100];
    char autor[50];
    int ano;
    int disponivel; // 1 = disponivel, 0 = emprestado
} Livro;

typedef struct
{
    Livro *livros; 
    int capacidade;
    int total_livros;
} Biblioteca;

int inicializar_biblioteca(Biblioteca *b);
void imprimir_menu();
void menu_switch(Biblioteca *b, int escolha_usuario);
void adicionar_livro(Biblioteca *b);
void print_livro(Livro *livro);
int tem_livros_cadastrados(Biblioteca *b);
Livro *buscar_por_id(Biblioteca *b, int id);
Livro *buscar_por_titulo(Biblioteca *b);
int emprestar_livro(Biblioteca *b, int id);
int devolver_livro(Biblioteca *b, int id);
int digitar_id();
int remover_livro(Biblioteca *b, int id);
int confirmar_operacao();
void finalizar_biblioteca(Biblioteca *b);
void salvar_em_arquivo(Biblioteca *b);

#endif