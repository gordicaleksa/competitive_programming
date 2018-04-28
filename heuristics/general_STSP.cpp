#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <random>
#include <algorithm>
#include <queue>
#include <utility>
#include <numeric>
using namespace std;

typedef vector<int> vi;
typedef vector<vector<int>> vvi;

#define all(v) (v).begin(), (v).end()

// solution #1
int travellingSalesmanProblem(vvi& graph, vi& path, int s) {
	// store all vertices apart from source vertex
	vi vertices;
	for (int i = 0; i < graph.size(); i++)
		if (i != s)
			vertices.push_back(i);

	// store minimum weight Hamiltonian Cycle.
	int min_path = numeric_limits<int>::max();
	int n = graph.size();
	// n^2 was max number of iterations beyond that we get TLE
	for (int i = 0; i < n*n; i++) {

		int current_pathweight = 0;

		// compute path weight for this random permutation
		int k = s;
		for (int i = 0; i < vertices.size(); i++) {
			current_pathweight += graph[k][vertices[i]];
			k = vertices[i];
		}
		current_pathweight += graph[k][s];

		// update minimum
		if (current_pathweight < min_path) {
			min_path = current_pathweight;
			path = vertices;
		}
		
		// shuffle again
		std::random_shuffle(all(vertices));
	}

	return min_path;
}

// A utility function to find the vertex with minimum key value, from
// the set of vertices not yet included in MST
int min_key(vector<int>& key, vector<int>& visited)
{
	// Initialize min value
	int min = numeric_limits<int>::max(), min_index;

	for (int v = 0; v < key.size(); v++)
		if (visited[v] == 0 && key[v] < min)
			min = key[v], min_index = v;

	return min_index;
}

void build_path(vector<int>& parents, vector<vector<int>>& graph, vector<int>& path, int parent) {
	for (int i = 0; i < parents.size(); i++) {
		if (parents[i] == parent) {
			path.push_back(i);
			build_path(parents, graph, path, i);
		}
	}
}

// A utility function to print the solution
void print_solution(vector<int>& parent, vector<vector<int>>& graph)
{
	vector<int> path;
	build_path(parent, graph, path, 0);
	// find cost of this path
	int cost = 0;
	for (int i = 0; i < path.size() - 1; i++) {
		cost += graph[path[i]][path[i + 1]];
	}
	cost += graph[0][path[0]];
	cost += graph[path[path.size() - 1]][0];
	// print the solution in requested format:
	cout << cost << endl;
	cout << "1 ";
	for (int &i : path) cout << i + 1 << " ";
	cout << "1" << endl;
}


// we can make it smarter ;) don't do preorder traversal do maybe greedy locally
// solution #2: 2-approximate algo using MST (assumes triangle inequality)
void mst_tsp(vector<vector<int>>& graph)
{
	int n = graph.size();
	vi parent(n); // Array to store constructed MST
	vi key(n);    // Key values used to pick minimum weight edge in cut
	vi visited(n);// To represent set of vertices not yet included in MST

	// Initialize all keys as INFINITE
	int inf = numeric_limits<int>::max();
	for (int i = 0; i < n; i++)
		key[i] = inf, visited[i] = 0;

	// Always include first 1st vertex in MST.
	key[0] = 0;     // Make key 0 so that this vertex is picked as first vertex
	parent[0] = -1; // First node is always root of MST 

	// The MST will have n vertices
	for (int count = 0; count < n - 1; count++)
	{
		// Pick the minimum key vertex from the set of vertices
		// not yet included in MST
		int u = min_key(key, visited);
		// Add the picked vertex to the MST Set
		visited[u] = 1;
		// Update key value and parent index of the adjacent vertices of
		// the picked vertex. Consider only those vertices which are not yet
		// included in MST
		for (int v = 0; v < n; v++)
			// graph[u][v] is non zero only for adjacent vertices of m
			// visited[v] is false for vertices not yet included in MST
			// Update the key only if graph[u][v] is smaller than key[v]
			if (graph[u][v] && visited[v] == false && graph[u][v] <  key[v])
				parent[v] = u, key[v] = graph[u][v];
	}
	// print the solution
	print_solution(parent, graph);
}

