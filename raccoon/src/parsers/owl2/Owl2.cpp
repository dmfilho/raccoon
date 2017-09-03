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
 
// STL
#include <string>
#include <iostream>
// raccoon
extern "C" {
	#include "owl2_parser.h"
}
#include "Owl2.h"
#include "../../exceptions/parser_exception.h"
#include "../../exceptions/unsupported_feature_exception.h"
#include "../../ir/Ontology.h"
#include "../../ir/Clause.h"
#include "../../ir/ConceptRealization.h"
#include "../../ir/RoleRealization.h"
#include "../../ir/UniversalRealization.h"
#include "../../ir/ExistentialRealization.h"

using namespace std;
namespace raccoon
{
	
	Owl2::Owl2()
	 : _declarationCount(0)
	 , _classAxiomCount(0)
	 , _objectPropertyAxiomCount(0)
	 , _dataPropertyAxiomCount(0)
	 , _datatypeDefinitionCount(0)
	 , _hasKeyCount(0)
	 , _assertionCount(0)
	 , _annotationCount(0)
	{
		// Create the ObjectUnionOf node and all its children.
		unionNode = ast_new_node();
		unionNode->tokenId = OWL2_ClassExpression;
		ast_node* node = ast_new_node();
		unionNode->firstChild = node;
		node->tokenId = OWL2_ObjectUnionOf;
		node->firstChild = ast_new_node();
		node = node->firstChild;
		node->tokenId = OWL2_OBJECTUNIONOF;
		node->nextSibling = ast_new_node();
		node = node->nextSibling;
		node->tokenId = OWL2_LPAR;
		node->nextSibling = 0;
	}
	
	Owl2::~Owl2()
	{
		if (unionNode != nullptr)
		{
			unionNode->firstChild->firstChild->nextSibling->nextSibling = 0;
			ast_free(unionNode);
		}
	}
	
	void Owl2::parseString(string& data, Ontology* ontology, ClauseSet* clauseSet, bool neg)
	{
		parse_result* pr = OWL2_parse_string((char*)data.c_str());
		parse(pr, ontology, clauseSet, neg);
		parse_result_free(pr);
	}
	
	/**
	 * Loads an OWL2 Functional-Syntax File and tries to parse it.
	 * \param fileName the name of the file.
	 */
	void Owl2::parseFile(string& fileName, Ontology* ontology, ClauseSet* clauseSet, bool neg)
	{
		parse_result* pr = OWL2_parse_file((char*)fileName.c_str());
		parse(pr, ontology, clauseSet, neg);
		parse_result_free(pr);
	}
	
	/**
	 * \brief Convert a parse_result into a clauseSet for the given ontology.
	 */
	void Owl2::parse(parse_result* pr, Ontology* ontology, ClauseSet* clauseSet, bool neg)
	{
		ast_node* node = pr->ast;
		this->ontology = ontology;
		this->clauseSet = clauseSet;
		// Check the root node
		if (node == nullptr || node->tokenId != OWL2_ontologyDocument)
		{
			throw parser_exception("OWL2 Parser Error: Invalid OWL2 document. Invalid ROOT node?.");
		}
		// Find the "Ontology" node.
		node = findChild(node, OWL2_Ontology);
		if (node == nullptr)
		{
			throw parser_exception("OWL2 Parser Error: The document doesn't contain an Ontology definition.");
		}
		// Find the "axioms" child node of the "Ontology" node.
		node = findChild(node, OWL2_axioms);
		if (node == nullptr)
		{
			throw parser_exception("OWL2 Parser Error: The document doesn't contain any axiom.");
		}
		// Iterate over all axioms
		while (node != nullptr)
		{
			node = node->firstChild;
			// break if there are no more axioms
			if (node == nullptr)
			{
				break;
			}
			// if it is an axiom, parse it
			if (node->tokenId == OWL2_Axiom)
			{
				try 
				{
					Owl2::parseAxiom(node, neg);
				} 
				catch (unsupported_feature_exception ex)
				{
					this->unsupportedFeatures.emplace(ex.feature());
				}
			}
			node = findSibling(node, OWL2_axioms);
		}		
	}
	
