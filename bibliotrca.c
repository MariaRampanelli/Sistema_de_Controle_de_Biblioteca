#include <stdio.h>
#include "bibioteca.h"


void menuCadastro() {

    int opcao;

    do {

        printf("\n===== CADASTRO =====\n");
        printf("1. Livros\n");
        printf("2. Usuarios\n");
        printf("0. Voltar\n");


        scanf("%d", &opcao);


        switch(opcao) {

            case 1:
                cadastrarLivro();
                break;

            case 2:
                cadastrarUsuario();
                break;

        }

    } while(opcao != 0);
}



void menuConsulta() {

    int opcao;

    do {

        printf("\n===== CONSULTA =====\n");
        printf("1. Livros\n");
        printf("2. Usuarios\n");
        printf("3. Emprestimos\n");
        printf("0. Voltar\n");


        scanf("%d", &opcao);


        switch(opcao) {

            case 1:
                consultarLivroPorCodigo();
                break;

            case 2:
                consultarUsuarioPorEmail();
                break;

            case 3:
                consultarEmprestimosUsuario();
                break;

        }

    } while(opcao != 0);
}



void menuAtualizacao() {

    int opcao;

    do {

        printf("\n===== ATUALIZACAO =====\n");
        printf("1. Livros\n");
        printf("2. Usuarios\n");
        printf("0. Voltar\n");


        scanf("%d", &opcao);


        switch(opcao) {

            case 1:
                atualizarLivro();
                break;

            case 2:
                atualizarUsuario();
                break;

        }

    } while(opcao != 0);

}



void menuExclusao() {

    int opcao;

    do {

        printf("\n===== EXCLUSAO =====\n");
        printf("1. Livros\n");
        printf("2. Usuarios\n");
        printf("0. Voltar\n");


        scanf("%d", &opcao);


        switch(opcao) {

            case 1:
                excluirLivro();
                break;

            case 2:
                excluirUsuario();
                break;

        }

    } while(opcao != 0);

}
