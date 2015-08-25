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
 * \date 2015-08-11
 * \file
 * This file contains the implementation of the CM-ALC (with regularity and PURE reduction) reasoner class.
 */

// stl
#include <iostream>
#include <list>
// raccoon
#include "CMALCrp.h"
#include "../ir/Path.h"
#include "../ir/Connection.h"
#include "../ir/ConceptRealization.h"
#include "../ir/RoleRealization.h"
#include "../ir/UniversalRealization.h"
#include "../ir/Clause.h"
#include "../ir/ClauseSet.h"
#include "../misc/time.h"
#include "../misc/debug.h"

namespace raccoon
{		
	/**
	 * \brief Checks the consistency of the ontology.
	 * \param ontology
	 * \return true when the ontology is consistent, false otherwise.
	 */
	bool CMALCrp::consistency(Ontology* ontology)
	{
		Instance* inst1 = nullptr;
		Instance* inst2 = nullptr;
		raccoon_time before;
		if (this->pure)
		{
			cout << endl << "Performing PURE reduction..." << endl;
			gettime(&before);
			ontology->pureReduction();
			cout << "End of PURE reduction... [" << msecdiff(&before) << "ms]" << endl;
		}
		for (Clause* clause: *kb)
		{
			printd("\n# CMALCr::consistency start clause: ");
			calld(clause->print());
			if (clause->start && this->proveClause(clause, &inst1, 0, &inst2, -1))
			{
				printd("\n# CMALCr::consistency end (INCONSISTENT)\n");
				return false;
			}
			inst1 = nullptr;
			inst2 = nullptr;
		}
		printd("\n# CMALCr::consistency end (CONSISTENT)\n");
		return true;
	}
	
	/**
	 * \brief Query an hypothesis to the ontology.
	 * \param query The hypothesis
	 * \return true if the ontology entails the hypothesis, false otherwise.
	 */
	bool CMALCrp::query(ClauseSet* query)
	{
		Instance* inst1 = nullptr;
		Instance* inst2 = nullptr;
		this->path.clear();
		for (Clause* clause: *query)
		{
			printd("\n# CMALCr::query start clause: ");
			if (this->proveClause(clause, &inst1, 0, &inst2, -1))
			{
				printd("\n # CMALCr::query end\n");
				return true;
			}
			inst1 = nullptr;
			inst2 = nullptr;
		}
		printd("\n # CMALCr::query end\n");
		return false;
	}
	
	/**
	 * \brief Checks the regularity of the clause of a given possible connection.
	 * For all purposes a regularity occurs when the clause contains the path and the connection clause contains the
	 * exact same literal with the exact same instances.
	 * \param conn The connection to check.
	 * \return true when the clause contains a regular literal.
	 */
	bool CMALCrp::regularity(Clause* obj, Instance** instances)
	{
		// Check if the path itself contains a regular literal.
		if (path.regular())
		{
			return true;
		}
		// Check regularity for all concepts of the clause
		for (ConceptRealization* C: obj->concepts)
		{
			if (path.containsConcept(C, instances[C->var]))
			{
				return true;
			}
		}
		// Check regularity for all roles of the clause
		for (RoleRealization* R: obj->roles)
		{
			if (path.containsRole(R, instances[R->var1], instances[R->var2]))
			{
				return true;
			}
		}
		// Check regularity for all universals of the clause
		for (UniversalRealization* U: obj->universals)
		{
			if (path.containsConcept(&U->concept, instances[U->concept.var]) && 
			    path.containsRole(&U->role, instances[U->role.var1], instances[U->role.var2]))
			{
				return true;
			}
		}
		return false;
	}
	