int random(int n) {
	// range is inclusive
	const int range_from = 0;
	const int range_to = n - 1;

	std::random_device                  rand_dev;
	std::mt19937                        generator(rand_dev());
	std::uniform_int_distribution<int>  r(range_from, range_to);

	return r(generator);
}

// solution #3: NN (nearest neighbour) greedy algorithm (resembles Prim's algo)
void nearest_neighbour_tsp(vvi& graph) {
	int n = graph.size();
	int start = random(n);
	vi visited(n, 0);
	visited[start] = 1;
	int current = start, next = start;

	// init path and result
	vi path = { start };
	int res = 0;
	for (int i = 0; i < n - 1; i++) {
		int min = numeric_limits<int>::max();

		// find nearest, unvisited neighbor
		for (int j = 0; j < n; j++) {
			if (!visited[j] && graph[current][j] < min) {
				min = graph[current][j];
				next = j;
			}
		}
		// update path and path weight
		path.push_back(next);
		res += min;
		// mark as visited
		visited[next] = 1;
		current = next;
	}
	// close the cycle
	path.push_back(start);
	res += graph[next][start];

	// print the result in requested format
	cout << res << endl;
	for (int& i : path) cout << i + 1 << " ";
	cout << endl;
}

class Edge {
public:
	int from, to;
	int cost;
	Edge(int f, int t, int c) : from(f), to(t), cost(c) {}
	bool operator<(const Edge& e) const {
		return cost < e.cost;
	}
	// prints out this point/vector in format (x,y) (used for debugging)
	friend ostream& operator<<(ostream& strm, const Edge& e) {
		return strm << "(" << e.cost << " (" << e.from << "," << e.to << "))";
	}
};

// solution #4: got WA bad algo for this data set
// Greedy (resembles Kruskal's algo) O(n^2*log(n))
void greedy_tsp(vvi& graph, vector<Edge>& edges) {
	int n = graph.size();
	vector<list<int>> path(n / 2); // n/2 for maximum of n/2 connected components
	int res = 0;

	unordered_map<int, int> visited; // which node and to which connected component does it belong
	unordered_set<int> visited2;
	unordered_set<int> not_visited2;
	for (int i = 0; i < n; i++) not_visited2.insert(i);
	int cnt = 0;
	int cid = 0; // connected component id
	for (Edge e : edges) {
		int f = e.from, t = e.to, c = e.cost;

		if (visited2.find(f) != visited2.end() || visited2.find(t) != visited2.end()) continue;

		unordered_map<int, int>::iterator it1 = visited.find(f);
		unordered_map<int, int>::iterator it2 = visited.find(t);

		if (it1 == visited.end() && it2 == visited.end()) {
			visited.insert(make_pair(f, cid));
			visited.insert(make_pair(t, cid));
			// update path
			(path[cid]).push_back(f + 1);
			(path[cid]).push_back(t + 1);
			cid++;
		}
		else if ((it1 == visited.end() && it2 != visited.end()) || (it1 != visited.end() && it2 == visited.end())) {
			if (it1 != visited.end()) {
				visited2.insert(it1->first);
				not_visited2.erase(it1->first);
				visited.insert(make_pair(t, it1->second));
				// update path
				if (path[cid - 1].front() == f + 1)
					(path[cid - 1]).push_front(t + 1);
				else
					(path[cid - 1]).push_back(t + 1);
			}
			else {
				visited2.insert(it2->first);
				not_visited2.erase(it2->first);
				visited.insert(make_pair(f, it2->second));
				// update path
				if (path[cid - 1].front() == t + 1)
					(path[cid - 1]).push_front(f + 1);
				else
					(path[cid - 1]).push_back(f + 1);
			}
		}
		else {
			if (it1->second == it2->second) continue;
			else {
				visited2.insert(f);
				visited2.insert(t);
				not_visited2.erase(f);
				not_visited2.erase(t);
				int mini = min(it1->second, it2->second);
				int maxi = max(it1->second, it2->second);
				// update path
				if (path[mini].front() == t + 1 || path[mini].front() == f + 1) {
					if (path[maxi].front() == t + 1 || path[maxi].front() == f + 1) {
						path[maxi].reverse();
						(path[mini]).splice((path[mini]).begin(), path[maxi]);
					}
					else {
						(path[mini]).splice((path[mini]).begin(), path[maxi]);
					}
				}
				else {
					if (path[maxi].front() == t + 1 || path[maxi].front() == f + 1) {
						(path[mini]).splice((path[mini]).end(), path[maxi]);
					}
					else {
						path[maxi].reverse();
						(path[mini]).splice((path[mini]).end(), path[maxi]);
					}
				}
				// update so that both components have same cid (component id)
				for (auto it = visited.begin(); it != visited.end(); it++) {
					if (it->second == maxi) it->second = mini;
				}
			}
		}

		res += c; // add current edge cost

		cnt++;
		if (cnt >= n - 1) break; // if we collected n-1 edges break out of loop
	}

	// add last edge
	int n1 = *(not_visited2.begin());
	auto ittmp = not_visited2.end();
	ittmp = prev(ittmp);
	int n2 = *ittmp;
	res += graph[n1][n2];
	int tmp = (path[0]).front();
	(path[0]).push_back(tmp);

	// print the result in requested format
	cout << res << endl;
	list<int> tmplist = path[0];
	for (int i : tmplist) cout << i << " ";
	cout << endl;
}