	void Owl2::parseAxiom(ast_node* node, bool neg)
	{
		// Parse the Axiom according to its type
		node = node->firstChild;
		if (node == nullptr)
		{
			throw parser_exception("OWL2 Parser Error: The document contains an empty or undefined Axiom");
		}
		switch (node->tokenId)
		{
			case OWL2_Declaration:
				++this->_declarationCount;
				parseDeclaration(node);
				break;
			case OWL2_ClassAxiom:
				++this->_classAxiomCount;
				parseClassAxiom(node, neg);
				break;
			case OWL2_ObjectPropertyAxiom:
				++this->_objectPropertyAxiomCount;
				parseObjectPropertyAxiom(node);
				break;
			case OWL2_DataPropertyAxiom:
				++this->_dataPropertyAxiomCount;
				throw unsupported_feature_exception(
					"OWL2 Parser Error: The reasoner doesn't support DataPropertyAxiom constructs.",
					"DataPropertyAxiom");
				break;
			case OWL2_DatatypeDefinition:
				++this->_datatypeDefinitionCount;
				throw unsupported_feature_exception(
					"OWL2 Parser Error: The reasoner doesn't support DatatypeDefinition constructs.",
					"DatatypeDefinition");
				break;
			case OWL2_HasKey:
				++this->_hasKeyCount;
				throw unsupported_feature_exception(
					"OWL2 Parser Error: The reasoner doesn't support HasKey constructs.",
					"HasKey");
				break;
			case OWL2_Assertion:
				++this->_assertionCount;
				parseAssertion(node, neg);
				break;
			case OWL2_AnnotationAxiom:
				++this->_annotationCount;
				// ignores AnnotationAxiom
				break;
			default:
				throw parser_exception("OWL2 Parser Error: Unknown Axiom Type on the Document.");
		}
		
	}
	
	void Owl2::parseDeclaration(ast_node* node)
	{
		// find the "Entity" node
		node = findChild(node, OWL2_Entity);
		if (node == nullptr)
		{
			throw parser_exception("OWL2 Parser Error: Declaration without Entity node");
		}
		// parse the Entity according to its type
		node = node->firstChild;
		switch (node->tokenId)
		{
			case OWL2_CLASS:
				parseClassDeclaration(findSibling(node, OWL2_Class));
				break;
			case OWL2_OBJECTPROPERTY:
				parseObjectPropertyDeclaration(findSibling(node, OWL2_ObjectProperty));
				break;
			case OWL2_NAMEDINDIVIDUAL:
				parseNamedIndividualDeclaration(findSibling(node, OWL2_NamedIndividual));
				break;
			default:
				return;
		}
	}
	
	void Owl2::parseClassDeclaration(ast_node* node)
	{
		if (node == nullptr || node->firstChild == nullptr || node->firstChild->firstChild == nullptr)
		{
			throw parser_exception("OWL2 Parser Error: Class Declaration missing class name");
		}
		// class name = Class->IRI->[IRITYPE]->data
		string className(node->firstChild->firstChild->data);
		ontology->assertConcept(className);
	}
	
	void Owl2::parseObjectPropertyDeclaration(ast_node* node)
	{
		if (node == nullptr || node->firstChild == nullptr || node->firstChild->firstChild == nullptr)
		{
			throw parser_exception("OWL2 Parser Error: ObjectProperty Declaration missing name");
		}
		// ObjectProperty name = ObjectProperty->IRI->[IRITYPE]->data
		string objectPropertyName(node->firstChild->firstChild->data);
		ontology->assertRole(objectPropertyName);
	}
	
	void Owl2::parseNamedIndividualDeclaration(ast_node* node)
	{
		if (node == nullptr || node->firstChild == nullptr || node->firstChild->firstChild == nullptr)
		{
			throw parser_exception("OWL2 Parser Error: NamedIndividual Declaration missing name");
		}
		// NamedIndividual name = NamedIndividua->IRI->[IRITYPE]->data
		string namedIndividualName(node->firstChild->firstChild->data);
		ontology->assertInstance(namedIndividualName);
	}	
	