	/**
	 * \brief Prove a clause considering the current path and at max two instances with their respective connection 
	 * indexes. Consider the term "this clause" to be the clause that we want to prove, and "connecting clause" the 
	 * clause that has a literal that is trying to connect to this clause.
	 * \param obj The clause to prove
	 * \param inst0 The pointer to the instance that is used by the "connecting clause" to connect to "this clause".
	 * \param inst0idx The number of the variable of "this clause" to set to inst0
	 * \param inst1 The pointer to the other instance (in case it is a role) that is used by the "connecting clause" to
	 * conect to "this clause".
	 * \param inst1idx The number of the variable of "this clause" to set to inst1
	 * \return true if able to connect everything, false otherwise.
	 */
	bool CMALCrp::proveClause(Clause* obj, Instance** inst0, int inst0idx, Instance** inst1, int inst1idx)
	{
		// Return in case the clause was removed by a reduction.
		if (obj->blocked) return false;
		int varcount = obj->varCount();
		printd("\n# proveClause (%d) PATH: ", ++clauseDepth);
		calld(path.print());
		// Check if it is possible to match the instances of the variables
		if (obj->values[inst0idx] != *inst0 && obj->values[inst0idx] != nullptr && *inst0 != nullptr)
		{
			printd("\n# proveClause (%d): FAIL (incompatible first variable) - backtrack", clauseDepth--);
			return false;
		}
		if (inst1idx != -1 && obj->values[inst1idx] != *inst1 && obj->values[inst1idx] != nullptr && *inst1 != nullptr)
		{
			printd("\n# proveClause (%d): FAIL (incompatible second variable) - backtrack", clauseDepth--);
			return false;
		}
		// Initialize a new list of instances of variables for the clause
		Instance* instances[varcount];
		for (int i = 0; i < varcount; ++i)
		{
			instances[i] = obj->values[i];
		}
		// Set variables accordingly
		if (instances[inst0idx] == nullptr)
		{
			if (*inst0 != nullptr)
			{
				instances[inst0idx] = *inst0;
			}
		}
		else
		{
			if (*inst0 == nullptr)
			{
				*inst0 = instances[inst0idx];
			}
		}
		if (inst1idx != -1 && instances[inst1idx] == nullptr)
		{
			if (*inst1 != nullptr)
			{
				instances[inst1idx] = *inst1;
			}
		}
		else
		{
			if (*inst1 == nullptr)
			{
				*inst1 = instances[inst1idx];
			}
		}
		if (this->regularity(obj, instances))
		{
			printd("\n# proveClause(%d,%d): Regular Clause", clauseDepth--, literalIndex);
			return false;
		}
		// Try to prove the clause, go prove its first concept
		if (this->proveNextConcept(obj, 0, instances))
		{
			if (instances[inst0idx] != nullptr)
			{
				*inst0 = instances[inst0idx];
			}
			if (inst1idx != -1 && instances[inst1idx] != nullptr && inst1 != nullptr)
			{
				*inst1 = instances[inst1idx];
			}
			printd("\n# proveClause (%d): SUCCESS", clauseDepth--);
			return true;
		}
		printd("\n# proveClause (%d): FAIL (no valid connections found) - backtrack", clauseDepth--);
		return false;
	}
	
