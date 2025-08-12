#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO 4  // Definindo o tamanho do tabuleiro como 4x4

int tabuleiro[TAMANHO][TAMANHO];  // Tabuleiro onde o jogo ocorrerá
int pontuacao = 0;  // Variável para armazenar a pontuação do jogador

// Função para imprimir o tabuleiro
void imprimirTabuleiro() {
    for (int i = 0; i < TAMANHO; i++) {  // Loop para percorrer todas as linhas do tabuleiro
        for (int j = 0; j < TAMANHO; j++) {  // Loop para percorrer todas as colunas de cada linha
            if (tabuleiro[i][j] == 0)  // Se a casa estiver vazia, imprime um ponto
                printf(".\t");
            else  // Caso contrário, imprime o valor da peça
                printf("%d\t", tabuleiro[i][j]);
        }
        printf("\n");
    }
    // Imprime a pontuação do jogador
    printf("Pontuação: %d\n\n", pontuacao);
}

// Função para verificar se o tabuleiro está cheio
int estaCheio() {
    for (int i = 0; i < TAMANHO; i++) {  // Percorre todas as linhas
        for (int j = 0; j < TAMANHO; j++) {  // Percorre todas as colunas
            if (tabuleiro[i][j] == 0)  // Se encontrar uma casa vazia, retorna 0 (tabuleiro não cheio)
                return 0;
        }
    }
    return 1;  // Se não houver casas vazias, o tabuleiro está cheio
}

// Função para gerar uma nova peça aleatória (2 ou 4) em uma casa vazia
void gerarPeca() {
    int vazias[TAMANHO * TAMANHO][2];  // Vetor para armazenar as posições das casas vazias
    int count = 0;  // Contador de casas vazias

    // Percorre o tabuleiro e armazena as posições das casas vazias
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            if (tabuleiro[i][j] == 0) {
                vazias[count][0] = i;  // Armazena a linha da casa vazia
                vazias[count][1] = j;  // Armazena a coluna da casa vazia
                count++;  // Incrementa o contador de casas vazias
            }
        }
    }

    // Se não houver casas vazias, não gera nenhuma peça
    if (count == 0) return;

    // Escolhe uma posição aleatória entre as casas vazias
    int r = rand() % count;
    int x = vazias[r][0];
    int y = vazias[r][1];
    
    // Gera uma peça 2 ou 4 na casa escolhida aleatoriamente
    tabuleiro[x][y] = (rand() % 2 == 0) ? 2 : 4;
}

// Função para combinar as peças à esquerda
void combinarEsquerda() {
    for (int i = 0; i < TAMANHO; i++) {  // Percorre todas as linhas
        for (int j = 0; j < TAMANHO - 1; j++) {  // Percorre todas as colunas, exceto a última
            // Se duas peças consecutivas tiverem o mesmo valor, elas se combinam
            if (tabuleiro[i][j] == tabuleiro[i][j + 1] && tabuleiro[i][j] != 0) {
                tabuleiro[i][j] *= 2;  // Dobra o valor da peça
                pontuacao += tabuleiro[i][j];  // Atualiza a pontuação do jogador
                tabuleiro[i][j + 1] = 0;  // A casa à direita é zerada, pois a peça foi combinada
            }
        }
    }
}

// Função para deslocar todas as peças à esquerda
void deslocarEsquerda() {
    for (int i = 0; i < TAMANHO; i++) {  // Percorre todas as linhas
        int temp[TAMANHO] = {0};  // Cria um vetor temporário para armazenar a nova configuração
        int pos = 0;
        for (int j = 0; j < TAMANHO; j++) {  // Percorre todas as colunas
            if (tabuleiro[i][j] != 0) {  // Se a peça não for zero, coloca ela na posição mais à esquerda
                temp[pos++] = tabuleiro[i][j];
            }
        }
        // Atualiza a linha com a nova configuração de peças
        for (int j = 0; j < TAMANHO; j++) {
            tabuleiro[i][j] = temp[j];
        }
    }
}

