#include "lib.h"
using namespace std;
void push(set** b, set** e, int x) {
	set* p = new set;
	p->info = x;
	p->next = nullptr;
	if (*b == nullptr) {
		*b = *e = p;
	}
	else {
		(*e)->next = p;
		*e = p;
	}
}
set* out(set* b, int* out) {
	set* p;
	*out = b->info;
	p = b->next;
	delete b;
	return p;
}