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