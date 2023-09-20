// Created by grace on 17/09/2023.
#include "cofo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//---------------------------------------------------------------------------------
gCofo *criarCofo(int max_itens) {
    if (max_itens > 0) {
        gCofo *cofo = (gCofo *)malloc(sizeof(gCofo));

        if (cofo != NULL) {
            cofo->item = (void **)malloc(sizeof(void *) * max_itens);

            if (cofo->item != NULL) {
                cofo->num_itens = 0;
                cofo->max_itens = max_itens;
                cofo->current = -1;
                return cofo;
            }
            free(cofo); // Libere o cofo se a alocação de cofo->item falhar.
        }
        free(cofo); // Libere o cofo se a alocação de cofo falhar.
    }
    return NULL;
}
//--------------------------------------------------------------------------------------
int inserirNoCofo(gCofo *cofo, void *item) {
    if (cofo != NULL && cofo->num_itens < cofo->max_itens) {
        cofo->item[cofo->num_itens] = item;
        cofo->num_itens++;
        return TRUE;
    }
    return FALSE;
}
//---------------------------------------------------------------------------------------
void *removerDoCofo(gCofo *cofo, void *chave1, void *chave2, void *chave3, int (*cmp)(void *, void *, void *, void *)) {
    if (cofo != NULL && cofo->num_itens > 0) {
        void *dado = NULL;
        int i;
        for (i = 0; i < cofo->num_itens; i++) {
            if (cmp(cofo->item[i], chave1, chave2, chave3) == TRUE) {
                dado = cofo->item[i];
                for (int j = i; j < cofo->num_itens - 1; j++) {
                    cofo->item[j] = cofo->item[j + 1];
                }
                cofo->num_itens--; // Mova esta linha para fora do loop for
                break; // Saia do loop após encontrar o elemento.
            }
        }
        return dado;
    }
    return NULL;
}
//---------------------------------------------------------------------------------------

void *consultarElemento(gCofo *cofo, char nome[30], int idade, float nota) {
    if (cofo != NULL) {
        for (int i = 0; i < cofo->num_itens; i++) {
            Aluno *b = (Aluno *)cofo->item[i];
            int comparacao = strcmp(nome, b->nome);

            if (comparacao == 0 && b->idade == idade && b->nota == nota) {
                return cofo->item[i];
            }
        }
    }
    return NULL;
}
//-------------------------------------------------------------------------------------

void **listarElementos(gCofo *cofo) {
    if (cofo != NULL && cofo->num_itens > 0) {
        void **elementos = (void **)malloc(sizeof(void *) * cofo->num_itens);
        if (elementos != NULL) {
            for (int i = 0; i < cofo->num_itens; i++) {
                cofo->current = i;
                elementos[i] = cofo->item[cofo->current];
            }
            return elementos;
        }
    }
    return NULL;
}
//-----------------------------------------------------------------------------------
int destruirCofo(gCofo *cofo) {
    if (cofo != NULL) {
        free(cofo->item);
        free(cofo);
        return TRUE;
    }
    return FALSE;
}

//------------------------------------------------------------------------------------

int esvaziarCofo(gCofo *cofo) {
    if (cofo != NULL) {
        free(cofo->item);
        cofo->num_itens = 0;
        return TRUE;
    }
    return FALSE;
}
//------------------------------------------------------------------------------------