	void Owl2::parseClassAxiom(ast_node* node, bool neg)
	{
		// parse the class axiom according to its type
		node = node->firstChild;
		switch (node->tokenId)
		{
			case OWL2_SubClassOf:
				parseSubClassOf(node, neg);
				break;
			case OWL2_EquivalentClasses:
				parseEquivalentClasses(node, neg);
				break;
			case OWL2_DisjointClasses:
				parseDisjointClasses(node, neg);
				break;
			case OWL2_DisjointUnion:
				parseDisjointUnion(node, neg);
				break;				
		}
	}
	
	void Owl2::parseSubClassOf(ast_node* node, bool neg)
	{
		node = findChild(node, OWL2_subClassExpression);
		if (node == nullptr)
		{
			throw parser_exception("OWL2 Parser Error: a SubClassOf requires a ClassExpression.");
		}
		parseInclusion(node->firstChild, node->nextSibling->firstChild, neg, neg);
	}
	
	void Owl2::parseEquivalentClasses(ast_node* node, bool neg)
	{
		node = findChild(node, OWL2_ClassExpression);
		if (node == nullptr)
		{
			throw parser_exception("OWL2 Parser Error: a EquivalentClasses Node requires a ClassExpression.");
		}
		while (node != nullptr)
		{
			ast_node* eqNode = node->nextSibling;
			while (eqNode != nullptr)
			{
				if (eqNode->tokenId == OWL2_ClassExpressionList)
				{
					eqNode = eqNode->firstChild;
					if (eqNode == nullptr)
					{
						break;
					}
				}
				parseInclusion(node, eqNode, neg, neg);
				parseInclusion(eqNode, node, neg, neg);
				eqNode = eqNode->nextSibling;
			}
			node = node->nextSibling;
			if (node != nullptr && node->tokenId == OWL2_ClassExpressionList)
			{
				node = node->firstChild;
			}
		}
	}
	
	void Owl2::parseDisjointClasses(ast_node* node, bool neg)
	{
		node = findChild(node, OWL2_ClassExpression);
		if (node == nullptr)
		{
			throw parser_exception("OWL2 Parser Error: a DisjointClasses Node requires a ClassExpression.");
		}
		
		while (node != nullptr)
		{
			ast_node* dcNode = node->nextSibling;
			while (dcNode != nullptr)
			{
				if (dcNode->tokenId == OWL2_ClassExpressionList)
				{
					dcNode = dcNode->firstChild;
					if (dcNode == nullptr)
					{
						break;
					}
				}
				parseInclusion(node, dcNode, neg, !neg);
				dcNode = dcNode->nextSibling;
			}
			node = node->nextSibling;
			if (node != nullptr && node->tokenId == OWL2_ClassExpressionList)
			{
				node = node->firstChild;
			}
		}
	}
	
	// DisjointUnion(C C1..Cn) is the same as:
	// EquivalentClasses(C ObjectUnionOf(C1..Cn)) followed by
	// DisjointClasses(C1..Cn)
	void Owl2::parseDisjointUnion(ast_node* node, bool neg)
	{
		ast_node classExpr;
		node = findChild(node, OWL2_Class);
		if (node == nullptr)
		{
			throw parser_exception("OWL2 Parser Error: a DisjointUnion Node requires a ClassExpression.");
		}
		classExpr.tokenId = OWL2_ClassExpression;
		classExpr.firstChild = node;
		unionNode->firstChild->firstChild->nextSibling->nextSibling = node->nextSibling->firstChild;
		// Simulate EquivalentClasses(C ObjectUnionOf(C1..Cn))
		parseInclusion(&classExpr, unionNode, neg, neg);
		parseInclusion(unionNode, &classExpr, neg, neg);
		// Call DisjointClasses for (C1..Cn)
		classExpr.tokenId = OWL2_DisjointClasses;
		classExpr.firstChild = node->nextSibling->firstChild;
		parseDisjointClasses(&classExpr, neg);
		unionNode->firstChild->firstChild->nextSibling->nextSibling = nullptr;
	}
	
	/**
	 * Adds an inclusion to the ontology. Both params need to be ClassExpressions.
	 * \param nodeSub the subclass expression
	 * \param nodeSuper the superclass expression
	 */
	void Owl2::parseInclusion(ast_node* nodeSub, ast_node* nodeSuper, bool negNodeSub, bool negNodeSuper)
	{
		Clause* clause = nullptr;
		try
		{
			clause = new Clause();
			parseClassExpression(nodeSub, !negNodeSub, clause, 0);
			parseClassExpression(nodeSuper, negNodeSuper, clause, 0);
			clauseSet->add(clause);
		}
		catch (parser_exception ex)
		{
			if (clause != nullptr)
			{
				delete clause;
			}
		}
	}
	
