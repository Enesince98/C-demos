#include <bits/stdc++.h> 
using namespace std; 
  
vector<vector<int> > g; 
bool box[100000000]; 
  
vector<int> Dominant(int ver, int edge) 
{ 
    vector<int> S; // set S 
    for (int i = 0; i < ver; i++) { 
        if (!box[i]) { 
            S.push_back(i); 
            box[i] = true; 
            for (int j = 0; j < (int)g[i].size(); j++) { 
                if (!box[g[i][j]]) { 
                    box[g[i][j]] = true; 
                    break; 
                } 
            } 
        } 
    } 
    return S; 
} 
  
// Driver function 
int main() 
{ 
    int ver, edge, x, y; 
  
    ver = 11; // Enter number of vertices 
    edge = 18; // Enter number of Edges 
    g.resize(ver); 
  
    // Setting all index value of an array as 0 
    memset(box, 0, sizeof(box));  
  
    // Enter all the end-points of all the Edges 
    // g[x--].push_back[y--]      g[y--].push_back[x--] 
    
    g[5].push_back(4);
    g[6].push_back(4);
    g[7].push_back(4);
    g[9].push_back(4);
    g[5].push_back(6);
    g[5].push_back(9);
    g[6].push_back(5);
    g[9].push_back(5);
	g[6].push_back(9);
    g[9].push_back(6);
    g[7].push_back(9);
    g[9].push_back(7); 
	g[8].push_back(9);
	g[9].push_back(8);
	g[9].push_back(10);
	g[10].push_back(9); 
g[0].push_back(1); 
    g[0].push_back(2); 
    g[0].push_back(3); 
    g[0].push_back(4); 
    g[0].push_back(5); 
    g[0].push_back(6); 
    g[0].push_back(7); 
    g[0].push_back(8); 
    g[1].push_back(0); 
    g[2].push_back(0); 
    g[3].push_back(0); 
    g[4].push_back(0);
    g[5].push_back(0);
    g[6].push_back(0);
    g[7].push_back(0);
    g[8].push_back(0);
    g[4].push_back(5);
    g[4].push_back(6);
    g[4].push_back(7);
    g[4].push_back(9);
    vector<int> S = Dominant(ver, edge); 
    cout << "The Dominant Set is : { "; 
    for (int i = 0; i < (int)S.size(); i++) 
        cout << S[i] + 1 << " "; 
    cout << "}"; 
    return 0; 
}
