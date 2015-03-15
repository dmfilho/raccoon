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
 * This file contains the implementation of the UniversalRealization class.
 */
 
#include "UniversalRealization.h"

namespace raccoon
{

	UniversalRealization::UniversalRealization(
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

	UniversalRealization::~UniversalRealization()
	{
	}

	/**
	 * Implementation of the ILiteralRealization::type method.
	 * \returns the same unique integer for all objects of this class.
	 */
	int UniversalRealization::type()
	{
		return UniversalRealization::TYPE;
	}
	
	/**
	 * \returns true when the literal is negated.
	 */
	bool UniversalRealization::negated()
	{
		// this doesn't apply, since the role and the concept can be negated independently.
		// always returns false
		return false;
	}

	/**
	 * Implementation of the ILiteralRealization::complementOf method.
	 * \returns true when the given ILiteralRealization is the complement of this one.
	 */
	bool UniversalRealization::complementOf(ILiteralRealization* L)
	{
		// In order for something to be the complement of an Universal Quantifier it has to be an Existential Quantifier
		// with complementary roles and complementary concepts. Such Existential Quantifiers are NOT represented as an
		// ILiteralRealization. Because of that, this method always return false.
		return false;
	}
	
	/**
	 * Implementation of the ILiteralRealization::equivalentTo method.
	 * \returns true when the given ILiteralRealization is equivalent to this one.
	 */
	bool UniversalRealization::equivalentTo(ILiteralRealization* L)
	{
		return (
			L->type() == UniversalRealization::TYPE &&											// if they are both Universal Realizations
			reinterpret_cast<UniversalRealization*>(L)->concept.equivalentTo(&this->concept) && // with equivalent concepts
			reinterpret_cast<UniversalRealization*>(L)->role.equivalentTo(&this->role)			// and equivalent roles
		);
	}


}

