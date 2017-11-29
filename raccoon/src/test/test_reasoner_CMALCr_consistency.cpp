
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
	parse_result* pr = OWL2_parse_file("../../test/consistency/test_acyclic_inconsistency001.owl");
	CHECK(pr != NULL);
	owl2.parse(pr, &ontology, &ontology.clauseSet, true);
	CMALCrp reasoner(&ontology.clauseSet, true);
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
	parse_result* pr = OWL2_parse_file("../../test/consistency/test_acyclic_tbox_inconsistency001.owl");
	CHECK(pr != NULL);
	owl2.parse(pr, &ontology, &ontology.clauseSet, true);
	CMALCrp reasoner(&ontology.clauseSet, true);
	CHECK(reasoner.consistency(&ontology) == false);
	parse_result_free(pr);
}

/**
 * \brief Test Acyclic TBox Inconsistency 2.
 */
TEST(ReasonerCMALCrp_AcyclicTBoxInconsistency002)
{
	Owl2 owl2;
	Ontology ontology;
	parse_result* pr = OWL2_parse_file("../../test/consistency/test_acyclic_tbox_inconsistency002.owl");
	CHECK(pr != NULL);
	owl2.parse(pr, &ontology, &ontology.clauseSet, true);
	CMALCrp reasoner(&ontology.clauseSet, true);
	CHECK(reasoner.consistency(&ontology) == false);
	parse_result_free(pr);
}

/**
 * \brief Test Acyclic TBox Inconsistency 3. Contributed by *Diogo Espinhara*.
 * \description This case caused false consistency problems on versions between 0.1.3 and 0.1.5 
 * (inclusive) it was caused by a premature blocking of connections containing skolem functions.
 */
TEST(ReasonerCMALCrp_AcyclicTBoxInconsistency003)
{
	Owl2 owl2;
	Ontology ontology;
	parse_result* pr = OWL2_parse_file("../../test/consistency/test_acyclic_tbox_inconsistency003.owl");
	CHECK(pr != NULL);
	owl2.parse(pr, &ontology, &ontology.clauseSet, true);
	CMALCrp reasoner(&ontology.clauseSet, true);
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
	parse_result* pr = OWL2_parse_file("../../test/consistency/test_acyclic_tbox_abox_inconsistency.owl");
	CHECK(pr != NULL);
	owl2.parse(pr, &ontology, &ontology.clauseSet, true);
	CMALCrp reasoner(&ontology.clauseSet, true);
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
	parse_result* pr = OWL2_parse_file("../../test/consistency/test_cyclic_inconsistency001.owl");
	CHECK(pr != NULL);
	owl2.parse(pr, &ontology, &ontology.clauseSet, true);
	CMALCrp reasoner(&ontology.clauseSet, true);
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
	parse_result* pr = OWL2_parse_file("../../test/consistency/test_cyclic_inconsistency002.owl");
	CHECK(pr != NULL);
	owl2.parse(pr, &ontology, &ontology.clauseSet, true);
	CMALCrp reasoner(&ontology.clauseSet, true);
	CHECK(reasoner.consistency(&ontology) == false);
	parse_result_free(pr);
}

/**
 * \brief Test Cyclic Inconsistency.
 */
TEST(ReasonerCMALCrp_CyclicInconsistency003)
{
	Owl2 owl2;
	Ontology ontology;
	parse_result* pr = OWL2_parse_file("../../test/consistency/test_cyclic_inconsistency003.owl");
	CHECK(pr != NULL);
	owl2.parse(pr, &ontology, &ontology.clauseSet, true);
	CMALCrp reasoner(&ontology.clauseSet, true);
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
	parse_result* pr = OWL2_parse_file("../../test/consistency/test_cyclic_consistency001.owl");
	CHECK(pr != NULL);
	owl2.parse(pr, &ontology, &ontology.clauseSet, true);
	CMALCrp reasoner(&ontology.clauseSet, true);
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
	parse_result* pr = OWL2_parse_file("../../test/consistency/test_cyclic_consistency002.owl");
	CHECK(pr != NULL);
	owl2.parse(pr, &ontology, &ontology.clauseSet, true);
	CMALCrp reasoner(&ontology.clauseSet, true);
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
	parse_result* pr = OWL2_parse_file("../../test/consistency/test_cyclic_consistency003.owl");
	CHECK(pr != NULL);
	owl2.parse(pr, &ontology, &ontology.clauseSet, true);
	CMALCrp reasoner(&ontology.clauseSet, true);
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
	parse_result* pr = OWL2_parse_file("../../test/consistency/test_cyclic_consistency004.owl");
	CHECK(pr != NULL);
	owl2.parse(pr, &ontology, &ontology.clauseSet, true);
	CMALCrp reasoner(&ontology.clauseSet, true);
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
	parse_result* pr = OWL2_parse_file("../../test/consistency/test_cyclic_consistency005_slow.owl");
	CHECK(pr != NULL);
	owl2.parse(pr, &ontology, &ontology.clauseSet, true);
	CMALCrp reasoner(&ontology.clauseSet, true);
	CHECK(reasoner.consistency(&ontology) == true);
	parse_result_free(pr);
}

/**
 * \brief Test Cyclic Consistency.
 */
