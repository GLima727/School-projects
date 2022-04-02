#Guilherme Goncalves Gutierrez de Lima n199077

def cria_posicao(c, l):
    """
    str × str → posicao
    Esta funcao ira receber dois argumentos, coluna e linha, que irao formar uma posicao.
    Esta posicao sera uma coordenada de um tabuleiro 3 por 3, onde as colunas serao avaliadas como
    "a", "b" ou "c" e as linhas como "1", "2" ou "3".

    """
    if (c != "a" and c != "b" and c != "c") or (l != "1" and l != "2" and l != "3"):
        raise ValueError("cria_posicao: argumentos invalidos")
    return (c, l)

def cria_copia_posicao(p):
    """
        posicao → posicao
        Esta funcao ira criar uma copia da posicao que receber como argumento.
    """
    return cria_posicao(p[0], p[1])

def obter_pos_c(p):
    """
        posicao → str
        Esta funcao ira devolver a componente coluna da posicao que receber como argumento.
    """
    return p[0]

def obter_pos_l(p):
    """
        posicao → str
        Esta funcao ira devolver a componente linha da posicao que receber como argumento.
    """
    return p[1]

def eh_posicao(arg):
    """
        universal → bool
        Esta funcao recebe um argumento de qualquer tipo e devolve True se o seu argumento
        corresponde a uma posicao e False caso contrario.
        Uma posicao valida corresponde a um tuplo constituido por dois elementos, uma coluna e uma linha,
        onde as colunas serao avaliadas como "a", "b" ou "c" e as linhas como "1", "2" ou "3".
        Exemplo:

        >>> eh_posicao(’a’, ’2’)
        True
        >>> eh_posicao(’d’, ’2’)
        False
        >>> eh_posicao(’a’, ’4’)
        False

    """
    if type(arg) != tuple or len(arg) != 2 or (obter_pos_c(arg) != "a" and obter_pos_c(arg) != "b" and
       obter_pos_c(arg) != "c") or (obter_pos_l(arg) != "1" and obter_pos_l(arg) != "2" and obter_pos_l(arg) != "3"):
        return False
    return True

def posicoes_iguais(p1,p2):
    """
        posicao × posicao → bool
        Esta funcao devolve True apenas se p1 e p2 sao posicoes e sao iguais.
    """
    if eh_posicao(p1) and eh_posicao(p2):
        return obter_pos_c(p1) == obter_pos_c(p2) and obter_pos_l(p1) == obter_pos_l(p2)
    return False
def posicao_para_str(p):
    """
        posicao → str
        Esta funcao  devolve a cadeia de caracteres ‘cl’ que representa o seu
        argumento, sendo os valores c e l as componentes coluna e linha de p.
    """
    return str(obter_pos_c(p)) + str(obter_pos_l(p))

def obter_posicoes_adjacentes(p):
    """
        posicao → tuplo de posicoes
        Esta funcao  devolve um tuplo com as posicoes adjacentes a posicao
        p de acordo com a ordem de leitura do tabuleiro.
        Foi utilizado um dicionario com todas as posicoes adjacentes de cada posicao.
    """
    posicoes_adjacentes = {('a', '1'): (('b', '1'), ('a', '2'), ('b', '2')),
                           ('a', '2'): (('a', '1'), ('b', '2'), ('a', '3') ),
                           ('a', '3'): (('a', '2'), ('b', '2'), ('b', '3')),

                           ('b', '1'): (('a', '1'), ('c', '1'), ('b', '2')),
                           ('b', '2'): (('a', '1'), ('b', '1'), ('c', '1'), ('a', '2'), ('c', '2'), ('a', '3'),
                                        ('b', '3'), ('c', '3')),
                           ('b', '3'): (('b', '2'), ('a', '3'), ('c', '3')),

                           ('c', '1'): (('b', '1'), ('b', '2'), ('c', '2')),
                           ('c', '2'): (('c', '1'), ('b', '2'), ('c', '3')),
                           ('c', '3'): (('b', '2'), ('c', '2'), ('b', '3'))}

    return posicoes_adjacentes[((obter_pos_c(p),obter_pos_l(p)))]

