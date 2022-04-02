:- [codigo_comum].
:- set_prolog_flag(answer_write_options,[max_depth(0)]).

/* |----------------------------------------------|
   | Guilherme Goncalves Gutierrez de Lima 199077 |
   |----------------------------------------------|
   |     Solucionador de Puzzles Kakuro           |    
   |----------------------------------------------|
*/

/*  combinacoes_soma(N, Els, Soma, Combs).
    Em que N e um inteiro, Els e uma Lista de inteiros, e Soma e um inteiro,
    significa que Combs e a lista ordenada cujos elementos sao as combinacoes N a N,
     dos elementos de Els cuja soma e Soma.

    Neste predicado iremos receber as combinacoes dos Elementos da Lista
    recebida cuja soma de elementos sera igual a um certo numero.
    Para  combinacoes_soma(2, [1,2,3,4,5,6,7,8,9], 13, Combs), o output sera
    Combs = [[4, 9], [5, 8], [6, 7]].                                                   */

combinacoes_soma(N, Els, Soma, Res) :-
    findall(Z,(combinacao(N, Els, Z), sum_list(Z,Soma)), Res).

/*  permutacoes_soma(N, Els, Soma, Perms)
    Em que N e um inteiro, Els e uma lista de inteiros, e Soma e um inteiro,
    significa que Perms e a lista ordenada cujos elementos sao as permutacoes das combinacoes N a N,
    dos elementos de Els cuja soma e Soma.

    O predicado findall ira conseguir as permutacoes das combinacoes em uma lista desordenada.
    Perms = [[4,9],[9,4],[5,8],[8,5],[6,7],[7,6]]. (antes do sort)
    Com a utilizacao do sort, conseguimos ordenar de forma ascendente (@<) e devolver para o output.
    Perms = [[4,9],[5,8],[6,7],[7,6],[8,5],[9,4]]. (depois do sort)*/


permutacoes_soma(N, Els, Soma, Res) :-
    findall(G, (combinacao(N, Els, X),permutation(X,G), sum_list(G,P), P =:= Soma),List),
    sort(List,Res).

 /* espaco_fila(Fila, Esp, H_V).
    Em que Fila e uma fila (linha ou coluna) de um puzzle e H_V e um dos atomos h ou v,
    conforme se trate de uma fila horizontal ou vertical, respectivamente,
    significa que Esp e um espaco de Fila.
    Este predicado e simplesmente uma subdivisao da lista obtida no predicado espacos_fila.*/

espaco_fila(Fila,X,h):-
    espacos_fila(h,Fila,Esp),
    member(X, Esp).

espaco_fila(Fila,X,v):-
    espacos_fila(v,Fila,Esp),
    member(X, Esp).

/*  espacos_fila(H_V, Fila, Espacos).
    Em que Fila e uma fila (linha ou coluna) de uma grelha e e H_V e um dos atomos h ou v,
    significa que Espacos e a lista de todos os espacos de Fila, da esquerda para a direita.
    Este predicado utilizou um predicado auxiliar que ajudou a criar os espacos.
    O conceito e percorrer uma Fila, avaliar os elementos e avancar ate a lista ficar vazia.
    Cada vez que o primeiro elemento da Fila e uma lista nao vazia, que nao esta seguida de uma
    lista ou que nao seja o ultimo elemento, o predicado auxiliar ira unificar essa lista com as 
    variaveis a sua frente, obtendo um espaco.*/

/* Caso terminal. */
espacos_fila(_,[],[]).

/* Verifica se o elemento da lista e [0,0]. */
espacos_fila(h,[H|R],Lista) :-
    H == [0,0],
    espacos_fila(h, R, Lista),!.

espacos_fila(v, [H|R], Lista) :-
    H == [0,0],
    espacos_fila(v, R, Lista),!.

/* Verifica se o primeiro elemento da Fila nao e uma lista. */
espacos_fila(h, [H|R], Lista):-
    \+ is_list(H),
    espacos_fila(h, R, Lista).

espacos_fila(v, [H|R], Lista):-
    \+ is_list(H),
    espacos_fila(v, R, Lista),!.

