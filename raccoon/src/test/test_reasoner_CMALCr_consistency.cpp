
// STL
#include <string>
#include <string.h>
// UnitTest++
#include <unittest++/UnitTest++.h>
// raccoon
extern "C" {
#include "../parsers/owl2/owl2_parser.h"
}
#include "../parsers/owl2/Owl2.h"
#include "../ir/Ontology.h"
#include "../ir/ClauseSet.h"
#include "../back/CMALCr.h"

using namespace std;

/**
 * \brief Test Acyclic TBox Inconsistency.
 */
TEST(ReasonerCMALCr_AcyclicTBoxInconsistency)
{
	string strOntology(
		"Prefix(owl:=<http://www.w3.org/2002/07/owl#>)\n"
		"Prefix(:=<http://cin.ufpe.br/~dldmf/raccoon/test_acyclic_tbox_inconsistency.owl>)\n"
		"Ontology(<http://cin.ufpe.br/~dldmf/raccoon/test_acyclic_tbox_inconsistency.owl>\n"
		" EquivalentClasses(:a :d)\n"
		" EquivalentClasses(:b :e)\n"
		" SubClassOf(:a ObjectComplementOf(:b))\n"
		" SubClassOf(:c :d)\n"
		" SubClassOf(ObjectComplementOf(:a) :c)\n"
		" SubClassOf(:c :b)\n"
		" SubClassOf(ObjectComplementOf(:e) :c)\n"
		")\n"
	);
	Owl2 owl2;
	Ontology ontology;
	ClauseSet clauseSet;
	parse_result* pr = OWL2_parse_string((char*)strOntology.c_str());
	owl2.parse(pr, &ontology, &clauseSet, true);
	CMALCr reasoner(&clauseSet);
	CHECK(reasoner.consistency(&ontology) == false);
}

/**
 * \brief Test Acyclic TBox + ABox Inconsistency.
 */
TEST(ReasonerCMALCr_AcyclicTBoxAboxInconsistency)
{
	string strOntology(
		"Prefix(owl:=<http://www.w3.org/2002/07/owl#>)\n"
		"Prefix(:=<http://cin.ufpe.br/~dldmf/raccoon/test_acyclic_tbox_abox_inconsistency.owl>)\n"
		"Ontology(<http://cin.ufpe.br/~dldmf/raccoon/test_acyclic_tbox_abox_inconsistency.owl>\n"
		" SubClassOf(:A :B)\n"
		" ClassAssertion(:A :z)\n"
		" ClassAssertion(ObjectComplementOf(:B) :z)\n"
		")\n"
	);
	Owl2 owl2;
	Ontology ontology;
	ClauseSet clauseSet;
	parse_result* pr = OWL2_parse_string((char*)strOntology.c_str());
	owl2.parse(pr, &ontology, &clauseSet, true);
	CMALCr reasoner(&clauseSet);
	CHECK(reasoner.consistency(&ontology) == false);
}

// TODO: More unit tests