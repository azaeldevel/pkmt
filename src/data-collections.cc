
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
#include <libgen.h>


#include "data.hh"


namespace pkmt
{

	std::map<std::string,Package*>::iterator Collections::end()
	{
		return packages.end();
	}
	std::map<std::string,Package*>::iterator Collections::begin()
	{
		return packages.begin();
	}
	Collections::~Collections()
	{
		for(std::pair<std::string,Package*> pkg : packages)
		{
			delete pkg.second;
		}
	}
	void Collections::read()
	{
		coreutils::Shell shell;

		std::list<std::string> files;

		shell.cd(filename);
		
		shell.ls(files);		

		Package* pkg;
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
			
			
			//std::cout << "\t\t" << file << "\n";
			pkg = new Package(filename + "/" + file,basename((char*)filename.c_str()),file);
			packages.insert(std::pair<std::string,Package*>(file,pkg));				
		}
	}
	Collections::Collections()
	{

	}
	Collections::Collections(const std::string& fn)
	{
		filename = fn;
		read();
	}
	 


}