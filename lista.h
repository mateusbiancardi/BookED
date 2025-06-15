/*
 *
 * Lista Duplamente Encadeada para itens genéricos
 * Autores: Mateus Biancardi e Rafaela Capovilla
 *
 */

#ifndef LISTA_H
#define LISTA_H

typedef struct celula Celula;
typedef struct lista Lista;

/**
 * @brief Cria e inicializa uma nova lista duplamente encadeada vazia.
 *
 * @return Um ponteiro para a estrutura Lista recém-alocada.
 */
Lista *criaLista();

/**
 * @brief Insere um novo item no final da lista.
 *
 * @param l Ponteiro para a lista na qual o item será inserido.
 * @param item Ponteiro genérico (void*) para o dado a ser armazenado. A lista
 * armazena apenas o ponteiro, não uma cópia do dado.
 */
void insereItemLista(Lista *l, void *item);

/**
 * @brief Remove um item da lista com base em uma chave de busca.
 *
 * A busca é realizada por uma função de comparação fornecida pelo usuário.
 * A célula da lista é liberada, mas o item contido nela não é.
 *
 * @param l Ponteiro para a lista da qual o item será removido.
 * @param id Ponteiro para uma chave de busca a ser passada para a função de
 * comparação.
 * @param c Ponteiro para a função de comparação. A função deve receber a chave
 * (id) e um item da lista, retornando 1 em caso de correspondência.
 * @return O ponteiro (void*) para o item que foi removido, ou NULL se não for
 * encontrado.
 */
void *removeItemLista(Lista *l, void *id, int (*c)(void *id, void *item));

/**
 * @brief Libera toda a memória associada à lista, incluindo suas células.
 *
 * Opcionalmente, pode liberar a memória de cada item armazenado se uma função
 * para isso for fornecida.
 *
 * @param l Ponteiro para a lista a ser liberada.
 * @param liberaItem Ponteiro para uma função que libera a memória de um item.
 * Se for NULL, a memória dos itens não será liberada por esta função.
 */
void liberaLista(Lista *l, void (*liberaItem)(void *item));

/**
 * @brief Retorna um ponteiro para a primeira célula da lista.
 *
 * @param l Ponteiro para a lista.
 * @return Um ponteiro para a primeira célula, ou NULL se a lista estiver vazia.
 */
Celula *getPrimeiraCelula(Lista *l);

/**
 * @brief Retorna um ponteiro para a última célula da lista.
 *
 * @param l Ponteiro para a lista.
 * @return Um ponteiro para a última célula, ou NULL se a lista estiver vazia.
 */
Celula *getUltimaCelula(Lista *l);

/**
 * @brief Retorna um ponteiro para a célula seguinte a uma célula fornecida.
 *
 * @param c Ponteiro para a célula atual.
 * @return Um ponteiro para a próxima célula, ou NULL se não houver próxima.
 */
Celula *getProximaCelula(Celula *c);

/**
 * @brief Retorna um ponteiro para a célula anterior a uma célula fornecida.
 *
 * @param c Ponteiro para a célula atual.
 * @return Um ponteiro para a célula anterior, ou NULL se não houver anterior.
 */
Celula *getAnteriorCelula(Celula *c);

/**
 * @brief Retorna o ponteiro para o item genérico armazenado em uma célula.
 *
 * @param c Ponteiro para a célula da qual se deseja obter o item.
 * @return O ponteiro (void*) para o item armazenado.
 */
void *getItemFromCelula(Celula *c);

#endif // LISTA_H