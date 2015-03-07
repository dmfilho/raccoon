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
 * This file contains the declaration of the ConceptRealization class.
 */
 
#ifndef __RACCOON_IR_CONCEPTREALIZATION_H
#define __RACCOON_IR_CONCEPTREALIZATION_H

// raccoon
#include "Instance.h"
#include "Literal.h"
#include "ILiteralRealization.h"

namespace raccoon
{

	class ConceptRealization
	 : public ILiteralRealization
	{
	public:
		/**
		 * This is the value returned by the ConceptRealization::type() method.
		 */
		const int TYPE = 1;
		
		/**
		 * Reference to the concept of this realization.
		 */
		Literal& concept;
		
		/**
		 * The variable identifier of the concept on the clause. 0 is the default variable of the clause.
		 * This field is useful on cases where quantifiers where normalized to the clausal form, to tell wether the
		 * concept refers to the default variable of the clause or other variable.
		 */
		unsigned int var;
		
		/**
		 * True when the Concpt is negated on the clause that it belongs.
		 */
		bool neg;
		
		/**
		 * The instance of the variable.
		 */
		Instance* ivar;
		
		/**
		 * Constructor.
		 */
		ConceptRealization(Literal& concept, unsigned int var, bool neg);
		
		/**
		 * \brief Copy constructor
		 * \param other Copy this ConceptRealization.
		 */
		ConceptRealization(const ConceptRealization& other);
		
		/**
		 * Destructor. Currently does nothing.
		 */
		~ConceptRealization();
		
		/**
		 * Implementation of the ILiteralRealization::type method.
		 * \returns the same unique integer for all objects of this class.
		 */
		virtual int type();
		
		/**
		 * \returns true when the literal is negated.
		 */
		virtual bool negated();
		
		/**
		 * Implementation of the ILiteralRealization::complementOf method.
		 * \returns true when the given ILiteralRealization is the complement of this one.
		 */
		virtual bool complementOf(ILiteralRealization* L);
		
		/**
		 * Implementation of the ILiteralRealization::equivalentTo method.
		 * \returns true when the given ILiteralRealization is equivalent to this one.
		 */
		virtual bool equivalentTo(ILiteralRealization* L);
	};
}

#endif // __RACCOON_IR_CONCEPTREALIZATION_H
