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


int longestCommonIncreasingSubsequence(std::vector<int> a, std::vector<int> b, int n, int m) {
    std::vector<int> sizes(m, 0);
    int res = 0;
    for (int i=0; i<n; i++) {
        int longest = 0;

        for (int j=0; j<m; j++) {           
            if (a[i] == b[j]) {
                if (longest + 1 > sizes[j]){
                    sizes[j] = longest + 1;
                    if(res < sizes[j]){
                        res = sizes[j];
                    }
                }
            }

            else if (a[i] > b[j]){
                if (sizes[j] > longest){
                    longest = sizes[j];
                    }
                }
        }
    }

    return res;
}


std::vector<int> filter(std::vector<int> u ,int u_sz){

    std::vector<int> common = {};
    char c = ' ';
    int num = 0;

    while (c != '\n') {
        std::cin >> num;
        for (int i=0; i<u_sz; i++) {
            if (u[i] == num){
                common.push_back(num);
                break;}
            }
        c = getchar();
    }
    return common;
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
        int u_sz = u.size(); 
        std::vector<int> v = filter(u, u_sz);  
        int v_sz = v.size();

        int b = longestCommonIncreasingSubsequence(u, v, u_sz, v_sz);

        std::cout << b << '\n';

        return 0;
    }

    return -1;
}
    