	/**
	 * \brief Prove the next concept of the clause.
	 * \param obj The objective clause
	 * \param i The index of the concept on the clause
	 * \param instances The instance set to consider for this usage of the clause, this allows the same clause to be
	 * used again in the same path with differing instances.
	 * \return true when able to connect every LITERAL of the clause, including concepts, roles and universals 
	 * (see remark). It returns false otherwise.
	 * \remark after all subsequent concepts are connected, the method proceeds to call proveNextRole for the first role 
	 * on the clause. After all subsequent roles are connected, the proveNextRole method proceeds to call 
	 * proveNextUniversal to prove the first universal quantifier on the clause. Once all subsequent universals are 
	 * proved, it returns true. the truth is returned in a chain when all literals are connected.
	 */
	bool CMALCrp::proveNextConcept(Clause* obj, unsigned int i, Instance* instances[])
	{
		// If this concept index is beyond the last concept, go prove the first role
		if (i >= obj->concepts.size())
		{
			return proveNextRole(obj, 0, instances);
		}
		// Print debug information when in debug mode
		printd("\n# proveNextConcept (%d,%d): ", clauseDepth, ++literalIndex);
		calld(obj->concepts[i]->print(instances[obj->concepts[i]->var], nullptr));
		// Save the pointer of the instance for the variable of the concept, and its original value
		Instance** instptr = &instances[obj->concepts[i]->var];
		Instance* insttemp = nullptr;
		Instance* instorig = *instptr;
		// Check if this concept already appears on the path
		if (path.containsNegationOfConcept(obj->concepts[i], instorig))
		{
			printd("\n# proveNextConcept (%d,%d): SUCCESS (complement in path), trying next concept", clauseDepth, literalIndex--);
			return this->proveNextConcept(obj, i+1, instances);
		}
		// Try to connect the concept
		list<Connection*> * connList = obj->concepts[i]->concept.getconns(obj->concepts[i]->neg);
		PathItemConcept pathConcept = {
			.clause = obj,
			.concept = obj->concepts[i],
			.inst = instptr
		};
		path.pushConcept(&pathConcept);
		for (Connection* conn: *connList)
		{
			if (conn->universal) continue;
			printd("\n# proveNextConcept (%d,%d): ", clauseDepth, literalIndex); 
			calld(obj->concepts[i]->print(instances[obj->concepts[i]->var], nullptr));
			printd(" - CONNECT - ");
			calld(conn->clause->print());
			// Try to prove the connection, if it succeeds try to prove the next concept, if it succeeds, return true
			if (this->proveClause(conn->clause, instptr, conn->var1, &insttemp, conn->var2))
			{
				printd("\n# proveNextConcept (%d,%d): valid connection found, trying next literal)", clauseDepth, literalIndex);
				path.popConcept();
				if (this->proveNextConcept(obj, i+1, instances))
				{
					printd("\n# proveNextConcept (%d,%d): SUCCESS (valid connection)", clauseDepth, literalIndex--);
					return true;
				}
				if (*instptr == instorig) // the failure wasn't because of an instantiation.
				{
					printd("\n# (%d,%d): Literal Failed.", clauseDepth, literalIndex--);
					return false;
				}
				printd("\n# proveNextConcept (%d,%d): could not connect the remaining literals, trying another connection.", clauseDepth, literalIndex);
				path.pushConcept(&pathConcept);
			}
			// if something fail, restore the original instance of the variable of the concept, just in case it was
			// changed by the connection
			*instptr = instorig;
			insttemp = nullptr;
			printd("\n# proveNextConcept (%d,%d): STILL ", clauseDepth, literalIndex);
			calld(obj->concepts[i]->print(instances[obj->concepts[i]->var], nullptr));
		}
		path.popConcept();
		printd("\n# proveNextConcept (%d,%d): FAIL (no valid connections) - backtrack", clauseDepth, literalIndex--);
		return false;
	}
	
