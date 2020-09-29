
#ifndef PKMT_COMMANDS
#define PKMT_COMMANDS

namespace pkmt
{

class Interpret
{
private:
	//int argc;
	//char* argv[];

	//
	void pkmt(int argc, char* argv[]);
	void prephost(int argc, char* argv[]);
	void build(int argc, char* argv[]);
	void writeParamschar (std::string& argout, int argc, char *argv[]);
	
public:
	Interpret();
	void execute(int argc, char* argv[]);
};

class pkmt
{

};


}

#endif