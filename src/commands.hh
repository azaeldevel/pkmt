
#ifndef PKMT_COMMANDS
#define PKMT_COMMANDS

#include <bdt/header.hh>


namespace pkmt
{

class Interpret
{
private:
	const bdt::Header* configure;
	//
	void pkmt(int argc, char* argv[]);
	void prephost(int argc, char* argv[]);
	void prephost_build(int argc, char* argv[]);
	void writeParamschar (std::string& argout, int argc, char *argv[]);
	
public:
	Interpret(const bdt::Header& configure);
	void execute(int argc, char* argv[]);
};

class pkmt
{

};


}

#endif