def cria_peca(s):
    """
        str → peca
        Esta funcao recebe uma cadeia de carateres correspondente ao identificador
        de um dos dois jogadores (’X’ ou ’O’) ou a uma peca livre (’ ’) e devolve a peca correspondente.
        A funcao ira avaliar o arumento, e caso este nao seja "X", "O" ou " " ira devolver um ValueError.

    """
    if s != "X" and s != "O" and s != " ":
        raise ValueError("cria_peca: argumento invalido")
    return s

def cria_copia_peca(j):
    """
        peca → peca
        Esta funcao recebe uma peca e devolve uma copia nova da peca.
    """
    return cria_peca(j)

def eh_peca(arg):
    """
        universal → bool
        Esta funcao devolve True caso o seu argumento seja um TAD peca e False caso contrario.
    """
    return arg == "X" or arg == "O" or arg == " "

def pecas_iguais(j1, j2):
    """
        peca × peca → bool
        Esta funcao devolve True apenas se p1 e p2 sao pecas e sao iguais.
    """
    if eh_peca(j1) and eh_peca(j2):
        return j1 == j2

def peca_para_str(j):
    """
        peca → str
        Esta funcao devolve a cadeia de caracteres que representa o jogador dono da peca, isto e, ’[X]’, ’[O]’ ou ’[ ]’.
    """
    return "["+str(j)+"]"

def peca_para_inteiro(j):
    """
        peca → int
        Esta funcao devolve um inteiro valor 1, -1 ou 0,
        dependendo se a peca e do jogador ’X’, ’O’ ou livre (" "), respetivamente.
        Foi utilizado um dicionario com os valores inteiros respetivos a cada peca.
    """
    pecas = {'X': 1, 'O': -1, ' ': 0}
    return pecas[j]

def cria_tabuleiro():
    """
        () → tabuleiro
        Esta funcao devolve um tabuleiro de jogo do moinho de 3x3 sem posicoes ocupadas por pecas de jogador.
        Este tabuleiro consiste numa lista, composta por 3 listas, que são compostas por 3 pecas vazias cada.
    """
    return [[" "," "," "],[" "," "," "],[" "," "," "]]

def cria_copia_tabuleiro(t):
    """
        tabuleiro → tabuleiro
        Esta funcao recebe um tabuleiro e devolve uma copia nova do tabuleiro.
    """
    return [list(t[0])]+[list(t[1])]+[list(t[2])]

def alisa(t):
    """
        tabuleiro → lista
        Alisa a lista t -> [[" "," "," "],[" "," "," "],[" "," "," "]] => [" "," "," "," "," "," "," "," "," "].
        Esta funcao recebe o tabuleiro na variavel t.
        Esta funcao sera utilizada bastante pelo programa e facilita bastante a procura de posicoes pelo tabuleiro.
        Esta funcao ira obter todos os elementos de t e ira transferi-los para uma lista que levara return na funcao.
    """
    lista = []
    for j in t:
        for r in range(0, 3):
            lista += [j[r],]
    return lista

posicoes = {('a', '1'): 0, ('b', '1'): 1, ('c', '1'): 2,
            ('a', '2'): 3, ('b', '2'): 4, ('c', '2'): 5,
            ('a', '3'): 6, ('b', '3'): 7, ('c', '3'): 8}

posicoes_inversas = {0: ('a', '1'), 1: ('b', '1'), 2: ('c', '1'),
                     3: ('a', '2'), 4: ('b', '2'), 5: ('c', '2'),
                     6: ('a', '3'), 7: ('b', '3'), 8: ('c', '3')}

