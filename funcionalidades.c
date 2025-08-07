/*
 *
 * Tad Funcionalidades
 * Lê e processa os arquivos, implementando as funcinalidades do bookED
 * Autores: Mateus Biancardi e Rafaela Capovilla
 *
 */

#include "funcionalidades.h"
#include "leitor.h"
#include "lista.h"
#include "livro.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct funcionalidades {
  Lista *leitores;
  Lista *livros;
};

Funcionalidades *criaFuncionalidades() {
  Funcionalidades *func = (Funcionalidades *)calloc(1, sizeof(Funcionalidades));
  func->leitores = criaLista();
  func->livros = criaLista();

  return func;
}

void leArqLeitores(Funcionalidades *func, const char *path) {
  FILE *f = fopen(path, "r");
  if (!f) {
    perror("Erro ao abrir leitores.txt");
    exit(1);
  }

  //serve pra ignorar o cabeçalho do arquivo
  fscanf(f, "%*[^\n]\n");

  while (!feof(f)) {
    Leitor *l = inicializaLeitor();
    if (leLeitorDoArquivo(l, f)) {
      insereLeitorLista(func->leitores, l);
    } else {
      liberaLeitor(l); //libera se a leitura falhar
    }
  }
  fclose(f);
}

void leArqLivros(Funcionalidades *func, const char *path) {
  FILE *f = fopen(path, "r");
  if (!f) {
    perror("Erro ao abrir livros.txt");
    exit(1);
  }
  fscanf(f, "%*[^\n]\n");

  Livro *livro = inicializaLivro();
  while (leLivroDoArquivo(livro, f) == 5) { //evita quebra do programa

    //se a leitura funcionou, insere o livro na lista
    insereLivroLista(func->livros, livro);

    //prepara um novo livro em branco para a proxima iteração
    livro = inicializaLivro();
  }
  //pra liberar o ultimo livro em branco que não foi usado
  liberaLivro(livro);

  fclose(f);
}

int verificaAfinidades(Leitor *leitor1, Leitor *leitor2) {
  int nPrefs1 = getNPreferencia(leitor1);
  char **prefs1 = getPreferencias(leitor1);
  int nPrefs2 = getNPreferencia(leitor2);
  char **prefs2 = getPreferencias(leitor2);

  for (int i = 0; i < nPrefs1; i++) {
    for (int j = 0; j < nPrefs2; j++) {
      if (strcmp(prefs1[i], prefs2[j]) == 0) {
        return 1;
      }
    }
  }

  return 0;
}

void constroiAfinidades(Funcionalidades *func) {
  Celula *cel1 = getPrimeiraCelula(func->leitores);
  while (cel1 != NULL) {
    Leitor *leitor1 = (Leitor *)getItemFromCelula(cel1);

    //começa a comparação a partir do proximo leitor pra evitar duplicidades
    Celula *cel2 = getProximaCelula(cel1);

    while (cel2 != NULL) {
      Leitor *leitor2 = (Leitor *)getItemFromCelula(cel2);

      if (verificaAfinidades(leitor1, leitor2)) {
        insereLeitorLista(getListaAfinidades(leitor1), leitor2);
        insereLeitorLista(getListaAfinidades(leitor2), leitor1);
      }
      cel2 = getProximaCelula(cel2);
    }
    cel1 = getProximaCelula(cel1);
  }
}

//função auxiliar para verificar caminho de afinidade
static int temCaminhoAfinidade(Leitor *origem, Leitor *destino,
                               Lista *visitados) {
  if (origem == destino)
    return 1;

  insereLeitorLista(visitados, origem);

  Lista *afinidades = getListaAfinidades(origem);
  Celula *celulaVizinho = getPrimeiraCelula(afinidades);

  while (celulaVizinho != NULL) {
    Leitor *vizinho = (Leitor *)getItemFromCelula(celulaVizinho);
    //se o vizinho ainda nao foi visitado
    if (!getLeitorListaById(visitados, getIdLeitor(vizinho))) {
      if (temCaminhoAfinidade(vizinho, destino, visitados)) {
        return 1;
      }
    }
    celulaVizinho = getProximaCelula(celulaVizinho);
  }

  return 0;
}

int verificaAfinidadeTransitiva(Leitor *origem, Leitor *destino) {
  Lista *visitados = criaLista();

  int resultado = temCaminhoAfinidade(origem, destino, visitados);

  liberaLista(visitados, NULL);

  return resultado;
}

