/*
 *
 * Tad Livro
 * Autores: Mateus Biancardi e Rafaela Capovilla
 *
 */

#ifndef LIVRO_H_
#define LIVRO_H_

#include "lista.h"
#include <stdio.h>
typedef struct livro Livro;

/**
 * @brief Inicializa uma nova estrutura do tipo Livro.
 *
 * @return Ponteiro para a estrutura Livro inicializada.
 */
Livro *inicializaLivro();

/**
 * @brief Lê uma estrutura Livro de um arquivo.
 *
 * Esta função lê os dados de uma estrutura Livro a partir do ponteiro de
 * arquivo fornecido.
 *
 * @param l Ponteiro para uma estrutura Livro onde os dados lidos serão
 * armazenados.
 * @param arquivo Ponteiro para o objeto FILE de onde ler.
 * @return int Retorna 1 se o Livro foi lido com sucesso, 0 caso contrário.
 */

int leLivroDoArquivo(Livro *l, FILE *arquivo);

/**
 * @brief Recupera o ID do Livro fornecido.
 *
 * @param l Ponteiro para uma estrutura Livro.
 * @return int O ID do Livro.
 */
int getIdLivro(Livro *l);

/**
 * @brief Obtém o título de um livro.
 *
 * @param l Ponteiro para a estrutura Livro da qual se deseja obter o título.
 * @return Ponteiro para a string (char*) contendo o título.
 * @note O ponteiro retornado aponta para a memória interna da struct,
 * não devendo ser modificado ou liberado pelo chamador.
 */
char *getTitulo(Livro *l);

/**
 * @brief Obtém o autor de um livro.
 *
 * @param l Ponteiro para a estrutura Livro da qual se deseja obter o autor.
 * @return Ponteiro para a string (char*) contendo o nome do autor.
 * @note O ponteiro retornado aponta para a memória interna da struct,
 * não devendo ser modificado ou liberado pelo chamador.
 */
char *getAutor(Livro *l);

/**
 * @brief Obtém o gênero de um livro.
 *
 * @param l Ponteiro para a estrutura Livro da qual se deseja obter o gênero.
 * @return Ponteiro para a string (char*) contendo o gênero do livro.
 * @note O ponteiro retornado aponta para a memória interna da struct,
 * não devendo ser modificado ou liberado pelo chamador.
 */
char *getGenero(Livro *l);

/**
 * @brief Obtém o ano de publicação de um livro.
 *
 * @param l Ponteiro para a estrutura Livro da qual se deseja obter o ano.
 * @return O ano de publicação como um valor inteiro (int).
 */
int getAno(Livro *l);

/**
 * @brief Busca um livro em uma lista pelo seu ID.
 *
 * Utiliza a função genérica de busca da lista, passando uma função de
 * comparação específica para IDs de livros.
 *
 * @param lista Ponteiro para a lista de livros onde a busca será realizada.
 * @param id O ID do livro a ser buscado.
 * @return Livro* Ponteiro para o Livro encontrado, ou NULL se não existir na
 * lista.
 */
Livro *getLivroListaById(Lista *lista, int id);

/**
 * @brief Remove um livro de uma lista com base no seu ID.
 *
 * @note Esta função remove a referência da lista (a célula), mas não libera
 * a memória da estrutura `Livro` em si, que pode estar sendo usada em outras
 * listas.
 *
 * @param lista Ponteiro para a lista de onde o livro será removido.
 * @param id O ID do livro a ser removido.
 * @return Livro* Ponteiro para o Livro que foi removido da lista.
 */
Livro *removeLivroLista(Lista *lista, int id);

/**
 * @brief Insere um livro no final de uma lista.
 *
 * Esta é uma função "wrapper" que simplifica a chamada para a função genérica
 * de inserção da lista.
 *
 * @param lista Ponteiro para a lista onde o livro será inserido.
 * @param livro Ponteiro para a estrutura `Livro` a ser inserida.
 */
void insereLivroLista(Lista *lista, Livro *livro);

/**
 * @brief Libera a memória alocada para a estrutura Livro.
 *
 * @param l Ponteiro para a estrutura Livro a ser liberada.
 */
void liberaLivro(Livro *l);

/**
 * @brief Imprime as informações de um livro.
 *
 * Esta função recebe um ponteiro para uma estrutura Livro e exibe
 * seus dados formatados na saída padrão.
 *
 * @param l Ponteiro para a estrutura Livro a ser impressa.
 */
void imprimeLivro(Livro *l);

#endif // LIVRO_H_