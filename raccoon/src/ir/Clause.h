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
#include "Connection.h"

using namespace std;
namespace raccoon
{
	class Clause
	{
	private:
		unsigned int _varCount;
	public:
		/**
		 * When true, the clause is not used on the reasoning process.
		 */
		bool blocked;
		
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
		 * List of list of instances, each list of instances contains the instances used within a usage of the clause
		 * on the proof.
		 */
		vector<Instance*> values;
		
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
		bool contains(unsigned int id, bool negated, int* var1, int* var2);
		
		/**
		 * \brief Negates each literal of the clause.
		 */
		void negate();
		
		/**
		 * Adds a ConceptRealization to the concepts vector.
		 */
		inline void add(ConceptRealization* cr, bool newvar = false)
		{
			// Do not add Thing neither !Nothing since they don't change the value of disjunctions.
			if ((cr->concept.name() == "owl:Thing" && cr->neg == false) ||
			   (cr->concept.name() == "owl:Nothing" && cr->neg == true))
			{
				delete cr;
				return;
			}
			this->concepts.push_back(cr);
			if (newvar)
			{
				cr->var = _varCount++;
				values.push_back(nullptr);
			}
			cr->conn_ptr = cr->concept.addconn(new Connection(this, cr->var, 0, false), cr->neg, (values[cr->var] != nullptr));
		}
		
		/**
		 * \brief Adds a RoleRealization to the concepts vector.
		 * \param rr The RoleRealization object
		 * \param assertion true if adding an assertion (i.e. role with instances). this is used to order the
		 * connections for the role.
		 */
		inline void add(RoleRealization* rr, bool assertion)
		{
			this->roles.push_back(rr);
			rr->var2 = _varCount++;
			values.push_back(nullptr);
			rr->conn_ptr = rr->role.addconn(new Connection(this, rr->var1, rr->var2, false), rr->neg, assertion);
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
			ur->concept.conn_ptr = ur->concept.concept.addconn(new Connection(this, var2, 0, true), ur->concept.neg, false);
			ur->role.conn_ptr = ur->role.role.addconn(new Connection(this, ur->role.var1, var2, true), ur->role.neg, false);
		}
		
		inline int blockIfPureUniversal()
		{
			int cblocked = 0;
			for (UniversalRealization* u: universals)
			{
				if (u->concept.concept.pure() && u->role.role.pure())
				{
					++cblocked;
					this->block();
				}
			}
			return cblocked;
		}
		
		inline void block()
		{
			blocked = true;
			for (ConceptRealization* c: concepts)
				c->concept.delconn(c->conn_ptr, c->neg);
			for (RoleRealization* r: roles)
				r->role.delconn(r->conn_ptr, r->neg);
			for (UniversalRealization* u: universals)
			{
				u->concept.concept.delconn(u->concept.conn_ptr, u->concept.neg);
				u->role.role.delconn(u->role.conn_ptr, u->role.neg);
			}
		}
		
		/**
		 * \brief Prints the clause in a user friendly form, horizontally.
		 */
		void print();
		
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
