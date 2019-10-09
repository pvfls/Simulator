class Simulator
{
	private:
		std::string pathName;
        
        std::string hostName;
        std::string hostBegin;
        std::string hostEnd;

		std::vector<std::string> windowsInst;
        std::vector<std::string> linuxInst;

        bool notFound = false;
        bool directoryCommand = false;
        bool newlineRequire = false;
        bool andFlag = false;

	public:
		Simulator();
        void appendVector(std::vector<std::string>);
        std::string dir();
        std::string host();
        std::string Template();
        void run();
        void decoder(std::string);
        void debugger();
};


std::string Simulator::dir()
{
    return this->pathName;
}


std::string Simulator::Template()
{
    return (this->hostName + this->hostBegin + this->pathName + this->hostEnd);
}

std::string setPathName(std::string user)
{
    char ch;
    size_t size;
    std::string path, npath;
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
    pathName.close();
    remove("path.txt");

    size = path.size();
    for(int i = 0; i < size; i++)
    {
        if(path[i] == '\\')
        {
            path[i] = '/';
        }
    }

    size = path.find(user);

    npath = path.substr(size + user.size());

    return npath;
}

std::string setHostBegin()
{
    std::string space;
    space.push_back(':');
    space.push_back('~'); 
    return space;
}

std::string setHostEnd()
{
    std::string space;
    space.push_back('$');
    space.push_back(' '); 
    return space;
}

std::string setHostName()
{
    char ch;
    std::string host;
    std::ifstream hostname;

    system("echo %username% > hostname.txt");
    
    hostname.open("hostname.txt", std::ifstream::in);
    while(hostname && hostname.get(ch))
    {
        if(ch == '\n')
            break;
        else
            host.push_back(ch);
    }
    hostname.close();
    remove("hostname.txt");
    host.pop_back();

    return host;
}

std::string Simulator::host()
{
    return this->hostName;
}

std::string substitutionBar(std::vector<std::string> dir, std::string path)
{
    path.pop_back();
    size_t size = dir.size();
    std::string newDir = path;

    for(int i = 1; i < size; i++)
    {
        if(dir[1][i] == '/')
        {
            newDir.push_back('\\');
        }
        else
        {
            newDir.push_back(dir[1][i]);
        }
    }

    return newDir;
}