	/**
	 * \brief Prove the next role of the clause.
	 * \param obj The objective clause
	 * \param i The index of the role on the clause
	 * \param instances The instance set to consider for this usage of the clause, this allows the same clause to be
	 * used again in the same path with differing instances.
	 * \return true when able to connect every role and universal quantifier of the clause, false otherwise.
	 * \remark after all subsequent roles are connected, the method proceeds to call proveNextUniversal for the first 
	 * role on the clause.
	 */
	bool CMALCrp::proveNextRole(Clause* obj, unsigned int i, Instance* instances[])
	{
		// If this role index is beyond the last role, go prove the first universal quantifier
		if (i >= obj->roles.size())
		{
			return proveNextUniversal(obj, 0, instances);
		}
		// Print debug information when in debug mode
		printd("\n# proveNextRole (%d,%d): ", clauseDepth, ++literalIndex);
		calld(obj->roles[i]->print(instances[obj->roles[i]->var1], instances[obj->roles[i]->var2]));
		// Save the poitners of the instances for the variables of the role, and their original values
		Instance** instptr1 = &instances[obj->roles[i]->var1];
		Instance** instptr2 = &instances[obj->roles[i]->var2];
		Instance* instorig1 = *instptr1;
		Instance* instorig2 = *instptr2;
		// Check if the role already appears in the path
		if (path.containsNegationOfRole(obj->roles[i], instorig1, instorig2))
		{
			printd("\n# proveNextRole (%d,%d): SUCCESS (complement in path), trying next role", clauseDepth, literalIndex--);
			return this->proveNextRole(obj, i+1, instances);
		}
		// Try to connect the role
		list<Connection*> * connList = obj->roles[i]->role.getconns(obj->roles[i]->neg);
		PathItemRole pathRole = {
			.clause = obj,
			.role = obj->roles[i],
			.inst1 = instptr1,
			.inst2 = instptr2
		};
		path.pushRole(&pathRole);
		for (Connection* conn: *connList)
		{
			if (conn->universal) continue;
			printd("\n# proveNextConcept (%d,%d): ", clauseDepth, literalIndex); 
			calld(obj->roles[i]->print(instances[obj->roles[i]->var1], instances[obj->roles[i]
			->var2]));
			printd(" - CONNECT - ");
			calld(conn->clause->print());
			// Try to prove the connection, if it succeeds try to prove the next role, if it succeeds, return true
			if (this->proveClause(conn->clause, instptr1, conn->var1, instptr2, conn->var2))
			{
				printd("\n# proveNextRole (%d,%d): valid connection found, trying next literal)", clauseDepth, literalIndex);
				path.popRole();
				if (this->proveNextRole(obj, i+1, instances))
				{
					printd("\n# proveNextRole (%d,%d): SUCCESS (valid connection)", clauseDepth, literalIndex--);
					return true;
				}
				if (*instptr1 == instorig1) // the failure wasn't because of an instantiation.
				{
					printd("\n# (%d,%d): Literal Failed.", clauseDepth, literalIndex--);
					return false;
				}
				printd("\n# proveNextRole (%d,%d): could not connect the remaining literals, trying another connection.", clauseDepth, literalIndex);
				path.pushRole(&pathRole);
			}
			// if something fail, restore the original instances of the variables of the role, just in case it was
			// changed by the connection
			*instptr1 = instorig1;
			*instptr2 = instorig2;
			printd("\n# proveNextRole (%d,%d): STILL ", clauseDepth, literalIndex);
			calld(obj->roles[i]->print(instances[obj->roles[i]->var1], instances[obj->roles[i]->var2]));
		}
		path.popRole();
		printd("\n# proveNextRole (%d,%d): FAIL (no valid connection) - backtrack", clauseDepth, literalIndex--);
		return false;			
	}
	
