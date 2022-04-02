#Guilherme Goncalves Gutierrez de Lima n199077

def eh_tabuleiro(tab):
    """Avalia o tabuleiro para verificar se e um tuplo que inclui 3 tuplos de 3 elementos com valores de 0, -1 ou 1.
        Caso a variavel tab nao seja um tuplo constituido por 3 tuplos constituidos por 3 elementos,
        com elementos de -1, 0 ou 1, a funcao ira dar return False, caso contrario ira dar return True
    """
    if not isinstance(tab, tuple) or len(tab) != 3:
        return False
    if not isinstance(tab[0], tuple) or not isinstance(tab[1], tuple) or not isinstance(tab[2], tuple):
        return False
    if len(tab[0]) != 3 or len(tab[1]) != 3 or len(tab[2]) != 3:
        return False
    else:
        for n in tab:
            for i in n:
                if type(i) == int and ((i == 1) or (i == 0) or (i == -1)):
                    pass
                else:
                    return False
    return True


def eh_posicao(n):
    """Verifica se e uma posicao do tabuleiro.
       Recebe a variavel n e verifica se e um numero inteiro entre 1 e 9, caso seja da return True, caso nao da return False
    """
    if type(n) != int or n < 1 or n > 9:
        return False
    else:
        return True


def alisa(tab):
    """Alisa o tuplo tab -> ("((0, 0, 0), (0, 0, 0), (0, 0, 0)) => (0,0,0,0,0,0,0,0,0)").
        Esta funcao recebe o tabuleiro na variavel tab.
        Esta funcao sera utilizada bastante pelo programa e facilita bastante a procura de posicoes pelo tabuleiro.
        Esta funcao ira obter todos os elementos de tab e ira transferi-los para um tuplo que levara return na funcao.
    """
    lista = ()
    for j in tab:
        for r in range(0, 3):
            lista += (j[r],)
    return lista


def obter_posicao(tab, n):
    """Obtem o valor da posicao do tabuleiro.
       Esta funcao recebera o tabuleiro e uma posicao. Ira entregar o valor do tabuleiro na respetiva posicao.
       Esta funcao e apenas utilizada na funcao canto_oposto.
    """
    return alisa(tab)[n - 1]


def obter_coluna(tab, t):
    """Obter coluna 1, 2 ou 3.
       Esta funcao avalia o tabuleiro e se o numero da coluna e inteiro e entre 1 e 3.
       Esta funcao ira obter o primeiros valor de cada um dos 3 tuplos dentro do tuplo tab.
       Estes valores serao entregados para uma variavel coluna que a funcao ira receber e dar return.
    """
    coluna = ()
    if type(t) != int or t < 1 or t > 3 or not eh_tabuleiro(tab):
        raise ValueError("obter_coluna: algum dos argumentos e invalido")
    for n in tab:
        coluna += (n[t - 1],)
    return coluna


def obter_linha(tab, l):
    """Obter linha 1, 2 ou 3.
       Esta funcao avalia o tabuleiro e se o numero da linha e inteiro e entre 1 e 3.
       Esta funcao ira receber um dos 3 tuplos dentro do tuplo tab.
    """
    if type(l) != int or l < 1 or l > 3 or not eh_tabuleiro(tab):
        raise ValueError("obter_linha: algum dos argumentos e invalido")
    return tab[l - 1]


def obter_diagonal(tab, d):
    """Obter a diagonal descendente da esquerda para a direita ou ascendente da esquerda para a direita.
    Esta funcao avalia o tabuleiro e se o numero da diagonal e inteiro (1 ou 2).
    Caso o utilizador queira a diagonal descendente da esquerda para a direita tera de escolher a diagonal 1,
    e recebera o primeiro valor do primeiro tuplo do tuplo tab, o segundo valor do segundo tuplo e o
    terceiro valor do terceiro tuplo.
    Caso o utilizador queira a diagonal ascendente da esquerda para a direita tera de escolher a diagonal 2,
    e recebera o primeiro valor do terceiro tuplo do tuplo tab, o segundo valor do segundo tuplo e o
    terceiro valor do primeiro tuplo.

    """
    diag = ()
    if not eh_tabuleiro(tab) or type(d) != int:
        raise ValueError("obter_diagonal: algum dos argumentos e invalido")
    if d == 1:
        return diag + (alisa(tab)[1 - d], alisa(tab)[5 - d], alisa(tab)[9 - d])
    if d == 2:
        return diag + (alisa(tab)[8 - d], alisa(tab)[6 - d], alisa(tab)[4 - d])
    else:
        raise ValueError("obter_diagonal: algum dos argumentos e invalido")


