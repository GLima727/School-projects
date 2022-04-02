#include <iostream>
#include <vector>
#include <queue>


// BINARY TREE 
struct Node {
    int data;
    Node* left;
    Node* right;
};
 
Node* createNode(int data){
    Node* newNode = new Node();
    if (!newNode) {
        std::cout << "Memory error\n";
        return NULL;
    }
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}
 
Node* insertNode(Node* root, int data){
    if (root == NULL) {
        root = createNode(data);
        return root;
    }
 
    std::queue<Node*> q;
    q.push(root);
 
    while (!q.empty()) {
        Node* temp = q.front();
        q.pop();
 
        if (temp->left != NULL)
            q.push(temp->left);
        else {
            temp->left = createNode(data);
            return root;
        }
 
        if (temp->right != NULL)
            q.push(temp->right);
        else {
            temp->right = createNode(data);
            return root;
        }
    }

    return root;
}

bool nodeExists(struct Node* node, int key){ // pre-order traversal
    if (node == NULL)
        return false;
 
    if (node->data == key)
        return true;
 
    bool res1 = nodeExists(node->left, key);
    if(res1) return true;
 
    bool res2 = nodeExists(node->right, key);
    return res2;
}


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

    struct Node* root = new Node();
    for (int i=0; i<u_sz; i++) 
        insertNode(root, u[i]);

    while (c != '\n') {
        std::cin >> num;
        if (nodeExists(root, num)) common.push_back(num);
        /*
        for (int i=0; i<u_sz; i++) {
            if (u[i] == num){
                common.push_back(num);
                break;}
            }
        */
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
        //std::vector<int> u = {24, 3, 36, 45, 30, 47, 25, 46, 40, 30, 41, 24, 18, 22, 33, 49, 2, 26, 19, 19, 45, 43, 31};
        std::vector<int> u = readInputVector();  
        
        int u_sz = u.size(); 
        std::vector<int> v = filter(u, u_sz);  
        //std::vector<int> v = {25, 22, 33, 21, 49, 17, 45, 35, 40, 9, 24, 11, 35, 23, 50, 49, 11, 48, 5, 31, 46, 1, 31, 45, 9, 16, 43, 26, 49, 11, 16, 38, 16, 1}; 
        int v_sz = v.size();
       // for(int i = 0; i< v_sz; i++)
          // printf("%d|", v[i]);
 //15 22 32 7 27 23 15 13 13 1 17 26 6 5 25 3 44 8 27 6 40 39 44]
 //31 22 42 7 17 23 15 13 25 14 4 11 6 5 25 3 36 17 13 43 46 10 44 2 11 1 21 14 23 11 45 12 31 49
        int b = longestCommonIncreasingSubsequence(u, v, u_sz, v_sz);

        std::cout << b << '\n';

        return 0;
    }

    return -1;
}
    
