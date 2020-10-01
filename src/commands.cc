
/**
 * 
 *  This file is part of pkmt.
 *  pkmt is a Package Mangement Tool.
 *  Copyright (C) 2020  Azael Reyes
 * 
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 * */


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
	cmd = cmd + " -f " + strfromparam + " " + ((bdt::HeaderLFS*)configure)->getLFS() + "/tools/sources " + ((bdt::HeaderLFS*)configure)->getLFS_TGT() + " " + ((bdt::HeaderLFS*)configure)->getLFS() ;
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