def convertor(n):
    """Converte os valores 0, 1 e -1 em "", "X" e "O" respetivamente.
       Esta funcao sera utilizada para desenhar o tabuleiro.
    """
    if n == 0:
        return "   "
    if n == 1:
        return " X "
    if n == -1:
        return " O "


def tabuleiro_str(tab):
    """Desenhar o tabuleiro.
       Depois de avaliar a variavel tab, esta funcao desenha o tabuleiro atraves da funcao que converte os valores
       dentro dos tuplos do tuplo tab em "X", "O" ou " ".
    """
    if not eh_tabuleiro(tab):
        raise ValueError("tabuleiro_str: o argumento e invalido")
    tabuleiro = str(convertor(alisa(tab)[0])) + "|" + str(convertor(alisa(tab)[1])) + "|" + str(convertor(alisa(tab)[2])) + "\n-----------\n"\
                + str(convertor(alisa(tab)[3])) + "|" + str(convertor(alisa(tab)[4]))\
                + "|" + str(convertor(alisa(tab)[5])) + "\n---------\n" + str(convertor(alisa(tab)[6]))\
                + "|" + str(convertor(alisa(tab)[7])) + "|" + str(convertor(alisa(tab)[8]))
    return tabuleiro


def eh_posicao_livre(tab, n):
    """Verificar se a posicao esta livre.
       Esta funcao avalia o tabuleiro e se o numero da posicao e inteiro e esta entre 1 e 9.
       Esta funcao ira avaliar o valor na posicao desejada, caso seja 0 ira dar return True pois a posicao
       esta vazia, caso contrario ira dar return False.
    """
    if type(n) != int or n < 1 or n > 9 or not eh_tabuleiro(tab):
        raise ValueError("eh_posicao_livre: algum dos argumentos e invalido")
    return alisa(tab)[n - 1] == 0


def obter_posicoes_livres(tab):
    """Obter posicoes livres
       Esta funcao avalia o tabuleiro e entrega as posicoes livres dentro de um tuplo.
       As posicoes livres sao obtidas comparando os valores dos tuplos de tab com 0.
    """
    livres = ()
    if eh_tabuleiro(tab) == False:
        raise ValueError("obter_posicoes_livres: o argumento e invalido")
    for k in range(0, 9):
        if alisa(tab)[k] == 0:
            livres += k + 1,
    return livres


def jogador_ganhador(tab):
    """Avalia se alguem ganhou.

       Esta funcao ira avaliar o tabuleiro e todas as linhas, colunas e diagonais.
       Caso estas sejam constituidas apenas por 1 ou -1 ira entregar esse mesmo valor.
       Nao e necessario verificar se existem dois vencedores num tabuleiro pois
       na funcao do jogo esse caso e impossivel de obter
    """
    if not eh_tabuleiro(tab):
        raise ValueError("jogador_ganhador: o argumento e invalido")
    for l in (1, 2, 3):
        if obter_linha(tab, l) == (1, 1, 1):
            return 1
        elif obter_coluna(tab, l) == (1, 1, 1):
            return 1
        elif obter_linha(tab, l) == (-1, -1, -1):
            return -1
        elif obter_coluna(tab, l) == (-1, -1, -1):
            return -1
    for l in (1, 2):
        if obter_diagonal(tab, l) == (1, 1, 1):
            return 1
        elif obter_diagonal(tab, l) == (-1, -1, -1):
            return -1
    return 0


def marcar_posicao(tab, j, n):
    """Substitui uma posicao pelo valor do jogador ou computador.
       Esta funcao avalia o tabuleiro e se o numero da posicao e inteiro e entre 1 e 9 e se nao esta ocupada.
       Ira avaliar tambem se o jogador e "X" ou "O" que sao as unicas opcoes.
       Esta funcao ira substituir uma posicao vazia, ou seja, com valor de 0 dentro dos tuplos de tab, por
       1, caso o jogador seja "X", ou por -1, caso o jogador seja "O".
    """
    if not eh_tabuleiro(tab) or type(j) != int or (j != -1 and j != 1) or type(n) != int or n < 1 or n > 9 or not eh_posicao_livre(tab,n):
        raise ValueError("marcar_posicao: algum dos argumentos e invalido")
    tuplo = alisa(tab)[:n - 1] + (j,) + alisa(tab)[n:]
    trio1 = trio2 = trio3 = lista = ()
    for n in (0, 1, 2):
        trio1 += tuplo[n],
    for n in (3, 4, 5):
        trio2 += tuplo[n],
    for n in (6, 7, 8):
        trio3 += tuplo[n],
    lista = (trio1, trio2, trio3)
    return lista


