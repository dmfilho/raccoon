/**
 * raccoon, (Rac)iocinador baseado em (Co)nexões para (On)tologias
 * 			Connection based Reasoner for Ontologies
 * 
 * Copyright (C) 2015 Dimas Melo Filho
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA. 
 * 
 * The author can be reached by e-mail: dldmf@cin.ufpe.br.
 * 
 * \author Dimas Melo Filho <dldmf@cin.ufpe.br>
 * \date 2015-02-17
 * \file
 * This file contains the declaration of the Instance class.
 */
 
#ifndef __RACCOON_IR_INSTANCE_H
#define __RACCOON_IR_INSTANCE_H

// STL
#include <string>

using namespace std;
namespace raccoon
{
	class Instance
	{
	public:
		string name;
		unsigned int id;
        bool skolem;
		
		Instance(string& name, unsigned int id)
		 : name(name)
		 , id(id)
         , skolem(name.length() > 2 && name[0] == '$' && name[1] == 'U')
		 {
		 }
		 
		Instance(const Instance& other)
		 : name(other.name)
		 , id(other.id)
         , skolem(other.skolem)
		{
		}
		
		Instance& operator=(const Instance& other)
		{
			this->name = other.name;
			this->id = other.id;
            this->skolem = other.skolem;
			return *this;
		}
		
		~Instance()
		{
		}
	};
}

#endif // __RACCOON_IR_INSTANCE_H
