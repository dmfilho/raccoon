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
 * This file contains the implementation of the RoleRealization class.
 */
// stl
#include <vector>
#include <iostream>
// raccoon
#include "Instance.h"
#include "RoleRealization.h"

namespace raccoon
{
	/**
	 * Constructor.
	 */
	RoleRealization::RoleRealization(Literal& role, unsigned int var1, unsigned int var2, bool neg)
	 : role(role)
	 , var1(var1)
	 , var2(var2)
	 , neg(neg)
	{
	}

	/**
	 * Destructor. Currently does nothing.
	 */
	RoleRealization::~RoleRealization()
	{
	}
	
	/**
	 * Implementation of the ILiteralRealization::type method.
	 * \returns the same unique integer for all objects of this class.
	 */
	int RoleRealization::type()
	{
		return RoleRealization::TYPE;
	}
	
	/**
	 * \returns true when the literal is negated.
	 */
	bool RoleRealization::negated()
	{
		return this->neg;
	}

	/**
	 * Implementation of the ILiteralRealization::complementOf method.
	 * \returns true when the given ILiteralRealization is the complement of this one.
	 */
	bool RoleRealization::complementOf(ILiteralRealization* L)
	{
		return (
			L->type() == RoleRealization::TYPE &&							// if they are both roles 
			reinterpret_cast<RoleRealization*>(L)->role == this->role &&	// if their roleIDs are the same
			reinterpret_cast<RoleRealization*>(L)->neg != this->neg			// one is neg'd and the other isn't
		);
	}
	
	/**
	 * Implementation of the ILiteralRealization::equivalentTo method.
	 * \returns true when the given ILiteralRealization is equivalent to this one.
	 */
	bool RoleRealization::equivalentTo(ILiteralRealization* L)
	{
		return (
			L->type() == RoleRealization::TYPE &&							// if they are both roles 
			reinterpret_cast<RoleRealization*>(L)->role == this->role &&	// if their roleIDs are the same
			reinterpret_cast<RoleRealization*>(L)->neg == this->neg			// both are neg'd or both aren't
		);
	}
	
	/**
	 * Prints the role, its sign and variables.
	 */
	void RoleRealization::print(std::vector<Instance*>& values)
	{
		if (this->neg)
		{
			cout << '-';
		}
		cout << this->role.name() << '(';
		if (values[this->var1] == nullptr)
		{
			cout << '?' << this->var1 << ',';
		}
		else
		{
			cout << values[this->var1]->name << ',';
		}
		if (values[this->var2] == nullptr)
		{
			cout << '?' << this->var2 << ')';
		}
		else
		{
			cout << values[this->var2]->name << ')';
		}
	}
	
}

