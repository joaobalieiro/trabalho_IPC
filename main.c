#include <stdio.h>
#include <stdlib.h>
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

// essa funcao serve para limpar o terminal apos cada movimento valido
// como o comando eh diferente para windows e linus eu coloquei para verificar qual o sistema
// e aplicar o comando correspondente
void limpa_tela() {
    #ifdef __linux__
        system("clear");
    #elif __WIN64__
        system("cls");
    #else

    #endif
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

int movimento_valido(int tabuleiro[8][8], int linha, int coluna, char jogador)
{
    int i, j, x, y, tem_adversario;
    int adversario = (jogador == 'P') ? 'B' : 'P';

    // verifica se as coordenadas estao no tabuleiro
    if (linha < 0 || linha >= 8 || coluna < 0 || coluna >= 8) {
        return 0;
    }

    // verifica se a celula esta vazia
    if (tabuleiro[linha][coluna] != ' ') {
        return 0;
    }

    // verifica em todas as direcoes se ha peças do oponente que podem ser capturadas
    for (i = -1; i <= 1; i++) {
        for (j = -1; j <= 1; j++) {
            // ignora a propria posicao e verifica apenas as direcoes
            if (i == 0 && j == 0) {
                continue;
            }

            x = linha + i;
            y = coluna + j;
            tem_adversario = 0;

            // verifica se tem uma peca adversaria
            while (x >= 0 && x < 8 && y >= 0 && y < 8 && tabuleiro[x][y] == adversario) {
                x += i;
                y += j;
                tem_adversario = 1;
            }

            // volta como verdadeiro se tem uma jogada valida
            if (tem_adversario && x >= 0 && x < 8 && y >= 0 && y < 8 && tabuleiro[x][y] == jogador) {
                return 1;
            }
        }
    }

    return 0;
}

// -------------------------------------------------------------

// verifica quem eh o vencedor
int jogador_vencedor(int tabuleiro[8][8]) {
    char vencedor;
    int i, j, jogador_preto, jogador_branco;

    jogador_preto = 0;
    jogador_branco = 0;

    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            if (tabuleiro[i][j] == 'P') {
                jogador_preto++;
            }
            if (tabuleiro[i][j] == 'B') {
                jogador_branco++;
            }
        }
    }

    if (jogador_branco > jogador_preto) {
        vencedor = 'B';
    }
    else if (jogador_branco < jogador_preto) {
        vencedor = 'P';
    }
    else {
        return 0;
    }

    return vencedor;
}

// -------------------------------------------------------------

// verifica se a jogada eh valida e registra ela na matriz
void jogada(int tabuleiro[8][8], char jogador) {
    char adversario;
    int linha, coluna, tem_adversario, x, y, i, j, jogadas_validas;

    // forca a comecar com as pecas pretas
    jogador = 'P';

    // isso vai servir para iniciar o while
    // depois o valor vai variar de acordo com as jogadas validas
    jogadas_validas = 1;

    while (jogadas_validas > 0) {
        // recebe as coordenadas da jogada
        printf("\nJogador %c, insira a linha e a coluna da sua jogada separadas por um espaco:", jogador);
        scanf("%d %d", &linha, &coluna);
        printf("\n");

        // verifica se as coordenadas são válidas
        if (movimento_valido(tabuleiro,linha,coluna,jogador) == false) {
            printf("Jogada invalida. Tente novamente.\n");
            continue;
        }

        // limpa a tela apos cada movimento
        limpa_tela();

        // salva a jogada na matriz
        tabuleiro[linha][coluna] = jogador;

        // define o adversario
        adversario = (jogador == 'P') ? 'B' : 'P';

        // faz o loop para verificar quais pecas podem ser capturadas
        // o codigo eh praticamente igual ao para verificar a validade do movimento
        // a unica adicao eh para capturar as pecas
        for (i = -1; i <= 1; i++) {
            for (j = -1; j <= 1; j++) {
                if (i == 0 && j == 0) {
                    continue;
                }

                x = linha + i;
                y = coluna + j;
                tem_adversario = 0;

                while (x >= 0 && x < 8 && y >= 0 && y < 8 && tabuleiro[x][y] == adversario) {
                    x += i;
                    y += j;
                    tem_adversario = 1;
                }

                if (tem_adversario && x >= 0 && x < 8 && y >= 0 && y < 8 && tabuleiro[x][y] == jogador) {
                    // gira as peças do adversario
                    x -= i;
                    y -= j;
                    // captura as pecas do adversario
                    while (tabuleiro[x][y] == adversario) {
                        tabuleiro[x][y] = jogador;
                        x -= i;
                        y -= j;
                    }
                }
            }
        }

        // mostra o tabuleiro atualizado
        mostra_tabuleiro(tabuleiro);

        jogadas_validas = 0;

        for (i = 0; i < 8; i++) {
            for (j = 0; j < 8; j++) {
                if (movimento_valido(tabuleiro,i,j,adversario) == true) {
                    jogadas_validas = jogadas_validas + 1;
                }
            }
        }

        // passa a vez para o adversario
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

    jogada(tabuleiro, jogador);

    printf("\n O jogador %c venceu!", jogador_vencedor(tabuleiro));

    return 0;
}