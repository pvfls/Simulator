#include <bits/stdc++.h>
#include "class_Simulator.hpp"

using namespace std;

void simulator()
{
	Simulator config();

	config.setPathName();
	string userInput;

	cout << endl << config.actual_Dir();
	while(getline(cin, userInput))
	{
		config.setLinuxInst(userInput);
		config.decoder();
		config.run();
		cout << config.actual_Dir();
	}
}

int main(int argc, char* argv[])
{	
	simulator();
}