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


std::vector<int> filter(std::vector<int> u, std::vector<int> v){
    int u_sz = u.size();
    int v_sz = v.size();
    std::vector<int> common = {};

    for (int i=0; i<u_sz; i++) {
        for (int j=0; j<v_sz; j++) {
            if (u[i] == v[j])
                common.push_back(v[j]);
        }
    }

    return common;
}


int lcis(std::vector<int> x, std::vector<int> y, int a, int b) {
    if (x[a] == '\0' || y[b] == '\0')
        return 0;

    else if (x[a] == y[b])
        return 1 + lcis(x, y, a+1, b+1);

    //ver quando o elemento seguinte é menor que o anterior?
    else
        return std::max(lcis(x, y, a+1, b), lcis(x, y, a, b+1));
}


int main()
{
    int ex = 1;
    std::cin >> ex;

    if(ex == 1) {
        std::vector<int> v = readInputVector();
        std::vector<int>a = longestIncreasingSubsequence(v);

        std::cout << a.at(0) << ' ' << a.at(1);
        std::cout << "\n";
        
        return 0;
    }
    
    else if (ex == 2) {
        std::vector<int> u = readInputVector();
        std::vector<int> v = readInputVector();

        std::vector<int> w = filter(v, u);
        
        u.push_back('\0');
        w.push_back('\0');
        std::cout << lcis(u, w, 0, 0) << '\n';

        return 0;
        
        /*
        for (int x=0; x<ws; x++)
            std::cout << w.at(x) << ' ';
        std::cout << '\n';
        */
        
        /*
        int b = longestCommonIncreasingSubsequence(u, v);

        std::cout << b << '\n';
        */
    }

    return -1;
}
    
