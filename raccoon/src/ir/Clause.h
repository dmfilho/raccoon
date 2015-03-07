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
 * This file contains the definition of the Clause class.
 */

#ifndef __RACCOON_IR_CLAUSE_H
#define __RACCOON_IR_CLAUSE_H

// STL
#include <vector>
#include <functional>
// raccoon
#include "ConceptRealization.h"
#include "RoleRealization.h"
#include "UniversalRealization.h"

using namespace std;
namespace raccoon
{
	class Clause
	{
	private:
		unsigned int _varCount;
	public:
		/**
		 * List of concept realizations of the clause. A concept realization is a concept coupled to an instance when
		 * necessary. Since a clause can deal with multiple variables, the realization also tells which var of the 
		 * clause the concept deals with.
		 */
		vector<ConceptRealization*> concepts;		// List of concepts of the clause
		
		/**
		 * List of role realizations of the clause. A role realization is a role coupled with up to two instances when
		 * necessary. Since a clause can deal with multiple variables and a role uses two variables, the realization
		 * also tells which variables of the clause the role deals with.
		 */
		vector<RoleRealization*> roles;				// List of roles of the clause
		
		/**
		 * List of universal realizations of the clause. An universal realization consists of a tuple of (role,concept).
		 * Since a clause can deal with multiple variables and an universal quantifier uses two variables, the
		 * realization also tells which variables of the clause the universal quantifier deals with.
		 */
		vector<UniversalRealization*> universals;	// List of universal quantifiers of the clause
		
		/**
		 * List of instances associated to each variable by default. This is only used by assertions, since they are
		 * bound to an instance from the beggining.
		 */
		vector<Instance*> values;					// List of instances assigned to each variable by default
		
		/**
		 * Return the number of variables used by the current clause.
		 */
		inline unsigned int varCount()
		{
			return _varCount;
		}
		
		/**
		 * \returns true when the clause contains the specified literal.
		 */
		bool contains(unsigned int id, bool negated);
		
		/**
		 * Adds a ConceptRealization to the concepts vector.
		 */
		inline void add(ConceptRealization* cr, bool newvar = false)
		{
			this->concepts.push_back(cr);
			if (newvar)
			{
				cr->var = _varCount++;
				values.push_back(nullptr);
			}
		}
		
		/**
		 * \brief Adds a RoleRealization to the concepts vector.
		 */
		inline void add(RoleRealization* rr)
		{
			this->roles.push_back(rr);
			rr->var2 = _varCount++;
			values.push_back(nullptr);
		}
		
		/**
		 * \brief Adds an UniversalRealization to the concepts vector.
		 */
		inline void add(UniversalRealization* ur)
		{
			this->universals.push_back(ur);
			unsigned int var2 = _varCount++;
			ur->concept.var = var2;
			ur->role.var2 = var2;
			values.push_back(nullptr);
		}
		
		/**
		 * Constructor
		 */
		Clause();
		
		/**
		 * Destructor
		 */
		~Clause();

	};

}

#endif // __RACCOON_IR_CLAUSE_H