	/**
	 * \brief 
	 * \param node
	 * \param neg
	 * \param clause
	 */
	void Owl2::parseClassExpression(ast_node* node, bool neg, Clause* clause, unsigned int var)
	{
		node = node->firstChild;
		switch (node->tokenId)
		{
			case OWL2_Class:
				parseClass(node, neg, clause, var);
				break;
			case OWL2_ObjectIntersectionOf:
				if (neg)
				{
					parseDisjunction(findChild(node, OWL2_ClassExpression), true, clause, var);
				}
				else
				{
					parseConjunction(findChild(node, OWL2_ClassExpression), false, clause, var);
				}
				break;
			case OWL2_ObjectUnionOf:
				if (neg)
				{
					parseConjunction(findChild(node, OWL2_ClassExpression), true, clause, var);
				}
				else
				{
					parseDisjunction(findChild(node, OWL2_ClassExpression), false, clause, var);
				}
				break;
			case OWL2_ObjectComplementOf:
				parseClassExpression(findChild(node, OWL2_ClassExpression), !neg, clause, var);
				break;
			case OWL2_ObjectOneOf:
				throw unsupported_feature_exception(
					"The ObjectOneOf construct ins't supported by the reasoner.",
					"ObjectOneOf");
				break;
			case OWL2_ObjectSomeValuesFrom:
				if (neg)
				{
					parseUniversalQuantifier(findChild(node, OWL2_ObjectPropertyExpression), findChild(node, OWL2_ClassExpression), true, true, clause, var);
				}
				else
				{
					parseExistentialQuantifier(findChild(node, OWL2_ObjectPropertyExpression), findChild(node, OWL2_ClassExpression), false, false, clause, var);
				}
				break;
			case OWL2_ObjectAllValuesFrom:
				if (neg)
				{
					parseExistentialQuantifier(findChild(node, OWL2_ObjectPropertyExpression), findChild(node, OWL2_ClassExpression), false, true, clause, var);
				}
				else
				{
					parseUniversalQuantifier(findChild(node, OWL2_ObjectPropertyExpression), findChild(node, OWL2_ClassExpression), true, false, clause, var);
				}
				break;
			case OWL2_ObjectHasValue:
				throw unsupported_feature_exception(
					"The ObjectHasValue construct isn't supported by the reasoner.",
					"ObjectHasValue");
			case OWL2_ObjectHasSelf:
				throw unsupported_feature_exception(
					"The ObjectHasSelf construct isn't supported by the reasoner.",
					"ObjectHasSelf");
			case OWL2_ObjectMinCardinality:
				throw unsupported_feature_exception(
					"The ObjectMinCardinality construct isn't supported by the reasoner.",
					"ObjectMinCardinality");
			case OWL2_ObjectMaxCardinality:
				throw unsupported_feature_exception(
					"The ObjectMaxCardinality construct isn't supported by the reasoner.",
					"ObjectMaxCardinality");
			case OWL2_ObjectExactCardinality:
				throw unsupported_feature_exception(
					"The ObjectExactCardinality construct isn't supported by the reasoner.",
					"ObjectExactCardinality");
			case OWL2_DataSomeValuesFrom:
				throw unsupported_feature_exception(
					"The DataSomeValuesFrom construct isn't supported by the reasoner.",
					"DataSomeValuesFrom");
			case OWL2_DataAllValuesFrom:
				throw unsupported_feature_exception(
					"The DataAllValuesFrom construct isn't supported by the reasoner.",
					"DataAllValuesFrom");
			case OWL2_DataHasValue:
				throw unsupported_feature_exception(
					"The DataHasValue construct isn't supported by the reasoner.",
					"DataHasValue");
			case OWL2_DataMinCardinality:
				throw unsupported_feature_exception(
					"The DataMinCardinality construct isn't supported by the reasoner.",
					"DataMinCardinality");
			case OWL2_DataMaxCardinality:
				throw unsupported_feature_exception(
					"The DataMaxCardinality construct isn't supported by the reasoner.",
					"DataMaxCardinality");
			case OWL2_DataExactCardinality:
				throw unsupported_feature_exception(
					"The DataExactCardinality construct isn't supported by the reasoner.",
					"DataExactCardinality");				
		}
	}
	
