class Simulator
{
	private:
		std::string pathName;
		std::string linuxInst;
		std::string windowsInst;
	public:
		Simulator();
		void setPathName();
		void setLinuxInst(std::string);
		void checkSingle(std::string);
		void decoder();
		void run();
		std::string actual_Dir();
};

Simulator::Simulator()
{
	this->pathName.clear();
	this->linuxInst.clear();
	this->windowsInst.clear();

	system("title Simulator");
	system("cls");
	system("color 5F");
	std::cout << "Simulator Linux [Version 0.0.0001]" << std::endl << "Copyright (c) 2018 Pulho. All rights reserved." << std::endl;
}

void Simulator::setPathName()
{
	char ch;
	std::ifstream pathName;

	system("cd > path.txt");
	
	pathName.open("path.txt", std::ifstream::in);
	while(pathName && pathName.get(ch))
	{
		if(ch == '\n')
			break;
		else
			this->pathName.push_back(ch);
	}
	this->pathName.push_back('>');
	pathName.close();
	remove("path.txt");
}

void Simulator::setLinuxInst(std::string command)
{

	this->linuxInst = command;
}

void Simulator::checkSingle(std::string part)
{
	bool empty_flag = false;
	bool interruption_flag = false;
	std::string aux;

	if(this->windowsInst.empty())
		empty_flag = true;

	if(part == "clear")
		aux = "cls";
	else
	{
		std::cerr << (char)39 << part << (char)39 << " nao e reconhecido como um comando interno\nou externo, um programa operavel ou um arquivo em lotes." << std::endl; 
		interruption_flag = true;
	}

	if(!interruption_flag)
	{
		if(empty_flag)
			this->windowsInst = aux;
		else
			this->windowsInst += aux;
	}
}

std::string Simulator::actual_Dir()
{

	return this->pathName;
}

void Simulator::run()
{
	system(this->windowsInst.c_str());
	this->windowsInst.clear();
	this->linuxInst.clear();
}

void Simulator::decoder()
{
	int lastCheck = 0;
	size_t size = linuxInst.size();

	for(int i = 0; i < size; i++)
	{
		if(linuxInst[i] == ' ' || i == size - 1)
		{
			checkSingle(linuxInst.substr(lastCheck, i+1));
			lastCheck = i;
		}
	}
	system("exit");
}
