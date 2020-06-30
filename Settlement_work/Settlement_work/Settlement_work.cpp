#include <iostream>
#include <fstream>
#include <Windows.h>
using namespace std;
int end_of_edge(int j, int v, int** arr, int row) {
	for (int i = 0; i < row; i++) {
		if (i != v && arr[i][j] != 0)
			return i;
	}
}
bool* dfs(int v, int** arr, int row, int col, int p = -1) {
	static int s[20], up[20], time = 1;
	static bool result[20];
	s[v] = up[v] = time++;  //прямой путь до вершины
	int children = 0;//дети узла
	for (int i = 0; i < col; i++) {
		if (arr[v][i] != 0) {
			int to = end_of_edge(i, v, arr, row);  //следующий узел
			if (s[to] == 0) {
				dfs(to, arr, row, col, v);//обход в глубину
				children++;
				up[v] = min(up[v], up[to]);//максимальная высота на которую можно подняться
				if (up[to] >= s[v] && p != -1)
					result[v] = true;//есили максимальная высота ниже либо равна пути к предку
			}
			else if (to != p)
				up[v] = min(up[v], s[to]);//проверяем можем ли мы пойти выше
		}
	}
	if (p == -1 && children > 1)
		result[v] = true;//проверка корня
	if (p == -1) {
		fill(s, s + 20, false);
		fill(up, up + 20, false);
		return result;
	}
}
int main() {
	setlocale(LC_ALL, "ru");
	int** arr = new int* [20];
	for (int i = 0; i < 20; i++)
		arr[i] = new int[20];
	int  num_of_test = 0, count_v = 0, row, col;
	ifstream file("1");
	while (!file.eof()) {
		num_of_test++;
		for (int i = 0; i < 20; i++)
			fill(arr[i], arr[i] + 20, false);
		file >> row >> col;
		//Заполнение матрицы из файла
		for (int i = 0; i < row; i++)
			for (int j = 0; j < col; j++)
				file >> arr[i][j];
		bool* result;
		result = dfs(0, arr, row, col);
		cout << "TEST " << num_of_test << " :" << endl;
		for (int i = 0; i < row; i++) {
			if (result[i] == true)
				count_v++;
		}
		cout << "Количество шарниров графа : " << count_v << endl;
		//Вывод вершин сочленения
		if (count_v > 0) {
			cout << "Номера вершин шарниров :\n";
			for (int i = 0; i < row; i++) {
				if (result[i] == true)
					cout << i + 1 << " ";
			}cout << endl;
		}cout << "--------------------" << endl;
		count_v = 0;
		fill(result, result + 20, false);
	}
	file.close();
}