def obter_peca(t, p):
    """
        tabuleiro × posicao → peca
        Esta funcao devolve a peca na posicao p do tabuleiro. Se a posicao nao estiver ocupada, devolve uma peca livre.
        Esta funcao ira utilizar um dicionario de forma a obter todas as posicoes do tabuleiro.
        Atraves dos numeros fornecidos pelo dicionario conseguimos as posicoes da lista alisa(t).
    """
    return alisa(t)[posicoes[(obter_pos_c(p),obter_pos_l(p))]]


def obter_vetor(t, s):
    """
        tabuleiro × str → tuplo de pecas
        Esta funcao devolve todas as pecas da linha ou coluna especificada pelo seu argumento.
        Esta funcao ira utilizar um dicionario de forma a obter todos os vetores do tabuleiro.
        Atraves dos numeros fornecidos pelo dicionario conseguimos as posicoes da lista alisa(t).
    """
    colunas_linhas = {('a'): (0, 3, 6), ('b'): (1, 4, 7), ('c'): (2, 5, 8),
                      ('1'): (0, 1, 2), ('2'): (3, 4, 5), ('3'): (6, 7, 8)}

    return tuple((alisa(t)[k]) for k in colunas_linhas[s])

def coloca_peca(t, j, p):
    """
        tabuleiro × peca × posicao → tabuleiro
        Esta funcao modifica destrutivamente o tabuleiro t colocando a peca j na posicao p,
        e devolve o proprio tabuleiro alterado.
        Atraves do uso da tabela ASCII, a funcao transforma as strings das colunas na posicao em numeros,
        que serao utlizados para obter os valores da lista do tabuleiro.
    """
    x = ord(obter_pos_c(p)) - 97
    y = int(obter_pos_l(p)) - 1
    t[y][x] = j
    return t

def remove_peca(t, p):
    """
        tabuleiro × posicao → tabuleiro
        Esta funcao modifica destrutivamente o tabuleiro t removendo a peca da posicao p,
         e devolve o proprio tabuleiro.
        Atraves do uso da tabela ASCII, a funcao transforma as strings das colunas na posicao em numeros,
        que serao utlizados para obter os valores da lista do tabuleiro.
    """
    x = ord(obter_pos_c(p)) - 97
    y = int(obter_pos_l(p)) - 1
    t[y][x] = " "
    return t

def move_peca(t, p1, p2):
    """
        tabuleiro × posicao × posicao → tabuleiro
        Esta funcao modifica destrutivamente o tabuleiro t movendo a peca que se encontra
        na posicao p1 para a posicao p2, e devolve o proprio tabuleiro.
    """
    j = obter_peca(t, p1)
    remove_peca(t,p1)
    coloca_peca(t, j, p2)
    return t

def numero_pecas(t,j):
    """
        tabuleiro × peca → int
        Esta funcao ira receber um tabuleiro e uma peca, e ira devolver o numero de pecas do argumento peca.
        Esta funcao ira ser utilizada para avaliar o tabuleiro.
    """
    lista = alisa(t)
    contador = 0
    for n in range(0,9):
        if lista[n] == j:
            contador += 1
    return contador

def jogador_vencedor(t, j):
    """
        tabuleiro × peca → int
        Esta funcao ira receber um tabuleiro e uma peca, e ira devolver 1 caso exista um vetor no tabuleiro
        constituido por 3 pecas recebidas seguidas.
        Caso nao ira devolver 0.
        Esta funcao ira ser utilizada na funcao obter_ganhador.
    """
    i = (j, j, j)
    for n in ("a","b","c","1","2","3"):
        if obter_vetor(t, n) == i:
            return 1
    return 0

