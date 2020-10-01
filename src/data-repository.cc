
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
	}
	void Repository::readCollentions()
	{		
		coreutils::Shell shell;

		std::list<std::string> files;

		shell.cd(filename);
		
		shell.ls(files);
		
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

			
			std::cout << "\t" << file << "\n";
			coll = new Collections(filename + "/" + file);
			collections.insert(std::pair<std::string,Collections*>(file,coll));			
		}
	}
	void Repository::readData()
	{
		libconfig::Config cfg;
		
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