	/**
	 * \brief Prove the next universal quantifier of the clause.
	 * \param obj The objective clause
	 * \param i The index of the universal quantifier on the clause
	 * \param instances The instance set to consider for this usage of the clause, this allows the same clause to be
	 * used again in the same path with differing instances.
	 * \return true when able to connect every universal quantifier on the clause, false otherwise.
	 * \remark after all subsequent universal quantifiers are connected, the method returns true.
	 */
	bool CMALCrp::proveNextUniversal(Clause* obj, unsigned int i, Instance* instances[])
	{
		// If this universal index is beyond the last universal, everything was proved. Return true.
		if (i >= obj->universals.size())
		{
			printd("\n# proveNextUniversal (%d): SUCCESS (no more literals on clause)", clauseDepth);
			return true;
		}
		// Print debug information when in debug mode
		printd("\n# proveNextUniversal (%d,%d): ", clauseDepth, ++literalIndex);
		calld(obj->universals[i]->print(instances[obj->universals[i]->role.var1], instances[obj->universals[i]->role.var2]));
		// Save the poitners of the instances for the variables of the universal, and their original values
		Instance** instptr1 = &instances[obj->universals[i]->role.var1];
		Instance** instptr2 = &instances[obj->universals[i]->role.var2];
		Instance* instorig1 = *instptr1;
		Instance* instorig2 = *instptr2;
		Instance* insttemp = nullptr;
		// Check if the universal's concept or role already appear in the path
		if (path.containsNegationOfConcept(&obj->universals[i]->concept, instorig2) ||
			path.containsNegationOfRole(&obj->universals[i]->role, instorig1, instorig2))
		{
			printd("\n# proveNextUniversal(%d,%d): SUCCESS (complement in path), trying next universal", clauseDepth, literalIndex--);
			return this->proveNextUniversal(obj, i+1, instances);
		}
		// Try to connect the concept pf the universal
		list<Connection*> * connList = obj->universals[i]->concept.concept.getconns(obj->universals[i]->concept.neg);
		// Save number of connections of concept for PURE checking later
		int connSize = connList->size();
		PathItemConcept pathConcept = {
			.clause = obj,
			.concept = &obj->universals[i]->concept,
			.inst = instptr2
		};
		path.pushConcept(&pathConcept);
		for (Connection* conn: *connList)
		{
			if (conn->universal) continue;
			printd("\n# proveNextUniversal (%d,%d): ", clauseDepth, literalIndex); 
			calld(obj->universals[i]->concept.print(instances[obj->universals[i]->concept.var], nullptr));
			printd(" - CONNECT - ");
			calld(conn->clause->print());
			// Try to prove the connection, if it succeeds try to prove the next concept, if it succeeds, return true
			if (this->proveClause(conn->clause, instptr2, conn->var1, &insttemp, conn->var2))
			{
				printd("\n# proveNextUniversal (%d,%d): (valid concept connection found), trying next literal", clauseDepth, literalIndex);
				path.popConcept();
				if (this->proveNextUniversal(obj, i+1, instances))
				{
					printd("\n# proveNextUniversal (%d,%d): SUCCESS (valid concept connection)", clauseDepth, literalIndex--);
					return true;
				}
				break;
				//printd("\n# proveNextUniversal (%d,%d): could not connect the remaining literals, trying another connection.", clauseDepth, literalIndex);
				//path.pushConcept(&pathConcept);
			}
			// if something fail, restore the original instance of the variable of the concept, just in case it was
			// changed by the connection
			*instptr2 = instorig2;
			insttemp = nullptr;
			printd("\n# proveNextUniversal (%d,%d): STILL CONCEPT ", clauseDepth, ++literalIndex);
			calld(obj->universals[i]->print(instances[obj->universals[i]->role.var1], instances[obj->universals[i]->role.var2]));
		}
		path.popConcept();
		// Try to connect the role of the universal
		connList = obj->universals[i]->role.role.getconns(obj->universals[i]->role.neg);
		// If both literals from universal restriciton are PURE literals, ignore clause from now on.
		connSize += connList->size();
		PathItemRole pathRole = {
			.clause = obj,
			.role = &obj->universals[i]->role,
			.inst1 = instptr1,
			.inst2 = instptr2
		};
		path.pushRole(&pathRole);
		for (Connection* conn: *connList)
		{
			if (conn->universal) continue;
			printd("\n# proveNextUniversal (%d,%d): ", clauseDepth, literalIndex); 
			calld(obj->universals[i]->role.print(instances[obj->universals[i]->role.var1], instances[obj->universals[i]->role.var2]));
			printd(" - CONNECT - ");
			calld(conn->clause->print());
			// Try to prove the connection, if it succeeds try to prove the next role, if it succeeds, return true
			if (this->proveClause(conn->clause, instptr1, conn->var1, instptr2, conn->var2))
			{
				printd("\n# proveNextUniversal (%d,%d): valid role connection found, trying next literal)", clauseDepth, literalIndex);
				path.popRole();
				if (this->proveNextUniversal(obj, i+1, instances))
				{
					printd("\n# proveNextUniversal (%d,%d): SUCCESS (valid role connection)", clauseDepth, literalIndex--);
					return true;
				}
				if (*instptr1 == instorig1) // the failure wasn't because of an instantiation.
				{
					printd("\n# (%d,%d): Literal Failed.", clauseDepth, literalIndex--);
					return false;
				}
				printd("\n# proveNextUniversal (%d,%d): could not connect the remaining literals, trying another connection.", clauseDepth, literalIndex);
				path.pushRole(&pathRole);
			}
			// if something fail, restore the original instances of the variables of the role, just in case it was
			// changed by the connection
			*instptr1 = instorig1;
			*instptr2 = instorig2;
			printd("\n# proveNextUniversal (%d,%d): STILL ROLE ", clauseDepth, ++literalIndex);
			calld(obj->universals[i]->print(instances[obj->universals[i]->role.var1], instances[obj->universals[i]->role.var2]));
		}
		path.popRole();
		printd("\n# proveNextUniversal (%d,%d): FAIL (no connection found) - backtrack", clauseDepth, literalIndex--);
		return false;	
	}
	
	CMALCrp::CMALCrp(ClauseSet* kb, bool pure)
	 : kb(kb)
	 , pure(pure)
	{
		calld(this->clauseDepth = 0);
		calld(this->literalIndex = 0);
	}

	CMALCrp::~CMALCrp()
	{
	}
}

