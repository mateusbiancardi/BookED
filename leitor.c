/*
 *
 * Tad Leitor
 * Autores: Mateus Biancardi e Rafaela Capovilla
 *
 */

#include "leitor.h"
#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct leitor {
  int id;
  char nome[MAX_TAM_NOME];
  int nPreferencias;
  char **preferencias;
  Lista *livrosLidos;
  Lista *livrosDesejados;
  Lista *livrosRecomendados;
  Lista *afinidades;
};

Leitor *inicializaLeitor() {
  Leitor *l = calloc(1, sizeof(Leitor));

  l->id = 0;
  l->nPreferencias = 0;
  l->preferencias = NULL;
  l->livrosLidos = criaLista();
  l->livrosDesejados = criaLista();
  l->livrosRecomendados = criaLista();
  l->afinidades = criaLista();

  return l;
};

//funcao auxiliar pra remover espaços do inicio e fim de uma string
static char* trim(char* str) {
    char* end;
    //remove espaço do inicio
    while (isspace((unsigned char)*str)) str++;

    if (*str == 0) return str; //se a string for so espaços

    //remove espaço do fim
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;

    //adiciona nulo pra terminar
    *(end + 1) = '\0';

    return str;
}

int leLeitorDoArquivo(Leitor *l, FILE *arquivo) {
    char linha_inteira[256];

    //primeiro tenta ler a linha inteira, e se falhar é o fim do arquivo
    if (fgets(linha_inteira, sizeof(linha_inteira), arquivo) == NULL) {
        return 0; //fim da leitura
    }

    char *token;
    
    token = strtok(linha_inteira, ";\n\r");
    if (token == NULL) return 0;
    l->id = atoi(token);

    token = strtok(NULL, ";\n\r");
    if (token == NULL) return 0;
    strncpy(l->nome, token, MAX_TAM_NOME - 1);
    l->nome[MAX_TAM_NOME - 1] = '\0';

    token = strtok(NULL, ";\n\r");
    if (token == NULL) return 0;
    l->nPreferencias = atoi(token);

    l->preferencias = malloc(l->nPreferencias * sizeof(char *));

    for (int i = 0; i < l->nPreferencias; i++) {
        token = strtok(NULL, ";\n\r");
        if (token != NULL) {
            //Limpamos o token para remover espaços
            char* token_limpo = trim(token);
            //Salvamos a versão limpa
            l->preferencias[i] = strdup(token_limpo);
        } else {
            l->nPreferencias = i;
            break;
        }
    }

    return 1;
}

int getIdLeitor(Leitor *l) { return l->id; };
char *getNome(Leitor *l) { return l->nome; }
char **getPreferencias(Leitor *l) { return l->preferencias; }

int comparaIdLeitor(void *idPtr, void *leitorPtr) {
  int id = *(int *)idPtr;
  Leitor *leitor = (Leitor *)leitorPtr;
  return id == leitor->id;
}

Leitor *getLeitorListaById(Lista *lista, int id) {
  return (Leitor *)getItemLista(lista, &id, comparaIdLeitor);
}

int verificaLeitorListaExiste(Lista *l, int id) {
  return verificaItemListaExiste(l, &id, comparaIdLeitor);
}

Leitor *removeLeitorLista(Lista *lista, int id) {
  Leitor *leitor = removeItemLista(lista, &id, comparaIdLeitor);
  return leitor;
}

void insereLeitorLista(Lista *lista, Leitor *leitor) {
  insereItemLista(lista, leitor);
}

Lista *getListaLivrosLidos(Leitor *l) { return l->livrosLidos; };

Lista *getListaLivrosDesejados(Leitor *l) { return l->livrosDesejados; };

Lista *getListaLivrosRecomendados(Leitor *l) { return l->livrosRecomendados; };

Lista *getListaAfinidades(Leitor *l) { return l->afinidades; }

void liberaLeitor(Leitor *l) {
  if (l == NULL)
    return;

  for (int i = 0; i < l->nPreferencias; i++) {
    free(l->preferencias[i]);
  }
  free(l->preferencias);
  //passando NULL pra não liberar os livros pq eles vão ser liberados em outro lugar
  liberaLista(l->livrosLidos, NULL);
  liberaLista(l->livrosDesejados, NULL);
  liberaLista(l->livrosRecomendados, NULL);
  liberaLista(l->afinidades, NULL);
  free(l);
};

int getNPreferencia(Leitor *l) { return l->nPreferencias; }