
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> adj;
vector<int> subtree_size;
vector<int> result;
int n, k;

// DFS to calculate subtree sizes from root
int dfs(int u, int parent) {
    subtree_size[u] = 1;
    
    for (int v : adj[u]) {
        if (v != parent) {
            subtree_size[u] += dfs(v, u);
        }
    }
    
    return subtree_size[u];
}

// Check if removing node u results in all components having size <= k
bool check_node(int u) {
    // Check all neighbors
    for (int v : adj[u]) {
        int component_size;
        
        // If v is a child in the rooted tree, component size is subtree_size[v]
        // If v is the parent, component size is n - subtree_size[u]
        if (subtree_size[v] < subtree_size[u]) {
            // v is a child
            component_size = subtree_size[v];
        } else {
            // v is the parent
            component_size = n - subtree_size[u];
        }
        
        if (component_size > k) {
            return false;
        }
    }
    
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n >> k;
    
    adj.resize(n + 1);
    subtree_size.resize(n + 1);
    
    // Read edges
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    
    // Calculate subtree sizes from root (node 1)
    dfs(1, 0);
    
    // Check each node
    for (int i = 1; i <= n; i++) {
        if (check_node(i)) {
            result.push_back(i);
        }
    }
    
    // Output results
    if (result.empty()) {
        cout << "None";
    } else {
        // Sort in descending order
        sort(result.rbegin(), result.rend());
        for (size_t i = 0; i < result.size(); i++) {
            if (i > 0) cout << " ";
            cout << result[i];
        }
    }
    cout << endl;
    
    return 0;
}
