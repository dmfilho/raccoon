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
 * This file contains the declaration of the RoleRealization class.
 */

#ifndef __RACCOON_IR_ROLEREALIZATION_H
#define __RACCOON_IR_ROLEREALIZATION_H

// stl
#include <vector>
// raccoon
#include "Instance.h"
#include "Literal.h"
#include "ILiteralRealization.h"

namespace raccoon
{
	class RoleRealization
	 : public ILiteralRealization
	{
	public:
		/**
		 * This is the value returned by the RoleRealization::type() method.
		 */
		const int TYPE = 2;
		
		/**
		 * The literal that represents the role.
		 */
		Literal& role;
		
		/**
		 * The identifier of the first variable of the role (the leftmost variable) which should be the same variable
		 * of the clause.
		 */
		int var1;
		
		/**
		 * The identifier of the second variable of the role (the rightmost variable) which should be different from
		 * the variable of the clause.
		 */
		int var2;
		
		/**
		 * The instance of the first variable.
		 */
		Instance* ivar1;
		
		/**
		 * The instance of the second variable.
		 */
		Instance* ivar2;
		
		/**
		 * Wether the role is negated or not, in its clause.
		 */
		bool neg;
		
		/**
		 * Constructor.
		 */
		RoleRealization(Literal& role, unsigned int var1, unsigned int var2, bool neg);
		
		/**
		 * Destructor. Currently does nothing.
		 */
		~RoleRealization();
		
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
		
		/**
		 * Prints the role, its sign and variables.
		 */
		virtual void print(std::vector<Instance*>& values);
		
		/**
		 * \brief Prints the role, its sign and variables.
		 * \param inst1 The instance corresponding to the first variable, or nullptr if no instance
		 * \param inst2 The instance corresponding to the second variable, or nullptr if no instance
		 * \remark if there are no instances in any inst parameter, the variable reference will be printed instead.
		 */
		virtual void print(Instance* inst1, Instance* inst2);
		
		/**
		 * Prints the role and its sign.
		 */
		virtual void print();
	};
}

#endif // __RACCOON_IR_ROLEREALIZATION_H
