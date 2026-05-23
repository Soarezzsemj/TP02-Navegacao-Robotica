#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "caminho.h"

static Posicao *CriarPosicao(int x, int y) {
    Posicao *pos = malloc(sizeof(Posicao));

    if (!pos) {
        return NULL;
    }

    pos->X = x;
    pos->Y = y;
    pos->Proximo = NULL;

    return pos;
}

static Comando *CriarComando(char direcao) {
    Comando *cmd = malloc(sizeof(Comando));

    if (!cmd) {
        return NULL;
    }

    cmd->Direcao = direcao;
    cmd->Proximo = NULL;

    return cmd;
}

Caminho *InicializarCaminho(const char *Sequencia, int xInicial, int yInicial) {
    if (!Sequencia) {
        return NULL;
    }

    Caminho *caminho = malloc(sizeof(Caminho));

    if (!caminho) {
        return NULL;
    }

    caminho->Instrucoes = NULL;
    caminho->N = 0;

    Posicao *inicio = CriarPosicao(xInicial, yInicial);

    if (!inicio) {
        free(caminho);
        return NULL;
    }

    caminho->Inicio = inicio;
    caminho->Historico = inicio;
    caminho->Fim = inicio;

    Posicao *posAtual = inicio;
    Comando *cmdAtual = NULL;

    int x = xInicial;
    int y = yInicial;

    for (int i = 0; Sequencia[i] != '\0'; i++) {

        char movimento = Sequencia[i];

        if (movimento != 'N' &&
            movimento != 'S' &&
            movimento != 'L' &&
            movimento != 'O') {

            DestruirCaminho(caminho);
            return NULL;
        }

        Comando *novoCmd = CriarComando(movimento);

        if (!novoCmd) {
            DestruirCaminho(caminho);
            return NULL;
        }

        if (!caminho->Instrucoes) {
            caminho->Instrucoes = novoCmd;
        } else {
            cmdAtual->Proximo = novoCmd;
        }

        cmdAtual = novoCmd;

        if (movimento == 'N') {
            y++;
        } else if (movimento == 'S') {
            y--;
        } else if (movimento == 'L') {
            x++;
        } else {
            x--;
        }

        Posicao *novaPosicao = CriarPosicao(x, y);

        if (!novaPosicao) {
            DestruirCaminho(caminho);
            return NULL;
        }

        posAtual->Proximo = novaPosicao;
        posAtual = novaPosicao;

        caminho->N++;
    }

    caminho->Fim = posAtual;

    return caminho;
}

void DestruirCaminho(Caminho *C) {
    if (!C) {
        return;
    }

    Comando *cmd = C->Instrucoes;

    while (cmd) {
        Comando *proxCmd = cmd->Proximo;
        free(cmd);
        cmd = proxCmd;
    }

    Posicao *pos = C->Historico;

    while (pos) {
        Posicao *proxPos = pos->Proximo;
        free(pos);
        pos = proxPos;
    }

    free(C);
}

Posicao *DeterminarFim(Caminho *C) {
    if (!C) {
        return NULL;
    }

    return C->Fim;
}

Posicao *HistoricoPosicoes(Caminho *C) {
    if (!C) {
        return NULL;
    }

    return C->Historico;
}

int CalcularDistanciaTotal(Caminho *C) {
    if (!C) {
        return -1;
    }

    return C->N;
}

double CalcularDistanciaGeometrica(Caminho *C) {
    if (!C || !C->Inicio || !C->Fim) {
        return -1.0;
    }

    double deltaX = C->Fim->X - C->Inicio->X;
    double deltaY = C->Fim->Y - C->Inicio->Y;

    return sqrt((deltaX * deltaX) + (deltaY * deltaY));
}

int CalcularDistanciaManhattan(Caminho *C) {
    if (!C || !C->Inicio || !C->Fim) {
        return -1;
    }

    int diferencaX = abs(C->Fim->X - C->Inicio->X);
    int diferencaY = abs(C->Fim->Y - C->Inicio->Y);

    return diferencaX + diferencaY;
}

int ContarInstrucoes(Caminho *C) {
    if (!C) {
        return -1;
    }

    return C->N;
}