/* Verifica se estamos no ultimo elemento da lista. */
espacos_fila(h,R,Lista):-
    is_list(R),
    length(R,1),
    espacos_fila(h,[],Lista),!.

espacos_fila(v,R,Lista):-
    is_list(R),
    length(R,1),
    espacos_fila(v,[],Lista),!.

/* Verifica se o proximo elemento e uma lista. */
espacos_fila(h, [_|R], Lista):-
    nth0(0,R,Nxt),
    is_list(Nxt),
    espacos_fila(h, R, Lista),!.

espacos_fila(v, [_|R], Lista):-
    nth0(0,R,Nxt),
    is_list(Nxt),
    espacos_fila(v, R, Lista),!.

/* Verifica se o proximo elemento nao e uma lista para unificar. */
espacos_fila(h, [H|R],[espaco(El,List)|Resto]) :-
    is_list(H),
    nth0(0,R,Nxt),
    \+ is_list(Nxt),
    nth0(1,H,El),
    aux(R,List),
    espacos_fila(h, R,Resto),!.

espacos_fila(v, [H|R],[espaco(El,List)|Resto]) :-
    is_list(H),
    nth0(0,R,Nxt),
    \+ is_list(Nxt),
    nth0(0,H,El),
    aux(R,List),
    espacos_fila(v, R,Resto),!.

/* Funcao auxiliar que ira percorrer uma lista, enviar os elementos que le para uma lista,
   e parar quando encontrar uma lista. */

aux([H|T], [H|R]) :-
    \+ is_list(H),
    aux(T, R).
aux([H|_], []) :- is_list(H).
aux([], []).

/* espacos_puzzle(Puzzle, Espacos)    
   Em que Puzzle E um puzzle, significa que Espacos E a lista de espacos de Puzzle,
   Este predicado utiliza um predicado auxiliar que agrupa as filas de um puzzle e descobre os espacos.
   Ira descobrir as filas de um puzzle e de um puzzle invertido para conseguir espacos verticais
   e horizontais.
*/
aux_puzzle(Puzzle,Res,H_V) :-
    member(X, Puzzle),
    espaco_fila(X,Res,H_V).

espacos_puzzle(Puzzle, Espacos):-
    mat_transposta(Puzzle, Inv_Puzzle),
    bagof(Z, aux_puzzle(Puzzle,Z,h),List),
    bagof(Z, aux_puzzle(Inv_Puzzle,Z,v) ,List2),
    append(List,List2,Espacos),!.

espacos_puzzle(_,[]).

/* espacos_com_posicoes_comuns(Espacos, Esp, Esps_com)
   Em que Espacos e uma lista de espacos e Esp e um espaco,
   significa que Esps_com e a lista de espacos com variaveis em comum com Esp, exceptuando Esp.
   Os espacos em Esps_com devem aparecer pela mesma ordem que aparecem em Espacos.
   Este predicado utilizou um predicado auxiliar que verifica membros em comum entre duas listas para
   devolver apenas espacos com membros comuns entre as suas listas.
*/
espacos_com_posicoes_comuns(Lista, Esp1, Res):-
    bagof(X, List2^List1^El2^El^(member(X,Lista), espaco(El,List1) = X, espaco(El2,List2) = Esp1, List1 \== List2, membro_comum(List1,List2)), Res).

/* Funcao auxiliar que ira devolver false se nao houver elementos em comum. */
el_comum(X, [H|_]) :-
    X == H.
el_comum(X, [_|T]) :-
    el_comum(X, T).

membro_comum([H|_], L2) :-
    el_comum(H, L2).
membro_comum([_|T], L2) :-
    membro_comum(T, L2).


