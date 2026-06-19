#include <stdio.h>
#include "bibioteca.h"

typedef struct Usuario {
char email[100];
char nome[100];
} usuario;

typedef struct Livro{
    char titulo[20];
    char autor[100];
    int anoPublicacao;
    int codigo;
    int status;
    char emprestadoPara[100];
}livro;

typedef struct NoLivro {
    livro dados;
    struct NoLivro *esq;
    struct NoLivro *dir;
    int altura;
} NoLivro;

NoLivro *raizLivros = NULL;


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
                livro livro;
                printf("Cadastro de Livros\n");
                printf("Digite o titulo do livro: ");
                scanf(" %[^\n]s", livro.titulo);
                printf("Digite o autor do livro: ");
                scanf(" %[^\n]s", livro.autor);
                printf("Digite o ano de publicacao do livro: ");
                scanf("%d", &livro.anoPublicacao);
                
                raizLivros = inserirArvoreLivros(raizLivros, livro);
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
                consultarLivroPorId(raizLivros);
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

int altura(NoLivro *n) {
    if (n == NULL) return 0;
    return n->altura;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int fatorBalanceamento(NoLivro *n) {
    if (n == NULL) return 0;
    return altura(n->esq) - altura(n->dir);
}

NoLivro* rotacaoDireita(NoLivro *y) {
    NoLivro *x = y->esq;
    NoLivro *T2 = x->dir;

    x->dir = y;
    y->esq = T2;

    y->altura = max(altura(y->esq), altura(y->dir)) + 1;
    x->altura = max(altura(x->esq), altura(x->dir)) + 1;

    return x;
}

NoLivro* rotacaoEsquerda(NoLivro *x) {
    NoLivro *y = x->dir;
    NoLivro *T2 = y->esq;

    y->esq = x;
    x->dir = T2;

    x->altura = max(altura(x->esq), altura(x->dir)) + 1;
    y->altura = max(altura(y->esq), altura(y->dir)) + 1;

    return y;
}

NoLivro* inserirArvoreLivros(NoLivro *raiz, livro novoLivro) {

    if (raiz == NULL) {
        NoLivro *novo = (NoLivro*) malloc(sizeof(NoLivro));
        novo->dados = novoLivro;
        novo->esq = NULL;
        novo->dir = NULL;
        novo->altura = 1;
        return novo;
    }

    if (novoLivro.codigo < raiz->dados.codigo)
        raiz->esq = inserirArvoreLivros(raiz->esq, novoLivro);

    else if (novoLivro.codigo > raiz->dados.codigo)
        raiz->dir = inserirArvoreLivros(raiz->dir, novoLivro);

    else
        return raiz; // evita duplicado

    // atualiza altura
    raiz->altura = 1 + max(altura(raiz->esq), altura(raiz->dir));

    int balance = fatorBalanceamento(raiz);

    // CASOS DE ROTAÇÃO

    // Left Left
    if (balance > 1 && novoLivro.codigo < raiz->esq->dados.codigo)
        return rotacaoDireita(raiz);

    // Right Right
    if (balance < -1 && novoLivro.codigo > raiz->dir->dados.codigo)
        return rotacaoEsquerda(raiz);

    // Left Right
    if (balance > 1 && novoLivro.codigo > raiz->esq->dados.codigo) {
        raiz->esq = rotacaoEsquerda(raiz->esq);
        return rotacaoDireita(raiz);
    }

    // Right Left
    if (balance < -1 && novoLivro.codigo < raiz->dir->dados.codigo) {
        raiz->dir = rotacaoDireita(raiz->dir);
        return rotacaoEsquerda(raiz);
    }

    return raiz;
}

void consultarLivroPorId(NoLivro *raiz) {

    int id;
    
    printf("Informe o ID do livro: ");
    scanf("%d", &id);

    NoLivro *livroEncontrado = buscarLivro(raiz, id);

    if (livroEncontrado == NULL) {
        printf("Livro nao encontrado!\n");
        return;
    }

    printf("\n===== DADOS DO LIVRO =====\n");
    printf("ID: %d\n", livroEncontrado->dados.codigo);
    printf("Titulo: %s", livroEncontrado->dados.titulo);
    printf("Autor: %s", livroEncontrado->dados.autor);
    printf("Ano: %d\n", livroEncontrado->dados.anoPublicacao);

    if (livroEncontrado->dados.status == 0)
        printf("Status: Disponivel\n");
    else
        printf("Status: Emprestado\n");
}

NoLivro* buscarLivro(NoLivro *raiz, int id) {

    if (raiz == NULL)
        return NULL;

    if (id == raiz->dados.codigo)
        return raiz;

    if (id < raiz->dados.codigo)
        return buscarLivro(raiz->esq, id);

    return buscarLivro(raiz->dir, id);
}