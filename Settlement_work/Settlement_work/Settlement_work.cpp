#include <iostream>
#include <fstream>
#include <vector>
#include <Windows.h>
using namespace std;
int row, col, time = 1, num_of_test, count_v;
int s[20], up[20];
int** arr = new int* [20];
bool result[20];
int end_of_edge(int j, int v) {
	for (int i = 0; i < row; i++) {
		if (i != v && arr[i][j] != 0)
			return i;
	}
}
void dfs(int v, int p = -1) {
	s[v] = up[v] = time++;  //прямой путь до вершины
	int children = 0;//дети узла
	for (int i = 0; i < col; i++) {
		if (arr[v][i] != 0) {
			int to = end_of_edge(i, v);  //следующий узел
			if (s[to] == 0) {
				dfs(to, v);//обход в глубину
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
}
int main() {
	setlocale(LC_ALL, "ru");
	for (int i = 0; i < 20; i++)
		arr[i] = new int[20];
	ifstream file("1");
	while (!file.eof()) {
		time = 1;
		num_of_test++;
		fill(result, result + 20, false);
		fill(s, s + 20, false);
		fill(up, up + 20, false);
		for (int i = 0; i < 20; i++)
			for (int j = 0; j < 20; j++)
				arr[i][j] = 0;
		file >> row >> col;
		//Заполнение матрицы из файла
		for (int i = 0; i < row; i++)
			for (int j = 0; j < col; j++)
				file >> arr[i][j];
		dfs(0);
		cout << "TEST " << num_of_test << " :" << endl;
		for (int i = 0; i < row; i++) {
			if (result[i] == true)
				count_v++;
		}
		cout << "Количество точек сочленения : " << count_v << endl;
		//Вывод вершин сочленения
		if (count_v > 0) {
			cout << "Номера вершин сочленения :\n";
			for (int i = 0; i < row; i++) {
				if (result[i] == true)
					cout << i + 1 << " ";
			}cout << endl;
		}cout << "--------------------" << endl;
		count_v = 0;
	}
	file.close();
}
