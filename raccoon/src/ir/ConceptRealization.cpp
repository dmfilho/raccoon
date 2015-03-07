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
 * This file contains the implementation of the ConceptRealization class.
 */
 
#include "ConceptRealization.h"

namespace raccoon
{

	/**
	 * Constructor.
	 */
	ConceptRealization::ConceptRealization(Literal& concept, unsigned int var, bool neg)
	 : concept(concept)
	 , var(var)
	 , neg(neg)
	 , ivar(nullptr)
	{
	}
	
	ConceptRealization::ConceptRealization(const ConceptRealization& other)
	 : concept(other.concept)
	 , var(other.var)
	 , neg(other.neg)
	 , ivar(other.ivar)
	{
	}

	/**
	 * Destructor. Currently does nothing.
	 */
	ConceptRealization::~ConceptRealization()
	{
	}
	
	/**
	 * Implementation of the ILiteralRealization::type method.
	 * \returns the same unique integer for all objects of this class.
	 */
	int ConceptRealization::type()
	{
		return ConceptRealization::TYPE;
	}
	
	/**
	 * \returns true when the literal is negated.
	 */
	bool ConceptRealization::negated()
	{
		return this->neg;
	}

	/**
	 * Implementation of the ILiteralRealization::complementOf method.
	 * \returns true when the given ILiteralRealization is the complement of this one.
	 */
	bool ConceptRealization::complementOf(ILiteralRealization* L)
	{
		return (
			L->type() == ConceptRealization::TYPE &&									// if they are both concepts 
			reinterpret_cast<ConceptRealization*>(L)->concept == this->concept &&	// if their conceptIDs are the same
			reinterpret_cast<ConceptRealization*>(L)->neg != this->neg				// one is neg'd and the other isn't
		);
	}
	
	/**
	 * Implementation of the ILiteralRealization::equivalentTo method.
	 * \returns true when the given ILiteralRealization is equivalent to this one.
	 */
	bool ConceptRealization::equivalentTo(ILiteralRealization* L)
	{
		return (
			L->type() == ConceptRealization::TYPE &&									// if they are both concepts
			reinterpret_cast<ConceptRealization*>(L)->concept == this->concept &&	// if their conceptiDs are the same
			reinterpret_cast<ConceptRealization*>(L)->neg == this->neg				// both are neg'd or both aren't
		);
	}
}