def escolher_posicao_manual(tab):
    """Escolhe uma posicao manualmente.
       Esta funcao ira avaliar o tabuleiro e recebera um input de uma posicao onde o jogador ira jogar.
    """
    if not eh_tabuleiro(tab):
        raise ValueError("escolher_posicao_manual: o argumento e invalido")
    n = eval(input("Turno do jogador. Escolha uma posicao livre: "))
    if type(n) != int or n > 9 or n < 1 or not eh_posicao_livre(tab,n):
        raise ValueError("escolher_posicao_manual: a posicao introduzida e invalida")
    else:
        return n


def posicao_central(tab):
    """Verifica a posicao central.
       Caso a posicao central esteja livre, a funcao ira dar return na posicao 5.
    """
    if eh_posicao_livre(tab, 5) == True:
        return 5


def criterio_basico(tab):
    """Verifica cantos e posicoes laterais (criterios 7 e 8).
       Verifica se os cantos estao livres, caso exista um canto livre devolve a posicao do canto.
       Caso nao haja cantos livres, ira verificar se existe um lado livre, caso haja devolve essa posicao.
    """
    for n in (1, 3, 7, 9):
        if eh_posicao_livre(tab, n) == True:
            return n
    for n in (2, 4, 6, 8):
        if eh_posicao_livre(tab, n) == True:
            return n


def posicao_vencedora(tab, j):
    """Verifica se existe uma posicao para ganhar o jogo.
       Verifica todas as linhas, colunas e diagonais tal como a funcao jogador_ganhador.
       Caso baste apenas uma jogada para alcancar a vitoria, a funcao ira dar return na posicao
       que e preciso jogar para ganhar atraves de 3 formas diferentes, uma para as linhas, colunas e diagonais.
    """
    if jogador_ganhador(tab) == 0:
        for l in range(1, 4):
            if obter_linha(tab, l) == (j, 0, j) or obter_linha(tab, l) == (j, j, 0) or obter_linha(tab, l) == (0, j, j):
                for y in range(0, 3):
                    if obter_linha(tab, l)[y] == 0:
                        if l == 1:
                            return y + 1
                        elif l == 2:
                            return y + 4
                        elif l == 3:
                            return y + 7
            if obter_coluna(tab, l) == (j, 0, j) or obter_coluna(tab, l) == (j, j, 0) or obter_coluna(tab, l) == (0, j, j):
                for y in range(0, 3):
                    if obter_coluna(tab, l)[y] == 0:
                        if l == 1:
                            return 3 * (y + 1) - 2
                        elif l == 2:
                            return 3 * (y + 1) - 1
                        elif l == 3:
                            return 3 * (y + 1)
        for l in range(1, 3):
            if obter_diagonal(tab, l) == (j, 0, j) or obter_diagonal(tab, l) == (j, j, 0) or obter_diagonal(tab, l) == (0, j, j):
                for y in range(0, 3):
                    if obter_diagonal(tab, l)[y] == 0:
                        if l == 1:
                            if y == 0:
                                return y + 1
                            elif y == 1:
                                return y + 4
                            elif y == 2:
                                return y + 7
                        elif l == 2:
                            if y == 0:
                                return y + 7
                            elif y == 1:
                                return y + 4
                            elif y == 2:
                                return y + 1


def bloqueio(tab, j):
    """Verifica se o adversario esta em posicao de ganhar e bloqueia a jogada.
       Caso o jogador adversario esteja em posicao vencedora, ira dar return na posicao livre.
       Esta funcao funciona como a inversa da funcao posicao_vencedora, funcionando de maneira a
       em vez de devolver a posicao para ganhar, devolve a posicao para o adversario nao ganhar,
       bastando apenas trocar o valor do jogador, de -1 para 1 ou de 1 para -1.
    """
    return posicao_vencedora(tab, -j)


def canto_oposto(tab, j):
    """Descobrir o canto oposto.
       Esta funcao ira avaliar os cantos todos.
       Caso o jogador adversario tenha uma posicao em um canto ocupada,
       a funcao ira devolver a posicao do canto oposto.
    """
    for n in (1, 3, 7, 9):
        if obter_posicao(tab, n) == -j:
            if n == 1:
                if eh_posicao_livre(tab, n + 8):
                    return n + 8
            elif n == 3:
                if eh_posicao_livre(tab, n + 4):
                    return n + 4
            elif n == 7:
                if eh_posicao_livre(tab, n - 4):
                    return n - 4
            elif n == 9:
                if eh_posicao_livre(tab, n - 8):
                    return n - 8


