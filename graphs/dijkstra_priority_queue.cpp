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

    int N = 6;
    vvi edges = {{0,1}, {0,2}, {1,2}, {1,3}, {1,4}, {2,4}, {3,4}, {3,5}, {4,5}};
    vi costs = {10, 5, 8, 12, 6, 12, 5, 4, 6};

    vvii G = create_graph(N, edges, costs);
    vi D(N, 987654321);


    priority_queue<ii,vector<ii>, greater<ii> > Q;
    // priority_queue with reverse comparison operator,
    // so top() will return the least distance
    // initialize the start vertex, suppose it’s zero
    D[0] = 0;
    Q.push(ii(0,0));

    // iterate while queue is not empty
    while(!Q.empty()) {

        // fetch the nearest element
        ii top = Q.top();
        Q.pop();

        // v is vertex index, d is the distance
        int v = top.second, d = top.first;

        // this check is very important
        // we analyze each vertex only once
        // the other occurrences of it on queue (added earlier)
        // will have greater distance
        if(d <= D[v]) {
            // iterate through all outcoming edges from v
            traverse(G[v], it) {
                int v2 = it->second, cost = it->first;
                if(D[v2] > D[v] + cost) {
                    // update distance if possible
                    D[v2] = D[v] + cost;
                    // add the vertex to queue
                    Q.push(ii(D[v2], v2));

                }
            }
        }
    }

    print(D); // print distance vector

    return 0;
}