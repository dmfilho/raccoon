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
 * This file contains the declaration of the Path class.
 */

#ifndef __RACCOON_IR_PATH_H
#define __RACCOON_IR_PATH_H

// STL
#include <vector>
// raccoon
#include "ConceptRealization.h"
#include "RoleRealization.h"
#include "Instance.h"

using namespace std;
namespace raccoon
{
	/**
	 * \brief This structure defines the basic concept storage for the path (a concept and its instance).
	 */
	typedef struct _PathItemConcept
	{
		Clause* clause;
		ConceptRealization* concept;
		Instance** inst;
	} PathItemConcept;
	
	/**
	 * \brief This structure defines the basic role storage for the path (a role and its instances).
	 */
	typedef struct _PathItemRole
	{
		Clause* clause;
		RoleRealization* role;
		Instance** inst1;
		Instance** inst2;
	} PathItemRole;
	
	/**
	 * \class Path
	 * \brief Defines a walked path, containing concepts and roles.
	 */
	class Path
	{
	private:
		/**
		 * Contains the concepts on the path.
		 * The path does NOT own the pointers, thus it is not responsible for calling their destructors.
		 */
		vector<PathItemConcept*> concepts;
		
		/**
		 * Contains the roles on the path.
		 * The path does NOT own the pointers, thus it is not responsible for calling their destructors.
		 */
		vector<PathItemRole*> roles;
		
	public:		
		/**
		 * Clears the list of items on the path.
		 */
		void clear();
		
		/**
		 * \brief Tells whether the path contains a specific role with specific instances.
		 * If some instance is nullptr it is ignored while comparing.
		 * @param role The role to find on path
		 * @param inst1 The instance of the first variable of the role, or nullptr to ignore.
		 * @param inst2 The instance of the second variable of the role, or nullptr to ignore.
		 * @return true if the path contains the role.
		 */
		bool containsRole(RoleRealization* role, Instance* inst1, Instance* inst2);
		
		/**
		 * \brief Tells whether the path contains the negation of a specific role with specific instances.
		 * If some instance is nullptr it is ignored while comparing.
		 * @param role The role to find on path
		 * @param inst1 The instance of the first variable of the role, or nullptr to ignore.
		 * @param inst2 The instance of the second variable of the role, or nullptr to ignore.
		 * @return true if the path contains the negation of the given role.
		 */
		PathItemRole * containsNegationOfRole(RoleRealization* role, Instance* inst1, Instance* inst2);
		
		/**
		 * \brief Push a specific role with specific instances to the path.
		 * If some instance is nullptr it is treated as a variable (i.e. ignored).
		 * @param role The role to push to the path
		 * @param inst1 The instance of the first variable of the role, or nullptr to leave as a variable.
		 * @param inst2 The instance of hte second variable of the role, or nullptr to leave as a variable.
		 */
		void pushRole(PathItemRole *pathRole);
		
		/**
		 * \brief Pop the topmost role from the path.
		 * \remark This is different from popConcept (i.e. work on a different stack).
		 */
		void popRole();
		
		/**
		 * \brief Tells whether the path contains a specific concept with a specific instance.
		 * If the instance is nullptr it is treated as a variable and is ignored on the comaprison.
		 * @param concept The concept to check if it is in the path.
		 * @param inst The instance of the concept, or nullptr to ignore.
		 * @return true if the concept with its respective instance is in the path.
		 */
		bool containsConcept(ConceptRealization* concept, Instance* inst);
		
		/**
		 * \brief Tells whether the path contains the negation of a specific concept with a specific instance.
		 * If the instance is nullptr it is treated as a variable and is ignored on the comparison.
		 * @param concept The concept to check if it is in the path.
		 * @param inst The instance of the concept, or nullptr to ignore.
		 * @return true if a negation of the concept with its respective instance is in the path.
		 */
		PathItemConcept * containsNegationOfConcept(ConceptRealization* concept, Instance* inst);
		
		/**
		 * \brief Push a concept to the top of the path, with the given instance.
		 * if the instance is nullptr, it is treated as a variable (i.e. ignored).
		 * @param concept The concept to push to the top of the path.
		 * @param inst The instance of the concept, or nullptr to ignore.
		 */
		void pushConcept(PathItemConcept *pathCocnept);
		
		/**
		 * \brief Pop a concept from the top of the path.
		 * \remark this is different from popRole, i.e. uses a different stack.
		 */
		void popConcept();
		
		/**
		 * \brief Returns true if the path itself contains regular literals.
		 * \return true if the path contains regular literals.
		 */
		bool regular();
		
		/**
		 * \brief Prints the whole path.
		 */
		void print();
		
		/**
		 * Constructor. Currently does nothing.
		 */
		Path();
		
		/**
		 * Destructor. Currently does nothing.
		 */
		~Path();
	};
}

#endif // __RACCOON_IR_PATH_H
