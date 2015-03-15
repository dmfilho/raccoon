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
 * This file contains the definition of the OWL2 Parser. It is able to parse a 
 * OWL2 file in functional syntax using the automatically generated parser. It
 * also extract used information, normalizes it and build a knowledge base out
 * of it.
 */

#ifndef __PARSERS_OWL2_OWL2_H
#define __PARSERS_OWL2_OWL2_H

// STL
#include <string>
#include <vector>
// raccoon
#include "../../ir/Ontology.h"
#include "../../ir/Clause.h"
#include "../../ir/ClauseSet.h"
#include "owl2_parser.h"

using namespace std;
namespace raccoon
{
	class Owl2
	{
	private:
		Ontology* ontology;
		ClauseSet* clauseSet;
		ast_node* unionNode;		//< a fixed ObjectUnionOf node to be used on the parsing of DisjointUnion
	public:
		Owl2();
		~Owl2();
		void parseString(string& data, Ontology* ontology, ClauseSet* clauseSet, bool neg);
		void parseFile(string& fileName, Ontology* ontology, ClauseSet* clauseSet, bool neg);
		void parse(parse_result* pr, Ontology* ontology, ClauseSet* clauseSet, bool neg);
		void parseAxiom(ast_node* node, bool neg);
		void parseDeclaration(ast_node* node);
		void parseClassDeclaration(ast_node* node);
		void parseObjectPropertyDeclaration(ast_node* node);
		void parseNamedIndividualDeclaration(ast_node* node);
		void parseClassAxiom(ast_node* node, bool neg);
		void parseSubClassOf(ast_node* node, bool neg);
		void parseEquivalentClasses(ast_node* node, bool neg);
		void parseDisjointClasses(ast_node* node, bool neg);
		void parseDisjointUnion(ast_node* node, bool neg);
		void parseInclusion(ast_node* nodeSub, ast_node* nodeSuper, bool negNodeSub = false, bool negNodeSuper = false);
		void parseClassExpression(ast_node* node, bool lneg, Clause* clause, unsigned int var);
		void parseClass(ast_node* node, bool neg, Clause* clause, unsigned int var);
		void parseConjunction(ast_node* node, bool neg, Clause* clause, unsigned int var);
		void parseDisjunction(ast_node* node, bool neg, Clause* clause, unsigned int var);
		void parseUniversalQuantifier(ast_node* roleNode, ast_node* conceptNode, bool negRole, bool negConcept, Clause* clause, unsigned int var);
		void parseExistentialQuantifier(ast_node* roleNode, ast_node* conceptNode, bool negRole, bool negConcept, Clause* clause, unsigned int var);
		void parseObjectPropertyAxiom(ast_node* node);
		void parseAssertion(ast_node* node, bool neg);
		void parseClassAssertion(ast_node* classNode, ast_node* indiv, bool neg);
		void parseObjectPropertyAssertion(ast_node* roleNode, ast_node* source, ast_node* target, bool neg);
		Instance* getIndividualInstance(ast_node* individual);
		ast_node* findSibling(ast_node* node, int tokenId);
		ast_node* findChild(ast_node* node, int tokenId);

	};
}

#endif // __PARSERS_OWL2_OWL2_H
