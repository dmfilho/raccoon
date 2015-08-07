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
	time_t before = 0;
	
	if (options.valid)
	{
		if (!options.quiet) 
		{
			cout << "Parsing Ontology..." << flush;
			before = time(NULL);
		}
		parse_result* pr = OWL2_parse_file((char*)options.inputFileName->c_str());
		if (!options.quiet)
		{
			cout << (time(NULL) - before) <<  "secs" << endl;
			cout << "Normalizing Ontology..." << flush;
			before = time(NULL);
		}
		owl2.parse(pr, &ontology, &clauseSet, true);
		if (!options.quiet)
		{
			cout << (time(NULL) - before) <<  "secs"                                                     "\n"
			     << "--------------------------------------"                                             "\n"
			     << "Concepts: " << ontology.concepts.size() << " (" << ontology.conceptCount - ontology.newConceptCount << 
					" + " <<  ontology.newConceptCount << " new)"                                        "\n"
			     << "Roles: " << ontology.roles.size() <<                                                "\n"
			     << "Instances: " << ontology.instances.size() <<                                        "\n"
			     << "Axioms: " << (owl2.tboxCount() + owl2.aboxCount()) <<                               "\n"
			     << "TBox: " << owl2.tboxCount() <<                                                      "\n"
			     << "ABox: " << owl2.aboxCount() <<                                                      "\n"
			     << "Declarations: " << owl2.declarationCount() <<                                       "\n"
			     << "Annotations: " << owl2.annotationCount() <<                                         "\n"
			     << "Matrix Clauses: " << clauseSet.size() <<                                            "\n"
			     << "Unsupported Features: ";
			owl2.printUnsupportedFeatures();
			cout << endl
			     << "--------------------------------------" << endl << endl;
			before = time(NULL);
		}
		switch (options.command)
		{
			case OptionCmd::info:
			{
				return 0;
			}
			case OptionCmd::realization:
			{
				cout << "The realization is not implemented yet." << endl;
				return 1;
			}
			case OptionCmd::classification:
			{
				cout << "The classification is not implemented yet." << endl;
				return 1;
			}
			case OptionCmd::consistency:
			{
				FreitasMelo reasoner(&clauseSet);
				if (reasoner.consistency(&ontology))
				{
					cout << "true" << endl;
				}
				else
				{
					cout << "false" << endl;
				}
				if (!options.quiet)
				{
					cout << (time(NULL) - before) <<  "secs" << endl << flush;
				}
				return 0;
			}
			case OptionCmd::matrix:
			{
				cout << "Note: the matrix is transposed.\n";
				clauseSet.printClauses();
				return 0;
			}
			case OptionCmd::invalid_command:
			{
				cout << "Invalid command." << endl;
				return 1;
			}
		}
	}
}