	void Owl2::parseClass(ast_node* node, bool neg, Clause* clause, unsigned int var)
	{
		clause->add(
			new ConceptRealization(
				ontology->assertConcept(node->firstChild->firstChild->data),
				var,
				neg
			)
		);
	}
	
	void Owl2::parseConjunction(ast_node* node, bool neg, Clause* clause, unsigned int var)
	{
		while (node != nullptr && node->tokenId == OWL2_ClassExpression)
		{
			parseClassExpression(node, neg, clause, var);
			node = node->nextSibling;
			if (node != nullptr && node->tokenId == OWL2_ClassExpressionList)
			{
				node = node->firstChild;
			}
		}
	}	
	
	void Owl2::parseDisjunction(ast_node* node, bool neg, Clause* clause, unsigned int var) 
	{
		Literal& lit = ontology->newConcept();
		clause->add(new ConceptRealization(lit, var, false));
		while (node != nullptr && node->tokenId == OWL2_ClassExpression)
		{
			Clause* c = new Clause();
			c->add(new ConceptRealization(lit, var, true));
			parseClassExpression(node, neg, c, 0);
			clauseSet->add(c);
			node = node->nextSibling;
			if (node != nullptr && node->tokenId == OWL2_ClassExpressionList)
			{
				node = node->firstChild;
			}
		}
	}
	
	void Owl2::parseUniversalQuantifier(ast_node* roleNode, ast_node* conceptNode, bool negRole, bool negConcept, Clause* clause, unsigned int var)
	{
		Literal* roleLit = nullptr;
		roleNode = roleNode->firstChild;
		switch (roleNode->tokenId)
		{
			case OWL2_ObjectProperty:
				roleLit = &ontology->assertRole(roleNode->firstChild->firstChild->data);
				break;
			case OWL2_InverseObjectProperty: // inverse as in inverse function
				throw unsupported_feature_exception(
					"OWL2 Parser Error: The parser doesn't support the InverseObjectProperty.",
					"InverseObjectProperty");
			default:
				throw parser_exception("OWL2 Parser Error: Expected ObjectProperty or InverseObjectProperty on Quantifier.");
		}
		// If the Quantifier's class is not a simple class, create a new class to represent it, else just add it
		if (conceptNode->firstChild->tokenId != OWL2_Class)
		{
			Clause* c = new Clause();
			Literal& newConcept = ontology->newConcept();
			clause->add(new UniversalRealization(*roleLit, var, 0, negRole, newConcept, negConcept));
			clause->values[clause->varCount()-1] = &ontology->newUniqueInstance();
			c->add(new ConceptRealization(newConcept, 0, !negConcept));
			// this new clause can't be used to start the reasoning
			c->start = false;
			parseClassExpression(conceptNode, negConcept, c, 0);
			clauseSet->add(c);
		}
		else
		{
			Literal& concept = ontology->assertConcept(conceptNode->firstChild->firstChild->firstChild->data);
			clause->add(new UniversalRealization(*roleLit, var, 0, negRole, concept, negConcept));						// variable 2 id is set withihn clause->add
			clause->values[clause->varCount()-1] = &ontology->newUniqueInstance();
		}
	}
	
	void Owl2::parseExistentialQuantifier(ast_node* roleNode, ast_node* conceptNode, bool negRole, bool negConcept, Clause* clause, unsigned int var)
	{
		Literal* roleLit = nullptr;
		roleNode = roleNode->firstChild;
		switch (roleNode->tokenId)
		{
			case OWL2_ObjectProperty:
				roleLit = &ontology->assertRole(roleNode->firstChild->firstChild->data);
				break;
			case OWL2_InverseObjectProperty: // inverse as in inverse function
				throw unsupported_feature_exception(
					"OWL2 Parser Error: The parser doesn't support the InverseObjectProperty yet.",
					"InverseObjectProperty");
				break;
			default:
				throw parser_exception("OWL2 Parser Error: Expected ObjectProperty or InverseObjectProperty on Quantifier.");
		}
		// If the Quantifier's class is not a simple class, create a new class to represent it, else just add it
		if (conceptNode->firstChild->tokenId != OWL2_Class)
		{
			Clause* c = new Clause();
			Literal& newConcept = ontology->newConcept();
            clause->add(new ExistentialRealization(*roleLit, var, 0, negRole, newConcept, negConcept));
            c->add(new ConceptRealization(newConcept, 0, true));
			c->start = false;
			parseClassExpression(conceptNode, negConcept, c, 0);
			clauseSet->add(c);
		}
		else
		{
			Literal& concept = ontology->assertConcept(conceptNode->firstChild->firstChild->firstChild->data);
			clause->add(new ExistentialRealization(*roleLit, var, 0, negRole, concept, negConcept));
		}
	}
	
