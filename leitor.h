#ifndef LEITOR_H_
#define LEITOR_H_

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