def eh_tabuleiro(arg):
    """
        universal → bool
        Esta funcao recebe um argumento de qualquer tipo e devolve True se o seu argumento
        corresponde a um tabuleiro e False caso contrario.
        Um tabuleiro valido ira corresponder a uma lista constituida por 3 listas, que serao constituidas
        por 3 elementos.
        Estes elementos terao de corresponder a pecas validas, neste caso "X","O" ou " ".
        Para alem disto, um tabuleiro valido pode ter um maximo de 3 pecas de cada jogador, nao pode conter
        mais de 1 peca mais de um jogador que do contrario, e apenas pode haver um ganhador em simultaneo.

        Exemplo de uso:
        >>> eh_tabuleiro( [[" ","O"," "],[" ","X"," "],[" "," "," "]] )
        True
        >>> eh_tabuleiro( [["X","X","O"],["X"," "," "],[" "," "," "]] )
        False
        >>> eh_tabuleiro( [["X","X","X"],["O","O","O"],[" "," "," "]] )
        False
    """
    if type(arg) != list or len(arg) != 3 or type(arg[0]) != list or type(arg[1]) != list or type(arg[2]) != list\
       or len(arg[0]) != 3 or len(arg[1]) != 3 or len(arg[2]) != 3:
        return False
    for n in range(0,9):
        if alisa(arg)[n] != cria_peca("X") and alisa(arg)[n] != cria_peca("O") and alisa(arg)[n] != cria_peca(" "):
            return False
    if ((numero_pecas(arg, "X") > 3
            or numero_pecas(arg, "O") > 3
            or (numero_pecas(arg, "X") - numero_pecas(arg, "O")) > 1
            or (numero_pecas(arg, "0") - numero_pecas(arg, "X")) > 1
            or (jogador_vencedor(arg, "X") + jogador_vencedor(arg, "O")) == 2)):
        return False
    return True

def eh_posicao_livre(t, p):
    """
        tabuleiro × posicao → bool
        Esta funcao devolve True apenas no caso da posicao p do tabuleiro corresponder a uma posicao livre ( " " ).
    """
    return alisa(t)[posicoes[p]] == cria_peca(" ")

def tabuleiros_iguais(t1,t2):
    """
        tabuleiro × tabuleiro → bool
        Esta funcao devolve True apenas se t1 e t2 sao tabuleiros e sao iguais.
    """
    if eh_tabuleiro(t1) and eh_tabuleiro(t2):
        return t1 == t2
    return False

def tabuleiro_para_str(t):
    """
        tabuleiro → str
        Esta funcao devolve a cadeia de caracteres que representa o tabuleiro.
    """
    return '   a   b   c\n1 ' + str(peca_para_str(obter_peca(t,("a","1")))) + '-' + \
           str(peca_para_str(obter_peca(t,("b","1")))) + '-' + \
           str(peca_para_str(obter_peca(t,("c","1")))) + '\n   | \\ | / |\n2 ' + \
           str(peca_para_str(obter_peca(t,("a","2")))) + '-' + \
           str(peca_para_str(obter_peca(t,("b","2")))) + '-' + \
           str(peca_para_str(obter_peca(t,("c","2")))) + '\n   | / | \\ |\n3 ' + \
           str(peca_para_str(obter_peca(t,("a","3")))) + '-' + \
           str(peca_para_str(obter_peca(t,("b","3")))) + '-' + \
           str(peca_para_str(obter_peca(t,("c","3"))))

def tuplo_para_tabuleiro(t):
    """
        tuplo → tabuleiro
        Esta funcao devolve o tabuleiro que e representado pelo tuplo t
        com 3 tuplos, cada um deles contendo 3 valores inteiros iguais a 1, -1 ou 0.
        Esta funcao ira utilizar um dicionario para converter os valores das pecas em valores inteiros
        da mesma forma utilizada em peca_para_inteiro
    """
    d = {0: " ", 1: "X", -1: "O"}
    l = list(map(lambda x: [d[x_] for x_ in x], t))
    return l

def obter_ganhador(t):
    """
        tabuleiro → peca
        Esta funcao devolve uma peca do jogador que tenha as suas 3 pecas em linha
        na vertical ou na horizontal no tabuleiro. Se nao existir nenhum ganhador, devolve
        uma peca livre.
        Esta funcao ira utilizar a funcao auxiliar jogador_vencedor, que devolve 1 caso exista um vetor
        com 3 pecas seguidas.
        Caso devolva 0 com a peca do jogador e do adversario
        significa que nao existe vencedor no tabuleiro, logo a funcao obter_ganhador devolve uma peca livre.
    """
    if jogador_vencedor(t, "X") == 1:
        return "X"
    elif jogador_vencedor(t, "O") == 1:
        return "O"
    elif jogador_vencedor(t, "O") == 0 and jogador_vencedor(t, "X") == 0:
        return " "

