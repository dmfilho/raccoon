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
 * This file contains the declaration of the FreitasMelo reasoner class.
 */

// raccoon
#include "FreitasMelo.h"
#include "../../ir/ConnectionList.h"
#include "../../ir/ConceptRealization.h"
#include "../../ir/RoleRealization.h"
#include "../../ir/UniversalRealization.h"
#include "../../ir/Clause.h"
#include "../../ir/ClauseSet.h"

#include <iostream>

namespace raccoon
{
	bool FreitasMelo::consistency(Ontology* ontology)
	{
		for (Clause* clause: *kb)
		{
			if (this->prove(clause))
			{
				return false;
			}
		}
		return true;
	}
	
	bool FreitasMelo::query(ClauseSet* query)
	{
		this->path.clear();
		for (Clause* clause: *query)
		{
			if (this->prove(clause))
			{
				return true;
			}
		}
		return false;
	}
	
	bool FreitasMelo::regularity(Clause* objective)
	{
		// Check regularity for all concepts of the clause
		for (ConceptRealization* C: objective->concepts)
		{
			if (this->path.contains(C))
			{
				return true;
			}
		}
		// Check regularity for all roles of the clause
		for (RoleRealization* R: objective->roles)
		{
			if (this->path.contains(R))
			{
				return true;
			}
		}
		// Check regularity for all universals of the clause
		for (UniversalRealization* U: objective->universals)
		{
			if (this->path.contains(&U->concept) && this->path.contains(&U->role))
			{
				return true;
			}
		}
		return false;
	}
	
	bool FreitasMelo::connect(ILiteralRealization* lit, unsigned int id, bool neg)
	{
		this->path.push(lit);
		ConnectionList* connList = kb->getConnections(id, neg);
		for (Clause* conn: *connList)
		{
			// Make sure the clause isn't ignored
			if (conn->ignore)
			{
				continue;
			}
			// Try to connect
			if (this->prove(conn))
			{ 
				this->path.pop();
				return true;
			}
			//conn->ignore = true;
		}
		this->path.pop();
		return false;
	}
	
	bool FreitasMelo::prove(Clause* objective)
	{
		// Check for regularity cases
		if (this->regularity(objective))
		{
			return false;
		}
		// Prove each concept (connect each concept) of the clause
		for (ConceptRealization* C: objective->concepts)
		{
			// If the negation of the Literal is in the path, this literal is proved, skip it.
			if (this->path.containsNegationOf(C))
			{
				continue;
			}
			// If it isn't proved already, try to prove each possible connection.
			if (!this->connect(C, C->concept.id(), C->neg))
			{
				return false;
			}
		}
		// If the code reaches this point, it's because all Concepts were proved. Now we need to prove the roles.
		for (RoleRealization* R: objective->roles)
		{
			// If the negation of the Literal is in the path, this literal is proved, skip it.
			if (this->path.containsNegationOf(R))
			{
				continue;
			}
			// If it isn't proved already, try to prove each possible connection.
			if (!this->connect(R, R->role.id(), R->neg))
			{
				return false;
			}
		}
		// If the code reaches this point, it's because all Roles were proved. Now we need to prove the Universals.
		for (UniversalRealization* U: objective->universals)
		{
			// If the negation of the concept or the role is in the path, this universal is proved, skip it.
			if (this->path.containsNegationOf(&U->concept) || this->path.containsNegationOf(&U->role))
			{
				continue;
			}
			// If it isn't proved already, try to prove each possible connection.
			if (!this->connect(&U->concept, U->concept.concept.id(), U->concept.neg) &&
				!this->connect(&U->role, U->role.role.id(), U->role.neg))
			{
				return false;
			}
		}
		// If the code reached this point, everything was proved for this clause
		return true;
	}
	
	FreitasMelo::FreitasMelo(ClauseSet* kb)
	 : kb(kb)
	{
	}

	FreitasMelo::~FreitasMelo()
	{
	}
}

