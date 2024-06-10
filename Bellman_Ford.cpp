#include <bits/stdc++.h>
using namespace std;

#define INF 1<<30
#define Node pair<int, int> 

void leituraGrafo(vector<vector<Node>> &, int);
void escritaGrafo(const vector<vector<Node>> &);
void bellmanFord(const vector<vector<Node>> &, int, int);

// Função de inicialização
void init(vector<int> &distancia, vector<int> &previo, int V) {
    for (int i = 0; i <= V; ++i) {
        distancia[i] = INF; //distâncias com valor infinito
        previo[i] = -1; 
    }
}

// imprimr caminho mais curto inicio -> destino
void print(const vector<int> &previo, int destino) {
    if (previo[destino] != -1)
        print(previo, previo[destino]); 
    printf("%d ", destino); 
}

// relaxa
bool relaxamento(vector<int> &distancia, vector<int> &previo, int atual, int adyacente, int peso) {
    if (distancia[atual] + peso < distancia[adyacente]) { 
        distancia[adyacente] = distancia[atual] + peso; 
        previo[adyacente] = atual; 
        return true; 
    }
    return false; 
}

// Algoritmo
void bellmanFord(const vector<vector<Node>> &ady, int V, int inicial) {
    vector<int> distancia(V+1, INF);
    vector<int> previo(V+1, -1);
    init(distancia, previo, V); 
    distancia[inicial] = 0; // distância inicial 0

    for (int i = 1; i <= V - 1; ++i) { 
        for (int atual = 0; atual < V; ++atual) { // loop para os vértices
            for (const auto &aresta : ady[atual]) { // vertice adjancente
                int adyacente = aresta.first; 
                int peso = aresta.second; // peso aresta
                relaxamento(distancia, previo, atual, adyacente, peso); 
            }
        }
    }

    // ciclo negativo
    for (int atual = 0; atual < V; ++atual) {
        for (const auto &aresta : ady[atual]) {
            int adyacente = aresta.first;
            int peso = aresta.second;
            if (relaxamento(distancia, previo, atual, adyacente, peso)) {
                puts("ciclo negativo");
                return;
            }
        }
    }

    puts("sem negativo");
    printf("Distancia mais curta inciando em: %d\n", inicial);
    for (int i = 0; i < V; ++i) {
        if (distancia[i] == INF)
            printf("vertice %d menor distancia = INF\n", i);
        else
            printf("vertice %d menor distancia = %d\n", i, distancia[i]);
    }

    puts("\nMenor Caminho");
    printf("vertice destino: ");
    int destino;
    cin >> destino;
    print(previo, destino);
    printf("\n");
}

void leituraGrafo(vector<vector<Node>> &G, int m) {
    int a, b, c;
    cout << "arestas:" << endl;
    while (m--) {
        cin >> a >> b >> c;
        G[a].push_back(make_pair(b, c));
    }
}

void escritaGrafo(const vector<vector<Node>> &G) {
    int n = G.size();
    cout << "adjacencias:" << endl;
    for (int u = 0; u < n; u++) {
        cout << u << ": ";
        for (auto v : G[u]) {
            cout << "[(" << u << "," << v.first << ") d: " << v.second << "] ";
        }
        cout << endl;
    }
}

int main() {
    int n, m;
    cout << "numero vertices: ";
    cin >> n;
    cout << "numero arestas: ";
    cin >> m;
    vector<vector<Node>> Grafo(n);
    leituraGrafo(Grafo, m);
    escritaGrafo(Grafo);
    cout << "vertices: " << n << endl;
    cout << "arestas: " << m << endl;

    int inicial;
    cout << "vertice inicial: ";
    cin >> inicial;

    bellmanFord(Grafo, n, inicial);

    return 0;
}
