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
 * \date 2015-03-14
 * \file
 * This is the main file.
 */


// raccoon
extern "C" {
	#include "parsers/owl2/owl2_parser.h"
}
#include "parsers/owl2/Owl2.h"
#include "ir/Ontology.h"
#include "ir/ClauseSet.h"
#include "back/fm/FreitasMelo.h"
#include "misc/Options.h"
// STL
#include <iostream>
#include <ctime>

using namespace std;
using namespace raccoon;
int main(int argc, char* argv[])
{
	Options options(argc, argv);
	Owl2 owl2;
	Ontology ontology;
	ClauseSet clauseSet;
	time_t before;
	
	if (options.valid)
	{
		cout << "Parsing Ontology..." << flush;
		before = time(NULL);
		parse_result* pr = OWL2_parse_file((char*)options.inputFileName->c_str());
		cout << (time(NULL) - before) <<  "secs" << endl;
		cout << "Normalizing Ontology..." << flush;
		before = time(NULL);
		owl2.parse(pr, &ontology, &clauseSet, true);
		cout << (time(NULL) - before) <<  "secs" << endl;
		cout << "--------------------------------------" << endl;
		cout << "Concepts: " << ontology.concepts.size() << " (" << ontology.conceptCount - ontology.newConceptCount << 
				" + " <<  ontology.newConceptCount << " new)" << endl;
		cout << "Roles: " << ontology.roles.size() << endl;
		cout << "Instances: " << ontology.instances.size() << endl;
		cout << "Matrix Clauses: " << clauseSet.size() << endl;
		cout << "--------------------------------------" << endl << endl;
		cout << "Reasoning..." << flush;
		before = time(NULL);
		FreitasMelo reasoner(&clauseSet);
		if (reasoner.consistency(&ontology))
		{
			cout << "true" << endl;
		}
		else
		{
			cout << "false" << endl;
		}
		cout << (time(NULL) - before) <<  "secs" << endl << flush;
	}
}