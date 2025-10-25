#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "funcoes_bib.h"

int proximo_id = 1;

int inicializar_biblioteca(Biblioteca *b)
{
    b->total_livros = 0;
    b->capacidade = 2;
    b->livros = malloc(2 * sizeof(Livro));

    if(b->livros == NULL)
    {
        printf("Erro em alocar memoria.");
        return ERRO;
    }

    return SUCESSO;
}

void imprimir_menu()
{
    printf("--------------------------------------------------\n");
    printf("-------------BIBLIOTECA DINAMICA------------------\n");
    printf("1- Adicionar livros\n");
    printf("2- Listar livros\n");
    printf("3- Buscar por Id\n");
    printf("4- Buscar por titulo\n");
    printf("5- Emprestar livro\n");
    printf("6- Devolver livro\n");
    printf("7- Remover livro\n");
    printf("8- Salvar em arquivo\n");
    printf("9- Sair do sistema\n");
    printf("\n");
}

void menu_switch(Biblioteca *b, int escolha_usuario)
{
    Livro *livro_encontrado = NULL;  

    switch (escolha_usuario)
    {
        case 1: // adicionar livro
            adicionar_livro(b);
            break;

        case 2: // listar livros
            if (!tem_livros_cadastrados(b))
                break;

            for (int i = 0; i < b->total_livros; i++)
            {
                print_livro(&b->livros[i]);
            }
            break;

        case 3: // buscar por id
            if (!tem_livros_cadastrados(b))
                break;

            livro_encontrado = buscar_por_id(b, digitar_id());

            if(livro_encontrado == NULL)
            {
                printf("Id nao encontrado.\n");
            }
            else
            {
                printf("Livro encontrado!\n");
                print_livro(livro_encontrado);
            }
            break;

        case 4: // buscar por titulo
            if (!tem_livros_cadastrados(b))
                break;

            livro_encontrado = buscar_por_titulo(b);

            if(livro_encontrado == NULL)
            {
                printf("Livro nao encontrado.\n");
            }
            else
            {
                printf("Livro encontrado!\n");
                print_livro(livro_encontrado);
            }
            break;

        case 5: // emprestar livro
            if (!tem_livros_cadastrados(b))
                break;

            emprestar_livro(b, digitar_id());
            break;

        case 6: // devolver livro
            if (!tem_livros_cadastrados(b))
                break;

            devolver_livro(b, digitar_id());
            break;

        case 7: // remover livro
            if (!tem_livros_cadastrados(b))
                break;

            remover_livro(b, digitar_id());
            break;

        case 8: // salvar em arquivo
            if (!tem_livros_cadastrados(b))
                break;

            salvar_em_arquivo(b);
            break;

        case 9: // sair do sistema
            printf("Saindo do sistema.\n");
            break;

        default:
            printf("Digite uma opcao valida.\n");
            break;
    }
}

int digitar_id()
{
    int id;
    char buffer[50];
    char *endptr;

    do {
        printf("Digite o ID desejado: ");
        fgets(buffer, sizeof(buffer), stdin);
        id = (int)strtol(buffer, &endptr, 10);

        if (*endptr != '\n' && *endptr != '\0') {
            printf("ERRO: Digite apenas numeros!\n");
            id = -1;  //força repetir
        }
    } while (id <= 0);

    return id;
}