def escolher_posicao_auto(tab, j, jogada):
    """Escolhe uma posicao automatica.
       Esta funcao ira avaliar o tabuleiro, se as estrategias do computador sao validas e se o computador joga apenas com
       1 ("X") ou -1 ("O").
       Esta funcao ira avaliar a estrategia e ira devolver uma posicao correspondente.
       A estrategia "basico" ira apenas conter 2 funcoes de estrategia, a funcao posicao_central e a do
       criterio_basico que avalia os cantos e os lados.
       A estrategia "normal" ira conter as funcoes da estrategia anterior mais a funcao posicao_vencedora,
       bloqueio e canto_oposto.
       A estrategia "perfeito" ira conter todas as funcoes anteriores mais a funcao bifuracao e bloqueio_bifurcacao
       sendo impossivel ganhar contra o computador usando esta estrategia.
       Nota: a bifurcacao e o bloqueio de bifurcacao nao estao incluidos neste trabalho, sendo a estrategia
       "perfeito" com os mesmos criterios que a "normal"
    """
    if not eh_tabuleiro(tab) or (jogada != "basico" and jogada != "normal" and jogada != "perfeito") or type(j) != int or (j != -1 and j != 1):
        raise ValueError("escolher_posicao_auto: algum dos argumentos e invalido")
    if jogada == "basico":
        if type(posicao_central(tab)) == int:
            return posicao_central(tab)
        elif type(criterio_basico(tab)) == int:
            return criterio_basico(tab)
    if jogada == "normal":
        if type(posicao_vencedora(tab, j)) == int:
            return posicao_vencedora(tab, j)
        elif type(bloqueio(tab, j)) == int:
            return bloqueio(tab, j)
        elif type(posicao_central(tab)) == int:
            return posicao_central(tab)
        elif type(canto_oposto(tab, j)) == int:
            return canto_oposto(tab, j)
        elif type(criterio_basico(tab)) == int:
            return criterio_basico(tab)
    if jogada == "perfeito":
        if type(posicao_vencedora(tab, j)) == int:
            return posicao_vencedora(tab, j)
        elif type(bloqueio(tab, j)) == int:
            return bloqueio(tab, j)
        elif type(posicao_central(tab)) == int:
            return posicao_central(tab)
        elif type(canto_oposto(tab, j)) == int:
            return canto_oposto(tab, j)
        elif type(criterio_basico(tab)) == int:
            return criterio_basico(tab)


def jogo_do_galo(j, jogada):
    """Realiza o jogo do galo.
       Esta funcao ira fazer decorrer o jogo fazendo com que caso o jogador escolha "X" para jogar
       ele possa comecar primeiro. Caso escolha "O" o computador ira comecar.
       Dentro do loop do jogo, depois de cada jogada iremos avaliar se todas as posicoes estao ocupadas
       ou se algum jogador ganhou.
       Caso as posicoes estejam ocupadas e nao haja vencedor, a funcao da return em 'EMPATE'.
       Caso o resultado da funcao jogador_ganhador seja 1 a funcao da return de 'X'.
       Caso o resultado da funcao jogador_ganhador seja -1 a funcao da return de 'O'
    """
    tab = ((0, 0, 0), (0, 0, 0), (0, 0, 0))
    if j == "O":
        m = 1
        s = "X"
        p = -1
    elif j == "X":
        m = -1
        s = "O"
        p = 1
    n = 0
    if eh_tabuleiro(tab):
        print("Bem-vindo ao JOGO DO GALO. \nO jogador joga com '{j}'.".format(j=j))
        while obter_posicoes_livres(tab) != ():
            if jogador_ganhador(tab) == 1 or jogador_ganhador(tab) == -1:
                break
            if p == 1:
                n = escolher_posicao_manual(tab)
                tab = marcar_posicao(tab, -m, n)
                print(tabuleiro_str(tab))
                p = -1
            if jogador_ganhador(tab) == 1 or jogador_ganhador(tab) == -1 or obter_posicoes_livres(tab) == ():
                break
            elif p == -1:
                print("Turno do computador ({jogada}):".format(jogada=jogada))
                tab = marcar_posicao(tab, m, escolher_posicao_auto(tab, -p, jogada))
                print(tabuleiro_str(tab))
                p = 1

        if jogador_ganhador(tab) == 0:
            return 'EMPATE'
        elif jogador_ganhador(tab) == 1:
            return 'X'
        elif jogador_ganhador(tab) == -1:
            return 'O'
print(jogo_do_galo("X","normal"))