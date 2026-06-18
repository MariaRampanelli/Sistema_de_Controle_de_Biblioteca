// Bibliotecas 
#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

void menuCadastro();
void menuConsulta();
void menuAtualizacao();
void menuExclusao();

void cadastrarLivro();
void cadastrarUsuario();

void consultarLivroPorCodigo();
void consultarLivroPorAutor();
void consultarUsuarioPorEmail();
void consultarUsuarioPorNome();
void consultarEmprestimosUsuario();

void atualizarLivro();
void atualizarUsuario();

void excluirLivro();
void excluirUsuario();

void emprestarLivro();
void devolverLivro();

void criarListaLivros();
void criarListaUsuarios();
void inserirLivro();
void inserirUsuario();
void buscarLivro();
void buscarUsuario();
void removerLivro();
void removerUsuario();
void liberarMemoria();
#endif