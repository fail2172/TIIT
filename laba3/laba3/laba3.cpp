#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>


using namespace std;

int set_begin = 3; // указывает на начало множества


bool check_sets(set<string>& first_set, set<string>& second_set);
void add_to_set(set<string>& my_set, string& set_line);

void set_to_vector(set<string>& first_set, vector<string>& first_set_vector) {
	for (auto itr : first_set) {
		first_set_vector.push_back(itr);
	}
}

bool compare(string& first_set_el, string& second_set_el) {
	if (first_set_el[0] == '{' && second_set_el[0] == '{' && (first_set_el.size() == second_set_el.size())) {
		set<string> first_set, second_set;
		add_to_set(first_set, first_set_el);
		add_to_set(second_set, second_set_el);
		return (check_sets(first_set, second_set));
	}
	else
		return (first_set_el == second_set_el);

}

void add_to_set(set<string>& my_set, string& my_line) {
	string set_line = my_line;
	int i = 1;
	int counter = 0, first_symbol_of_set = 0, last_symbol_of_set = 0;
	set_line[set_line.size() - 1] = ',';
	while (i < set_line.size()) {
		if (set_line[i] == '<') {
			counter++;
			first_symbol_of_set = i;
			i++;
			while (counter != 0) {
				if (set_line[i] == '<')
					counter++;
				if (set_line[i] == '>')
					counter--;
				i++;
			}
			last_symbol_of_set = i;
			my_set.insert(set_line.substr(first_symbol_of_set, last_symbol_of_set - first_symbol_of_set));
			i++;
		}

		if (set_line[i] == '{') {
			first_symbol_of_set = i;
			counter++;
			i++;
			while (counter != 0) {
				if (set_line[i] == '{')
					counter++;
				if (set_line[i] == '}')
					counter--;
				i++;
			}
			last_symbol_of_set = i;
			if (last_symbol_of_set - first_symbol_of_set != 1) {
				my_set.insert(set_line.substr(first_symbol_of_set, last_symbol_of_set - first_symbol_of_set));
				i++;
			}
			else {
				my_set.insert("{}");
				i += 2;
			}
		}

		counter = 0;
		first_symbol_of_set = i;

		if (set_line[i] != '<' && set_line[i] != '{' && i < set_line.size()) {
			while (set_line[i] != ',') {
				counter++;
				i++;
			}
			string tempinfo = set_line.substr(first_symbol_of_set, counter);
			if (tempinfo != "") {
				my_set.insert(tempinfo);
				counter = 0;
			}
			else
				i++;
		}
	}
}

bool check_sets(set<string>& first_set, set<string>& second_set) {
	vector<string> first_set_vector, second_set_vector;
	set_to_vector(first_set, first_set_vector);
	set_to_vector(second_set, second_set_vector);
	if (first_set_vector.size() != second_set_vector.size())
		return false;
	for (int i = 0; i < first_set.size(); i++) {
		if (!compare(first_set_vector[i], second_set_vector[i]))
			return false;
	}
	return true;
}


void difference(set<string>& first_set, set<string>& second_set, set<string>& new_set) {
	vector<string> first_set_vector, second_set_vector;
	int counter = 0;
	set_to_vector(first_set, first_set_vector);
	set_to_vector(second_set, second_set_vector);
	for (auto i : first_set_vector) {
		for (auto j : second_set_vector) {
			if (!compare(i, j))
				counter++;
			else {
				counter = 0;
				break;
			}
		}
		if (counter)
			new_set.insert(i);
	}
}


// Читаем из файла
bool read_from_file(string& first_set, string& second_set) {
	ifstream fin("input.txt");
	if (!fin.is_open()) {
		cout << endl << "Файл не может быть открыт!" << endl << endl;
		return false;
	}
	getline(fin, first_set);
	getline(fin, second_set);
	return true;
}

int main() {
	set<string> first_set, second_set, new_set;
	setlocale(LC_ALL, "rus");
	string first_set_line, second_set_line;

	if (!read_from_file(first_set_line, second_set_line))
		return 0;

	add_to_set(first_set, first_set_line);
	add_to_set(second_set, second_set_line);

	difference(first_set, second_set, new_set);

	//вывод
	cout << "{";
	int temp = new_set.size();
	int j = 1;

	for (auto a : new_set) {
		cout << a;
		if (j != temp)
			cout << ",";
		else
			cout << "}";
		j++;

	}
}