	void Owl2::parseObjectPropertyAxiom(ast_node* node)
	{
		node = node->firstChild;
		switch (node->tokenId)
		{
			case OWL2_SubObjectPropertyOf:
				throw unsupported_feature_exception(
					"OWL2 Parser Error: The reasoner doesn't support SubObjectPropertyOf",
					"SubObjectPropertyOf");
			case OWL2_EquivalentObjectProperties:
				throw unsupported_feature_exception(
					"OWL2 Parser Error: The reasoner doesn't support EquivalentObjectProperties",
					"EquivalentObjectProperties");
			case OWL2_DisjointObjectProperties:
				throw unsupported_feature_exception(
					"OWL2 Parser Error: The reasoner doesn't support DisjointObjectProperties",
					"DisjointObjectProperties");
			case OWL2_InverseObjectProperties:
				throw unsupported_feature_exception(
					"OWL2 Parser Error: The reasoner doesn't support InverseObjectProperties",
					"InverseObjectProperties");
			case OWL2_ObjectPropertyDomain:
				throw unsupported_feature_exception(
					"OWL2 Parser Error: The reasoner doesn't support ObjectPropertyDomain",
					"ObjectPropertyDomain");
			case OWL2_ObjectPropertyRange:
				throw unsupported_feature_exception(
					"OWL2 Parser Error: The reasoner doesn't support ObjectPropertyRange",
					"ObjectPropertyRange");
			case OWL2_FunctionalObjectProperty:
				throw unsupported_feature_exception(
					"OWL2 Parser Error: The reasoner doesn't support FunctionalObjectProperty",
					"FunctionalObjectProperty");
			case OWL2_InverseFunctionalObjectProperty:
				throw unsupported_feature_exception(
					"OWL2 Parser Error: The reasoner doesn't support InverseFunctionalObjectProperty",
					"InverseFunctionalObjectProperty");
			case OWL2_ReflexiveObjectProperty:
				throw unsupported_feature_exception(
					"OWL2 Parser Error: The reasoner doesn't support ReflexiveObjectProperty",
					"ReflexiveObjectProperty");
			case OWL2_IrreflexiveObjectProperty:
				throw unsupported_feature_exception(
					"OWL2 Parser Error: The reasoner doesn't support IrreflexiveObjectProperty",
					"IrreflexiveObjectProperty");
			case OWL2_SymmetricObjectProperty:
				throw unsupported_feature_exception(
					"OWL2 Parser Error: The reasoner doesn't support SymmetricObjectProperty",
					"SymmetricObjectProperty");
			case OWL2_AsymmetricObjectProperty:
				throw unsupported_feature_exception(
					"OWL2 Parser Error: The reasoner doesn't support AsymmetricObjectProperty",
					"AsymmetricObjectProperty");
			case OWL2_TransitiveObjectProperty:
				throw unsupported_feature_exception(
					"OWL2 Parser Error: The reasoner doesn't support TransitiveObjectProperty",
					"TransitiveObjectProperty");
		}
		
	}
	
