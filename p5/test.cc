#include <iostream>
#include <set>
<<<<<<< HEAD
#include <limits>
=======
>>>>>>> d75ec1345bd40be5e4bdaae35fd500f76cec49ea

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
