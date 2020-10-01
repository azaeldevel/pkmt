
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
	void Package::valid(const std::string& name,const std::string& ver)
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
	void Package::readData()
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
			version = (const std::string&)cfg.lookup("version");
		}
		catch(const libconfig::SettingNotFoundException &nfex)
		{
			throw NotFoundDataException("version",filename);
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
	}

	Package::Package(const std::string& fn, const std::string& name,const std::string& ver)
	{
		std::cout << "\t\t\t" << name << "\n";
		std::cout << "\t\t\t" << ver << "\n";
		filename = fn;
		readData();
		valid(name,ver);
	}

}