void ProcessaArqComandos(Funcionalidades *func, const char *commands_path,
                         const char *output_path) {
  FILE *f_in = fopen(commands_path, "r");
  if (!f_in) {
    perror("Erro ao abrir comandos.txt");
    exit(1);
  }
  FILE *f_out = fopen(output_path, "w");
  if (!f_out) {
    perror("Erro ao criar arquivo de saida");
    fclose(f_in);
    exit(1);
  }

  fscanf(f_in, "%*[^\n]\n");

  int id_func, id1, id2, id3;
  while (fscanf(f_in, "%d;%d;%d;%d", &id_func, &id1, &id2, &id3) == 4) {
    Leitor *leitor1 = getLeitorListaById(func->leitores, id1);
    Livro *livro = getLivroListaById(func->livros, id2);
    Leitor *leitor2 = getLeitorListaById(func->leitores, id3);

    switch (id_func) {
    case 1: //ADICIONAR LIVRO LIDO
      if (!leitor1) {
        fprintf(f_out, "Erro: Leitor com ID %d não encontrado\n", id1);
      } else if (!livro) {
        fprintf(f_out, "Erro: Livro com ID %d não encontrado\n", id2);
      } else {
        Lista *livrosLidos = getListaLivrosLidos(leitor1);
        if (verificaLivroListaExiste(livrosLidos, getIdLivro(livro))) {
          fprintf(f_out, "%s já leu \"%s\"\n", getNome(leitor1),
                  getTitulo(livro));
        } else {
          insereLivroLista(livrosLidos, livro);
          fprintf(f_out, "%s leu \"%s\"\n", getNome(leitor1), getTitulo(livro));
        }
      }
      break;

    case 2: //ADICIONAR LIVRO DESEJADO
      if (!leitor1) {
        fprintf(f_out, "Erro: Leitor com ID %d não encontrado\n", id1);
      } else if (!livro) {
        fprintf(f_out, "Erro: Livro com ID %d não encontrado\n", id2);
      } else {
        Lista *livrosDesejados = getListaLivrosDesejados(leitor1);
        if (verificaLivroListaExiste(livrosDesejados, getIdLivro(livro))) {
          fprintf(f_out, "%s já deseja ler \"%s\"\n", getNome(leitor1),
                  getTitulo(livro));
        } else {
          insereLivroLista(livrosDesejados, livro);
          fprintf(f_out, "%s deseja ler \"%s\"\n", getNome(leitor1),
                  getTitulo(livro));
        }
      }
      break;

    case 3: //RECOMENDAR UM LIVRO
      if (!leitor1) {
        fprintf(f_out, "Erro: Leitor recomendador com ID %d não encontrado\n",
                id1);
      } else if (!livro) {
        fprintf(f_out, "Erro: Livro com ID %d não encontrado\n", id2);
      } else if (!leitor2) {
        fprintf(f_out, "Erro: Leitor destinatário com ID %d não encontrado\n",
                id3);
      } else {
        Lista *livrosLidos = getListaLivrosLidos(leitor2);
        Lista *livrosDesejados = getListaLivrosDesejados(leitor2);
        if (verificaLivroListaExiste(livrosLidos, getIdLivro(livro))) {
          fprintf(f_out,
                  "%s não precisa da recomendação de \"%s\" pois já leu este "
                  "livro\n",
                  getNome(leitor2), getTitulo(livro));
        } else if (verificaLivroListaExiste(livrosDesejados,
                                            getIdLivro(livro))) {
          fprintf(
              f_out,

              "%s já deseja ler \"%s\", recomendação desnecessária\n",
              getNome(leitor2), getTitulo(livro));
        } else if (getIdLeitor(leitor1) == getIdLeitor(leitor2)) {
          fprintf(f_out, "%s não pode recomendar livros para si mesmo\n",
                  getNome(leitor1));
        } else {
          insereLivroLista(getListaLivrosRecomendados(leitor2), livro);
          fprintf(f_out, "%s recomenda \"%s\" para %s\n", getNome(leitor1),
                  getTitulo(livro), getNome(leitor2));
        }
      }
      break;

    case 4: //ACEITAR RECOMENDACAO
      //checa se as pessoas existem
      if (!leitor1) {
        fprintf(f_out, "Erro: Leitor com ID %d não encontrado\n", id1);
      } else if (!leitor2) {
        fprintf(f_out, "Erro: Leitor recomendador com ID %d não encontrado\n",
                id3);
      } else {
        //se as pessoas existem, tentamos executar a ação de remover a recomendação
        Livro *rec = removeLivroLista(getListaLivrosRecomendados(leitor1), id2);

        if (rec) {
          //sucesso
          if (!getLivroListaById(getListaLivrosDesejados(leitor1),
                                 getIdLivro(rec))) {
            insereLivroLista(getListaLivrosDesejados(leitor1), rec);
          }
          fprintf(f_out, "%s aceita recomendação \"%s\" de %s\n",
                  getNome(leitor1), getTitulo(rec), getNome(leitor2));
        } else {
          //falha
          fprintf(f_out,
                  "%s não possui recomendação do livro ID %d feita por %s\n",
                  getNome(leitor1), id2, getNome(leitor2));
        }
      }
      break;

    case 5: //REJEITAR RECOMENDACAO
      if (!leitor1) {
        fprintf(f_out, "Erro: Leitor com ID %d não encontrado\n", id1);
      } else if (!leitor2) {
        fprintf(f_out, "Erro: Leitor recomendador com ID %d não encontrado\n",
                id3);
      } else {
        Livro *remov =
            removeLivroLista(getListaLivrosRecomendados(leitor1), id2);

        if (remov) {
          fprintf(f_out, "%s rejeita recomendação \"%s\" de %s\n",
                  getNome(leitor1), getTitulo(remov), getNome(leitor2));
        } else {
          fprintf(f_out,
                  "%s não possui recomendação do livro ID %d feita por %s\n",
                  getNome(leitor1), id2, getNome(leitor2));
        }
      }
      break;

    case 6: //DESCOBRIR LIVROS EM COMUM
      if (!leitor1) {
        fprintf(f_out, "Erro: Leitor com ID %d não encontrado\n", id1);
      } else if (!leitor2) {
        fprintf(f_out, "Erro: Leitor com ID %d não encontrado\n", id3);
      } else {
        fprintf(f_out, "Livros em comum entre %s e %s: ", getNome(leitor1),
                getNome(leitor2));
        Lista *lidos1 = getListaLivrosLidos(leitor1);
        Lista *lidos2 = getListaLivrosLidos(leitor2);
        Celula *cel = getPrimeiraCelula(lidos1);
        int achou = 0;
        char buffer[1024] = {0};
        while (cel) {
          Livro *livroComum = (Livro *)getItemFromCelula(cel);
          if (getLivroListaById(lidos2, getIdLivro(livroComum))) {
            if (achou)
              strcat(buffer, ", ");
            strcat(buffer, getTitulo(livroComum));
            achou = 1;
          }
          cel = getProximaCelula(cel);
        }
        if (achou) {
          fprintf(f_out, "%s\n", buffer);
        } else {
          fprintf(f_out, "Nenhum livro em comum\n");
        }
      }
      break;

    case 7: //VERIFICAR CAMINHO DE AFINIDADE
      if (!leitor1) {
        fprintf(f_out, "Erro: Leitor com ID %d não encontrado\n", id1);
      } else if (!leitor2) {
        fprintf(f_out, "Erro: Leitor com ID %d não encontrado\n", id3);
      } else {
        if (verificaAfinidadeTransitiva(leitor1, leitor2)) {
          fprintf(f_out, "Existe afinidade entre %s e %s\n", getNome(leitor1),
                  getNome(leitor2));
        } else {
          fprintf(f_out, "Não existe afinidade entre %s e %s\n",
                  getNome(leitor1), getNome(leitor2));
        }
      }
      break;

    case 8: //IMPRIMIR BOOKED
      fprintf(f_out, "Imprime toda a BookED\n\n");
      Celula *celLeitor = getPrimeiraCelula(func->leitores);
      while (celLeitor) {
        Leitor *l = (Leitor *)getItemFromCelula(celLeitor);
        fprintf(f_out, "Leitor: %s\n", getNome(l));
        Celula *celItem;
        int primeiro;
        fprintf(f_out, "Lidos: ");
        celItem = getPrimeiraCelula(getListaLivrosLidos(l));
        primeiro = 1;

        while (celItem) {
          if (!primeiro)
            fprintf(f_out, ", ");
          fprintf(f_out, "%s", getTitulo(getItemFromCelula(celItem)));
          primeiro = 0;
          celItem = getProximaCelula(celItem);
        }

        fprintf(f_out, "\n");
        fprintf(f_out, "Desejados: ");
        celItem = getPrimeiraCelula(getListaLivrosDesejados(l));
        primeiro = 1;

        while (celItem) {
          if (!primeiro)
            fprintf(f_out, ", ");
          fprintf(f_out, "%s", getTitulo(getItemFromCelula(celItem)));
          primeiro = 0;
          celItem = getProximaCelula(celItem);
        }

        fprintf(f_out, "\n");
        fprintf(f_out, "Recomendacoes: ");
        celItem = getPrimeiraCelula(getListaLivrosRecomendados(l));
        primeiro = 1;

        while (celItem) {
          if (!primeiro)
            fprintf(f_out, ", ");
          fprintf(f_out, "%s", getTitulo(getItemFromCelula(celItem)));
          primeiro = 0;
          celItem = getProximaCelula(celItem);
        }

        fprintf(f_out, "\n");
        fprintf(f_out, "Afinidades: ");
        celItem = getPrimeiraCelula(getListaAfinidades(l));
        primeiro = 1;

        while (celItem) {
          if (!primeiro)
            fprintf(f_out, ", ");
          fprintf(f_out, "%s", getNome(getItemFromCelula(celItem)));
          primeiro = 0;
          celItem = getProximaCelula(celItem);
        }

        fprintf(f_out, "\n\n");
        celLeitor = getProximaCelula(celLeitor);
      }
      break;

    default:
      fprintf(f_out, "Erro: Comando %d não reconhecido\n", id_func);
      break;
    }
  }

  fclose(f_in);
  fclose(f_out);
}

//funções auxiliares para liberar os itens das listas principais
static void liberaLeitorCallback(void *item) { liberaLeitor((Leitor *)item); }
static void liberaLivroCallback(void *item) { liberaLivro((Livro *)item); }

void liberaFuncionalidades(Funcionalidades *func) {
  if (!func) {
    return;
  }

  liberaLista(func->leitores, liberaLeitorCallback);
  liberaLista(func->livros, liberaLivroCallback);
  free(func);
}