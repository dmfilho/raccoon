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
 * \date 2015-02-28
 * \file
 * This file contains the implementation of the ExistentialRealization class.
 */
 
// stl
#include <iostream>
#include <vector>
// raccoon
#include "Instance.h"
#include "ExistentialRealization.h"

namespace raccoon
{

	ExistentialRealization::ExistentialRealization(
		Literal& role, 
		unsigned int var1r, 
		unsigned int var2r, 
		bool negr, 
		Literal& concept, 
		bool negc
	)
	 : role(role, var1r, var2r, negr)
	 , concept(concept, var2r, negc)
	{
	}

	ExistentialRealization::~ExistentialRealization()
	{
	}

	/**
	 * Implementation of the ILiteralRealization::type method.
	 * \returns the same unique integer for all objects of this class.
	 */
	int ExistentialRealization::type()
	{
		return ExistentialRealization::TYPE;
	}
	
	/**
	 * \returns true when the literal is negated.
	 */
	bool ExistentialRealization::negated()
	{
		// this doesn't apply, since the role and the concept can be negated independently.
		// always returns false
		return false;
	}

	/**
	 * Implementation of the ILiteralRealization::complementOf method.
	 * \returns true when the given ILiteralRealization is the complement of this one.
	 */
	bool ExistentialRealization::complementOf(ILiteralRealization* L)
	{
        return concept.complementOf(L) || role.complementOf(L);
	}
	
	/**
	 * Implementation of the ILiteralRealization::equivalentTo method.
	 * \returns true when the given ILiteralRealization is equivalent to this one.
	 */
	bool ExistentialRealization::equivalentTo(ILiteralRealization* L)
	{
		return (
			L->type() == ExistentialRealization::TYPE &&											// if they are both Universal Realizations
			reinterpret_cast<ExistentialRealization*>(L)->concept.equivalentTo(&this->concept) &&   // with equivalent concepts
			reinterpret_cast<ExistentialRealization*>(L)->role.equivalentTo(&this->role)			// and equivalent roles
		);
	}
	
	/**
	 * Prints the role, its sign and variable, and the concept, its sign and variable.
	 */
	void ExistentialRealization::print(std::vector<Instance*>& values)
	{
		this->role.print(values);
		cout << "\n";
		this->concept.print(values);
	}
	
	/**
	 * \brief Prints the role, its sign and variables, the concept, its sign and variable.
	 * \param inst1 The instance corresponding to the first variable, or nullptr if no instance
	 * \param inst2 The instance corresponding to the second variable, or nullptr if no instance
	 * \remark if there are no instances in any inst parameter, the variable reference will be printed instead.
	 */
	void ExistentialRealization::print(Instance* inst1, Instance* inst2)
	{
		this->role.print(inst1, inst2);
		cout << '\n';
		this->concept.print(inst2, nullptr);
	}
	
	/**
	 * Prints the role, the concept and their sign.
	 */
	void ExistentialRealization::print()
	{
		this->role.print();
		cout << "\n";
		this->concept.print();
	}

}