Simulator::Simulator()
{
    this->hostBegin = setHostBegin();
    this->hostEnd = setHostEnd();
    this->hostName = setHostName();
	this->pathName = setPathName(this->hostName);

	system("title Simulator");
	system("cls");
	system("color 0F");
	std::cout << "Simulator Terminal [Version 0.0.0010]" << std::endl << "GPL 2018 Pulho " << std::endl;
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

int systemCall(std::vector<std::string> systemVector)
{
    size_t size = systemVector.size();
    std::string systemFunc;

    for(int i = 0; i < size; i++)
    {
        systemFunc += systemVector[i];
        systemFunc += " ";
    }
    return system(systemFunc.c_str());
}

std::string commandConvert(std::string command)
{
    if(command == "ls")
    {
        return "dir /b ";
    }
    else if(command == "clear")
    {
        return "cls ";
    }
    else if(command == "cat")
    {
        return "type ";
    }
    else if(command == "mkdir")
    {
        return "mkdir ";
    }
    else if(command == "touch")
    {
        return "NUL > ";
    }
    else if(command == "pwd")
    {
        return "cd ";
    }
    else if(command == "cd")
    {
        return "cd ";
    }  
    else
    {
        return "NONE";
    }
}

std::vector<std::string> lsFlags(std::vector<std::string> linuxInst)
{
    size_t size = linuxInst.size();
    size_t auxSize;
    std::vector<std::string> newFlag;
    std::vector<std::string> returnString;
    std::vector<std::string> auxString;

    if(size > 1) // Flags check
    {
        for(int i = 1; i < size; i++)
        {
            if(linuxInst[i] == "-r") // Reverse = /O:-
            {
                returnString.push_back("/O:-N ");
            }
            else if(linuxInst[i] == "-a") // Hidden Files = /A:H
            {
                returnString.push_back("/A:H ");
            }
            else if(linuxInst[i] == "&&" || linuxInst[i] == "&")
            {
                if((i + 1) < size)
                {
                    returnString.push_back("&& ");

                    if(linuxInst[i+1] != "NONE")
                    {
                        returnString.push_back(commandConvert(linuxInst[i+1]));
                        
                        for(int y = (i+1); y < size; y++)
                        {
                            newFlag.push_back(linuxInst[y]);
                        }

                        auxString= lsFlags(newFlag);
                        auxSize = auxString.size();

                        for(int y = 0; y < auxSize; y++)
                        {
                            returnString.push_back(auxString[y]);
                        }
                        break;
                    }
                    else
                    {
                        std::cerr << "comando nao e reconhecido como um comando interno\nou externo, um programa operavel ou um arquivo em lotes." << std::endl;  
                        returnString.clear();
                        returnString.push_back("NONE");
                        return returnString;
                    }
                }
                else
                {
                    std::cerr << "Sintaxe do comando esta incorreta" << std::endl; 
                    returnString.clear();
                    returnString.push_back("NONE");
                    return returnString;
                }
            }
        }
        return returnString;
    }   
}

void Simulator::appendVector(std::vector<std::string> commands)
{
    size_t size = commands.size();

    for(int i = 0; i < size; i++)
    {
        this->windowsInst.push_back(commands[i]);
    }
}

void Simulator::run()
{
    int index = 0;
    size_t size = this->linuxInst.size();
    std::vector<std::string> returned;
    std::string receive;
    this->notFound = true;

    if(size >= 1)
    {
        receive = commandConvert(this->linuxInst[0]);

        if(this->linuxInst[0] == "ls")
        {
            this->windowsInst.push_back(receive); // Default   
            if(size > 1)
            {
                returned = lsFlags(this->linuxInst);
                if(returned[0] != "NONE")
                {
                    this->appendVector(returned);
                    this->notFound = false;
                }
                else
                {
                    this->notFound = true;
                }
            }
            else
            {
                this->notFound = false;
            }
        }
        
        if(this->linuxInst[0] == "clear")
        {
            this->windowsInst.push_back(receive);
            this->notFound = false;
        }
        /*
        if(this->linuxInst[0] == "cat")
        {
            this->windowsInst.push_back(receive);
            this->windowsInst.push_back(this->linuxInst[index+1]);
            this->newlineRequire = true;
            this->notFound = false;
        }
        */
        if(this->linuxInst[0] == "mkdir")
        {
            this->windowsInst.push_back(receive);
            this->windowsInst.push_back(this->linuxInst[index+1]);
            this->notFound = false;
        }
        /*
        if(this->linuxInst[0] == "touch")
        {
            this->windowsInst.push_back(receive);
            this->windowsInst.push_back(this->linuxInst[index+1]);
            this->notFound = false;
        }
        */
        if(this->linuxInst[0] == "pwd")
        {
            this->windowsInst.push_back(receive);
            this->newlineRequire = true;
            this->notFound = false;
        }
        /*
        if(this->linuxInst[0] == "cd")
        {
            this->windowsInst.push_back(receive);
            this->windowsInst.push_back(this->linuxInst[index+1]);
            
            this->directoryCommand = true;

            if(systemCall(this->windowsInst) != 0)
            {
                this->notFound = false;
                this->pathName = substitutionBar(this->linuxInst, this->pathName); 
            }
        }
        */
        if(!this->notFound && !this->directoryCommand)
        {
            systemCall(this->windowsInst);
            if(newlineRequire)
            {
                std::cout << std::endl;
            }
        }

        if(this->notFound == true)
        {
            std::cerr << "Comando nao pode ser executado" << std::endl; 
            this->notFound = true;
        }
    }
    this->notFound = true;
    this->directoryCommand = false;
    this->newlineRequire = false;
    this->windowsInst.clear();
    this->linuxInst.clear();
}