#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioteca.h"

NoLivro *raizLivros = NULL;
int proximoCodigoLivro = 1;

// MENUS ------------------------------------------------

void menuCadastro() {
    int opcao;

    do {
        printf("\n===== CADASTRO =====\n");
        printf("1. Livros\n");
        printf("2. Usuarios\n");
        printf("0. Voltar\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: {
                livro novoLivro;

                printf("\nCadastro de Livros\n");

                printf("Digite o titulo do livro: ");
                scanf(" %[^\n]", novoLivro.titulo);

                printf("Digite o autor do livro: ");
                scanf(" %[^\n]", novoLivro.autor);

                printf("Digite o ano de publicacao do livro: ");
                scanf("%d", &novoLivro.anoPublicacao);

                novoLivro.codigo = proximoCodigoLivro++;
                novoLivro.status = 0;
                strcpy(novoLivro.emprestadoPara, "");

                raizLivros = inserirArvoreLivros(raizLivros, novoLivro);

                printf("Livro cadastrado com sucesso! ID: %d\n", novoLivro.codigo);
                break;
            }

            case 2:
               // cadastrarUsuario();
                break;

            case 0:
                break;

            default:
                printf("Opcao invalida!\n");
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
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                menuConsultaLivros();
                break;

            case 2:
              //  consultarUsuarioPorEmail();
                break;

            case 3:
              //  consultarEmprestimosUsuario();
                break;

            case 0:
                break;

            default:
                printf("Opcao invalida!\n");
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
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                atualizarLivro();
                break;

            case 2:
                // atualizarUsuario();
                break;

            case 0:
                break;

            default:
                printf("Opcao invalida!\n");
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
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                excluirLivro();
                break;

            case 2:
              //  excluirUsuario();
                break;

            case 0:
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while(opcao != 0);
}

// FUNÇÕES AVL

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

        if (novo == NULL) {
            printf("Erro ao alocar memoria!\n");
            exit(1);
        }

        novo->dados = novoLivro;
        novo->esq = NULL;
        novo->dir = NULL;
        novo->altura = 1;

        return novo;
    }

    if (novoLivro.codigo < raiz->dados.codigo) {
        raiz->esq = inserirArvoreLivros(raiz->esq, novoLivro);
    } else if (novoLivro.codigo > raiz->dados.codigo) {
        raiz->dir = inserirArvoreLivros(raiz->dir, novoLivro);
    } else {
        printf("Codigo de livro ja existente!\n");
        return raiz;
    }

    raiz->altura = 1 + max(altura(raiz->esq), altura(raiz->dir));

    int balance = fatorBalanceamento(raiz);

    if (balance > 1 && novoLivro.codigo < raiz->esq->dados.codigo)
        return rotacaoDireita(raiz);

    if (balance < -1 && novoLivro.codigo > raiz->dir->dados.codigo)
        return rotacaoEsquerda(raiz);

    if (balance > 1 && novoLivro.codigo > raiz->esq->dados.codigo) {
        raiz->esq = rotacaoEsquerda(raiz->esq);
        return rotacaoDireita(raiz);
    }

    if (balance < -1 && novoLivro.codigo < raiz->dir->dados.codigo) {
        raiz->dir = rotacaoDireita(raiz->dir);
        return rotacaoEsquerda(raiz);
    }

    return raiz;
}

// CONSULTA
NoLivro* buscarLivro(NoLivro *raiz, int id) {
    if (raiz == NULL)
        return NULL;

    if (id == raiz->dados.codigo)
        return raiz;

    if (id < raiz->dados.codigo)
        return buscarLivro(raiz->esq, id);

    return buscarLivro(raiz->dir, id);
}

void exibirLivro(livro l) {
    printf("\n===== DADOS DO LIVRO =====\n");
    printf("ID: %d\n", l.codigo);
    printf("Titulo: %s\n", l.titulo);
    printf("Autor: %s\n", l.autor);
    printf("Ano: %d\n", l.anoPublicacao);

    if (l.status == 0) {
        printf("Status: Disponivel\n");
    } else {
        printf("Status: Emprestado\n");
        printf("Emprestado para: %s\n", l.emprestadoPara);
    }
}

void consultarLivroPorAutor(NoLivro *raiz, char autor[], int *encontrou) {
    if (raiz == NULL) {
        return;
    }

    consultarLivroPorAutor(raiz->esq, autor, encontrou);

    if (strcmp(raiz->dados.autor, autor) == 0) {
        exibirLivro(raiz->dados);
        *encontrou = 1;
    }

    consultarLivroPorAutor(raiz->dir, autor, encontrou);
}

