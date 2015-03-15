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

#ifndef __RACCOON_BACK_FM_FREITASMELO_H
#define __RACCOON_BACK_FM_FREITASMELO_H

// raccoon
#include "../../ir/Path.h"
#include "../../ir/ClauseSet.h"
#include "../../ir/Clause.h"
#include "../../ir/Ontology.h"

namespace raccoon
{
	class FreitasMelo
	{
	private:
		ClauseSet* kb;
		Path path;
	public:
		bool consistency(Ontology* ontology);
		bool query(ClauseSet* query);
		bool regularity(Clause* objective);
		bool connect(ILiteralRealization* lit, unsigned int id, bool neg);
		bool prove(Clause* objective);
		
		FreitasMelo(ClauseSet* kb);
		~FreitasMelo();
	};
}

#endif // __RACCOON_BACK_FM_FREITASMELO_H
