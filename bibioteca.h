// Bibliotecas 
#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

//Menus
void menuCadastro();
void menuConsulta();
void menuAtualizacao();
void menuExclusao();

//Livros
NoLivro* inserirArvoreLivros(NoLivro *raiz, livro novoLivro);
NoLivro* buscarLivro(NoLivro *raiz, int id);
void consultarLivroPorId(NoLivro *raiz);



#endif