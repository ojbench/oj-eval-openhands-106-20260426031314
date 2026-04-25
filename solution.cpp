
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> adj;
vector<int> subtree_size;
vector<int> result;
int n, k;

// DFS to calculate component sizes when removing node u
void dfs_check(int u, int parent, int& max_size) {
    int component_size = 1;
    
    for (int v : adj[u]) {
        if (v != parent) {
            dfs_check(v, u, max_size);
            component_size += subtree_size[v];
        }
    }
    
    subtree_size[u] = component_size;
    max_size = max(max_size, component_size);
}

// Check if removing node u results in all components having size <= k
bool check_node(int u) {
    int max_component_size = 0;
    
    // For each neighbor of u, calculate the size of the component that would be formed
    for (int v : adj[u]) {
        // Reset subtree sizes
        fill(subtree_size.begin(), subtree_size.end(), 0);
        
        // Calculate size of component rooted at v (excluding u)
        dfs_check(v, u, max_component_size);
    }
    
    return max_component_size <= k;
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
    
    // Check each node
    for (int i = 1; i <= n; i++) {
        bool can_remove = check_node(i);
        if (can_remove) {
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