/* permutacoes_soma_espacos(Espacos, Perms_soma)
    Em que Espacos e uma lista de espacos, significa que Perms_soma e
    a lista de listas de 2 elementos, em que o 1o elemento e um espaco de Espacos
    e o 2o e a lista ordenada de permutacoes cuja soma e igual a soma do espaco.

    Este predicado utilizou nas permutacoes_soma o elemento do espacos recebidos,
    (3 em espaco(3,Lista)) como Soma dos elementos das permutacoes, e o numero de elementos
    da Lista do espaco como tamanho das permutacoes.
*/
permutacoes_soma_espacos(Fila, Res):-
    bagof([espaco(H,Els),Perms], L^(member(espaco(H,Els),Fila), length(Els,L), permutacoes_soma(L, [1,2,3,4,5,6,7,8,9], H, Perms) ),Res).

/* permutacao_possivel_espaco(Perm, Esp, Espacos, Perms_soma).
    Em que Perm e uma permutacao, Esp e um espaco, Espacos e uma lista de espacos, e
    Perms_soma e uma lista de listas tal como obtida pelo predicado anterior, significa que
    Perm e uma permutacao possivel para o espaco Esp.
    Este predicado ira consguir as permutacoes desejadas atraves do predicado permutacoes_soma
    e ira escolher a desejada atraves do predicado permutacao_compativel.
*/
permutacao_possivel_espaco(Perm, Esp, Espacos, Perms_soma):-
    espacos_com_posicoes_comuns(Espacos, Esp, Esp_coms),
    espaco(H,List) = Esp,
    obter_perms(Esp_coms,Perms_soma,Res),
    length(List,L),
    permutacoes_soma(L,[1,2,3,4,5,6,7,8,9],H,Perms_totais),
    member(X, Perms_totais),
    permutacao_compativel(X, Res),
    Perm = X.

/* Caso terminal. */
permutacao_compativel([],_).
permutacao_compativel(_,[]).

/*  Este predicado ira verificar se uma permutacao e compativel com uma lista de permutacoes,
    para isso ira utilizar um predicado auxiliar que ira avaliar os membros de cada permutacao e 
    verificar se sao iguais. 
    Este predicado recebe uma lista [8,9] por exemplo e verifica se os elementos (8 e 9) sao compativeis
    com as varias permutacoes da lista de permutacoes. Caso nao o seja retorna false. */
    
permutacao_compativel([Perm1|R], [H|T]):-
    permutacao_compativel_auxiliar(Perm1,H),
    permutacao_compativel(R, T),!. 

/* Este predicado ira verificar se os valores da lista Res
    pertencem a permutacao recebida. */
permutacao_compativel_auxiliar(Perm, Res) :-
    member(Z,Res),
    member(Perm,Z),!.

/*Este predicado ira obter as permutacoes dos espacos comuns. */
obter_perms(Esp_coms, Perms_soma, Res):-
    bagof(X, obter_perms_aux(Esp_coms,Perms_soma,X), Res).

obter_perms_aux(H, X, Res):-
    member(Z , H),
    member([Z , Res], X).

/*  permutacoes_possiveis_espaco(Espacos, Perms_soma, Esp,Perms_poss).
    Em que Espacos e uma lista de espacos, Perms_soma e uma lista
    de listas tal como obtida pelo predicado permutacoes_soma_espacos, e Esp e um
    espaco, significa que Perms_poss e uma lista de 2 elementos em que o primeiro e a lista
    de variaveis de Esp e o segundo e a lista ordenada de permutacoes possiveis para o espaco Esp.
    Este predicado ira passar as permutacoes possiveis do espaco para uma lista,
    e adiciona-la a sua lista de elementos.
*/
permutacoes_possiveis_espaco(Espacos, Perms_soma, Esp,Perms_poss):-
    espaco(_,Lista) = Esp,
    bagof(Perm,permutacao_possivel_espaco(Perm, Esp, Espacos, Perms_soma),Perms),
    append([Lista],[Perms],Perms_poss).

/* permutacoes_possiveis_espacos(Espacos, Perms_poss_esps).
    Em que Espacos e uma lista de espacos, significa que Perms_poss_esps e a
    lista de permutacoes possiveis.
    Este predicado ira utilizar o predicado permutacoes_possiveis_espaco em cada espaco do puzzle,
    para obter as suas permutacoes possiveis.
*/
permutacoes_possiveis_espacos(Espacos, Perms_poss_esps):-
    bagof(Perms_poss,Esp^Perms_soma^(member(Esp,Espacos),permutacoes_soma_espacos(Espacos, Perms_soma),permutacoes_possiveis_espaco(Espacos, Perms_soma, Esp,Perms_poss)),Perms_poss_esps).

