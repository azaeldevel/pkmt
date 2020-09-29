
#include <stdio.h>
#include <string.h>
#include <string>
#include<stdlib.h>
#include <iostream>

#include "commands.hh"




namespace pkmt
{



ConfigureLFS::ConfigureLFS()
{
	LFS="/mnt/lfs";
	LFS_PART="/dev/sda14";
	LFS_REPO_TMPSYS="/home/azael/develop/lfs/8.4/pkm/tmpsys";
	PKM="/home/azael/develop/lfs/8.4/pkm";
	LFS_TGT="x86_64-lfs-linux-gnu";
}






Interpret::Interpret(const Configure& configure)
{
	this->configure = &configure;
}
void Interpret::prephost_sync(int argc, char* argv[])
{
	std::string parms ;
	writeParamschar(parms,argc,argv);
	std::string cmd = "./prephost-sync ";
	cmd = cmd + " " + ((ConfigureLFS*)configure)->LFS_REPO_TMPSYS + " " + ((ConfigureLFS*)configure)->LFS + " " + ((ConfigureLFS*)configure)->PKM ;
	//std::cout << "Ejecutando : "<< cmd << "\n";
	system (cmd.c_str());
}
void Interpret::prephost_remove(int argc, char* argv[])
{
	std::string cmd = "./prephost-remove ";
	cmd = cmd + " " + ((ConfigureLFS*)configure)->LFS_PART + " " + ((ConfigureLFS*)configure)->LFS;
	//std::cout << "Ejecutando : "<< cmd << "\n";
	system (cmd.c_str());
}
void Interpret::prephost_install(int argc, char* argv[])
{
	std::string cmd = "./prephost-install ";
	cmd = cmd + " " + ((ConfigureLFS*)configure)->LFS_PART + " " + ((ConfigureLFS*)configure)->LFS;
	//std::cout << "Ejecutando : "<< cmd << "\n";
	system (cmd.c_str());
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
	std::string parms ;
	writeParamschar(parms,argc,argv);
	std::string cmd = "./prephost-build ";
	cmd = cmd + " -f begin " + ((ConfigureLFS*)configure)->LFS + "/sources " + ((ConfigureLFS*)configure)->LFS_TGT + " " + ((ConfigureLFS*)configure)->LFS ;
	//std::cout << "Ejecutando : "<< cmd << "\n";
	system (cmd.c_str());
}
void Interpret::prephost(int argc, char* argv[])
{
	if(strcmp(argv[0],"build") == 0)
	{
		prephost_build(argc-1,argv+1);
	}
	else if(strcmp(argv[0],"install") == 0)
	{
		prephost_install(argc-1,argv+1);
	}
	else if(strcmp(argv[0],"remove") == 0)
	{
		prephost_remove(argc-1,argv+1);
	}
	else if(strcmp(argv[0],"sync") == 0)
	{
		prephost_sync(argc-1,argv+1);
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