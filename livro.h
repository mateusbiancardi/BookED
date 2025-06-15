#ifndef LIVRO_H_
#define LIVRO_H_

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