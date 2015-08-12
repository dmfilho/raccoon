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
 * This file contains the declaration of the CM-ALC (with regularity) reasoner class.
 */

#ifndef __RACCOON_BACK_CMALCr_H
#define __RACCOON_BACK_CMALCr_H

// raccoon
#include "../ir/Path.h"
#include "../ir/ClauseSet.h"
#include "../ir/Clause.h"
#include "../ir/Ontology.h"
#include "../ir/Instance.h"


namespace raccoon
{
	class CMALCr
	{
	private:
		ClauseSet* kb;
		Path path;
		#ifdef _DEBUG
			int clauseDepth;
			int literalIndex;
		#endif
	public:
		bool consistency(Ontology* ontology);
		bool query(ClauseSet* query);
		bool regularity(Connection* obj);
		bool proveClause(Clause* obj, Instance** inst0, int inst0idx, Instance** inst1, int inst1idx);
		bool proveNextConcept(Clause* obj, unsigned int i, Instance* instances[]);
		bool proveNextRole(Clause* obj, unsigned int i, Instance* instances[]);
		bool proveNextUniversal(Clause* obj, unsigned int i, Instance* instances[]);
		
		CMALCr(ClauseSet* kb);
		~CMALCr();
	};
}

#endif /* __RACCOON_BACK_CMALCr_H */
