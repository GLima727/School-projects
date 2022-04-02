#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define WHITE -1
#define GRAY 0
#define BLACK 1
#define COMMON 2

void addEdge(int a, int b, vector<vector<int>> &invTree)
{
    invTree[b].push_back(a);
}
bool isNodeValid(int b, vector<int> &sizes)
{
    sizes[b] += 1;
    if (sizes[b] > 2)
    {
        return false;
    }
    return true;
}

bool dfs_aux(const int v, vector<bool> &visited, vector<bool> &stack, vector<vector<int>> &invTree)
{
    if (visited[v] == false)
    {
        visited[v] = true;
        stack[v] = true;
        for (auto i = invTree[v].begin(); i != invTree[v].end(); ++i)
        {
            if (!visited[*i] && dfs_aux(*i, visited, stack, invTree))
                return true;
            else if (stack[*i])
                return true;
        }
    }
    stack[v] = false;
    return false;
}

bool dfs(const int size, vector<vector<int>> &invTree)
{

    vector<bool> visited(size);
    vector<bool> stack(size);

    for (int i = 0; i < size; i++)
    {
        visited[i] = false;
        stack[i] = false;
    }

    for (int i = 0; i < size; i++)
        if (dfs_aux(i, visited, stack, invTree))
            return true;

    return false;
}


void bfs(int v, vector<int> &bfs, vector<vector<int>> &invTree)
{
    int u;

    bfs[v] = GRAY;
    queue<int> q;
    q.push(v);

    while (!(q.empty()))
    {
        u = q.front();
        q.pop();
        for (int n : invTree[u + 1])
        {
            if (bfs[n - 1] == WHITE)
            {
                bfs[n - 1] = GRAY;
                q.push(n - 1);
            }
        }
        bfs[u] = BLACK;
    }
}

void findCommonAncestors(int size, vector<vector<int>> &invTree, vector<int> &bfs1, vector<int> &bfs2, vector<int> &numParents, vector<int> &ancestors)
{
    for (int i = 0; i < size; i++)
    {

        if (bfs1[i] == bfs2[i] && bfs1[i] == BLACK)
        {

            ancestors.push_back(i + 1);

            for (int j : invTree[i + 1])
            {
                numParents[j]++;
            }
        }
    }
}

int create_tree(vector<vector<int>> &invTree)
{

    int v, e, s, d;
    vector<int> sizes;

    if (scanf("%d %d\n", &v, &e) != 2)
    {
        printf("0\n");
        return -1;
    }
    invTree = vector<vector<int>>(v + 1, vector<int>());
    for (int i = 0; i < v; i++)
        sizes.push_back(0);
    for (int i = 0; i < e; i++)
    {
        if (scanf("%d %d\n", &s, &d) != 2)
        {
            printf("0\n");
            return 0;
        }
        else
        {
            addEdge(s, d, invTree);
            if (!isNodeValid(d, sizes))
            {
                printf("0\n");
                return -1;
            }
        }
    }
    return v;
}

int main()
{
    int v1, v2, v;
    vector<vector<int>> invTree;

    if (scanf("%d %d\n", &v1, &v2) != 2)
    {
        printf("0\n");
        return 0;
    }

    v = create_tree(invTree);
    if (v == -1)
        return 0;

    if (dfs(v, invTree))
    {
        printf("0\n");
        return 0;
    }

    if (v1 == v2)
    {
        printf("%d \n", v1);
        return 0;
    }
    vector<int> bfs1(v, WHITE);
    vector<int> bfs2(v, WHITE);
    vector<int> ancestors;
    vector<int> numParents = vector<int>(v + 1, 0);
    vector<int> nodes;

    bfs(v1 - 1, bfs1, invTree);
    bfs(v2 - 1, bfs2, invTree);

    findCommonAncestors(v, invTree, bfs1, bfs2, numParents, ancestors);

    int k = ancestors.size();

    if (k == 0)
    {
        printf("-\n");
        return 0;
    }

    for (int i = 0; i < k; i++)
    {
        if (numParents[ancestors[i]] == 0)
        {
            printf("%d ", ancestors[i]);
        }
    }
    printf("\n");
    return 0;
}