// Função que faz o movimento à esquerda (desloca e combina as peças)
void moverEsquerda() {
    deslocarEsquerda();  // Desloca as peças para a esquerda
    combinarEsquerda();  // Combina as peças que podem ser combinadas
    deslocarEsquerda();  // Desloca novamente para ajustar as peças após a combinação
}

// Função para rotacionar o tabuleiro 90 graus
void rotacionarTabuleiro() {
    int temp[TAMANHO][TAMANHO];  // Matriz temporária para armazenar a rotação
    for (int i = 0; i < TAMANHO; i++) {  // Percorre as linhas
        for (int j = 0; j < TAMANHO; j++) {  // Percorre as colunas
            temp[i][j] = tabuleiro[j][TAMANHO - i - 1];  // Faz a rotação 90 graus no sentido horário
        }
    }
    // Atualiza o tabuleiro com a nova configuração
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            tabuleiro[i][j] = temp[i][j];
        }
    }
}

// Funções para movimentar o tabuleiro nas direções: cima, direita e baixo
void moverCima() {
    rotacionarTabuleiro();  // Rotaciona o tabuleiro 90 graus
    moverEsquerda();  // Faz o movimento à esquerda
    rotacionarTabuleiro();  // Rotaciona de volta para a posição original
    rotacionarTabuleiro();
    rotacionarTabuleiro();
}

void moverDireita() {
    rotacionarTabuleiro();
    rotacionarTabuleiro();
    moverEsquerda();
    rotacionarTabuleiro();
    rotacionarTabuleiro();
}

void moverBaixo() {
    rotacionarTabuleiro();
    rotacionarTabuleiro();
    rotacionarTabuleiro();
    moverEsquerda();
    rotacionarTabuleiro();
}

// Função para verificar se o jogo acabou
int verificarFimDeJogo() {
    if (!estaCheio()) return 0;  // Se ainda houver casas vazias, o jogo não acabou
    
    // Verifica se há combinações possíveis
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO - 1; j++) {
            if (tabuleiro[i][j] == tabuleiro[i][j + 1] || tabuleiro[j][i] == tabuleiro[j + 1][i]) {
                return 0;  // Se houver pelo menos uma combinação possível, o jogo não acabou
            }
        }
    }
    return 1;  // Se não houver casas vazias nem combinações possíveis, o jogo acabou
}

// Função principal
int main() {
    srand(time(NULL));  // Inicializa o gerador de números aleatórios
    
    // Inicializa o tabuleiro com 0 (todas as casas vazias)
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            tabuleiro[i][j] = 0;
        }
    }

    // Gera as primeiras duas peças
    gerarPeca();
    gerarPeca();

    while (1) {
        imprimirTabuleiro();  // Exibe o tabuleiro atual

        if (verificarFimDeJogo()) {  // Se o jogo acabou
            printf("Você perdeu! Pontuação final: %d\n", pontuacao);  // Exibe a mensagem de derrota
            break;  // Encerra o jogo
        }

        char movimento;
        printf("Movimento (W: Cima, A: Esquerda, S: Baixo, D: Direita): ");
        scanf(" %c", &movimento);  // Lê o movimento do jogador

        // Executa o movimento escolhido pelo jogador
        if (movimento == 'a') {
            moverEsquerda();
        } else if (movimento == 'd') {
            moverDireita();
        } else if (movimento == 'w') {
            moverCima();
        } else if (movimento == 's') {
            moverBaixo();
        }

        gerarPeca();  // Gera uma nova peça após o movimento

        // Se o jogador alcançar a pontuação de 2048, ele vence
        if (pontuacao >= 2048) {
            printf("Você venceu! Pontuação final: %d\n", pontuacao);
            break;  // Encerra o jogo
        }
    }

    return 0;
}