#include <bits/stdc++.h>
#include "class_Simulator.h"

using namespace std;

void simulator()
{
	Simulator config;
	string userInput;

	cout << endl << config.Template();
	while(getline(cin, userInput))
	{
		config.decoder(userInput);
		config.run();
		cout << config.Template();
	}
}

int main(int argc, char* argv[])
{	
	simulator();
}