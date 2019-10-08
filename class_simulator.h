class Simulator
{
	private:
		std::string pathName;
		std::vector<std::string> windowsInst;
        std::vector<std::string> linuxInst;
	public:
		Simulator();
        std::string dir();
        void run();
        void decoder(std::string);
        void debugger();
};

std::string setPathName()
{
	char ch;
    std::string path;
	std::ifstream pathName;

	system("cd > path.txt");
	
	pathName.open("path.txt", std::ifstream::in);
	while(pathName && pathName.get(ch))
	{
		if(ch == '\n')
			break;
		else
			path.push_back(ch);
	}
	path.push_back('>');
	pathName.close();
	remove("path.txt");

    return path;
}

Simulator::Simulator()
{
	this->pathName = setPathName();

	system("title Simulator");
	system("cls");
	system("color 0F");
	std::cout << "Simulator Terminal [Version 0.0.0000]" << std::endl << "GPL 2018 Pulho " << std::endl;
}

std::string Simulator::dir()
{
    return this->pathName;
}

void Simulator::decoder(std::string instr)
{
    size_t size = instr.size();
    int prevBreak = 0;
    std::string substr;

    for(int i = 0; i < size; i++)
    {
        if(instr[i] == ' ')
        {
            this->linuxInst.push_back(substr);
            substr.clear();
        }
        else
        {
            substr.push_back(instr[i]);
        }
    }
    this->linuxInst.push_back(substr);
}

void systemCall(std::vector<std::string> systemVector)
{
    size_t size = systemVector.size();
    std::string systemFunc;

    for(int i = 0; i < size; i++)
    {
        systemFunc += systemVector[i];
        systemFunc += " ";
    }
    system(systemFunc.c_str());
}

void Simulator::run()
{
    size_t size = this->linuxInst.size();
    bool notFound = false;


    if(size >= 1)
    {
        if(this->linuxInst[0] == "ls")
        {
            this->windowsInst.push_back("dir /b");
        }
        else if(this->linuxInst[0] == "clear")
        {
            this->windowsInst.push_back("cls");
        }
        else if(this->linuxInst[0] == "cat")
        {
            this->windowsInst.push_back("type");
            this->windowsInst.push_back(this->linuxInst[1]);
        }
        else if(this->linuxInst[0] == "mkdir")
        {
            this->windowsInst.push_back("mkdir");
            this->windowsInst.push_back(this->linuxInst[1]);
        }
        else
        {
            std::cerr << (char)39 << this->windowsInst[0] << (char)39 << " nao e reconhecido como um comando interno\nou externo, um programa operavel ou um arquivo em lotes." << std::endl; 
            notFound = true;
        }

        if(!notFound)
        {
            systemCall(this->windowsInst);
        }
    }
    this->windowsInst.clear();
    this->linuxInst.clear();
}