def obter_posicoes_livres(t):
    """
        tabuleiro → tuplo de posicoes
        Esta funcao devolve um tuplo com as posicoes nao ocupadas pelas pecas
        de qualquer um dos dois jogadores na ordem de leitura do tabuleiro.
    """
    lista = []
    for n in range(0, 9):
        if alisa(t)[n] == " ":
            lista.append(tuple(posicoes_inversas[n]))
    return tuple(lista)

def obter_posicoes_jogador(t, j):
    """
        tabuleiro × peca → tuplo de posicoes
        Esta funcao devolve um tuplo com as posicoes ocupadas pelas pecas
        j de um dos dois jogadores na ordem de leitura do tabuleiro.
    """
    lista = []
    for n in range(0, 9):
        if alisa(t)[n] == j:
            lista.append(tuple(posicoes_inversas[n]))
    return tuple(lista)

def obter_movimento_manual(t, j):
    """
        tabuleiro × peca → tuplo de posicoes
        Esta funcao recebe um tabuleiro e uma peca de um jogador, e devolve um tuplo com uma ou duas posicoes que
        representam uma posicao ou um movimento introduzido manualmente pelo jogador.

        Na fase de colocacao e de movimento, a posicao em str desejada pelo utilizador sera transformada numa
        lista, de forma a avalia-la, e transforma-la em uma posicao.
        Estas posicoes em str serao transformadas em listas nas duas fases e depois de avaliadas serao transformadas
        em um tuplo com posicoes, que depois sera utilizado nas funcoes coloca_peca e move_peca.

        Apenas podera colocar a peca na posicao desejada se esta posicao estiver vazia na fase de colocacao.
        Na fase de movimento o utilizador apenas podera mover uma peca de uma posicao para outra,
        caso na primeira posicao esteja uma peca que lhe pertece, e a segunda posicao esteja vazia e que seja uma
        posicao adjacente a primeira.

        Na fase de colocacao a funcao ira apenas colocar a peca no tabuleiro na posicao inserida,
        na de movimento ira mover a peca da posicao onde ela estava para a posicao desejada.
    """
    if numero_pecas(t, j) != 3:
        n = str(input("Turno do jogador. Escolha uma posicao: "))
        lista = list([x for x in n])
        posicao = tuple([tuple([obter_pos_c(lista), obter_pos_l(lista)]),])

        if len(lista) != 2 or not eh_posicao(posicao[0]) or not eh_posicao_livre(t, posicao[0]):
            raise ValueError("obter_movimento_manual: escolha invalida")

        coloca_peca(t, j, posicao[0])
        return posicao
    else:
        n = str(input("Turno do jogador. Escolha um movimento: "))
        lista = list([x for x in n])

        if len(lista) != 4:
            raise ValueError("obter_movimento_manual: escolha invalida")

        movimento = tuple([tuple([obter_pos_c(lista), obter_pos_l(lista)]), tuple([lista[2], lista[3]])])

        if not eh_posicao(movimento[0]) or not eh_posicao(movimento[1]) or\
           (not eh_posicao_livre(t, movimento[1]) and movimento[1] != movimento[0]) or \
                (obter_peca(t, movimento[0]) != j and movimento[1] != movimento[0])\
                or (movimento[1] not in obter_posicoes_adjacentes(movimento[0]) and movimento[1] != movimento[0]):
            raise ValueError("obter_movimento_manual: escolha invalida")

        move_peca(t, movimento[0], movimento[1])
        return movimento

