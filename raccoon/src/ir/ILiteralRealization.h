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
 * This file contains the definition of the ILiteralRealization class.
 */

#ifndef __RACCOON_IR_ILITERALREALIZATION_H
#define __RACCOON_IR_ILITERALREALIZATION_H

// stl
#include <vector>
// raccoon
#include "Instance.h"

namespace raccoon
{
	class ILiteralRealization
	{
	public:
		/**
		 * \returns the type of the object. Each descending class must implement this method returning an unique
		 * integer, according to the class's type.
		 */
		virtual int type() = 0;
		
		/**
		 * \returns true when the literal is negated.
		 */
		virtual bool negated() = 0;
		
		/**
		 * \returns true when the current Literal realization is the complement of another literal realization.
		 */
		virtual bool complementOf(ILiteralRealization* L) = 0;
		
		/**
		 * \returns true when the current Literal realization is equivalent to another literal realization.
		 */
		virtual bool equivalentTo(ILiteralRealization* L) = 0;
		
		/**
		 * Prints the literal realization accordingly.
		 */
		virtual void print(std::vector<Instance*>& values) = 0;
		
		/**
		 * Prints the literal realization with the given instances, accordingly.
		 */
		virtual void print(Instance* inst1, Instance* inst2) = 0;
		
		/**
		 * Prints the literal realization (without its variables) accordingly.
		 */
		virtual void print() = 0;
		
		/**
		 * Destructor. Currently does nothing.
		 */
		virtual ~ILiteralRealization();
	};
}

#endif // __RACCOON_IR_ILITERALREALIZATION_H
