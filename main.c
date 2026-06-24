#include "biblioteca.h"
#include <stdio.h>


int main() {

    int opcao;


    do {

        printf("\n===== MENU PRINCIPAL =====\n");
        printf("1. Cadastro\n");
        printf("2. Consulta\n");
        printf("3. Atualizacao\n");
        printf("4. Exclusao\n");
        printf("5. Emprestimo\n");
        printf("6. Devolucao\n");
        printf("0. Sair\n");
        printf("==========================\n");


        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);


        switch(opcao) {

            case 1:
                menuCadastro();
                break;

            case 2:
                menuConsulta();
                break;

            case 3:
                menuAtualizacao();
                break;

            case 4:
                menuExclusao();
                break;

            case 5:
                emprestarLivro();
                break;

            case 6:
                devolverLivro();
                break;

            case 0:
                //liberarLivros(*raizLivros);
                printf("Encerrando...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }


    } while(opcao != 0);


    return 0;
}