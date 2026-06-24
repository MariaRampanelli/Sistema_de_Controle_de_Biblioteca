// Bibliotecas 
#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

typedef struct Usuario {
    char email[100];
    char nome[100];
} usuario;

typedef struct Livro {
    char titulo[100];
    char autor[100];
    int anoPublicacao;
    int codigo;
    int status;
    char emprestadoPara[100];
} livro;

typedef struct NoLivro {
    livro dados;
    struct NoLivro *esq;
    struct NoLivro *dir;
    int altura;
} NoLivro;


//Menus
void menuCadastro();
void menuConsulta();
void menuAtualizacao();
void menuExclusao();

//usuários
/* void cadastrarUsuario();
void consultarUsuarioPorEmail();
void consultarEmprestimosUsuario();
void atualizarUsuario();
void excluirUsuario(); */

//Livros
int altura(NoLivro *n);
int max(int a, int b);
int fatorBalanceamento(NoLivro *n);
NoLivro* rotacaoDireita(NoLivro *y);
NoLivro* rotacaoEsquerda(NoLivro *x);
NoLivro* inserirArvoreLivros(NoLivro *raiz, livro novoLivro);
NoLivro* buscarLivro(NoLivro *raiz, int id);
void exibirLivro(livro l);
void menuConsultaLivros();
void consultarLivroPorAutor(NoLivro *raiz, char autor[], int *encontrou);
void atualizarLivro();
void excluirLivro();
NoLivro* excluirLivroArvore(NoLivro *raiz, int codigo);
NoLivro* menorValor(NoLivro *raiz);
void emprestarLivro();
void devolverLivro();
void liberarLivros(NoLivro *raiz);

#endif