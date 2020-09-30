
#include <stdio.h>
#include <string.h>
#include <string>
#include<stdlib.h>
#include <iostream>

#include "commands.hh"




namespace pkmt
{




Interpret::Interpret(const bdt::Header& configure)
{
	this->configure = &configure;
}
void Interpret::writeParamschar (std::string& argout, int argc, char *argv[])
{
	for(int i = 0; i < argc; i++)
	{
		argout = argout + " " + argv[i];
	}
}
void Interpret::prephost_build(int argc, char* argv[])
{
	std::string cmd = "pkmt-prephost-build ";
	std::string strfromparam = "begin";
	if(argc >= 1) strfromparam = argv[0];
	cmd = cmd + " -f " + strfromparam + " " + ((bdt::HeaderLFS*)configure)->getLFS() + "/sources " + ((bdt::HeaderLFS*)configure)->getLFS_TGT() + " " + ((bdt::HeaderLFS*)configure)->getLFS() ;
	//std::cout << "Ejecutando : "<< cmd << "\n";
	system (cmd.c_str());
}
void Interpret::prephost(int argc, char* argv[])
{
	if(strcmp(argv[0],"build") == 0)
	{
		prephost_build(argc-1,argv+1);
	}
	else
	{
		std::string msg = "En prephost, ";
		msg = msg + "'" + argv[0] + "' commando desconocida.";
		throw msg;
	}
}
void Interpret::execute(int argc, char* argv[])
{
	char* bn = basename(argv[0]);
	if(strcmp(bn,"pkmt") == 0)
	{
		pkmt(argc-1,argv+1);
	}
	else
	{
		std::string msg = "En execute, ";
		msg = msg + "'" + bn + "' commando desconocida.";
		throw msg;
	}
}
void Interpret::pkmt(int argc, char* argv[])
{
	if(strcmp(argv[0],"prephost") == 0)
	{
		prephost(argc-1,argv+1);
	}
	else
	{
		std::string msg = "En pkmt, ";
		msg = msg + "'" + argv[0] + "' commando desconocida.";
		throw msg;
	}
}

	
}