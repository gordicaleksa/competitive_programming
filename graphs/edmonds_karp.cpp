/* Returns true if there is a path from source 's' to sink 't' in
residual graph. Also stores path in parrent */
bool BFS(vvi& residual_graph, int s, int t, vi& parent) {

	int n = residual_graph.size();
	// Create a visited array and mark all vertices as not visited
	vector<int> visited(n, 0);

	// Create a queue, enqueue source vertex and mark source vertex as visited
	queue <int> Q;
	Q.push(s);
	visited[s] = true;
	parent[s] = -1; // source vertex doesn't have parent

	// Standard BFS Loop
	while (!Q.empty()) {
		int u = Q.front(); Q.pop();

		for (int v = 0; v < n; v++) {
			if (visited[v] == false && residual_graph[u][v] > 0) {
				Q.push(v);
				parent[v] = u;
				visited[v] = true;
			}
		}
	}

	// If we reached the sink node in BFS starting from source, return true else false
	return (visited[t] == true);
}

// Returns the maximum flow from s to t in the given graph
// using Ford-Fulkerson scheme more specifically Edmonds-Karp algo
int ek_max_flow(vvi& graph, int s, int t) {
	int n = graph.size();
	int u, v;

	// initially initilize res graph to graph
	vvi residual_graph(n, vi(n)); 
	for (u = 0; u < n; u++)
		for (v = 0; v < n; v++)
			residual_graph[u][v] = graph[u][v];

	vi parent(n);  // used by BFS

	int max_flow = 0;  // There is no flow initially

	// Augment the flow while there is path from source to sink
	while (BFS(residual_graph, s, t, parent)) {
		// Find minimum residual capacity of the edges along the
		// path filled by BFS
		int path_flow = numeric_limits<int>::max();
		for (v = t; v != s; v = parent[v]) {
			u = parent[v];
			path_flow = min(path_flow, residual_graph[u][v]);
		}

		// update residual capacities of the edges and reverse edges
		// along the path
		for (v = t; v != s; v = parent[v]) {
			u = parent[v];
			residual_graph[u][v] -= path_flow;
			residual_graph[v][u] += path_flow;
		}

		// Add path flow to overall flow
		max_flow += path_flow;
	}

	// Return the overall flow
	return max_flow;
}