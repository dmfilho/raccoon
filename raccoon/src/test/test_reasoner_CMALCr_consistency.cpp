
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
#include "../back/CMALCrp.h"

using namespace std;
using namespace raccoon;

/**
 * \brief Test Acyclic TBox Inconsistency.
 */
TEST(ReasonerCMALCrp_AcyclicInconsistency001)
{
	Owl2 owl2;
	Ontology ontology;
	ClauseSet clauseSet;
	parse_result* pr = OWL2_parse_file("../../test/consistency/test_acyclic_inconsistency001.owl");
	CHECK(pr != NULL);
	owl2.parse(pr, &ontology, &clauseSet, true);
	CMALCrp reasoner(&clauseSet);
	CHECK(reasoner.consistency(&ontology) == false);
	parse_result_free(pr);
}

/**
 * \brief Test Acyclic TBox Inconsistency.
 */
TEST(ReasonerCMALCrp_AcyclicTBoxInconsistency001)
{
	Owl2 owl2;
	Ontology ontology;
	ClauseSet clauseSet;
	parse_result* pr = OWL2_parse_file("../../test/consistency/test_acyclic_tbox_inconsistency001.owl");
	CHECK(pr != NULL);
	owl2.parse(pr, &ontology, &clauseSet, true);
	CMALCrp reasoner(&clauseSet);
	CHECK(reasoner.consistency(&ontology) == false);
	parse_result_free(pr);
}

/**
 * \brief Test Acyclic TBox Inconsistency.
 */
TEST(ReasonerCMALCrp_AcyclicTBoxInconsistency002)
{
	Owl2 owl2;
	Ontology ontology;
	ClauseSet clauseSet;
	parse_result* pr = OWL2_parse_file("../../test/consistency/test_acyclic_tbox_inconsistency002.owl");
	CHECK(pr != NULL);
	owl2.parse(pr, &ontology, &clauseSet, true);
	CMALCrp reasoner(&clauseSet);
	CHECK(reasoner.consistency(&ontology) == false);
	parse_result_free(pr);
}

/**
 * \brief Test Acyclic TBox + ABox Inconsistency.
 */
TEST(ReasonerCMALCrp_AcyclicTBoxAboxInconsistency)
{
	Owl2 owl2;
	Ontology ontology;
	ClauseSet clauseSet;
	parse_result* pr = OWL2_parse_file("../../test/consistency/test_acyclic_tbox_abox_inconsistency.owl");
	CHECK(pr != NULL);
	owl2.parse(pr, &ontology, &clauseSet, true);
	CMALCrp reasoner(&clauseSet);
	CHECK(reasoner.consistency(&ontology) == false);
	parse_result_free(pr);
}

/**
 * \brief Test Cyclic Inconsistency.
 */
TEST(ReasonerCMALCrp_CyclicInconsistency001)
{
	Owl2 owl2;
	Ontology ontology;
	ClauseSet clauseSet;
	parse_result* pr = OWL2_parse_file("../../test/consistency/test_cyclic_inconsistency001.owl");
	CHECK(pr != NULL);
	owl2.parse(pr, &ontology, &clauseSet, true);
	CMALCrp reasoner(&clauseSet);
	CHECK(reasoner.consistency(&ontology) == false);
	parse_result_free(pr);
}

/**
 * \brief Test Cyclic Inconsistency.
 */
TEST(ReasonerCMALCrp_CyclicInconsistency002)
{
	Owl2 owl2;
	Ontology ontology;
	ClauseSet clauseSet;
	parse_result* pr = OWL2_parse_file("../../test/consistency/test_cyclic_inconsistency002.owl");
	CHECK(pr != NULL);
	owl2.parse(pr, &ontology, &clauseSet, true);
	CMALCrp reasoner(&clauseSet);
	CHECK(reasoner.consistency(&ontology) == false);
	parse_result_free(pr);
}

/**
 * \brief Test Cyclic Consistency.
 */
