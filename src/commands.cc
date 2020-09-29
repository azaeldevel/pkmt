
#include <stdio.h>
#include <string.h>
#include <string>
#include<stdlib.h>
#include <iostream>

#include "commands.hh"




namespace pkmt
{

void Interpret::writeParamschar (std::string& argout, int argc, char *argv[])
{
	for(int i = 0; i < argc; i++)
	{
		argout = argout + " " + argv[i];
	}
}
void Interpret::build(int argc, char* argv[])
{
	std::string parms ;
	writeParamschar(parms,argc,argv);
	std::string cmd = "prephost-build ";
	cmd += parms;
	//std::cout << "Ejecutando : "<< cmd << "\n";
	system (cmd.c_str());
}
void Interpret::prephost(int argc, char* argv[])
{
	if(strcmp(argv[0],"build") == 0)
	{
		build(argc-1,argv+1);
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
Interpret::Interpret()
{
	//this->argc =argc;
	//this->argv = argv;
}
	
}