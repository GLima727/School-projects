#include <iostream>
#include <vector>

std::vector<int> readInputVector() {

    char c = ' ';
    int num = 0;
    std::vector<int> s = std::vector<int>(0,0);

    while (c != '\n') {
        std::cin >> num;
        s.push_back(num);

        c = getchar();
    }
    return s;
}


std::vector<int> longestIncreasingSubsequence(std::vector<int> a) {
    int n = a.size();
    std::vector<int> d(n,1);
    std::vector<int> l(n,1);
    std::vector<int> c(n,0);

    int maior = 1, aux = 0;
    int n_maior = 0;
    std::vector<int> res{maior, n_maior};   //tamanho da maior SSC e nº de SSCs com esse tamanho

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (a[j] < a[i]){

                if(d[i] < d[j] + 1){

                    d[i] = d[j] + 1;
                    l[i] = l[j]; 

                    if(d[i] > res[0]){

                        res[0] = d[i];
                    }

                }
                else if (d[j] + 1 == d[i]){
                    l[i] += l[j];
                }

            }             
        }
        if(d[i] == res[0]){
            aux = res[0];
            c[aux] += l[i];
        }
    }
    if(d[0] == res[0]){
        c[aux] += l[0];
    }
    res[1] = c[aux];

    return res;
}

/*
*/
int longestCommonIncreasingSubsequence(std::vector<int> a, std::vector<int> b) {
    int a_size = a.size();
    int b_size = b.size();
    int tamanho = 0;

    //fazer matriz com a colunas e b linhas, cujas entradas (0, i) e (j, 0) sejam 0, para i = 1...a
    // e j = 1...b

    std::vector<int> colunas(a_size + 1);
    std::vector<std::vector<int>> matriz(b_size + 1, colunas);
    
    for (int i = 0; i < b_size + 1; i++) {
        matriz[i][0] = 0;
    }
    for (int j = 0; j < a_size + 1; j++) {
        matriz[0][j] = 0;
    }

    for (int i = 1; i < b_size + 1; i++) {
        for (int j = 1; j < a_size + 1; j++) {            
            if(a[i] == b[j]){
                matriz[i][j] = 1 + matriz[i - 1][j - 1];
                tamanho = matriz[i][j];
            }
            
            else{
                matriz[i][j] = std::max(matriz[i][j - 1], matriz[i - 1][j]);
            }

        }

    }

    return tamanho;
}

int main()
{
    int ex = 1;
    std::cin >> ex;

    if(ex == 1) {
        std::vector<int> v = readInputVector();
        std::vector<int>a = longestIncreasingSubsequence(v);
        //int size = a.size();

        std::cout << a.at(0) << ' ' << a.at(1);
        std::cout << "\n";
        
       return 0;
    }
    
    else if (ex == 2) {
        std::vector<int> u = readInputVector();
        std::vector<int> v = readInputVector();

        int b = longestCommonIncreasingSubsequence(u, v);

        std::cout << b << '\n';

        return 0;
    }

    return -1;
}
    
