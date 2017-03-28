#include <iostream>
using namespace std;

int main() {
	int x1, y1, x2, y2;
	double m;
	double b;
	while (true) {
		cout << "Enter x1 y1 x2 y2 \n";
		cin >> x1 >> y1 >> x2 >> y2;
		m = ((y2 - y1) / (x2 - x1));
		b = (y1 - (m*x1));
		cout << "Slope: " << m << endl << "B: " << b;
		cout << endl;
	}
	return 0;
}