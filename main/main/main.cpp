#include <iostream>
#include "lib.h"
using namespace std;
set* head, * tail;
int main()
{
	setlocale(LC_ALL, "ru");
	int x;
	for (int i = 0; i < 5; i++) {
		cin >> x;
		push(&head, &tail, x);
	}
	for (int i = 0; i < 5; i++) {
		head = out(head, &x);
		cout << x << " ";
	}
}
