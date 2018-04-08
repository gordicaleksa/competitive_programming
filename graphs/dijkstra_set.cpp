#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <utility>
#include <iterator>

using namespace std;

#define all(c) (c).begin(), (c).end()
#define traverse(c, it) for(auto it = (c).begin(); it != (c).end(); ++it)

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef vector<vii> vvii;

void print(vector<int>& v) {
    for (int &x : v) {
        cout << x << " ";
    }
    cout << endl;
}

vvii create_graph(int N, vvi edges, vi costs) {
    vvii G(N);

    traverse(edges, it) {
        int vs = (*it)[0];
        int vd = (*it)[1];
        int i = distance(edges.begin(), it);
        int cost = costs[i];
        G[vs].push_back(make_pair(cost, vd));
        G[vd].push_back(make_pair(cost, vs));
    }

    return G;
}

int main() {

	const int inf = 987654321;

    // 1. raw graph data
    int N = 6;
    vvi edges = {{0,1}, {0,2}, {1,2}, {1,3}, {1,4}, {2,4}, {3,4}, {3,5}, {4,5}};
    vi costs = {10, 5, 8, 12, 6, 12, 5, 4, 6};

    // 2. data structures we need
    vvii G = create_graph(N, edges, costs);
    vi D(N, inf);
    set<ii> Q;

    // 3. init
    D[0] = 0;
    Q.insert(ii(0,0));

    // 4. start Dijkstra
    while (!Q.empty()) {

        ii current = *Q.begin();
        Q.erase(Q.begin());
        int d = current.first, v = current.second;
        
        traverse(G[v], it) {
            int cost = it->first, v2 = it->second;
            if (D[v2] > d + cost) {

                if (D[v2] != inf) {
                    Q.erase(Q.find(ii(D[v2],v2)));
                }

                D[v2] = d + cost;
                Q.insert(ii(D[v2], v2));
            }
        }

    }

    // 5. print distance vector
    print(D);

    return 0;
}