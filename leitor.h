/*
 *
 * Tad Leitor
 * Autores: Mateus Biancardi e Rafaela Capovilla
 *
 */

#ifndef LEITOR_H_
#define LEITOR_H_

#include "lista.h"
#include <stdio.h>
typedef struct leitor Leitor;
#define MAX_TAM_NOME 30
#define MAX_TAM_PREF 30

/**
 * @brief Inicializa uma nova estrutura Leitor.
 *
 * @return Um ponteiro para a estrutura Leitor inicializada.
 */
Leitor *inicializaLeitor();

/**
 * @brief Lê uma estrutura Leitor de um arquivo.
 *
 * Esta função tenta ler os dados de um objeto Leitor a partir do arquivo
 * especificado.
 *
 * @param l Ponteiro para uma estrutura Leitor onde os dados lidos serão
 * armazenados.
 * @param arquivo Ponteiro para o objeto FILE de onde ler.
 * @return int Retorna 1 se o Leitor foi lido com sucesso, 0 caso contrário.
 */
int leLeitorDoArquivo(Leitor *l, FILE *arquivo);

/**
 * @brief Obtém o ID único de um leitor.
 *
 * @param l Ponteiro para a estrutura Leitor da qual se deseja obter o ID.
 * @return O ID do leitor como um valor inteiro (int).
 */
int getIdLeitor(Leitor *l);

/**
 * @brief Obtém o nome de um leitor.
 *
 * @param l Ponteiro para a estrutura Leitor da qual se deseja obter o nome.
 * @return Ponteiro para a string (char*) contendo o nome do leitor.
 * @note O ponteiro retornado aponta para a memória interna da struct,
 * não devendo ser modificado ou liberado pelo chamador.
 */
char *getNome(Leitor *l);

/**
 * @brief Obtém a lista de preferências de gênero de um leitor.
 *
 * @param l Ponteiro para a estrutura Leitor.
 * @return Um ponteiro para o array de strings (char**) contendo as
 * preferências.
 * @note O ponteiro retornado e as strings contidas nele são gerenciados
 * pela struct Leitor e não devem ser liberados pelo chamador.
 */
char **getPreferencias(Leitor *l);

/**
 * @brief Busca um leitor em uma lista pelo seu ID.
 *
 * @param lista Ponteiro para a lista de leitores.
 * @param id O ID do leitor a ser buscado.
 * @return Leitor* Ponteiro para o Leitor encontrado, ou NULL se não existir na
 * lista.
 */
Leitor *getLeitorListaById(Lista *lista, int id);

/**
 * @brief Remove um leitor de uma lista com base no seu ID.
 *
 * @note Esta função remove a referência da lista, mas não libera a memória
 * da estrutura Leitor em si.
 *
 * @param lista Ponteiro para a lista de leitores.
 * @param id O ID do leitor a ser removido.
 * @return Leitor* Ponteiro para o Leitor que foi removido da lista.
 */
Leitor *removeLeitorLista(Lista *lista, int id);

/**
 * @brief Insere um leitor no final de uma lista de leitores.
 *
 * @param lista Ponteiro para a lista onde o leitor será inserido.
 * @param leitor Ponteiro para a estrutura Leitor a ser inserida.
 */
void insereLeitorLista(Lista *lista, Leitor *leitor);

/**
 * @brief Obtém a lista de livros lidos de um leitor.
 *
 * @param l Ponteiro para o leitor.
 * @return Lista* Ponteiro para a lista de livros lidos.
 */
Lista *getListaLivrosLidos(Leitor *l);

/**
 * @brief Obtém a lista de livros desejados de um leitor.
 *
 * @param l Ponteiro para o leitor.
 * @return Lista* Ponteiro para a lista de livros desejados.
 */
Lista *getListaLivrosDesejados(Leitor *l);

/**
 * @brief Obtém a lista de livros recomendados para um leitor.
 *
 * @param l Ponteiro para o leitor.
 * @return Lista* Ponteiro para a lista de livros recomendados.
 */
Lista *getListaLivrosRecomendados(Leitor *l);

/**
 * @brief Libera a memória alocada para a estrutura Leitor.
 *
 * Esta função libera toda a memória previamente alocada para um ponteiro do
 * tipo Leitor. Após a chamada desta função, o ponteiro passado não deve mais
 * ser utilizado.
 *
 * @param l Ponteiro para a estrutura Leitor a ser liberada.
 */
void liberaLeitor(Leitor *l);

/**
 * @brief Imprime as informações de um leitor.
 *
 * Esta função recebe um ponteiro para uma estrutura Leitor e exibe
 * seus dados formatados na saída padrão.
 *
 * @param l Ponteiro para a estrutura Leitor a ser impressa.
 */
void imprimeLeitor(Leitor *l);

#endif