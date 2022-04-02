#include <iostream>
#include <vector>

std::vector<int> readInputVector() {

    char c = ' ';
    int num = 0;
    std::vector<int> s(0,0);

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

//Linear search
int search(std::vector<int> arr, int x)
{
    int i, n = arr.size();
    for (i = 0; i < n; i++)
        if (arr[i] == x)
            return i;
    return -1;
}


//devolve o vetor com os elementos de u em comum com o vetor v
std::vector<int> filter(std::vector<int> u, std::vector<int> v){
    int u_sz = u.size();
    std::vector<int> common(0, 0);

    for (int i=0; i<u_sz; i++) {
        int el = search(v, u[i]);
        if (el != -1) common.push_back(v[el]);
    }

    return common;
}


int longestCommonIncreasingSubsequence(std::vector<int> a, std::vector<int> b) {
    int m = a.size();
    int n = b.size();

    /*matriz com o comprimento b de linhas e a de colunas*/
    std::vector<int> sizes(m+1);
    std::vector<std::vector<int>> size_mtx(n+1, sizes);

    for (int i=0; i<m+1; i++) {
        size_mtx[0][i] = 0;
    }
    for (int i=0; i<n+1; i++) {
        size_mtx[i][0] = 0;
    }

    for (int i=1; i<m+1; i++) {
        int longest = 0;

        for (int j=1; j<n+1; j++) {
            if (a[i-1] > a[i-2]){
                if (a[i-1] == b[j-1]) {
                    size_mtx[j][i] = size_mtx[j-1][i-1] + 1;
                    if (size_mtx[j][i] > longest){
                        longest = size_mtx[j][i];
                    }
                }

                else{
                    size_mtx[j][i] = std::max(size_mtx[j-1][i], size_mtx[j][i-1]);
                    if (a[i-1] > b[j-1]){
                        if (size_mtx[j][i] > longest){
                            longest = size_mtx[j][i];
                        }
                    }             
                }
            }

            else {
                if (a[i-1] == b[j-1]) {
                    size_mtx[j][i] = size_mtx[j-1][i-1];
                    if (size_mtx[j][i] > longest){
                        longest = size_mtx[j][i];
                    }
                }

                else {
                    size_mtx[j][i] = std::max(size_mtx[j-1][i], size_mtx[j][i-1]);
                    if (a[i-1] > b[j-1]){
                        if (size_mtx[j][i] > longest){
                            longest = size_mtx[j][i];
                        }
                    }                               
                }
            }
        }
        
    }

    int res = 0;
    for (int i=0; i<m+1; i++){
        for (int j=0; j<n+1;j++){
            if (size_mtx[j][i] > res){
                res = size_mtx[j][i];
            }
        }
    }
  
    return res;
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

        std::vector<int> w = filter(u, v);
        std::vector<int> t = filter(v, w);
        

        int res = longestCommonIncreasingSubsequence(w, t);
        std::cout << res << '\n';

        return 0;
    }

    return -1;
}
    
