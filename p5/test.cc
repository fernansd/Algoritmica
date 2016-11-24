#include <iostream>
#include <set>

using namespace std;

int main () {

	set<int> s {1,2,3,4,5,6};

	for (int i = 0; i < s.size(); i++) {
		cout << s [i] << " ";
	}


	return 0;
}
