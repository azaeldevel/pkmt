
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
#include <map>



namespace pkmt
{

class DataException : public std::exception
{
protected:
	std::string describe;
		
public:
	virtual const char* what() const throw();
};

class NotFoundDataException : public DataException
{		
public:
	NotFoundDataException(const std::string& dn,const std::string& fn);
	virtual const char* what() const throw();
};



/**
*\brief x86_64,i386
*/
class Architecture
{
private:
	std::string arch;

public:
	Architecture();
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
	Phase();
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
	Base();
	const std::string& operator = (const std::string&);
	operator const std::string&()const;
};

/**
*\brief autotools,cmake
*/
class Manager
{
private:
	std::string manager;

public:
	Manager(const std::string&);
	Manager();
	const std::string& operator = (const std::string&);
	operator const std::string&()const;
};

class Package
{
private:
	//from data file
	std::string name;
	std::string version;
	std::string md5sum;
	Phase phase;
	Base base;
	Manager manager;
	std::list<Package*> deps;

	//derived
	std::string filename;

	//getter and setter
	const std::string& getFilename()const;
	const std::string& getName()const;
	const std::string& getVersion()const;

	//
	void readData();
	void valid(const std::string& name,const std::string& ver);
public:
	Package(const std::string& fn, const std::string& name,const std::string& ver);

	class InvalidDataValueException : public DataException
	{
	public:
		enum Code
		{
			NAME_AMBIGUOUS,
			VERSION_AMBIGUOUS,
			MD5SUM,
			PHASE,
			BASE,
			MANAGER
		};

		InvalidDataValueException(const std::string& fn,Code c,const Package&,const std::string& val);
		virtual const char* what() const throw();

	};
};

class Collections
{
private:
	std::string filename;
	std::map<std::string,Package*> packages;
	
	//funciontions
	void read();
public:
	Collections();
	~Collections();
	Collections(const std::string&);

	//getter and setter
	const std::string& getFilename()const;

	//funciontions
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
	std::map<std::string,Collections*> collections;
	std::string filename;

	void readData();
	void readCollentions();
public:
	Repository(const std::string&);
	Repository();
	~Repository();
	const std::string& getName()const;
	const Architecture& getArchitecture()const;
	const Phase& getPhase()const;
	const Base& getBase()const;


	const std::string& operator = (const std::string&);
	operator const std::string&()const;

};




}

#endif