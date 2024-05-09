#include <stdio.h>
#include <stdbool.h>

// -------------------------------------------------------------

// cria o tabuleiro com as peças nas posições iniciais
void cria_tabuleiro(int tabuleiro[8][8]) {
    int i, j;

    for (i = 0; i < 8; i++)
    {
        for (j = 0; j < 8; j++)
        {
            tabuleiro[i][j] = ' ';
        }
    }

    tabuleiro[3][3] = 'B';
    tabuleiro[4][4] = 'B';
    tabuleiro[3][4] = 'P';
    tabuleiro[4][3] = 'P';
}

// -------------------------------------------------------------

// mostra o tabuleiro com as coordenadas
void mostra_tabuleiro(int tabuleiro[8][8]) {
    int i,j;

    printf("  ");

    // mostra as coordenadas na linha superior
    for (i = 0; i < 8; i++)
    {
        printf("%d ", i);
    }

    printf("\n");

    // mostra as peças e as coordenadas nas demais linhas
    for (i = 0; i < 8; i++)
    {
        printf("%d ", i);
        for (j = 0; j < 8; j++)
        {
            // verifica qual caracter colocar em cada posicao
            switch (tabuleiro[i][j])
            {
                case ' ':
                    printf("- ");
                    break;
                case 'P':
                    printf("P ");
                    break;
                case 'B':
                    printf("B ");
                    break;
            }
        }
        printf("\n");
    }
}

// -------------------------------------------------------------

// aqui vai a funcao para ver se a jogada eh valida

// -------------------------------------------------------------

// aqui vai a funcao para verificar se tem jogadas validas e quem ganhou

// -------------------------------------------------------------

// verifica se a jogada eh valida e registra ela na matriz
void jogada(int tabuleiro[8][8], char jogador) {
    char adversario;
    int linha, coluna;

    // forca a comecar com as pecas pretas
    jogador = 'P';

    while (true) {
        // recebe as coordenadas da jogada
        printf("\nJogador %c, insira a linha e a coluna da sua jogada separadas por um espaco:", jogador);
        scanf("%d %d", &linha, &coluna);
        printf("\n");

        // verifica se as coordenadas são válidas
        if (linha < 0 || linha >= 8 || coluna < 0 || coluna >= 8) {
            printf("Coordenadas invalidas. Tente novamente.\n");
            continue;
        }

        if (tabuleiro[linha][coluna] != ' ') {
            printf("Jogada invalida. Tente novamente.\n");
            continue;
        }

        // aqui vai um if para verificar se a jogada eh valida, ainda falta criar a funcao

        // salva a jogada na matriz
        tabuleiro[linha][coluna] = jogador;

        // aqui vai o codigo para capturar pecas adversarias

        // mostra o tabuleiro atualizado
        mostra_tabuleiro(tabuleiro);

        // aqui vai um codigo para verificar se tem movimento validos
        // minha ideia eh criar um funcao separada que verifica isso e aqui ficar apenas um if
        // ai mostra quem ganhou e da break

        // passa a vez para o adversario
        if (jogador == 'P'){
            adversario = 'B';
        }
        else {
            adversario = 'P';
        }
        jogador = adversario;
    }
}

// -------------------------------------------------------------

int main() {
    char jogador;
    int tabuleiro[8][8];

    // comeca o jogo
    cria_tabuleiro(tabuleiro);

    mostra_tabuleiro(tabuleiro);

    printf("\n");

    jogada(tabuleiro, jogador);

    return 0;
}