void adicionar_livro(Biblioteca *b)
{   
    if(b->total_livros >= b->capacidade)
    {
        Livro *temp = realloc(b->livros, 2 * b->capacidade * sizeof(Livro));
        if(temp == NULL)
        {
            printf("Erro em alocar memoria.\n");
            return;
        }
        b->livros = temp;
        b->capacidade *= 2;
    }

    int proximo_indice = b->total_livros;
    b->total_livros++;

    char buffer[50]; //para ler o ano como string
    char *endptr; //para verificar se ano é numero.

    b->livros[proximo_indice].id = proximo_id++;

    printf("Digite o titulo do livro: \n");
    fgets(b->livros[proximo_indice].titulo, sizeof(b->livros[proximo_indice].titulo), stdin);
    b->livros[proximo_indice].titulo[strcspn(b->livros[proximo_indice].titulo, "\n")] = '\0';  // remove o \n do final

    printf("Digite o autor do livro: \n");
    fgets(b->livros[proximo_indice].autor, sizeof(b->livros[proximo_indice].autor), stdin);
    b->livros[proximo_indice].autor[strcspn(b->livros[proximo_indice].autor, "\n")] = '\0';  

    do {
        printf("Digite o ano do livro: \n");
        fgets(buffer, sizeof(buffer), stdin);
        b->livros[proximo_indice].ano = (int)strtol(buffer, &endptr, 10);

        if (*endptr != '\n' && *endptr != '\0') {
            printf("ERRO: Digite apenas numeros!\n");
        }
    } while (*endptr != '\n' && *endptr != '\0');

    do {
        printf("Digite se o livro esta disponivel: (1 - sim, 0 - nao)\n");
        fgets(buffer, sizeof(buffer), stdin);
        b->livros[proximo_indice].disponivel = (int)strtol(buffer, &endptr, 10);

        if (*endptr != '\n' && *endptr != '\0') {
            printf("ERRO: Digite apenas numeros!\n");
            b->livros[proximo_indice].disponivel = -1;
        }
        else if(b->livros[proximo_indice].disponivel != 1 && b->livros[proximo_indice].disponivel != 0)
        {
            printf("ERRO: Digite apenas (1 - sim, 0 - nao)!\n"); 
            b->livros[proximo_indice].disponivel = -1;
        }
    } while (b->livros[proximo_indice].disponivel == -1); 

    printf("Livro adicionado com sucesso!\n");
}

void print_livro(Livro *livro)
{       
    printf("\nId: %d\n", livro->id);
    printf("Titulo: %s\n", livro->titulo);
    printf("Autor: %s\n", livro->autor);
    printf("Ano: %d\n", livro->ano);

    if(livro->disponivel == DISPONIVEL)
    {
        printf("Esta disponivel? Sim\n");
        printf("\n");
    }
    else if(livro->disponivel == EMPRESTADO)
    {
        printf("Esta disponivel? Nao, esta emprestado\n");
        printf("\n");
    }
}

int tem_livros_cadastrados(Biblioteca *b)
{
    if(b->total_livros == 0)
    {
        printf("Nao existem livros cadastrados\n");
        return NAO;
    }

    return SIM;
}

Livro *buscar_por_id(Biblioteca *b, int id)
{
    for (int i = 0; i < b->total_livros; i++)
    {
        if(id == b->livros[i].id)
        {
            return &b->livros[i];
        }
    }

    return NULL;
}

Livro *buscar_por_titulo(Biblioteca *b)
{
    char titulo_procurado[100];

    printf("Digite o titulo do livro: \n");
    fgets(titulo_procurado, sizeof(titulo_procurado), stdin);
    titulo_procurado[strcspn(titulo_procurado, "\n")] = '\0';  // remove o \n do final

     for (int i = 0; i < b->total_livros; i++)
    {
        if(strcmp(titulo_procurado, b->livros[i].titulo) == 0)
        {
            return &b->livros[i];
        }
    }

    return NULL;
}

int emprestar_livro(Biblioteca *b, int id) 
{
    Livro *livro_encontrado = buscar_por_id(b, id);

    if(livro_encontrado == NULL)
    {
        printf("Livro com ID %d nao encontrado.\n", id);
        return ERRO;
    }

    if(livro_encontrado->disponivel != DISPONIVEL)
    {
        printf("Livro ja esta emprestado.\n");
        return ERRO;
    }

    print_livro(livro_encontrado);

    if(confirmar_operacao() == CONFIRMADO)
    {
        livro_encontrado->disponivel = EMPRESTADO;
        printf("\nLivro emprestado com sucesso.\n");
        return SUCESSO;
    }
    else
    {
        printf("Operacao cancelada.\n");
        return CANCELADO;
    }
}

