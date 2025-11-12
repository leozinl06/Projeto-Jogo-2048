import random
import os

# Tamanho do tabuleiro (4x4)
TAMANHO = 4

# Cria o tabuleiro (começa vazio)
tabuleiro = [[0, 0, 0, 0] for _ in range(TAMANHO)]
pontuacao = 0


# Limpa a tela para deixar o jogo mais limpo
def limpar_tela():
    os.system("cls" if os.name == "nt" else "clear")


# Mostra o tabuleiro e a pontuação
def mostrar_tabuleiro():
    limpar_tela()
    for i in range(TAMANHO):
        for j in range(TAMANHO):
            if tabuleiro[i][j] == 0:
                print(".\t", end="")
            else:
                print(f"{tabuleiro[i][j]}\t", end="")
        print()
    print(f"\nPontuação: {pontuacao}\n")


# Verifica se o tabuleiro está cheio
def esta_cheio():
    for i in range(TAMANHO):
        for j in range(TAMANHO):
            if tabuleiro[i][j] == 0:
                return False
    return True


# Gera uma nova peça (2 ou 4) em uma casa vazia
def gerar_peca():
    casas_vazias = []

    for i in range(TAMANHO):
        for j in range(TAMANHO):
            if tabuleiro[i][j] == 0:
                casas_vazias.append((i, j))

    if len(casas_vazias) == 0:
        return

    x, y = random.choice(casas_vazias)
    tabuleiro[x][y] = random.choice([2, 4])


# Move todas as peças para a esquerda (sem combinar ainda)
def deslocar_esquerda():
    for i in range(TAMANHO):
        nova_linha = []
        for j in range(TAMANHO):
            if tabuleiro[i][j] != 0:
                nova_linha.append(tabuleiro[i][j])

        while len(nova_linha) < TAMANHO:
            nova_linha.append(0)

        for j in range(TAMANHO):
            tabuleiro[i][j] = nova_linha[j]


# Combina peças iguais na mesma linha (para a esquerda)
def combinar_esquerda():
    global pontuacao
    for i in range(TAMANHO):
        for j in range(TAMANHO - 1):
            if tabuleiro[i][j] == tabuleiro[i][j + 1] and tabuleiro[i][j] != 0:
                tabuleiro[i][j] *= 2
                pontuacao += tabuleiro[i][j]
                tabuleiro[i][j + 1] = 0


# Movimento completo para a esquerda
def mover_esquerda():
    deslocar_esquerda()
    combinar_esquerda()
    deslocar_esquerda()


# Rotaciona o tabuleiro (para usar os mesmos comandos em outras direções)
def rotacionar_tabuleiro():
    novo = [[0, 0, 0, 0] for _ in range(TAMANHO)]
    for i in range(TAMANHO):
        for j in range(TAMANHO):
            novo[i][j] = tabuleiro[j][TAMANHO - i - 1]
    for i in range(TAMANHO):
        for j in range(TAMANHO):
            tabuleiro[i][j] = novo[i][j]


def mover_direita():
    rotacionar_tabuleiro()
    rotacionar_tabuleiro()
    mover_esquerda()
    rotacionar_tabuleiro()
    rotacionar_tabuleiro()


def mover_cima():
    rotacionar_tabuleiro()
    mover_esquerda()
    rotacionar_tabuleiro()
    rotacionar_tabuleiro()
    rotacionar_tabuleiro()


def mover_baixo():
    rotacionar_tabuleiro()
    rotacionar_tabuleiro()
    rotacionar_tabuleiro()
    mover_esquerda()
    rotacionar_tabuleiro()


# Verifica se o jogo acabou
def fim_de_jogo():
    if not esta_cheio():
        return False

    for i in range(TAMANHO):
        for j in range(TAMANHO - 1):
            if tabuleiro[i][j] == tabuleiro[i][j + 1]:
                return False
            if tabuleiro[j][i] == tabuleiro[j + 1][i]:
                return False

    return True


# Programa principal
def main():
    global pontuacao

    gerar_peca()
    gerar_peca()

    while True:
        mostrar_tabuleiro()

        if fim_de_jogo():
            print("Você perdeu!")
            break

        movimento = input("Movimento (W = cima, A = esquerda, S = baixo, D = direita): ").lower()

        if movimento == "a":
            mover_esquerda()
        elif movimento == "d":
            mover_direita()
        elif movimento == "w":
            mover_cima()
        elif movimento == "s":
            mover_baixo()
        else:
            continue

        gerar_peca()

        for i in range(TAMANHO):
            for j in range(TAMANHO):
                if tabuleiro[i][j] == 2048:
                    mostrar_tabuleiro()
                    print("🎉 Você venceu!")
                    return


# Inicia o jogo
main()