TEST(ReasonerCMALCrp_CyclicConsistency001)
{
	Owl2 owl2;
	Ontology ontology;
	ClauseSet clauseSet;
	parse_result* pr = OWL2_parse_file("../../test/consistency/test_cyclic_consistency001.owl");
	CHECK(pr != NULL);
	owl2.parse(pr, &ontology, &clauseSet, true);
	CMALCrp reasoner(&clauseSet);
	CHECK(reasoner.consistency(&ontology) == true);
	parse_result_free(pr);
}

/**
 * \brief Test Cyclic Consistency.
 */
TEST(ReasonerCMALCrp_CyclicConsistency002)
{
	Owl2 owl2;
	Ontology ontology;
	ClauseSet clauseSet;
	parse_result* pr = OWL2_parse_file("../../test/consistency/test_cyclic_consistency002.owl");
	CHECK(pr != NULL);
	owl2.parse(pr, &ontology, &clauseSet, true);
	CMALCrp reasoner(&clauseSet);
	CHECK(reasoner.consistency(&ontology) == true);
	parse_result_free(pr);
}

/**
 * \brief Test Cyclic Consistency.
 */
TEST(ReasonerCMALCrp_CyclicConsistency003)
{
	Owl2 owl2;
	Ontology ontology;
	ClauseSet clauseSet;
	parse_result* pr = OWL2_parse_file("../../test/consistency/test_cyclic_consistency003.owl");
	CHECK(pr != NULL);
	owl2.parse(pr, &ontology, &clauseSet, true);
	CMALCrp reasoner(&clauseSet);
	CHECK(reasoner.consistency(&ontology) == true);
	parse_result_free(pr);
}

/**
 * \brief Test Cyclic Consistency.
 */
TEST(ReasonerCMALCrp_CyclicConsistency004)
{
	Owl2 owl2;
	Ontology ontology;
	ClauseSet clauseSet;
	parse_result* pr = OWL2_parse_file("../../test/consistency/test_cyclic_consistency004.owl");
	CHECK(pr != NULL);
	owl2.parse(pr, &ontology, &clauseSet, true);
	CMALCrp reasoner(&clauseSet);
	CHECK(reasoner.consistency(&ontology) == true);
	parse_result_free(pr);
}

/**
 * \brief Test Cyclic Consistency.
 */
TEST(ReasonerCMALCrp_CyclicConsistency005_Slow)
{
	Owl2 owl2;
	Ontology ontology;
	ClauseSet clauseSet;
	parse_result* pr = OWL2_parse_file("../../test/consistency/test_cyclic_consistency005_slow.owl");
	CHECK(pr != NULL);
	owl2.parse(pr, &ontology, &clauseSet, true);
	CMALCrp reasoner(&clauseSet);
	CHECK(reasoner.consistency(&ontology) == true);
	parse_result_free(pr);
}

/**
 * \brief Test Skolem Consistency.
 */
TEST(ReasonerCMALCrp_CyclicPure)
{
	Owl2 owl2;
	Ontology ontology;
	ClauseSet clauseSet;
	parse_result* pr = OWL2_parse_file("../../test/consistency/test_cyclic_pure.owl");
	CHECK(pr != NULL);
	owl2.parse(pr, &ontology, &clauseSet, true);
	CMALCrp reasoner(&clauseSet);
	CHECK(reasoner.consistency(&ontology) == true);
	parse_result_free(pr);
}

/**
 * \brief Test Skolem Consistency.
 */
TEST(ReasonerCMALCrp_SkolemConsistency)
{
	Owl2 owl2;
	Ontology ontology;
	ClauseSet clauseSet;
	parse_result* pr = OWL2_parse_file("../../test/consistency/test_skolem_consistency.owl");
	CHECK(pr != NULL);
	owl2.parse(pr, &ontology, &clauseSet, true);
	CMALCrp reasoner(&clauseSet);
	CHECK(reasoner.consistency(&ontology) == true);
	parse_result_free(pr);
}

// TODO: More unit tests