/*
 *
 * Tad Funcionalidades
 * Lê e processa os arquivos, implementando as funcinalidades do bookED
 * Autores: Mateus Biancardi e Rafaela Capovilla
 *
 */

#ifndef FUNCIONALIDADES_H_
#define FUNCIONALIDADES_H_

#include "leitor.h"
#include "livro.h"


typedef struct funcionalidades Funcionalidades;

/**
 * @brief Cria e inicializa a estrutura principal das funcionalidades do bookED.
 * @return Ponteiro para a estrutura funcionalidades.
 */
Funcionalidades *criaFuncionalidades();

/**
 * @brief Processa os leitores do arquivo 'leitores.txt'.
 * @param func Ponteiro para a estrutura funcionalidades.
 * @param path Caminho do arquivo de leitores.
 */
void leArqLeitores(Funcionalidades *func, const char *path);

/**
 * @brief Processa os livros do arquivo 'livros.txt'.
 * @param func Ponteiro para a estrutura funcionalidades.
 * @param path Caminho do arquivo de livros.
 */
void leArqLivros(Funcionalidades *func, const char *path);

/**
 * @brief Constrói a rede de afinidades entre os leitores com base em
 * preferências de gênero em comum.
 * @param func Ponteiro para a estrutura funcionalidades.
 */
void constroiAfinidades(Funcionalidades *func);

/**
 * @brief Processa o arquivo de comandos e gera o arquivo de saída.
 * @param func Ponteiro para a estrutura funcionalidades.
 * @param commands_path Caminho para o arquivo 'comandos.txt'.
 * @param output_path Caminho para o arquivo 'saida.txt' a ser gerado.
 */
void ProcessaArqComandos(Funcionalidades *func, const char *commands_path,
                             const char *output_path);

/**
 * @brief Libera toda a memória alocada pela funcionalidade, incluindo leitores e livros.
 * @param func Ponteiro para a estrutura funcionalidades.
 */
void liberaFuncionalidades(Funcionalidades *func);

#endif // FUNCIONALIDADES_H_