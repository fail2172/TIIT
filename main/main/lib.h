struct set {
	int info;
	set* next;
};
void push(set** b, set** e, int x);
set* out(set* b, int* out);