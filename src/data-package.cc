
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
#include <sys/stat.h>
#include <stdlib.h>




#include "data.hh"


namespace pkmt
{
	
	Package::IncompleteException::IncompleteException(const std::string& fn,const std::string& comp)
	{
		describe = fn + " : " + "No se encomtro '" + comp + "'";
	}
	const char* Package::IncompleteException::what() const throw()
	{
		return describe.c_str();
	}
	
	
	Package::InvalidDataValueException::InvalidDataValueException(const std::string& fn,Code c,const Package& pkg,const std::string& val)
	{
		switch(c)
		{
			case NAME_AMBIGUOUS:
				describe += fn + " : ";	
				describe += "El nombre de paquete deve coincidir con el nombre de la collecion.\n";
				describe += "\t";	
				describe += val + " != " + pkg.getName() ;
			break;
			case VERSION_AMBIGUOUS:
				describe = fn + " : ";
				describe += "La version de paquete deve coincidir con la version de la collecion.\n";	
				describe += "\t";	
				describe += val + " != " + pkg.getVersion() ;			
			break;
		}		
	}
	const char* Package::InvalidDataValueException::what() const throw()
	{
		return describe.c_str();
	}
	
	
	
	
	int Package::install(const std::vector<coreutils::Enviroment*> v,coreutils::Shell& s)
	{
		if(levelexe == 1)
		{
			std::string script = filename + "/" + (const std::string&)base;	
			//std::cout << script << "\n";
			s.set(v);
			return s.execute(script);
		}
		
		return -1;
	}
	
	
	void Package::createStackDeps(std::list<Package*>& stack)const
	{
		for(auto it = deps.begin() ;  it != deps.end();it++)
		{
			it->second->createStackDeps(stack);
			stack.push_back(it->second);
		}
	}
	std::map<std::string,Package*>& Package::getDependencies()
	{
		return deps;
	}
	const std::string& Package::getMD5sum()const
	{
		return md5sum;
	}
	const Phase& Package::getPhase()const
	{
		return phase;
	}
	const Base& Package::getBase()const
	{
		return base;
	}
	const Manager& Package::getManager()const
	{
		return manager;
	}
	const std::string& Package::getName()const
	{
		return name;
	}
	const std::string& Package::getVersion()const
	{
		return version;
	}
	const std::string& Package::getFilename()const
	{
		return filename;
	}
	void Package::valid(const std::string& name,const std::string& ver)const
	{
		if(this->name.compare(name) != 0)
		{
			throw InvalidDataValueException(filename,InvalidDataValueException::NAME_AMBIGUOUS,*this,name);
		}
		if(this->version.compare(version) != 0)
		{
			throw InvalidDataValueException(filename,InvalidDataValueException::VERSION_AMBIGUOUS,*this,name);
		}
		
		
	}
	bool Package::fileExists(const std::string& fn)
	{
		struct stat buffer;
		int exist = stat(fn.c_str(),&buffer);
		if(exist == 0)
		    return true;
		else // -1
        return false;
	}
	void Package::readLevelExecution()
	{
		if(fileExists(filename + "/" + (const std::string&)base))
		{
			levelexe = 1;
		}
		else
		{
			throw IncompleteException(filename,base);
		}
	}
	void Package::readDependencies(bool recursive)
	{	
		//std::cout << "Package::readDependencies : >>" << filename << "\n";
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
		
		//std::cout << "Package::readDependencies : <<" << filename << "\n";
		//
		const libconfig::Setting& root = cfg.getRoot();
		const libconfig::Setting* depsread;
  		try
  		{
			depsread = &root["deps"];			
		}
		catch(const libconfig::SettingNotFoundException &nfex)
  		{
  			//no hay dependencias.
  			return;
  		}
  
		int count = depsread->getLength();
		if(count == 0) return;
		
		Package* deppkg;
		//std::cout << "deps size = " << count << "\n";
    	for(int i = 0; i < count; ++i)
    	{
      		const libconfig::Setting &depread = (*depsread)[i];
			std::string nm,ver;
			
			try
			{
				depread.lookupValue("name",nm);
			}
			catch(const libconfig::SettingNotFoundException &nfex)
			{
				throw NotFoundDataException("name",filename);
			}				
			try
			{
				depread.lookupValue("version",ver);
			}
			catch(const libconfig::SettingNotFoundException &nfex)
			{
				//la version es opcional.
				ver = "";
			}
			
			//std::cout << "dep {name =" << nm << "," << "ver=" << ver << "};\n"; 
			if(ver.empty())
			{
				deppkg = repository->find(nm);	
				if(deppkg != NULL)
				{			
					if(recursive) deppkg->readDependencies(recursive);
					deps.insert(std::pair<std::string,Package*>(deppkg->getName(),deppkg));
				}
				else
				{
					throw NotFoundDependencyException(name,nm);
				}
			}
			else
			{
				deppkg = repository->find(nm,ver);		
				if(deppkg != NULL)
				{		
					if(recursive) deppkg->readDependencies(recursive);
					deps.insert(std::pair<std::string,Package*>(deppkg->getName(),deppkg));
				}
				else
				{
					throw NotFoundDependencyException(name,nm);
				}
				
			}
    	}
	}
	void Package::readDataIndex()
	{
		libconfig::Config cfg;
		//std::cout << "Package::readDataIndex : >>" << filename << "\n";
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
		//std::cout << "Package::readDataIndex : <<" << filename << "\n";
		
		
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
			version = (const std::string&)cfg.lookup("version");
		}
		catch(const libconfig::SettingNotFoundException &nfex)
		{
			throw NotFoundDataException("version",filename);
		}
				
	}
	void Package::readDataFull()
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
			md5sum = (const std::string&)cfg.lookup("md5sum");
		}
		catch(const libconfig::SettingNotFoundException &nfex)
		{
			throw NotFoundDataException("md5sum",filename);
		}
		
		try
		{
			phase = (const std::string&)cfg.lookup("phase");
		}
		catch(const libconfig::SettingNotFoundException &nfex)
		{
			throw NotFoundDataException("phase",filename);
		}
		
		try
		{
			base = (const std::string&)cfg.lookup("base");
		}
		catch(const libconfig::SettingNotFoundException &nfex)
		{
			throw NotFoundDataException("base",filename);
		}
		
		try
		{
			manager = (const std::string&)cfg.lookup("manager");
		}
		catch(const libconfig::SettingNotFoundException &nfex)
		{
			throw NotFoundDataException("manager",filename);
		}
		

		
		//optional values
		try
		{
			passingtype = (const std::string&)cfg.lookup("passingtype");
		}
		catch(const libconfig::SettingNotFoundException &nfex)
		{
			;
		}
		
	}

	Package::Package(Repository& repo,const std::string& fn, const std::string& name,const std::string& ver):repository(&repo)
	{
		//std::cout << "\t\t\t" << name << "\n";
		//std::cout << "\t\t\t" << ver << "\n";
		levelexe = 0;
		passingtype = "enviroment";
		
		filename = fn;
		readDataIndex();
		readLevelExecution();
		
		
		valid(name,ver);
	}

}