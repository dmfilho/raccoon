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
 * This file contains the implementation of the Path class.
 */

// stl
#include <iostream>
// raccoon
#include "Path.h"

/**
 * Macro used to check for regularity (simplifying instance check).
 * __Pi stands for Path Instance
 * __Li stands for Literal Instance
 */
#define INST_EQUIV_OR_SKOLEM(__Pi, __Li) \
    (__Pi == __Li || __Pi == nullptr || (__Li != nullptr && __Pi->skolem && __Li->skolem))

namespace raccoon
{
	/**
	 * Clears all concepts and roles on the path.
	 */
	void Path::clear()
	{
		while (this->concepts.size() > 0)
		{
			this->popConcept();
		}
		while (this->roles.size() > 0)
		{
			this->popRole();
		}
	}
	
	/**
	 * \brief Tells whether the path contains a specific role with specific instances.
	 * If some instance is nullptr it is ignored while comparing.
	 * @param role The role to find on path
	 * @param inst1 The instance of the first variable of the role, or nullptr to ignore.
	 * @param inst2 The instance of the second variable of the role, or nullptr to ignore.
	 * @return true if the path contains the role.
	 */
	bool Path::containsRole(RoleRealization* role, Instance* inst1, Instance* inst2)
	{
		for (PathItemRole* item: this->roles)
		{
            Instance * iinst1 = *(item->inst1);
            Instance * iinst2 = *(item->inst2);
			if (item->role->equivalentTo(role) && 
                INST_EQUIV_OR_SKOLEM(iinst1, inst1) &&
                INST_EQUIV_OR_SKOLEM(iinst2, inst2)
            )
			{
				return true;
			}
		}
		return false;
	}
	
	/**
	 * \brief Tells whether the path contains the negation of a specific role with specific instances.
	 * If some instance is nullptr it is ignored while comparing.
	 * @param role The role to find on path
	 * @param inst1 The instance of the first variable of the role, or nullptr to ignore.
	 * @param inst2 The instance of the second variable of the role, or nullptr to ignore.
	 * @return true if the path contains the negation of the given role.
	 */
	PathItemRole * Path::containsNegationOfRole(RoleRealization* role, Instance* inst1, Instance* inst2, bool exactly)
	{
        Instance * iinst1;
        Instance * iinst2;
		for (PathItemRole* item: this->roles)
		{
            iinst1 = *(item->inst1);
            iinst2 = *(item->inst2);
			if (item->role->complementOf(role) && 
                (
                    (!exactly && (inst1 == nullptr ||
                    iinst1 == nullptr)) ||
                    inst1 == iinst1
                ) && (
                    (!exactly && (inst2 == nullptr ||
                    iinst2 == nullptr)) ||
                    inst2 == iinst2
                )
            )
			{
				return item;
			}
		}
		return nullptr;
	}
		
	/**
	 * \brief Push a specific role with specific instances to the path.
	 * If some instance is nullptr it is treated as a variable (i.e. ignored).
	 * @param role The role to push to the path
	 * @param inst1 The instance of the first variable of the role, or nullptr to leave as a variable.
	 * @param inst2 The instance of hte second variable of the role, or nullptr to leave as a variable.
	 */
	void Path::pushRole(PathItemRole * pathRole)
	{
		this->roles.push_back(pathRole);
	}
	
	/**
	 * \brief Pop the topmost role from the path.
	 * \remark This is different from popConcept (i.e. work on a different stack).
	 */
	void Path::popRole()
	{
		this->roles.pop_back();
	}
	
	/**
	 * \brief Tells whether the path contains a specific concept with a specific instance.
	 * If the instance is nullptr it is treated as a variable and is ignored on the comaprison.
	 * @param concept The concept to check if it is in the path.
	 * @param inst The instance of the concept, or nullptr to ignore.
	 * @return true if the concept with its respective instance is in the path.
	 */
	bool Path::containsConcept(ConceptRealization* concept, Instance* inst)
	{
		for (PathItemConcept* item: this->concepts)
		{
            Instance * iinst = *(item->inst);
			if (item->concept->equivalentTo(concept) && 
                INST_EQUIV_OR_SKOLEM(iinst, inst)
            )
			{
				return true;
			}
		}
		return false;
	}
	
	/**
	 * \brief Tells whether the path contains the negation of a specific concept with a specific instance.
	 * If the instance is nullptr it is treated as a variable and is ignored on the comparison.
	 * @param concept The concept to check if it is in the path.
	 * @param inst The instance of the concept, or nullptr to ignore.
	 * @return pointer to ConceptRealization if a negation of the concept with its respective instance 
     * is in the path.
	 */
	PathItemConcept * Path::containsNegationOfConcept(ConceptRealization* concept, Instance* inst, bool exactly)
	{
        Instance * iinst;
		for (PathItemConcept* item: this->concepts)
		{
            iinst = *(item->inst);
			if (
                item->concept->complementOf(concept) && 
                (
                    (!exactly && (inst == nullptr ||
                    iinst == nullptr)) ||
                    inst == iinst
                )
            )
			{ 
				return item;
			}
		}
		return nullptr;
	}
	
	/**
	 * \brief Push a concept to the top of the path, with the given instance.
	 * if the instance is nullptr, it is treated as a variable (i.e. ignored).
	 * @param concept The concept to push to the top of the path.
	 * @param inst The instance of the concept, or nullptr to ignore.
	 */
	void Path::pushConcept(PathItemConcept * concept)
	{
		this->concepts.push_back(concept);
	}
	
	/**
	 * \brief Pop a concept from the top of the path.
	 * \remark this is different from popRole, i.e. uses a different stack.
	 */
	void Path::popConcept()
	{
		this->concepts.pop_back();
	}
	
	bool Path::regular()
	{
		if (concepts.size() > 0)
		{
			PathItemConcept* lastConcept = concepts.back();
			ConceptRealization* c = lastConcept->concept;
            Instance * lastInst = *(lastConcept->inst);
            Instance * pathInst;
			for (auto it = concepts.end()-1; it != concepts.begin(); )
			{
				--it;
                pathInst = *((*it)->inst);
				if (c->equivalentTo((*it)->concept) && 
                    INST_EQUIV_OR_SKOLEM(pathInst, lastInst))
				{
					return true;
				}
			}
		}
		if (roles.size() > 0)
		{
			PathItemRole* lastRole = roles.back();
			RoleRealization* r = lastRole->role;
            Instance * lastInst1 = *(lastRole->inst1);
            Instance * lastInst2 = *(lastRole->inst2);
            Instance * pathInst1;
            Instance * pathInst2;
			for (auto it = roles.end()-1; it != roles.begin(); )
			{
				--it;
                pathInst1 = *((*it)->inst1);
                pathInst2 = *((*it)->inst2);
				if (r->equivalentTo((*it)->role) && INST_EQUIV_OR_SKOLEM(pathInst1, lastInst1) && 
                    INST_EQUIV_OR_SKOLEM(pathInst2, lastInst2))
				{
					return true;
				}
			}
		}
		return false;
	}
	
	/**
	 * \brief Prints the full path.
	 */
	void Path::print()
	{
		for (PathItemRole* item: this->roles)
		{
			item->role->print(*(item->inst1), *(item->inst2));
			cout << ',';
		}
		for (PathItemConcept* item: this->concepts)
		{
			item->concept->print(*(item->inst), nullptr);
			cout << ',';
		}
	}
	
	/**
	 * Constructor. Currently does nothing.
	 */
	Path::Path()
	{
	}
	
	/**
	 * Destructor. Currently does nothing.
	 */
	Path::~Path()
	{
		this->clear();
	}
}

