/*
 * owl.cpp
 *
 *  Created on: Apr 14, 2014
 *      Author: Dimas Melo Filho
 */

#include "owl.h"
#include "../Parser.h"
#include <axe.h>
#include "../axe_utf8.h"
#include <string>
#include "../../rep/KB.h"

using namespace std;

namespace front {


Owl::Owl():
	line(0)
{ }

Owl::~Owl() { }

void Owl::parse(string& text, rep::KB& kb) {
	using namespace axe;
	auto newline = r_char('\n') >> e_ref([&](...){ this->line++; });
	auto space = r_any(" \t\r") | newline;
	auto w = *space;
	auto quotedString = r_char('"') & *(r_str("\\\\") | r_str("\\\"") | (r_any() - '"')) & r_char('"');
	auto languageTag = r_char('@') & r_many((r_alnum() | r_char('-')),2);
	auto PN_CHARS_BASE = r_alpha() | r_any8(0x00C0,0x00D6) | r_any8(0x00D8,0x00F6) | r_any8(0x00F8,0x02FF) | r_any8(0x370,0x37D) | r_any8(0x37F,0x1FFF) | r_any8(0x200C,0x200D) | r_any8(0x2070,0x218F) | r_any8(0x2C00,0x2FEF) | r_any8(0x3001,0xD7FF) | r_any8(0xF900,0xFDCF) | r_any8(0xFDF0,0xFFFD) | r_any8(0x10000,0xEFFFF);
	auto PN_CHARS_U = r_char('_') | PN_CHARS_BASE;
	auto PN_CHARS = PN_CHARS_U | r_char('-') | r_num() | r_any8(0x00B7) | r_any8(0x0300,0x036F) | r_any8(0x203F,0x2040);
	auto PN_LOCAL = (PN_CHARS_U | r_num()) & ((*(PN_CHARS | r_char('.'))) & PN_CHARS);
	auto nodeID = r_str("_:") & PN_LOCAL;
	auto fullIRI = r_char('<') & *(r_any() - r_char('>')) & r_char('>');
	auto PN_PREFIX = PN_CHARS_BASE & ~(*(PN_CHARS | r_char('.')) & PN_CHARS);
	auto prefixName = ~PN_PREFIX & ':';
	auto PNAME_NS = prefixName;
	auto abbreviatedIRI = prefixName & PN_LOCAL;
	auto IRI = fullIRI | abbreviatedIRI;
	auto ontologyIRI = IRI;
	auto versionIRI = IRI;
	auto Annotation = r_str("Annotation") &w& r_char('(') & *(w&(quotedString | (r_any() - r_char(')')))) &w& r_char(')');
	auto directlyImportsDocuments = *(w&r_str("Import") &w& r_char('(') &w& IRI &w& r_char(')'));
	auto ontologyAnnotations = *(w&Annotation);
	/*auto Entity = (r_str("Class") &w& '(' &w& Class &w& ')') |
			(r_str("Datatype") &w& '(' &w& Datatype &w& ')') |
			(r_str("ObjectProperty") &w& '(' &w& ObjectProperty &w& ')') |
			(r_str("DataProperty") &w& '(' &w& DataProperty &w& ')') |
			(r_str("AnnotationProperty") &w& '(' &w& AnnotationProperty &w& ')') |
			(r_str("NamedIndividual") &w& '(' &w& NamedIndividual &w& ')');
	auto Declaration = w& r_str("Declaration") &w& r_char('(') &w& Annotation &w& Entity &w& ')';
	auto Axiom = Declaration | ClassAxiom | ObjectPropertyAxiom | DataPropertyAxiom | DatatypeDefinition | HasKey | Assertion | AnnotationAxiom;
	auto axioms = *(w&Axiom);
	auto prefixDeclaration = w& r_str("Prefix") &w& r_char('(') &w& prefixName &w& r_char('=') &w& fullIRI &w& r_char(')');
	auto Ontology = w& r_str("Ontology") &w& r_char('(') &w& ~(ontologyIRI &w& ~versionIRI) & directlyImportsDocuments & ontologyAnnotations & axioms &w& r_char(')');
	auto ontologyDocument = *prefixDeclaration & Ontology;
	*/
}

} /* namespace front */
