
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


#include <libconfig.h++>
#include <iostream>

#include "data.hh"


namespace pkmt
{


	
	
	
	
	
	NotFoundDataException::NotFoundDataException(const std::string& dn,const std::string& fn)
	{
		describe = "No se encontro el dato '";
		describe += dn + "' en '" + fn + "'";
	}
	const char* NotFoundDataException::what() const throw()
	{
		return describe.c_str();
	}
	 
	 
	
	const char* DataException::what() const throw()
	{
		return describe.c_str();
	}
	 

	Manager::Manager() 
	{
	}
	Manager::Manager(const std::string& str) 
	{
		manager = str;
	}
	const std::string& Manager::operator = (const std::string& str)
	{
		manager = str;
		return str;
	}
	Manager::operator const std::string&()const
	{
		return manager;
	}
		 


	 

	Base::Base() 
	{
	}
	Base::Base(const std::string& str) 
	{
		base = str;
	}
	const std::string& Base::operator = (const std::string& str)
	{
		base = str;
		return str;
	}
	Base::operator const std::string&()const
	{
		return base;
	}



	  
	Phase::Phase()
	{
	}
	Phase::Phase(const std::string& str)
	{
		phase = str;
	}
	const std::string& Phase::operator = (const std::string& str)
	{
		phase = str;
		return str;
	}
	Phase::operator const std::string&()const
	{
		return phase;
	}






	 
	Architecture::Architecture()
	{
	}
	Architecture::Architecture(const std::string& str)
	{
		arch = str;
	}
	const std::string& Architecture::operator = (const std::string& str)
	{
		arch = str;
		return str;
	}
	Architecture::operator const std::string&()const
	{
		return arch;
	}


}