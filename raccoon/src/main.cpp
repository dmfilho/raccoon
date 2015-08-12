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
#include "back/CMALCr.h"
#include "misc/Options.h"
// STL
#include <iostream>
#include <sys/time.h>

using namespace std;
using namespace raccoon;

double msecdiff(struct timeval *before)
{
	struct timeval now;
	gettimeofday(&now, NULL);
	return (double)(now.tv_sec - before->tv_sec) * 1000.0f +
	       (double)(now.tv_usec - before->tv_usec) / 1000.0f;
}

int main(int argc, char* argv[])
{
	Options options(argc, argv);
	Owl2 owl2;
	Ontology ontology;
	ClauseSet clauseSet;
	struct timeval before;
	
	if (options.valid)
	{
		if (!options.quiet) 
		{
			cout << "Parsing Ontology..." << flush;
			gettimeofday(&before, NULL);
		}
		parse_result* pr = OWL2_parse_file((char*)options.inputFileName->c_str());
		if (pr == nullptr)
		{
			return 1;
		}
		if (!options.quiet)
		{
			cout << "OK [" << msecdiff(&before) <<  " ms]" << endl;
			cout << "Normalizing Ontology..." << flush;
			gettimeofday(&before, NULL);
		}
		owl2.parse(pr, &ontology, &clauseSet, true);
		if (!options.quiet)
		{
			cout << "OK [" << msecdiff(&before) <<  " ms]"                                               "\n"
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
			gettimeofday(&before, NULL);
		}
		switch (options.command)
		{
			case OptionCmd::info:
			{
				return 0;
			}
			case OptionCmd::realization:
			{
				// TODO: implement ontology realization, issue #4
				cout << "The realization is not implemented yet." << endl;
				return 1;
			}
			case OptionCmd::classification:
			{
				// TODO: implement ontology classification, issue #3
				cout << "The classification is not implemented yet." << endl;
				return 1;
			}
			case OptionCmd::consistency:
			{
				CMALCr reasoner(&clauseSet);
				if (!options.quiet)
				{
					cout << "Checking Consistency..." << flush;
				}
				if (reasoner.consistency(&ontology))
				{
					cout << "true";
				}
				else
				{
					cout << "false";
				}
				if (!options.quiet)
				{
					cout << " [" << msecdiff(&before) <<  " ms]";
				}
				cout << endl << flush;
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