
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

#ifndef PKMT_DATA_HH
#define PKMT_DATA_HH

#include <string>
#include <list>
#include <vector>


namespace pkmt
{

/**
*\brief x86_64,i386
*/
class Architecture
{
private:
	std::string arch;

public:
	Architecture(const std::string&);
	const std::string& operator = (const std::string&);
	operator const std::string&()const;
};

/**
*\brief stable,testing
*/
class Phase
{
private:
	std::string phase;

public:
	Phase(const std::string&);
	const std::string& operator = (const std::string&);
	operator const std::string&()const;
};

/**
*\brief source,binary
*/
class Base
{
private:
	std::string base;

public:
	Base(const std::string&);
	const std::string& operator = (const std::string&);
	operator const std::string&()const;
};

class Package
{
private:
	//from data file
	std::string filename;
	std::string name;
	std::string version;
	std::string md5sum;
	std::list<Package*> deps;
	Phase phase;
	Base base;

public:

};

class Collections
{
private:
	std::string filename;
	std::list<Package*> packages;

};

class Repository
{
private:
	//from data file
	std::string name;
	Architecture arch;
	Phase phase;
	Base base;

	//derived
	std::list<Collections*> packages;
	std::string filename;
public:
	const std::string& getName()const;
	const Architecture& getArchitecture()const;
	const Phase& getPhase()const;
	const Base& getBase()const;
};




}

#endif