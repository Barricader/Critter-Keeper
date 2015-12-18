#include <iostream>
#include "App.h"

using namespace std;

int main() {
	App myApp = App("Hello");

	cout << myApp.getMessage() << endl;

	return 0;
}