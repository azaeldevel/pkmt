
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
#include <fstream>
#include <libgen.h>
#include <octetos/core/Version.hh>
#include <algorithm>


#include "commands.hh"
#include "config.h"
#include "Shell.hh"

namespace pkmt
{


void Interpret::basic(int argc, char* argv[])
{
	for(int i = 0; i < argc; i++)
	{
		if(strcmp(argv[i],"--version") == 0 and argv[i+1] != NULL and i+1 <= argc)
		{
			version.set(argv[i+1]);
			i++;
		}
		else
		{
			packageName = argv[i];
		}		
	}
	#ifdef DEBUG
	sourcesDir = configure->getRoot_Repository() + "/sources/lfs/" + version.toString();
	packagesDir = configure->getRoot_Repository() + "/packages/lfs/" + version.toString() + "/basic";
	#else
	sourcesDir = configure->getRootDir() + "/tools/sources";
	packagesDir = configure->getRootDir() + "/tools/tmpsys";
	#endif
	try
	{
		
		std::cout << "Buscando repositorio de paquetes en : " << packagesDir << " \n";
		repo = packagesDir;
	}
	catch(const libconfig::FileIOException &fioex)
	{
		std::cerr << "\n" << fioex.what() << "\n";
		return;
	}
	
	package(argc,argv);
}

void Interpret::tmpsys(int argc, char* argv[])
{
	//std::cout << "Step 1 :  BuilderLFS::tmpsys \n";	
	for(int i = 0; i < argc; i++)
	{
		if(strcmp(argv[i],"--version") == 0 and argv[i+1] != NULL and i+1 <= argc)
		{
			version.set(argv[i+1]);
			i++;
		}
		else
		{
			packageName = argv[i];
		}		
	}
	#ifdef DEBUG
	sourcesDir = configure->getRoot_Repository() + "/sources/lfs/" + version.toString();
	packagesDir = configure->getRoot_Repository() + "/packages/lfs/" + version.toString() + "/tmpsys";
	#else
	sourcesDir = configure->getRootDir() + "/tools/sources";
	packagesDir = configure->getRootDir() + "/tools/tmpsys";
	#endif
	try
	{
		
		std::cout << "Buscando repositorio de paquetes en : " << packagesDir << " \n";
		repo = packagesDir;
	}
	catch(const libconfig::FileIOException &fioex)
	{
		std::cerr << "\n" << fioex.what() << "\n";
		return;
	}
	
	package(argc,argv);
}

void Interpret::package(int argc, char* argv[])
{	
	//std::cout << "Step 2 :  BuilderLFS::tmpsys \n";
	//std::cout << "\n";
	//std::cout << "Name repos : " << repo.getName() << "\n";
	
	pkmt::Package* pktmpsys = repo.find(packageName);
	if(pktmpsys == NULL)
	{
		std::cerr << "No se encontro el paquete " << packageName << "\n";
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
		//bdt::HeaderLFS confglfs;
		std::vector<coreutils::Enviroment*>* venv;
		std::list<std::string> installed;
		Database db;
		shell.cd(db.getDB());
		shell.ls(installed);
		std::list<std::string>::iterator it;
		
		for(Package* pk : stack)
		{
			it = std::find(installed.begin(),installed.end(),pk->getName());
			if(it == installed.end())//si ya esta instalado
			{
				continue;//salata hacia el siguiente paquete
			}
			shell.cd(sandbox_name);
			std::vector<coreutils::Enviroment*> venv;
			
			coreutils::Enviroment* env = new coreutils::Enviroment();
			env->name = "LFS_SOURCES";
			env->value = sourcesDir;
			venv.push_back(env);
			env = new coreutils::Enviroment();
			env->name = "LFS_TGT";
			env->value = configure->getTarget();
			venv.push_back(env);
			env = new coreutils::Enviroment();
			env->name = "LFS";
			env->value = configure->getRootDir();
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
			shell.set(venv);
			int st = pk->build(shell);
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
				std::cerr << ">> Error detectado ..\n";
				std::cerr << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n";
				return;
			}
			for(coreutils::Enviroment* env : venv)
			{
				delete env;
			}
			venv.clear();	
		}
	}
}











Interpret::Interpret(const Header& configure)
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
		tmpsys(argc,argv);
	}
	else if(strcmp(argv[0],"basic") == 0)
	{
		basic(argc,argv);
	}
	else
	{
		std::string msg = "En pkmt, ";
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
	else if(strcmp(argv[0],"--help") == 0)
	{
		std::cout << "pkmt lfs tmpsys version\n";
		std::cout << "pkmt lfs basic version\n";
	}
	else
	{
		std::string msg = "En pkmt, ";
		msg = msg + "'" + argv[0] + "' commando desconocida.";
		throw msg;
	}
}

	
}