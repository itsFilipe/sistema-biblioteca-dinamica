#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "funcoes_bib.h"

int main()
{   
    Biblioteca minha_biblioteca;

    if(inicializar_biblioteca(&minha_biblioteca) == SUCESSO)
    {
        printf("Biblioteca inicializada!\n");
    }
    else
    {
        printf("Erro em alocar memoria.");
        return 1;
    }

    char buffer[100];
    int opcao = 0;

    while (opcao != 9)
    {
        imprimir_menu();

        printf("Digite a opcao:\n");
        fgets(buffer, sizeof(buffer), stdin);
        opcao = (int)strtol(buffer, NULL, 10);  // converte string -> int

        menu_switch(&minha_biblioteca, opcao);
    }

    printf("Total de livros: %d\n", minha_biblioteca.total_livros);

    finalizar_biblioteca(&minha_biblioteca);

    getchar();
    return 0;
}