void menuConsultaLivros() {
    int opcao;
    int id;
    char autor[100];
    NoLivro *livroEncontrado;

    do {
        printf("\n===== CONSULTA DE LIVROS =====\n");
        printf("1. Por codigo\n");
        printf("2. Por autor\n");
        printf("0. Voltar\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                printf("Informe o ID do livro: ");
                scanf("%d", &id);

                livroEncontrado = buscarLivro(raizLivros, id);

                if (livroEncontrado == NULL) {
                    printf("Livro nao encontrado!\n");
                } else {
                    exibirLivro(livroEncontrado->dados);
                }
                break;

            case 2: {
                int encontrou = 0;

                printf("Informe o autor: ");
                scanf(" %[^\n]", autor);

                consultarLivroPorAutor(raizLivros, autor, &encontrou);

                if (!encontrou) {
                    printf("Livro nao encontrado!\n");
                }

                break;
            }

            case 0:
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while(opcao != 0);
}

// ATUALIZAÇÃO 

void atualizarLivro() {
    int id;
    int opcao;
    NoLivro *livroEncontrado;

    printf("Informe o ID do livro que deseja atualizar: ");
    scanf("%d", &id);

    livroEncontrado = buscarLivro(raizLivros, id);

    if (livroEncontrado == NULL) {
        printf("Livro nao encontrado!\n");
        return;
    }

    printf("\nO que deseja alterar?\n");
    printf("1. Titulo\n");
    printf("2. Autor\n");
    printf("3. Ano\n");
    printf("Opcao: ");
    scanf("%d", &opcao);

    switch(opcao) {
        case 1:
            printf("Novo titulo: ");
            scanf(" %[^\n]", livroEncontrado->dados.titulo);
            break;

        case 2:
            printf("Novo autor: ");
            scanf(" %[^\n]", livroEncontrado->dados.autor);
            break;

        case 3:
            printf("Novo ano: ");
            scanf("%d", &livroEncontrado->dados.anoPublicacao);
            break;

        default:
            printf("Opcao invalida!\n");
            return;
    }

    printf("Livro atualizado com sucesso!\n");
}

// EXCLUSÃO

NoLivro* menorValor(NoLivro *raiz) {
    NoLivro *atual = raiz;

    while (atual->esq != NULL) {
        atual = atual->esq;
    }

    return atual;
}

NoLivro* excluirLivroArvore(NoLivro *raiz, int codigo) {
    if (raiz == NULL) {
        return NULL;
    }

    if (codigo < raiz->dados.codigo) {
        raiz->esq = excluirLivroArvore(raiz->esq, codigo);
    } else if (codigo > raiz->dados.codigo) {
        raiz->dir = excluirLivroArvore(raiz->dir, codigo);
    } else {
        if (raiz->dados.status == 1) {
            printf("Nao e possivel excluir. Livro esta emprestado.\n");
            return raiz;
        }

        if (raiz->esq == NULL || raiz->dir == NULL) {
            NoLivro *temp = raiz->esq ? raiz->esq : raiz->dir;

            if (temp == NULL) {
                temp = raiz;
                raiz = NULL;
            } else {
                *raiz = *temp;
            }

            free(temp);
        } else {
            NoLivro *temp = menorValor(raiz->dir);
            raiz->dados = temp->dados;
            raiz->dir = excluirLivroArvore(raiz->dir, temp->dados.codigo);
        }

        printf("Livro excluido com sucesso!\n");
    }

    if (raiz == NULL) {
        return NULL;
    }

    raiz->altura = 1 + max(altura(raiz->esq), altura(raiz->dir));

    int balance = fatorBalanceamento(raiz);

    if (balance > 1 && fatorBalanceamento(raiz->esq) >= 0)
        return rotacaoDireita(raiz);

    if (balance > 1 && fatorBalanceamento(raiz->esq) < 0) {
        raiz->esq = rotacaoEsquerda(raiz->esq);
        return rotacaoDireita(raiz);
    }

    if (balance < -1 && fatorBalanceamento(raiz->dir) <= 0)
        return rotacaoEsquerda(raiz);

    if (balance < -1 && fatorBalanceamento(raiz->dir) > 0) {
        raiz->dir = rotacaoDireita(raiz->dir);
        return rotacaoEsquerda(raiz);
    }

    return raiz;
}

void excluirLivro() {
    int id;

    printf("Informe o ID do livro que deseja excluir: ");
    scanf("%d", &id);

    if (buscarLivro(raizLivros, id) == NULL) {
        printf("Livro nao encontrado!\n");
        return;
    }

    raizLivros = excluirLivroArvore(raizLivros, id);
}

// EMPRÉSTIMO E DEVOLUÇÃO

void emprestarLivro() {
    int id;
    char email[100];
    NoLivro *livroEncontrado;

    printf("Informe o ID do livro: ");
    scanf("%d", &id);

    livroEncontrado = buscarLivro(raizLivros, id);

    if (livroEncontrado == NULL) {
        printf("Livro nao encontrado!\n");
        return;
    }

    if (livroEncontrado->dados.status == 1) {
        printf("Livro ja esta emprestado!\n");
        return;
    }

    printf("Informe o email do usuario: ");
    scanf(" %[^\n]", email);

    livroEncontrado->dados.status = 1;
    strcpy(livroEncontrado->dados.emprestadoPara, email);

    printf("Emprestimo realizado com sucesso!\n");
}

void devolverLivro() {
    int id;
    NoLivro *livroEncontrado;

    printf("Informe o ID do livro: ");
    scanf("%d", &id);

    livroEncontrado = buscarLivro(raizLivros, id);

    if (livroEncontrado == NULL) {
        printf("Livro nao encontrado!\n");
        return;
    }

    if (livroEncontrado->dados.status == 0) {
        printf("Este livro nao estava emprestado!\n");
        return;
    }

    livroEncontrado->dados.status = 0;
    strcpy(livroEncontrado->dados.emprestadoPara, "");

    printf("Devolucao realizada com sucesso!\n");
}

// LIBERAR MEMÓRIA

void liberarLivros(NoLivro *raiz) {
    if (raiz == NULL) {
        return;
    }

    liberarLivros(raiz->esq);
    liberarLivros(raiz->dir);
    free(raiz);
}