// L&K algorithm adapted from here and modified (it also had some bugs)
// I corrected some of them. Will create version using directly original paper.
// https://github.com/lingz/LK-Heuristic/blob/master/LKMatrix.cpp
class LKMatrix {
public:
	int size;
	LKMatrix(vvi &g, vi &ids);

	int get_current_tour_distance();
	void optimize_tour();
	void printTour();

private:
	vi tour;
	vi ids;
	vvi edge_distances;

	// utility functions
	void LKMove(int tourStart);
	void reverse(int start, int end);
	bool isTour();
};

pair<int, int> make_sorted_pair(int x, int y) {
	if (x < y) {
		return make_pair(x, y);
	}
	else {
		return make_pair(y, x);
	}
}

LKMatrix::LKMatrix(vvi& g, vi &ids) {

	this->ids = ids;
	size = ids.size();

	// initialize tour
	tour = vector<int>(size, 0);

	// initial 'random' tour
	for (int i = 0; i < size; i++) {
		tour[i] = (i + 1) % size;
	}

	// sets the distanceVector
	edge_distances = g;
}

int LKMatrix::get_current_tour_distance() {
	
	int distance = 0;
	for (int i = 0; i < size; i++) {
		distance += edge_distances[i][tour[i]];
	}

	return distance;
}

int lastPossibleNextV;

