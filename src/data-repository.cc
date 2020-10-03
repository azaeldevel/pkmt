
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


#include <octetos/coreutils/shell.hh>
#include <iostream>

#include "data.hh"


namespace pkmt
{




	
	
	Package* Repository::find(const std::string& name,const std::string& version)
	{
		std::map<std::string,Collections*>::iterator it;
		it = collections.find(name);
		if(it == collections.end())
		{
			//std::cout << "No se encontro colecion : " << name << "\n";
			return NULL;
		}
		else
		{
			//std::cout << "Se encontro colecion : " << name << "\n";
			return it->second->find(version);
		}	
	}
	Package* Repository::find(const std::string& name)
	{
		std::map<std::string,Collections*>::iterator it;
		it = collections.find(name);
		if(it == collections.end())
		{
			return NULL;
		}
		Collections* c = it->second;
		std::map<std::string,Package*>::iterator pkIt;
		pkIt = c->begin();
		if(pkIt == c->end())
		{
			return NULL;
		}
		else
		{
			return pkIt->second;
		}
	}
	Repository::operator const std::string&()const
	{
		return filename;
	}
	const std::string& Repository::getName()const
	{
		return name;
	}
	const Architecture& Repository::getArchitecture()const
	{
		return arch;
	}
	const Phase& Repository::getPhase()const
	{
		return phase;
	}
	const Base& Repository::getBase()const
	{
		return  base;
	}
	const std::string& Repository::operator = (const std::string& str)
	{
		filename = str;
		readData();
		readCollentions();
		
		return str;
	}
	void Repository::readCollentions()
	{		
	
		//std::cout << "Repository::readCollentions 1: <<" << filename << "\n";
		coreutils::Shell shell;

		std::list<std::string> files;

		//std::cout << "Repository::readCollentions 2: <<" << filename << "\n";
		shell.cd(filename);
		//std::cout << "Repository::readCollentions 3: <<" << filename << "\n";
		
		shell.ls(files);
		//std::cout << "Repository::readCollentions 4: <<" << filename << "\n";
		
		Collections* coll;
		for(const std::string& file : files)
		{
			if(file.compare(".") == 0)
			{
				continue;
			}
			else if(file.compare("..") == 0)
			{
				continue;
			}
			else if(file.compare("data") == 0)
			{
				continue;
			}
			else if(file.compare(".gitignore") == 0)
			{
				continue;
			}
			else if(file.compare(".git") == 0)
			{
				continue;
			}

			
			//std::cout << "\tCollection: " << file << "\n";
			coll = new Collections(*this,filename + "/" + file);
			collections.insert(std::pair<std::string,Collections*>(file,coll));			
		}
		//std::cout << "Repository::readCollentions 5: <<" << filename << "\n";
	}
	void Repository::readData()
	{
		libconfig::Config cfg;
		//std::cout << "Repository::readData 1: >>" << filename << "\n";
		try
		{
			std::string datfile = filename + "/data";
			cfg.readFile(datfile.c_str());
		}
		catch(const libconfig::ParseException &pex)
		{
			std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
				      << " - " << pex.getError() << std::endl;
			return;
		}
		//std::cout << "Repository::readData 2: <<" << filename << "\n";
		
		
		try
		{
			name = (const std::string&)cfg.lookup("name");
		}
		catch(const libconfig::SettingNotFoundException &nfex)
		{
			throw NotFoundDataException("name",filename);
		}
		
		try
		{
			arch = cfg.lookup("arch");
		}
		catch(const libconfig::SettingNotFoundException &nfex)
		{
			throw NotFoundDataException("arch",filename);
		}
		
		try
		{
			phase = cfg.lookup("phase");
		}
		catch(const libconfig::SettingNotFoundException &nfex)
		{
			throw NotFoundDataException("phase",filename);
		}
		
		try
		{
			base = cfg.lookup("base");
		}
		catch(const libconfig::SettingNotFoundException &nfex)
		{
			throw NotFoundDataException("base",filename);
		}
		
		//std::cout << "Repository::readData 3: <<" << filename << "\n";
	}
	Repository::Repository()
	{
	}
	Repository::Repository(const std::string& fn)
	{
		filename = fn;
		readData();
		readCollentions();
	}
	Repository::~Repository()
	{
		for(std::pair<std::string,Collections*> coll : collections)
		{
			delete coll.second;
		}
	}
	 


}