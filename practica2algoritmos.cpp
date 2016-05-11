#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <fstream>
#include <cstring>
#include <string>
#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

#define D(x) cout << #x << " " << x << endl;
#define MAX 1005
bool estado[MAX];
vector <int> g[MAX];
int p[MAX];
bool visitados[MAX];
vector <int> ordenar;
int ganador;

void bfs(int n, int raiz) {
	for(int i = 0; i <= n; ++i) visitados[i] = false;
	p[raiz] = -1;
	visitados[raiz] = true;
	queue <int> q;
	q.push(raiz);
	ordenar.push_back(raiz);
	while(!q.empty()) {
		int actual = q.front();
		q.pop();
		for(int i = 0; i < g[actual].size(); ++i) {
			int next = g[actual][i];
			if(!visitados[next]) {
				visitados[next] = true;
				p[next] = actual;
				q.push(next);
				ordenar.push_back(next);
			}
		}
	}
}

void setestados(int raiz) {
	reverse(ordenar.begin(), ordenar.end());
	for(int x = 0; x < ordenar.size(); ++x) {
		int actual = ordenar[x];
		estado[actual] = false;
		for(int i = 0; i < g[actual].size(); ++i) {
			int next = g[actual][i];
			//D(actual);D(next);
			if(p[next] == actual && !estado[next]) {
				estado[actual] = true;
				if(actual == raiz && ganador > next) ganador = next;
			}
		}
	}
}

int main(){
	int n, raiz;
	cin >> n >> raiz;
	for(int i = 0; i < n - 1; ++i) {
		int x, y;
		cin >> x >> y;
		x--; y--;
		g[x].push_back(y);
		g[y].push_back(x);
	}
	raiz--;
	ganador = n + 1;
	bfs(n, raiz);
	setestados(raiz);
	if(estado[raiz]) printf("First player wins flying to airport %d\n", ganador + 1);
	else printf("First player loses\n");
}