/*  numeros_comuns(Lst_Perms, Numeros_comuns).
    Em que Lst_Perms e uma lista de permutacoes, significa que Numeros_comuns e uma
    lista de pares (pos, numero), significando que todas as listas de Lst_Perms
    contem o numero numero na posicao pos.
    Este predicado ira envolver varias funcoes auxiliares, cada uma com o seu proposito.*/

/*  O predicado vazio ira remover as listas vazias dos nosso numeros_comums_listas
    para conseguirmos apenas os numeros comuns. */
vazio([]).

/*  Este predicado ira receber os numeros comums em listas e com listas vazias,
    entao ira remover as listas vazias com o exclude e obter apenas os numeros comums.
    No fundo este predicado ira limpar o resultado para devolver. */
numeros_comuns(Lst_Perms, Numeros_comuns):-
    nth1(1,Lst_Perms,Lista1),
    length(Lista1,L),
    numeros_comums_auxiliar(Lst_Perms,0,L, Res),
    exclude(vazio, Res, Numeros_comuns_listas),
    findall(Y,(member(X,Numeros_comuns_listas), [Y] = X),Numeros_comuns).

/*  Este predicado sera a principal que ira obter todos os numeros comums numa lista.
    Com um contador ira percorrer todos os indexs das listas e verificar se os
    elementos sao iguais, obtendo os numeros comums. */
numeros_comums_auxiliar(Lst_Perms, Num, L, [Numeros_comuns|R]):-
    soma(Num,1,Id),
    Id =< L,
    findall((Id,X), numeros_comuns_aux(Lst_Perms,Id,X), Numeros_comuns),
    numeros_comums_auxiliar(Lst_Perms, Id,L, R),!.

/*  Como este predicado percorre todos os elementos da lista,
    a sua posicao nao podera ser maior que o numero de elementos da lista,
    logo ira parar. */
numeros_comums_auxiliar(_, Num,L, []):-
    soma(Num,1,Id),
    Id > L,!.

/*  Esta e o segundo predicado auxiliar que ira verificar se uma certa posicao das listas
    tem um numero igual em todas as posicoes. */
numeros_comuns_aux(Lista,Id,Num):-
    findall(X,(member(El,Lista), nth1(Id,El,X)),Z),
    comparar(Z),
    nth1(1,Z,Num).

/*Este predicado soma A com X, sera utilizada para percorrer as posicoes das listas.*/
soma(A,X,S) :-
  S is A+X .

/*Este predicado ira devolver true se uma lista tiver todos os elementos iguais, e false caso nao */
comparar([]).
comparar([X|Y]):-aux_comparar(Y,X).

aux_comparar([],_).
aux_comparar([Y|X],Y) :- aux_comparar(X,Y).

/*  atribui_comuns(Perms_Possiveis).
    Em que Perms_Possiveis e uma lista de permutacoes possiveis,
    actualiza esta lista atribuindo a cada espaco numeros comuns
    a todas as permutacoes possiveis para esse espaco.
    Este predicado utilizou um maplist que ira enviar cada elemento das
    permutacoes possiveis para um predicado auxiliar onde ira obter os
    numeros comuns e atraves do predicado novo_espaco, alterar o espaco
    e os seus elementos.
 */
atribui_comuns(Perms_poss_esps):-
    maplist(atribui_comuns_aux,Perms_poss_esps).

atribui_comuns_aux([Els,Perms]):-
    numeros_comuns(Perms,Nums_coms),
    novo_espaco(Nums_coms,Els).

/* Este predicado ira alterar o espaco recebido atribuindo numeros comuns. */
novo_espaco([],_).

novo_espaco([H|T],Els):-
    (Id,Num) = H,
    nth1(Id,Els,Num),
    novo_espaco(T,Els),!.