TEST(ReasonerCMALCrp_CyclicConsistency006_Slow)
{
	Owl2 owl2;
	Ontology ontology;
	parse_result* pr = OWL2_parse_file("../../test/consistency/test_cyclic_consistency006_slow.owl");
	CHECK(pr != NULL);
	owl2.parse(pr, &ontology, &ontology.clauseSet, true);
	CMALCrp reasoner(&ontology.clauseSet, true);
	CHECK(reasoner.consistency(&ontology) == true);
	parse_result_free(pr);
}

/**
 * \brief Test Cyclic Consistency. Contributed by Ivan Varzinczak.
 */
TEST(ReasonerCMALCrp_CyclicConsistency007)
{
	Owl2 owl2;
	Ontology ontology;
	parse_result* pr = OWL2_parse_file("../../test/consistency/test_cyclic_consistency007.owl");
	CHECK(pr != NULL);
	owl2.parse(pr, &ontology, &ontology.clauseSet, true);
	CMALCrp reasoner(&ontology.clauseSet, true);
	CHECK(reasoner.consistency(&ontology) == true);
	parse_result_free(pr);
}

/**
 * \brief Test Cyclic Consistency. Contributed by Diogo Espinhara.
 */
TEST(ReasonerCMALCrp_CyclicConsistency008)
{
	Owl2 owl2;
	Ontology ontology;
	parse_result* pr = OWL2_parse_file("../../test/consistency/test_cyclic_consistency008.owl");
	CHECK(pr != NULL);
	owl2.parse(pr, &ontology, &ontology.clauseSet, true);
	CMALCrp reasoner(&ontology.clauseSet, true);
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
	parse_result* pr = OWL2_parse_file("../../test/consistency/test_cyclic_pure.owl");
	CHECK(pr != NULL);
	owl2.parse(pr, &ontology, &ontology.clauseSet, true);
	CMALCrp reasoner(&ontology.clauseSet, true);
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
	parse_result* pr = OWL2_parse_file("../../test/consistency/test_skolem_consistency.owl");
	CHECK(pr != NULL);
	owl2.parse(pr, &ontology, &ontology.clauseSet, true);
	CMALCrp reasoner(&ontology.clauseSet, true);
	CHECK(reasoner.consistency(&ontology) == true);
	parse_result_free(pr);
}

/**
 * \brief Test Skolem Inconsistency.
 */
TEST(ReasonerCMALCrp_SkolemInconsistency)
{
	Owl2 owl2;
	Ontology ontology;
	parse_result* pr = OWL2_parse_file("../../test/consistency/test_skolem_inconsistency.owl");
	CHECK(pr != NULL);
	owl2.parse(pr, &ontology, &ontology.clauseSet, true);
	CMALCrp reasoner(&ontology.clauseSet, true);
	CHECK(reasoner.consistency(&ontology) == false);
	parse_result_free(pr);
}

/**
 * \brief Test owl:Thing Consistency.
 */
TEST(ReasonerCMALCrp_ThingConsistency)
{
	Owl2 owl2;
	Ontology ontology;
	parse_result* pr = OWL2_parse_file("../../test/consistency/test_thing_consistency.owl");
	CHECK(pr != NULL);
	owl2.parse(pr, &ontology, &ontology.clauseSet, true);
	CMALCrp reasoner(&ontology.clauseSet, true);
	CHECK(reasoner.consistency(&ontology) == true);
	parse_result_free(pr);
}

/**
 * \brief Test owl:Thing Inconsistency.
 */
TEST(ReasonerCMALCrp_ThingInconsistency)
{
	Owl2 owl2;
	Ontology ontology;
	parse_result* pr = OWL2_parse_file("../../test/consistency/test_thing_inconsistency.owl");
	CHECK(pr != NULL);
	owl2.parse(pr, &ontology, &ontology.clauseSet, true);
	CMALCrp reasoner(&ontology.clauseSet, true);
	CHECK(reasoner.consistency(&ontology) == false);
	parse_result_free(pr);
}

/**
 * \brief Test owl:Nothing Consistency.
 */
TEST(ReasonerCMALCrp_NothingConsistency)
{
	Owl2 owl2;
	Ontology ontology;
	parse_result* pr = OWL2_parse_file("../../test/consistency/test_nothing_consistency.owl");
	CHECK(pr != NULL);
	owl2.parse(pr, &ontology, &ontology.clauseSet, true);
	CMALCrp reasoner(&ontology.clauseSet, true);
	CHECK(reasoner.consistency(&ontology) == true);
	parse_result_free(pr);
}

/**
 * \brief Test owl:Nothing Inconsistency.
 */
TEST(ReasonerCMALCrp_NothingInconsistency)
{
	Owl2 owl2;
	Ontology ontology;
	parse_result* pr = OWL2_parse_file("../../test/consistency/test_nothing_inconsistency.owl");
	CHECK(pr != NULL);
	owl2.parse(pr, &ontology, &ontology.clauseSet, true);
	CMALCrp reasoner(&ontology.clauseSet, true);
	CHECK(reasoner.consistency(&ontology) == false);
	parse_result_free(pr);
}

/**
 * \brief Test Path Instantiation.
 */
TEST(ReasonerCMALCrp_PathInstantiation)
{
	Owl2 owl2;
	Ontology ontology;
	parse_result* pr = OWL2_parse_file("../../test/consistency/test_path_instantiation.owl");
	CHECK(pr != NULL);
	owl2.parse(pr, &ontology, &ontology.clauseSet, true);
	CMALCrp reasoner(&ontology.clauseSet, true);
	CHECK(reasoner.consistency(&ontology) == true);
	parse_result_free(pr);
}

// TODO: More unit tests