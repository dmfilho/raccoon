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
 * This file contains the implementation of the Clause class.
 */

#include <iostream>
#include "Clause.h"

namespace raccoon
{
	
	bool Clause::contains(unsigned int id, bool negated)
	{
		for (ConceptRealization* concept: this->concepts)
		{
			if (concept->concept.id() == id)
			{
				return true;
			}
		}
		for (RoleRealization* role: this->roles)
		{
			if (role->role.id() == id)
			{
				return true;
			}
		}
		for (UniversalRealization* universal: this->universals)
		{
			if (universal->concept.concept.id() == id || universal->role.role.id() == id)
			{
				return true;
			}
		}
		return false;
	}
	
	void Clause::negate()
	{
		for (auto concept: concepts)
		{
			concept->neg = !concept->neg;
		}
		for (auto role: roles)
		{
			role->neg = !role->neg;
		}
		for (auto universal: universals)
		{
			universal->concept.neg = !universal->concept.neg;
			universal->role.neg = !universal->role.neg;
		}
	}
	
	void Clause::print()
	{
		for (auto concept: this->concepts)
		{
			if (concept->neg) 
			{
				cout << '-';
			}
			cout << concept->concept.name();
			if (this->values.size() > 0)
			{
				cout << "(" << this->values[0]->name << ")";
			}
			cout << ", ";
		}
		for (auto role: this->roles)
		{
			if (role->neg)
			{
				cout << '-';
			}
			cout << role->role.name();
			if (this->values.size() > 0)
			{
				cout << "(" << this->values[0]->name;
				if (this->values.size() > 1)
				{
					cout << "," << this->values[1]->name << ")";
				}
				else
				{
					cout << ",?)";
				}
			}
		}
		for (auto universal: this->universals)
		{
			cout << '[';
			if (universal->concept.neg)
			{
				cout << '-';
			}
			cout << universal->concept.concept.name() << " | ";
			if (universal->role.neg)
			{
				cout << '-';
			}
			cout << universal->role.role.name() << "], ";
		}
	}
	
	Clause::Clause()
	 : _varCount(1)
	 , ignore(false)
	{
	}

	Clause::~Clause()
	{
		for (ConceptRealization* cr: concepts)
		{
			delete cr;
		}
		for (RoleRealization* rr: roles)
		{
			delete rr;
		}
	}
}