void LKMatrix::LKMove(int tourStart) {
	set<pair<int, int> > broken_set, joined_set;
	vector<int> tour_opt = tour;
	double g_opt = 0;
	double g = 0; // := G_i
	double g_local; // := g_i
	int lastNextV = tourStart;
	int fromV;
	int nextV;
	int nextFromV;
	//int lastPossibleNextV;
	pair<int, int> broken_edge;
	double y_opt_length;
	double broken_edge_length;
	double g_opt_local;

	fromV = tour[lastNextV];
	long initialTourDistance = get_current_tour_distance();

	do {
		// default, no nextV is found
		nextV = -1;

		broken_edge = make_sorted_pair(lastNextV, fromV); // := x_i
		broken_edge_length = edge_distances[broken_edge.first][broken_edge.second];

		// Condition 4(c)(1)
		if (joined_set.count(broken_edge) > 0) break;

		// y_i := (fromV, nextV)
		for (int possibleNextV = tour[fromV]; nextV == -1 && possibleNextV != tourStart; possibleNextV = tour[possibleNextV]) {

			// calculate local gain
			g_local = broken_edge_length - edge_distances[fromV][possibleNextV];

			// conditions that make this edge not a valid y_i
			if (!(
				// condition 4(c)(2)
				broken_set.count(make_sorted_pair(fromV, possibleNextV)) == 0 &&
				// condition 4(d)
				g + g_local > 0 &&
				// condition 4(e)
				// x_{i+1} has never been joined before
				joined_set.count(make_sorted_pair(lastPossibleNextV, possibleNextV)) == 0 &&
				tour[possibleNextV] != 0 && // not already joined to start
				possibleNextV != tour[fromV] // not the one already joined to fromV
				)) {
				lastPossibleNextV = possibleNextV;
				continue;
			}

			// If we are here, then y_i := (fromV, possibleNextV)
			nextV = possibleNextV;
		}

		// a next y_i exists
		if (nextV != -1) {

			// add to our broken_set and joined_set
			broken_set.insert(broken_edge);
			joined_set.insert(make_sorted_pair(fromV, nextV));

			// condition 4(f)
			y_opt_length = edge_distances[fromV][tourStart]; // y_i_opt

			// The tour length if we exchanged the broken edge (x_i)
			// with y_opt, (t_{2i}, t_0)
			g_opt_local = g + (broken_edge_length - y_opt_length);

			if (g_opt_local > g_opt) {
				g_opt = g_opt_local;
				tour_opt = tour;
				// join the optimal tour
				tour_opt[tourStart] = fromV;
			}
			// recalculate g
			g += broken_edge_length - edge_distances[fromV][nextV];

			// reverse tour direction between newNextV and fromV
			// implicitly breaks x_i
			reverse(fromV, lastPossibleNextV);

			// remember our new t_{2i+1}
			nextFromV = lastPossibleNextV;
			//cout << "Joined to " << nextFromV << endl;

			// build y_i
			tour[fromV] = nextV;

			// set new fromV to t_{2i+1}
			// and out lastNextV to t_{2i}
			lastNextV = nextV;
			fromV = nextFromV;
		}
	} while (nextV != -1);

	tour = tour_opt;
	long distanceAfter = get_current_tour_distance();
}

void LKMatrix::optimize_tour() {
	// we need to test for convergence and also the difference from last time
	int diff;
	int old_distance = 0;
	int new_distance = 0;

	for (int j = 0; j < 200; j++) {
		for (int i = 0; i < size; i++) {
			LKMove(i);
		}
		new_distance = get_current_tour_distance();
		diff = old_distance - new_distance;
		if (j != 0) {
			if (diff == 0) {
				break;
			}
		};
		old_distance = new_distance;
	}
}

/*
* Reverse the tour between indices start and end
*/
void LKMatrix::reverse(int start, int end) {
	int current = start;
	int next = tour[start];
	int nextNext;
	do {
		// look ahead to where we need to go after this iteration
		nextNext = tour[next];

		// reverse the direction at this point
		tour[next] = current;

		// move to the next pointer
		current = next;
		next = nextNext;
	} while (current != end); // terminate once we've reversed up to end
}

// Sanity check function
bool LKMatrix::isTour() {
	int count = 1;
	int start = tour[0];
	while (start != 0) {
		start = tour[start];
		count++;
	}
	return (count == size);
}

void LKMatrix::printTour() {
	int current = 0;
	do {
		current = tour[current];
		cout << current + 1 << " ";
	} while (current != 0);
	cout << tour[0] + 1 << endl;
}

int main()
{
	ios_base::sync_with_stdio(false); // gives speed to C++ IO

	int n; // # of bakeries

	cin >> n;

	// input
	vvi graph(n, vi(n));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> graph[i][j];
		}
	}
	vi ids(n);
	iota(all(ids), 0);
	LKMatrix mat(graph, ids);

	mat.optimize_tour();

	cout << mat.get_current_tour_distance() << endl;
	mat.printTour();

	//used for testing: 
	//string filepath = "tsp.txt";
	//
	//create_data_set(filepath, 100 * 1000, 10 * 1000 * 1000);
	//ifstream f;
	//f.open(filepath);
	//if (f.is_open()) {
	//	std::string line;
	//	getline(f, line);
	//	istringstream iss(line);
	//	iss >> n;
	//	vvi graph(n, vi(n));
	//	for (int i = 0; i < n; i++) {
	//		getline(f, line);
	//		std::istringstream iss(line);
	//		for (int j = 0; j < n; j++) {
	//			iss >> graph[i][j];
	//		}
	//	}
	//	// solution goes here
	//	solution(graph);
	//}
	//else { cout << "couldn't find a file." << endl; return 1; }

	return 0;
}