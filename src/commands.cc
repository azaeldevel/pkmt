
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
#include <stdlib.h>
#include <iostream>
#include <libconfig.h++>
#include <filesystem>



#include "commands.hh"
#include "data.hh"
#include "config.h"



namespace pkmt
{



void BuilderLFS::tmpsys(int argc, char* argv[])
{
	//std::cout << "Step 1 :  BuilderLFS::tmpsys \n";
	pkmt::Repository repo;
	std::string dir;
	try
	{
		#ifdef DEBUG
		dir = PATHDIR;
		dir += "/src/tmpsys";
		#else
		bdt::HeaderLFS confglfs;
		dir = confglfs.getLFS() + "/tools/tmpsys";
		#endif
		std::cout << "Buscando repositorio de paquetes en :" << dir << " \n";
		repo = dir;
	}
	catch(const libconfig::FileIOException &fioex)
	{
		std::cerr << "\n" << fioex.what() << "\n";
		return;
	}
	//std::cout << "Step 2 :  BuilderLFS::tmpsys \n";
	//std::cout << "\n";
	//std::cout << "Name repos : " << repo.getName() << "\n";

	
	pkmt::Package* pktmpsys = repo.find("tmpsys");
	if(pktmpsys == NULL)
	{
		std::cerr << "No se encontro el paquete tmpsys\n";
		return;
	}
	else
	{
		//std::cout << "Paquete : " << pktmpsys->getName() << " in " << pktmpsys->getFilename() << "\n";

		try
		{
			pktmpsys->readDependencies();
		}
		catch(pkmt::NotFoundDependencyException e)
		{
			std::cerr << "Fallo la lectura de dependencias\n";
			std::cerr << e.what() << "\n";
		}
		catch(std::exception& e)
		{
			std::cerr << "Fallo la lectura de dependencias\n";
			std::cerr << e.what() << "\n";
			return;
		}
		
		char sandbox_template[] = "/tmp/sandbox-XXXXXX";
        char *sandbox_name = mkdtemp(sandbox_template);
        //std::cout << "sandbox=" << sandbox_name << "\n";
		std::list<Package*> stack;
		pktmpsys->createStackDeps(stack);
		coreutils::Enviroment* env;
		bdt::HeaderLFS confglfs;
		std::vector<coreutils::Enviroment*>* venv;
		coreutils::Shell shell;
		
		
		for(Package* pk : stack)
		{
			shell.cd(sandbox_name);
			std::vector<coreutils::Enviroment*> venv;
			env = new coreutils::Enviroment();
			env->name = "LFS_SOURCES";
			#ifdef DEBUG
			env->value = confglfs.getREPO_ORIGIN_SOURCES();
			#else
			env->value = confglfs.getLFS() + "/tools/sources";
			#endif
			venv.push_back(env);
			env = new coreutils::Enviroment();
			env->name = "LFS_TGT";
			env->value = confglfs.getLFS_TGT();
			venv.push_back(env);
			env = new coreutils::Enviroment();
			env->name = "LFS";
			env->value = confglfs.getLFS();
			venv.push_back(env);
			env = new coreutils::Enviroment();
			env->name = "PKNAME";
			env->value = pk->getName();
			venv.push_back(env);
			env = new coreutils::Enviroment();
			env->name = "PKVER";
			env->value = pk->getVersion();
			venv.push_back(env);
			env = new coreutils::Enviroment();
			env->name = "SANDBOX";
			env->value = sandbox_name;
			venv.push_back(env);
			std::cout <<">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n";
			std::cout <<">> Installing package : " << pk->getName() << "\n";
			std::cout <<">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n";
			int st = pk->install(venv,shell);
			if(st == 130)
			{
				std::cerr << "\n\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n";
				std::cerr << ">> Manulmente terminado (ctrl + c)\n";
				std::cerr << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n";
				return;
			}
			else if(st > 0)
			{
				
				std::cerr << "\n\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n";
				std::cerr << ">> Eror detectado ..\n";
				std::cerr << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n";
				return;
			}
			for(coreutils::Enviroment* env : venv)
			{
				delete env;
			}
			
		}
	}
}











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
void Interpret::lfs(int argc, char* argv[])
{
	if(strcmp(argv[0],"tmpsys") == 0)
	{
		BuilderLFS buider;
		buider.tmpsys(argc-1,argv+1);
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
	if(strcmp(argv[0],"lfs") == 0)
	{
		lfs(argc-1,argv+1);
	}
	else
	{
		std::string msg = "En pkmt, ";
		msg = msg + "'" + argv[0] + "' commando desconocida.";
		throw msg;
	}
}

	
}