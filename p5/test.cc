#include <iostream>
#include <set>
#include <limits>

using namespace std;

int main () {
	int opcion;
	cout << "> ";
		
	if (!(cin >> opcion)) {
		cout << "Not a number" << endl;
		cin.clear();
		cin.ignore(std::numeric_limtis<std::streamsize>::max(), '\n');
	}


	return 0;
}