def peca_adversaria(j):
    """
        peca → peca
        Esta funcao recebe uma peca e ira devolver a peca adversaria.
    """
    if pecas_iguais(j, cria_peca("O")):
        return cria_peca("X")
    elif pecas_iguais(j, cria_peca("X")):
        return cria_peca("O")

def minimax(t, j, p, seq_movimentos):
    """
        tabuleiro × peca × profundidade × seq_movimentos → peca
        Esta é a funcao recursiva minimax proveniente do ficheiro pdf proj2.20201211
    """
    if obter_ganhador(t) != cria_peca(" ") or p == 0:
        return peca_para_inteiro(obter_ganhador(t)), seq_movimentos
    else:
        melhor_resultado = -peca_para_inteiro(j)
        melhor_seq_movimentos = ()
        for n in obter_posicoes_jogador(t, j):
            for i in obter_posicoes_adjacentes(n):
                if eh_posicao_livre(t,i):
                    tab = cria_copia_tabuleiro(t)
                    tab = move_peca(tab, n, i)
                    novo_resultado, nova_seq_movimentos = minimax(tab, peca_adversaria(j), p-1, seq_movimentos + ((n, i),))
                    if melhor_seq_movimentos == () or (j == cria_peca("X") and novo_resultado > melhor_resultado) or \
                       (j == cria_peca("O") and novo_resultado < melhor_resultado):
                        melhor_resultado, melhor_seq_movimentos = novo_resultado, nova_seq_movimentos

        return melhor_resultado, melhor_seq_movimentos

def posicao_vencedora(t, j):
    """
         tabuleiro × peca  → posicao
         Esta funcao ira devolver uma posicao que permita que o jogador venca, caso esteja em posicao de vencer.
     """
    c = 0
    l = 0
    for n in ("a","b","c"):
        if obter_vetor(t, n) == (cria_peca(" "), j, j) or obter_vetor(t, n) == (j, cria_peca(" "), j)\
                or obter_vetor(t, n) == (j, j,cria_peca(" ")):
            c = n

    if type(c) == str:
        for n in ("1","2","3"):
            if eh_posicao_livre(t, cria_posicao(c, n)):
                l = n

        return cria_posicao(c, l)

    for n in ("1","2","3"):
        if obter_vetor(t, n) == (cria_peca(" "), j, j) or obter_vetor(t, n) == (j, cria_peca(" "), j)\
                or obter_vetor(t, n) == (j, j,cria_peca(" ")):
            l = n

    if type(l) == str:
        for n in ("a","b","c"):
            if eh_posicao_livre(t, cria_posicao(n, l)):
                c = n

        return cria_posicao(c, l)

def bloqueio(t, j):
    """
         tabuleiro × peca  → posicao
         Esta funcao ira devolver uma posicao que evite que o jogador adversario venca,
         caso este esteja em posicao de vencer.
         Funciona de forma inversa a funcao posicao_vencedora.
     """
    return posicao_vencedora(t, peca_adversaria(j))

def posicao_central(t):
    """
         tabuleiro → posicao
         Esta funcao ira devolver a posicao central caso esta esteja livre.
     """
    if eh_posicao_livre(t,cria_posicao("b","2")):
        return cria_posicao("b", "2")

def cantos(t):
    """
         tabuleiro → posicao
         Esta funcao ira devolver uma posicao de um canto pela ordem do tabuleiro caso esta esteja livre.
     """
    for n in (cria_posicao('a', '1'),cria_posicao('c', '1'),cria_posicao('a', '3'),cria_posicao('c', '3')):
        if eh_posicao_livre(t, n):
            return n

def laterais(t):
    """
         tabuleiro → posicao
         Esta funcao ira devolver uma posicao de um lateral pela ordem do tabuleiro caso esta esteja livre.
     """
    for n in (cria_posicao('b', '1'),cria_posicao('a', '2'),cria_posicao('c', '2'),cria_posicao('b', '3')):
        if eh_posicao_livre(t, n):
            return n