int devolver_livro(Biblioteca *b, int id)
{
    Livro *livro_encontrado = buscar_por_id(b, id);

    if(livro_encontrado == NULL)
    {
        printf("Livro com ID %d nao encontrado.\n", id);
        return ERRO;
    }

    if(livro_encontrado->disponivel == DISPONIVEL)
    {
        printf("Livro ja estava disponivel.\n");
        return SUCESSO;
    }

    print_livro(livro_encontrado);

    if(confirmar_operacao() == CONFIRMADO)
    {
        livro_encontrado->disponivel = DISPONIVEL;
        printf("Livro devolvido com sucesso.\n");
        return SUCESSO;
    }
    else
    {
        printf("Operacao cancelada.\n");
        return CANCELADO;
    }
}

int remover_livro(Biblioteca *b, int id)
{
    Livro* livro_encontrado = buscar_por_id(b, id);

    if (livro_encontrado == NULL) {
        printf("Livro com ID %d nao encontrado!\n", id);
        return ERRO;
    }

    print_livro(livro_encontrado);

    if(livro_encontrado->disponivel == EMPRESTADO)
    {
        printf("ERRO: Nao e possivel remover livro emprestado!\n");
        printf("Devolva o livro antes de remove-lo.\n");
        return ERRO;
    }

    if(confirmar_operacao() == CONFIRMADO)
    {
        int indice = livro_encontrado - b->livros;

        for (int i = indice; i < b->total_livros - 1; i++)
        {
            b->livros[i] = b->livros[i + 1];
        }

        b->total_livros--;

        if(b->total_livros > 0 && b->capacidade > 2 && b->total_livros < b->capacidade / 4)
        {
            Livro *temp = realloc(b->livros, (b->capacidade / 2) * sizeof(Livro));
            
            if(temp != NULL)  
            {
                b->livros = temp;
                b->capacidade /= 2; 
                printf("Biblioteca otimizada! Nova capacidade: %d\n", b->capacidade);
            }
            else
            {
                // Se falhar, não é crítico - continua com a capacidade maior
                printf("Aviso: Nao foi possivel otimizar a memoria.\n");
            }
        }

        printf("Livro removido com sucesso!\n");
        return SUCESSO;
    }
    else
    {
        printf("Operacao cancelada.\n");
        return CANCELADO;
    } 
}

int confirmar_operacao()
{
    char resposta[10];
    printf("Tem certeza? (s/n): ");
    fgets(resposta, sizeof(resposta), stdin);

    if (resposta[0] == 's' || resposta[0] == 'S') {
        return CONFIRMADO;
    }
    return CANCELADO;
}

void finalizar_biblioteca(Biblioteca *b)
{
    free(b->livros);           
    b->livros = NULL;       
    b->total_livros = 0;       
    b->capacidade = 0;
}

void salvar_em_arquivo(Biblioteca *b)
{
    FILE *arquivo = fopen("lista_livros.txt", "w");
    if(arquivo)
    {
         for (int i = 0; i < b->total_livros; i++)
        {
            fprintf(arquivo, "Id: %d\n", b->livros[i].id);
            fprintf(arquivo, "Titulo: %s\n", b->livros[i].titulo);
            fprintf(arquivo, "Autor: %s\n", b->livros[i].autor);
            fprintf(arquivo, "Ano: %d\n", b->livros[i].ano);
            fprintf(arquivo, "Disponivel: %s\n",
                    b->livros[i].disponivel == DISPONIVEL ? "Sim" : "Nao");
            fprintf(arquivo, "----------------------------\n");
         }
        
        fclose(arquivo);
        printf("Todos os livros foram salvos no arquivo!\n");
    }
    else
    {
        printf("ERRO: nao foi possivel abrir o arquivo.\n");
    }
}