
#ifndef OCTETOS_PKMT_V0_HH
#define OCTETOS_PKMT_V0_HH

/**
 *  This file is part of pkmt.
 *  pkmt is a Package Manager Tool
 *  Copyright (C) 2018  Azael Reyes
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
 * */

#include <string>

//#include <core/3/array.hh>
#include <core/3/tree.hh>

namespace oct::pkmt::v0
{
    namespace core = oct::core::v3;

    struct package
    {
        int major,minor,patch;
        std::string brief,name;
    };
    typedef core::Node<package> Package;
    void print(std::ostream& out,Package const& pack, size_t margin = 0);

}

#endif