def obter_movimento_auto(t, j, jogada):
    """
        tabuleiro × peca × str → tuplo de posicoes
        Esta funcao recebe um tabuleiro, uma peca de um jogador e uma cadeia de
        carateres representando o nivel de dificuldade do jogo, e devolve um tuplo com uma ou
        duas posicoes que representam uma posicao ou um movimento escolhido automaticamente.

        Na fase de colocacao o programa ira avaliar as regras da seccao 1.3.1 e caso uma seja
        valida ira devolver uma posicao proveniente das funcoes das regras. Se nao for possivel movimentar nenhuma
        peca por estarem todas bloqueadas, a funcao devolve como movimento a posicao da primeira
        peca do jogador correspondente seguida da mesma posicao que ocupa.

        Na fase de movimento, o tuplo contem a posicao de origem da peca a movimentar e a posicao de destino.
        A escolha automatica do movimento depende do nivel de dificuldade do jogo.
    """
    if numero_pecas(t, j) != 3:
        if type(posicao_vencedora(t, j)) == tuple:
            return (posicao_vencedora(t, j),)
        elif type(bloqueio(t, j)) == tuple:
            return (bloqueio(t, j),)
        elif type(posicao_central(t)) == tuple:
            return (posicao_central(t),)
        elif type(cantos(t)) == tuple:
            return (cantos(t),)
        elif type(laterais(t)) == tuple:
            return (laterais(t),)
    else:
        if jogada == "facil":
            for n in obter_posicoes_jogador(t, j):
                for i in obter_posicoes_adjacentes(n):
                    if eh_posicao_livre(t, i):
                        return (n, i)
        if jogada == "normal":
            if minimax(t, j, 1, ())[0] == peca_para_inteiro(j):
                return minimax(t, j, 1, ())[1][0]
            else:
                for n in obter_posicoes_jogador(t, j):
                    for i in obter_posicoes_adjacentes(n):
                        if eh_posicao_livre(t, i):
                            return (n, i)
        if jogada == "dificil":
            return minimax(t, j, 5, ())[1][0]

def moinho(j, jogada):
    """
        str × str → str
        Funcao principal que permite jogar um jogo completo do jogo do moinho de um jogador
        contra o computador. A funcao recebe duas cadeias de caracteres e devolve a representacao externa da
        peca ganhadora (’[X]’ ou ’[O]’). O primeiro argumento corresponde a representacao externa da peca
        com que deseja jogar o jogador humano, e o segundo argumento selecciona o nivel de dificuldade do jogo.

        Se algum dos argumentos dados forem invalidos, a funcao deve gerar um erro com a mensagem ’moinho: argumentos
        invalidos’. A funcao deve apresentar a mensagem ’Turno do computador (<nivel>):’, em que <nivel>
        corresponde a cadeia de caracteres passada como segundo argumento, quando for o turno do computador.
    """
    dicionario = {"[X]": "X", "[O]": "O"}
    j = dicionario[j]
    print("Bem-vindo ao JOGO DO MOINHO. Nivel de dificuldade {jogada}.".format(jogada=jogada))
    t = cria_tabuleiro()
    m = j
    s = peca_adversaria(m)
    print(tabuleiro_para_str(t))
    while obter_ganhador(t) == " ":
        if j == cria_peca("X"):
            obter_movimento_manual(t, m)
            print(tabuleiro_para_str(t))
            j = peca_adversaria(j)
        if obter_ganhador(t) == m or obter_ganhador(t) == s:
            break
        if j == cria_peca("O"):
            print("Turno do computador ({jogada}):".format(jogada=jogada))
            if numero_pecas(t, s) != 3:
                coloca_peca(t, s, obter_movimento_auto(t, s, jogada)[0])
            else:
                move_peca(t, obter_movimento_auto(t, s, jogada)[0], obter_movimento_auto(t, s, jogada)[1])
            print(tabuleiro_para_str(t))
            j = peca_adversaria(j)

    if obter_ganhador(t) == m:
        return peca_para_str(m)
    elif obter_ganhador(t) == s:
        return peca_para_str(s)