	void Owl2::parseAssertion(ast_node* node, bool neg)
	{
		node = node->firstChild;
		switch (node->tokenId)
		{
			case OWL2_SameIndividual:
				throw unsupported_feature_exception(
					"OWL2 Parser Error: The reasoner doesn't support SameIndividual Assertions",
					"SameIndividual");
			case OWL2_DifferentIndividuals:
				throw unsupported_feature_exception(
					"OWL2 Parser Error: The reasoner doesn't support DifferentIndividuals Assertions",
					"DifferentIndividuals");
			case OWL2_ClassAssertion:
				parseClassAssertion(findChild(node, OWL2_ClassExpression), findChild(node, OWL2_Individual), neg);
				break;
			case OWL2_ObjectPropertyAssertion:
				parseObjectPropertyAssertion(findChild(node, OWL2_ObjectPropertyExpression), findChild(node, OWL2_sourceIndividual), findChild(node, OWL2_targetIndividual), neg);
				break;
			case OWL2_NegativeObjectPropertyAssertion:
				parseObjectPropertyAssertion(findChild(node, OWL2_ObjectPropertyExpression), findChild(node, OWL2_sourceIndividual), findChild(node, OWL2_targetIndividual), !neg);
				break;
			case OWL2_DataPropertyAssertion:
				throw unsupported_feature_exception(
					"OWL2 Parser Error: The reasoner doesn't support DataPropertyAssertion",
					"DataPropertyAssertion");
			case OWL2_NegativeDataPropertyAssertion:
				throw unsupported_feature_exception(
					"OWL2 Parser Error: The reasoner doesn't support NegativeDataPropertyAssertion",
					"NegativeDataPropertyAssertion");
		}
	}
	
	void Owl2::parseClassAssertion(ast_node* classNode, ast_node* indiv, bool neg)
	{
		Clause* clause = new Clause();
		parseClassExpression(classNode, neg, clause, 0);
		if (clause->values.size() <= 0)
		{
			clause->values.push_back(getIndividualInstance(indiv));
		}
		else
		{
			clause->values[0] = getIndividualInstance(indiv);
		}
		clauseSet->add(clause);
	}
	
	void Owl2::parseObjectPropertyAssertion(ast_node* roleNode, ast_node* source, ast_node* target, bool neg)
	{
		Literal* lit = nullptr;
		Clause* clause = new Clause();
		roleNode = roleNode->firstChild;
		switch (roleNode->tokenId)
		{
			case OWL2_ObjectProperty:
				lit = &ontology->assertRole(roleNode->firstChild->firstChild->data);
				clause->add(new RoleRealization(*lit, 0, 1, neg), true);
				break;
			case OWL2_InverseObjectProperty:
				throw unsupported_feature_exception(
					"OWL2 Parser Error: The parser doesn't support the InverseObjectProperty.",
					"InverseObjectProperty");
				break;
			default:
				throw parser_exception("OWL2 Parser Error: Expected ObjectProperty or InverseObjectProperty on Quantifier.");
		}
		if (clause->values.size() <= 0)
		{
			clause->values.push_back(getIndividualInstance(source->firstChild));
		}
		else
		{
			clause->values[0] = getIndividualInstance(source->firstChild);
		}
		if (clause->values.size() <= 1)
		{
			clause->values.push_back(getIndividualInstance(target->firstChild));
		}
		else
		{
			clause->values[1] = getIndividualInstance(target->firstChild);
		}
			
		clauseSet->add(clause);
	}
	
	Instance* Owl2::getIndividualInstance(ast_node* individual)
	{
		individual = individual->firstChild;
		switch (individual->tokenId)
		{
			case OWL2_NamedIndividual:
				return &ontology->assertInstance(individual->firstChild->firstChild->data);
			case OWL2_AnonymousIndividual:
				return &ontology->assertInstance(individual->firstChild->data);
		}
		return nullptr;
	}
	
	ast_node* Owl2::findSibling(ast_node* node, int tokenId)
	{
		while (node != nullptr)
		{
			if (node->tokenId == tokenId)
			{
				return node;
			}
			node = node->nextSibling;
		}
		return nullptr;
	}
	
	ast_node* Owl2::findChild(ast_node* node, int tokenId)
	{
		if (node == nullptr)
		{
			return nullptr;
		}
		node = node->firstChild;
		return findSibling(node, tokenId);
	}
	
	void Owl2::printUnsupportedFeatures()
	{
		auto it = this->unsupportedFeatures.begin();
		if (it != this->unsupportedFeatures.end())
		{
			cout << *it;
			++it;
		}
		while (it != this->unsupportedFeatures.end())
		{
			cout << ',' << *it;
			++it;
		}
	}
		
}