/*  retira_impossiveis(Perms_Possiveis, Novas_Perms_Possiveis).
    Em que Perms_Possiveis e uma lista de permutacoes possiveis, significa que
    Novas_Perms_Possiveis e o resultado de tirar permutacoes impossiveis de Perms_Possiveis. */
retira_impossiveis(Perms_Possiveis, Novas_Perms_Possiveis):-
    bagof([Els,New_Perms],X^Perms^(member(X,Perms_Possiveis), [Els,Perms] = X, retira_impossiveis_aux(Els,Perms,New_Perms)),Novas_Perms_Possiveis ).

/*Este predicado ira retirar as permutacoes impossiveis de uma lista de permutacoes.*/
retira_impossiveis_aux(Els,Perms,New_Perms):-
    findall(Perm,(member(Perm,Perms), compatibilidade(Els,Perm)),New_Perms).

/* Este predicado ira verificar se uma lista de numeros e,ou variaveis e compativel com outra lista
    de numeros. Por exemplo, [1,A,B,3] e compativel com [1,2,4,3] mas nao [1,2,3,4].
    Retorna false caso seja incompativel e true caso seja compativel.*/
compatibilidade([],[]):- true.
compatibilidade([H|T],[_|Tail]):-
    \+ number(H),
    compatibilidade(T,Tail),!.

compatibilidade([H|T],[Head|Tail]):-
    number(H),
    H =:= Head,
    compatibilidade(T,Tail),!.

/*  simplifica(Perms_Possiveis, Novas_Perms_Possiveis).
    Em que Perms_Possiveis e uma lista de permutacoes possiveis, significa que
    Novas_Perms_Possiveis e o resultado de simplificar Perms_Possiveis.
    Para simplificar uma lista de permutacoes possiveis, deve aplicar-lhe os
    predicados atribui_comuns e retira_impossiveis, por esta ordem, ate nao haver mais alteracoes.
    Este predicado ira apenas atribuir os elementos comuns e retirar os impossiveis ate a lista 
    antes de ser alterada e a lista obtida serem iguais.
*/
simplifica(Perms_Possiveis, Novas_Perms_Possiveis):-
    atribui_comuns(Perms_Possiveis),
    retira_impossiveis(Perms_Possiveis, Novas_Perms_Possiveis_verificador),
    Novas_Perms_Possiveis_verificador \= Perms_Possiveis,
    simplifica(Novas_Perms_Possiveis_verificador, Novas_Perms_Possiveis).

simplifica(Perms_Possiveis, Novas_Perms_Possiveis_verificador):-
    atribui_comuns(Perms_Possiveis),
    retira_impossiveis(Perms_Possiveis, Novas_Perms_Possiveis_verificador),
    Novas_Perms_Possiveis_verificador == Perms_Possiveis.

/*  inicializa(Puzzle, Perms_Possiveis).
    Em que Puzzle e um puzzle, significa que Perms_Possiveis e a lista de permutacoes possiveis simplificada para Puzzle.
    Este predicado ira utilizar espacos_puzzle, permutacoes_possiveis_espacos e simplifica para inicializar o Puzzle.
*/
inicializa(Puzzle, Novas_Perms_Possiveis):-
    espacos_puzzle(Puzzle, Espacos),
    permutacoes_possiveis_espacos(Espacos, Perms_Possiveis),
    simplifica(Perms_Possiveis, Novas_Perms_Possiveis).


/*  escolhe_menos_alternativas(Perms_Possiveis, Escolha).
    Em que Perms_Possiveis e uma lista de permutacoes possiveis, significa que Escolha
    e o elemento de Perms_Possiveis. Se todos os espacos em Perms_Possiveis
    tiverem associadas listas de permutacoes unitarias, o predicado deve devolver "falso".
    Este predicado ira ter um predicado auxiliar que ira devolver uma lista de listas,
    onde o ultimo elemento sera a nossa Escolha.
    Caso a lista de listas tenha apenas uma lista a Escolha sera essa lista em si.
*/
escolhe_menos_alternativas(Perms_Possiveis, Escolha):-
    escolhe_menos_alternativas_aux(Perms_Possiveis, 999, Escolha_lista),
    length(Escolha_lista,L),
    L =:= 1,
    nth1(1,Escolha_lista,Escolha).

