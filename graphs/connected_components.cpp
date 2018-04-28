// O(V+E)
void DFS(int v, vector<int>& visited, vector<vector<int>>& adj) {
	// Mark the current node as visited
	visited[v] = 1;

	// Recur for all the vertices adjacent to this vertex
	for (auto it = adj[v].begin(); it != adj[v].end(); ++it)
		if (!visited[*it])
			DFS(*it, visited);
}

// only non zero vertices are taken into consideration
bool is_connected(vector<vector<int>>& adj) {
	int n = adj.size();
	// Mark all the vertices as not visited
	vector<int> visited(n, 0);

	// Find the first vertex with non-zero degree
	int nz;
	for (nz = 0; nz < n; nz++)
		if (adj[nz].size() != 0)
			break;

	// If there are no edges in the graph, return true
	if (nz == n)
		return true;

	// Start DFS traversal from a vertex with non-zero degree
	DFS(nz, visited);

	// Check if all non-zero degree vertices are visited
	for (int i = 0; i < n; i++)
		if (visited[i] == 0 && adj[i].size() > 0)
			return false;

	return true;
}

int connected_components(vector<vector<int>>& adj) {
	int n = adj.size();
	// Mark all the vertices as not visited
	vector<int> visited(n, 0);
	
	int cnt = 0;
	for (int i = 0; i < n; i++) 
		if (!visited[i]) {
			// Start DFS traversal from a vertex with non-zero degree
			DFS(i, visited, adj);
			cnt++;
		}

	return cnt;
}