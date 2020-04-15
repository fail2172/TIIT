#include <iostream>
#include <fstream>
#include <vector>
#include <Windows.h>
using namespace std;
int row, col, time = 1, num_of_test, count_v;
int s[20], up[20];
bool result[20];
vector<vector<int>> list(20);
void dfs(int v, int p = -1) {
	s[v] = up[v] = time++;
	int children = 0;
	for (int i = 0; i < list[v].size(); i++) {
		int to = list[v][i];
		if (s[to] == 0) {
			dfs(to, v);
			children++;
			up[v] = min(up[v], up[to]);
			if (up[to] >= s[v] && p != -1)
				result[v] = true;
		}
		else if (to != p)
			up[v] = min(up[v], s[to]);
	}
	if (p == -1 && children > 1)
		result[v] = true;
}
int arr_to_list(int** arr, int j, int v) {
	for (int i = 0; i < row; i++) {
		if (i != v && arr[i][j] != 0)
			return i;
	}
}
int main() {
	setlocale(LC_ALL, "ru");
	ifstream file("1");
	while (!file.eof()) {
		time = 1;
		num_of_test++;
		fill(result, result + 20, false);
		fill(s, s + 20, false);
		fill(up, up + 20, false);
		file >> row >> col;
		//Создание матрицы инцидентности
		int** arr = new int* [row];
		for (int i = 0; i < row; i++)
			arr[i] = new int[col];
		//Заполнение матрицы из файла
		for (int i = 0; i < row; i++)
			for (int j = 0; j < col; j++)
				file >> arr[i][j];
		//Перевод матрицы в список векторов
		for (int i = 0; i < row; i++)
			for (int j = 0; j < col; j++) {
				if (arr[i][j] != 0)
					list[i].push_back(arr_to_list(arr, j, i));
			}
		//Удаление матрицы
		for (int i = 0; i < row; i++)
			delete[] arr[i];
		delete[] arr;
		dfs(0);
		//Очистка списка векторов
		for (int i = 0; i < row; i++)
			list[i].clear();
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
