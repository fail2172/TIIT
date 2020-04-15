#include <iostream>
#include <fstream>
#include <Windows.h>
using namespace std;
const int INF = 1e6,MAX_E=1e6,MAX_V=302;
int sours, stock, cows, type_of_dishes,  max_dishes, count_edge;
int end_of_edge[MAX_E], next_edge[MAX_E], first_edge[MAX_E],capacity[MAX_E],visit[MAX_V];
void Add_Edge(int u, int v, int cap) {
	//Прямое ребро
	end_of_edge[count_edge] = v;
	next_edge[count_edge] = first_edge[u];
	first_edge[u] = count_edge;
	capacity[count_edge++] = cap;
	//Обратное ребро
	end_of_edge[count_edge] = u;
	next_edge[count_edge] = first_edge[v];
	first_edge[v] = count_edge;
	capacity[count_edge++] = 0;
}
int findFlow(int u, int flow) {
	if (u == stock)return flow;
	visit[u] = true;
	for (int edge = first_edge[u]; edge != -1; edge = next_edge[edge]) {
		int to = end_of_edge[edge];
		if (!visit[to] && capacity[edge] > 0) {
			int minflow = findFlow(to, min(flow, capacity[edge]));
			if (minflow > 0) {
				capacity[edge] -= minflow;
				capacity[edge ^ 1] += minflow;
				return minflow;
			}
		}
	}
	return 0;
}
int main() {
	fill(first_edge, first_edge + MAX_E, -1);
	ifstream file;
	file.open("party.in");
	file >> cows >> max_dishes >> type_of_dishes;
	sours = cows + type_of_dishes + 1;
	stock = cows + type_of_dishes + 2;
 	for (int i = 1; i <= cows; i++) {
		Add_Edge(cows + type_of_dishes + 1, i, max_dishes);
	}
	for (int i = cows + 1; i <= cows + type_of_dishes; i++) {
		int lim_of_dishes;
		file >> lim_of_dishes;
		Add_Edge(i, cows + type_of_dishes + 2, lim_of_dishes);
	}
	for (int i = 1; i <= cows; i++) {
		int numb_of_dishes;
		file >> numb_of_dishes;
		for (int j = 0; j < numb_of_dishes; j++) {
			int type_of_dish;
			file >> type_of_dish;
			Add_Edge(i,cows+ type_of_dish, 1);
		}
	}
	file.close();
	int maxflow = 0 , num_of_iteretions;
	while (num_of_iteretions = findFlow(sours, INF) > 0) {
		fill(visit, visit + MAX_V, false);
		maxflow += num_of_iteretions;
	}
	cout << maxflow;
	ofstream fout("party.out");
	fout << maxflow;
	fout.close();
}