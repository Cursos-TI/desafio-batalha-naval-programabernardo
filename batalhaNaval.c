#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 5  // Tamanho do tabuleiro 5x5
#define AGUA '~'
#define NAVIO 'N'
#define ACERTO 'X'
#define ERRO 'O'

// Função para inicializar os tabuleiros
void inicializarTabuleiro(char tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

// Função para exibir o tabuleiro
void mostrarTabuleiro(char tabuleiro[TAM][TAM], int esconderNavios) {
    printf("  ");
    for (int i = 0; i < TAM; i++) printf("%d ", i);
    printf("\n");

    for (int i = 0; i < TAM; i++) {
        printf("%d ", i);
        for (int j = 0; j < TAM; j++) {
            if (esconderNavios && tabuleiro[i][j] == NAVIO)
                printf("%c ", AGUA); // esconde os navios
            else
                printf("%c ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// Posiciona os navios aleatoriamente
void posicionarNavios(char tabuleiro[TAM][TAM], int quantidade) {
    int i = 0;
    while (i < quantidade) {
        int x = rand() % TAM;
        int y = rand() % TAM;
        if (tabuleiro[x][y] == AGUA) {
            tabuleiro[x][y] = NAVIO;
            i++;
        }
    }
}

// Função de ataque
int atacar(char tabuleiro[TAM][TAM], int x, int y) {
    if (tabuleiro[x][y] == NAVIO) {
        tabuleiro[x][y] = ACERTO;
        return 1;
    } else if (tabuleiro[x][y] == AGUA) {
        tabuleiro[x][y] = ERRO;
    }
    return 0;
}

// Contar navios restantes
int contarNavios(char tabuleiro[TAM][TAM]) {
    int count = 0;
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            if (tabuleiro[i][j] == NAVIO)
                count++;
    return count;
}

int main() {
    char player[TAM][TAM], computador[TAM][TAM];
    int x, y;
    int navios = 3;

    srand(time(NULL));

    inicializarTabuleiro(player);
    inicializarTabuleiro(computador);

    posicionarNavios(player, navios);
    posicionarNavios(computador, navios);

    printf("=== BATALHA NAVAL ===\n");

    while (1) {
        printf("\nSeu Tabuleiro:\n");
        mostrarTabuleiro(player, 0);

        printf("\nTabuleiro do Computador:\n");
        mostrarTabuleiro(computador, 1);

        printf("\nInforme as coordenadas para atacar (linha e coluna): ");
        scanf("%d %d", &x, &y);

        if (x < 0 || x >= TAM || y < 0 || y >= TAM) {
            printf("Coordenadas inválidas. Tente novamente.\n");
            continue;
        }

        if (computador[x][y] == ACERTO || computador[x][y] == ERRO) {
            printf("Você já atacou essa posição.\n");
            continue;
        }

        if (atacar(computador, x, y)) {
            printf("Acertou um navio!\n");
        } else {
            printf("Água!\n");
        }

        // Jogada do computador
        x = rand() % TAM;
        y = rand() % TAM;
        atacar(player, x, y);

        // Verificar fim de jogo
        if (contarNavios(computador) == 0) {
            printf("\nVocê venceu!\n");
            break;
        } else if (contarNavios(player) == 0) {
            printf("\nO computador venceu!\n");
            break;
        }
    }

    printf("\nTabuleiro final do Computador:\n");
    mostrarTabuleiro(computador, 0);

    return 0;
}