escolhe_menos_alternativas(Perms_Possiveis, Escolha):-
    escolhe_menos_alternativas_aux(Perms_Possiveis, 999, Escolha_lista),
    length(Escolha_lista,L),
    L =\= 1,
    last(Escolha_lista,Escolha).

escolhe_menos_alternativas_aux([ [Els,Perms] | Resto],Min, [[Els,Perms] | Rest]):-
    length(Perms, L),
    L > 1,
    L < Min,
    escolhe_menos_alternativas_aux( Resto, L, Rest),!.

escolhe_menos_alternativas_aux([ [_,Perms] | Resto],Min, Escolha):-
    length(Perms, L),
    L > 1,
    L >= Min,
    escolhe_menos_alternativas_aux( Resto, Min, Escolha),!.

escolhe_menos_alternativas_aux([ [_,Perms] | Resto],Min, Escolha):-
    length(Perms, L),
    L =:= 1,
    escolhe_menos_alternativas_aux( Resto, Min, Escolha),!.

escolhe_menos_alternativas_aux([],_,[]).

/*  A chamada experimenta_perm(Escolha, Perms_Possiveis,Novas_Perms_Possiveis),
    em que Perms_Possiveis e uma lista de permutacoes possiveis, e Escolha e
    um dos seus elementos (escolhido pelo predicado anterior), segue os seguintes passos:
    1. Sendo Esp e Lst_Perms o espaco e a lista de permutacoes de Escolha,
    respectivamente, escolhe uma permutacao de Lst_Perms, Perm.
    Utilize o predicado member para escolher esta permutacao.
    2. Unifica Esp com Perm.
    3. Novas_Perms_Possiveis e o resultado de substituir, em Perms_Possiveis, o
    elemento Escolha pelo elemento [Esp, [Perm]].
    Este predicado ira obter a Posicao da Escolha nas Permutacoes Possiveis,
    e ira alterar essa mesma posicao com um membro das permutacoes da Escolha.*/

experimenta_perm(Escolha, Perms_Possiveis,Novas_Perms_Possiveis):-
    [Els, Perm] = Escolha,
    nth1(Id,Perms_Possiveis,[Els, Perm],Rest),
    member(X,Perm),
    Els = X,
    nth1(Id,Novas_Perms_Possiveis,[Els,[X]],Rest).

/*  resolve_aux(Perms_Possiveis, Novas_Perms_Possiveis).
    Em que Perms_Possiveis e uma lista de permutacoes possiveis, significa que
    Novas_Perms_Possiveis e o resultado de aplicar um algoritmo. 
    Neste predicado iremos aplicar um algoritmo de escolher a permutacao com menos alternativas,
    exmprimentar essa permutacao e simplificar, ate as Novas_Perms_Possiveis conter apenas
    uma Permutacao por espaco.
*/
 
resolve_aux(Perms_Possiveis, Novas_Perms_Possiveis):-
    escolhe_menos_alternativas(Perms_Possiveis,Escolha),
    experimenta_perm(Escolha, Perms_Possiveis, Novas_Perms_Possiveis_aux),
    simplifica(Novas_Perms_Possiveis_aux, Novas_Perms_Possiveis_simp),
    resolve_aux(Novas_Perms_Possiveis_simp ,Novas_Perms_Possiveis),!.

resolve_aux(Perms_Possiveis, Perms_Possiveis).

/*  resolve(Puz). 
    Em que Puz e um puzzle, resolve esse puzzle, isto e, apos a invocacao
    deste predicado a grelha de Puz tem todas as variaveis substituidas por numeros que
    respeitam as restricoes Puz.
    Este predicado ira simplesmente inicializar o puzzle e utilizar o predicado
    resolve_aux para resolve-lo. */

resolve(Puzzle):-
    inicializa(Puzzle, Perms_Possiveis),
    resolve_aux(Perms_Possiveis, _).