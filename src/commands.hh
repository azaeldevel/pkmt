
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


#ifndef PKMT_COMMANDS
#define PKMT_COMMANDS


#include "data.hh"
#include "header.hh"

namespace pkmt
{

class Interpret
{
private:
	//
	void pkmt(int argc, char* argv[]);
	void lfs(int argc, char* argv[]);
	void writeParamschar (std::string& argout, int argc, char *argv[]);
	Repository repo;
	std::string dir, packageName,sourcesDir,packagesDir;
	octetos::core::Semver version;

protected:
	const Header* configure;
	Shell shell;

public:
	Interpret(const Header& configure);
	void execute(int argc, char* argv[]);
	void tmpsys(int argc, char* argv[]);
	void basic(int argc, char* argv[]);
	void package(const std::string&);
};




}

#endif