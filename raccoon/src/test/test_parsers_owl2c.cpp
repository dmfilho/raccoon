
// STL
#include <string>
// UnitTest++
#include <unittest++/UnitTest++.h>
// raccoon
#include "../parsers/owl2/Owl2.h"
#include "../ir/Ontology.h"
#include "../ir/ClauseSet.h"
#include "../ir/Clause.h"
#include "../parsers/owl2/owl2_parser.h"

using namespace std;
using namespace raccoon;

/**
 * \brief Returns true when a Clause has the specified concept
 * @param cs The Clause to search in
 * @param name The name of the concept we are looking for
 * @param neg Are we looking for a negated concept?
 * @param var What is the variable id of the concept?
 * @return True when the specified concept is found within the clauseset.
 */
bool hasConcept(Clause* clause, const char* name, bool neg, int var)
{
	for (auto concept: clause->concepts)
	{
		if (concept->concept._name == name &&
			concept->neg == neg &&
			concept->var == var)
		{
			return true;
		}
	}
	return false;
}

/**
 * \brief Returns true when a Clause has the specified role
 * @param cs The Clause to search in
 * @param name The name of the role we are looking for
 * @param neg Are we looking for a negated role?
 * @param var1 What is the first variable id of the role?
 * @param var2 What is the second variable id of the role?
 * @return True when the specified role is found within the clauseset.
 */
bool hasRole(Clause* clause, const char* name, bool neg, int var1, int var2)
{
	for (auto role: clause->roles)
	{
		if (role->role._name == name &&
			role->neg == neg &&
			role->var1 == var1 &&
			role->var2 == var2)
		{
			return true;
		}
	}
	return false;
}

/**
 * \brief Returns true when a Clause has the specified universal quantifier
 * @param cs The Clause to search in
 * @param roleName The name of the role we are looking for
 * @param conceptName The name of the concept we are looking for
 * @param roleNeg Are we looking for a negated role?
 * @param conceptNeg Are we looking for a negated concept?
 * @param var1 What is the first variable id of the universal quantifier
 * @param var2 What is the second variable id of the universal quantifier
 * @return True when the specified role is found within the clauseset.
 */
bool hasUniversal(Clause* clause, const char* roleName, const char* conceptName, bool roleNeg, bool conceptNeg, 
	int var1, int var2)
{
	for (auto universal: clause->universals)
	{
		if (universal->role.role._name == roleName &&
			universal->concept.concept._name == conceptName &&
			universal->role.neg == roleNeg &&
			universal->concept.neg == conceptNeg &&
			universal->role.var1 == var1 &&
			universal->role.var2 == var2 &&
			universal->concept.var == var2)
		{
			return true;
		}
	}
	return false;
}

/**
 * \brief Returns true when a Clause has the specified existential quantifier
 * @param cs The Clause to search in
 * @param roleName The name of the role we are looking for
 * @param conceptName The name of the concept we are looking for
 * @param roleNeg Are we looking for a negated role?
 * @param conceptNeg Are we looking for a negated concept?
 * @param var1 What is the first variable id of the existential quantifier
 * @param var2 What is the second variable id of the existential quantifier
 * @return True when the specified role is found within the clauseset.
 */
bool hasExistential(Clause* clause, const char* roleName, const char* conceptName, bool roleNeg, bool conceptNeg, 
	int var1, int var2)
{
	for (auto existential: clause->existentials)
	{
		if (existential->role.role._name == roleName &&
			existential->concept.concept._name == conceptName &&
			existential->role.neg == roleNeg &&
			existential->concept.neg == conceptNeg &&
			existential->role.var1 == var1 &&
			existential->role.var2 == var2 &&
			existential->concept.var == var2)
		{
			return true;
		}
	}
	return false;
}

/**
 * \brief Test the conversion of the SubClassOf
 */
TEST(Owl2Conv_SubClassOf)
{
	ClauseSet cs;
	Owl2 owl2;
	string strOntology(
		"Prefix(:=<http://www.w3.org/2002/07/owl#>)\n"
		"Prefix(t:=<http://cin.ufpe.br/~dldmf/raccoon/test_subclassof.owl>)\n"
		"Ontology(<http://cin.ufpe.br/~dldmf/raccoon/test_subclassof.owl>\n"
		" SubClassOf(t:Class1 t:Class2)\n"
		")"
	);
	Ontology ontology;
	
	parse_result* pr = OWL2_parse_string((char*)strOntology.c_str());
	CHECK(pr != NULL);
	if (pr == NULL) return;
	
	owl2.parse(pr, &ontology, &cs, true);
	CHECK(cs.clauses.size() == 1);
	CHECK(cs.clauses[0]->concepts.size() == 2);
	CHECK(cs.clauses[0]->concepts[0]->concept._name == "t:Class1");
	CHECK(cs.clauses[0]->concepts[1]->concept._name == "t:Class2");
	CHECK(cs.clauses[0]->concepts[0]->neg == false);
	CHECK(cs.clauses[0]->concepts[1]->neg == true);
	CHECK(cs.clauses[0]->concepts[0]->var == 0);
	CHECK(cs.clauses[0]->concepts[1]->var == 0);
	CHECK(ontology.concepts.at("t:Class1") == &cs.clauses[0]->concepts[0]->concept);
	CHECK(ontology.concepts.at("t:Class2") == &cs.clauses[0]->concepts[1]->concept);
	CHECK(ontology.conceptsById.at(cs.clauses[0]->concepts[0]->concept.id()) == &cs.clauses[0]->concepts[0]->concept);
	CHECK(ontology.conceptsById.at(cs.clauses[0]->concepts[1]->concept.id()) == &cs.clauses[0]->concepts[1]->concept);
	CHECK(ontology.conceptCount == 4); // because owl:Thing and owl:Nothing are always there
	CHECK(ontology.roleCount == 0);
	CHECK(ontology.instanceCount == 0);
}

/**
 * \brief Test the conversion of the EquivalentClasses
 */
TEST(Owl2Conv_EquivalentClasses)
{
	ClauseSet cs;
	Owl2 owl2;
	string strOntology(
		"Prefix(:=<http://www.w3.org/2002/07/owl#>)\n"
		"Prefix(t:=<http://cin.ufpe.br/~dldmf/raccoon/test_subclassof.owl>)\n"
		"Ontology(<http://cin.ufpe.br/~dldmf/raccoon/test_subclassof.owl>\n"
		" EquivalentClasses(t:Class1 t:Class2)\n"
		")"
	);
	Ontology ontology;
	
	parse_result* pr = OWL2_parse_string((char*)strOntology.c_str());
	CHECK(pr != NULL);
	if (pr == NULL) return;
	
	owl2.parse(pr, &ontology, &cs, true);
	CHECK(cs.clauses.size() == 2);
	CHECK(cs.clauses[0]->concepts.size() == 2);
	CHECK(cs.clauses[0]->concepts[0]->concept._name == "t:Class1");
	CHECK(cs.clauses[0]->concepts[1]->concept._name == "t:Class2");
	CHECK(cs.clauses[0]->concepts[0]->neg == false);
	CHECK(cs.clauses[0]->concepts[1]->neg == true);
	CHECK(cs.clauses[0]->concepts[0]->var == 0);
	CHECK(cs.clauses[0]->concepts[1]->var == 0);
	CHECK(cs.clauses[1]->concepts.size() == 2);
	CHECK(cs.clauses[1]->concepts[0]->concept._name == "t:Class2");
	CHECK(cs.clauses[1]->concepts[1]->concept._name == "t:Class1");
	CHECK(cs.clauses[1]->concepts[0]->neg == false);
	CHECK(cs.clauses[1]->concepts[1]->neg == true);
	CHECK(cs.clauses[1]->concepts[0]->var == 0);
	CHECK(cs.clauses[1]->concepts[1]->var == 0);
	CHECK(ontology.concepts.at("t:Class1") == &cs.clauses[0]->concepts[0]->concept);
	CHECK(ontology.concepts.at("t:Class2") == &cs.clauses[0]->concepts[1]->concept);
	CHECK(ontology.conceptsById.at(cs.clauses[0]->concepts[0]->concept.id()) == &cs.clauses[0]->concepts[0]->concept);
	CHECK(ontology.conceptsById.at(cs.clauses[0]->concepts[1]->concept.id()) == &cs.clauses[0]->concepts[1]->concept);
	CHECK(ontology.conceptCount == 4); // because owl:Thing and owl:Nothing are always there
	CHECK(ontology.roleCount == 0);
	CHECK(ontology.instanceCount == 0);
}

/**
 * \brief Test the conversion of the DisjointClasses
 */
TEST(Owl2Conv_DisjointClasses)
{
	ClauseSet cs;
	Owl2 owl2;
	string strOntology(
		"Prefix(:=<http://www.w3.org/2002/07/owl#>)\n"
		"Prefix(t:=<http://cin.ufpe.br/~dldmf/raccoon/test_subclassof.owl>)\n"
		"Ontology(<http://cin.ufpe.br/~dldmf/raccoon/test_subclassof.owl>\n"
		" DisjointClasses(t:Class1 t:Class2 t:Class3)\n"
		")"
	);
	Ontology ontology;
	
	parse_result* pr = OWL2_parse_string((char*)strOntology.c_str());
	CHECK(pr != NULL);
	if (pr == NULL) return;
	
	owl2.parse(pr, &ontology, &cs, true);
	CHECK(cs.clauses.size() == 3);
	CHECK(cs.clauses[0]->concepts.size() == 2);
	CHECK(cs.clauses[0]->concepts[0]->concept._name == "t:Class1");
	CHECK(cs.clauses[0]->concepts[1]->concept._name == "t:Class2");
	CHECK(cs.clauses[0]->concepts[0]->neg == false);
	CHECK(cs.clauses[0]->concepts[1]->neg == false);
	CHECK(cs.clauses[0]->concepts[0]->var == 0);
	CHECK(cs.clauses[0]->concepts[1]->var == 0);
	CHECK(cs.clauses[1]->concepts.size() == 2);
	CHECK(cs.clauses[1]->concepts[0]->concept._name == "t:Class1");
	CHECK(cs.clauses[1]->concepts[1]->concept._name == "t:Class3");
	CHECK(cs.clauses[1]->concepts[0]->neg == false);
	CHECK(cs.clauses[1]->concepts[1]->neg == false);
	CHECK(cs.clauses[1]->concepts[0]->var == 0);
	CHECK(cs.clauses[1]->concepts[1]->var == 0);
	CHECK(cs.clauses[2]->concepts.size() == 2);
	CHECK(cs.clauses[2]->concepts[0]->concept._name == "t:Class2");
	CHECK(cs.clauses[2]->concepts[1]->concept._name == "t:Class3");
	CHECK(cs.clauses[2]->concepts[0]->neg == false);
	CHECK(cs.clauses[2]->concepts[1]->neg == false);
	CHECK(cs.clauses[2]->concepts[0]->var == 0);
	CHECK(cs.clauses[2]->concepts[1]->var == 0);
	CHECK(ontology.concepts.at("t:Class1") == &cs.clauses[0]->concepts[0]->concept);
	CHECK(ontology.concepts.at("t:Class2") == &cs.clauses[0]->concepts[1]->concept);
	CHECK(ontology.concepts.at("t:Class3") == &cs.clauses[1]->concepts[1]->concept);
	CHECK(ontology.conceptsById.at(cs.clauses[0]->concepts[0]->concept.id()) == &cs.clauses[0]->concepts[0]->concept);
	CHECK(ontology.conceptsById.at(cs.clauses[0]->concepts[1]->concept.id()) == &cs.clauses[0]->concepts[1]->concept);
	CHECK(ontology.conceptsById.at(cs.clauses[1]->concepts[1]->concept.id()) == &cs.clauses[1]->concepts[1]->concept);
	CHECK(ontology.conceptCount == 5); // because owl:Thing and owl:Nothing are always there
	CHECK(ontology.roleCount == 0);
	CHECK(ontology.instanceCount == 0);
}

/**
 * \brief Test the conversion of the DisjointUnion
 */
TEST(Owl2Conv_DisjointUnion)
{
	ClauseSet cs;
	Owl2 owl2;
	string strOntology(
		"Prefix(:=<http://www.w3.org/2002/07/owl#>)\n"
		"Prefix(t:=<http://cin.ufpe.br/~dldmf/raccoon/test_subclassof.owl>)\n"
		"Ontology(<http://cin.ufpe.br/~dldmf/raccoon/test_subclassof.owl>\n"
		" DisjointUnion(t:Class1 t:Class2 t:Class3)\n"
		")"
	);
	Ontology ontology;
	
	parse_result* pr = OWL2_parse_string((char*)strOntology.c_str());
	CHECK(pr != NULL);
	if (pr == NULL) return;
	
	owl2.parse(pr, &ontology, &cs, true);
	
	CHECK(cs.clauses.size() == 5);
	CHECK(cs.clauses[0]->concepts.size() == 3);
	CHECK(cs.clauses[0]->concepts[0]->concept._name == "t:Class1");
	CHECK(cs.clauses[0]->concepts[1]->concept._name == "t:Class2");
	CHECK(cs.clauses[0]->concepts[2]->concept._name == "t:Class3");
	CHECK(cs.clauses[0]->concepts[0]->neg == false);
	CHECK(cs.clauses[0]->concepts[1]->neg == true);
	CHECK(cs.clauses[0]->concepts[2]->neg == true);
	CHECK(cs.clauses[0]->concepts[0]->var == 0);
	CHECK(cs.clauses[0]->concepts[1]->var == 0);
	CHECK(cs.clauses[0]->concepts[2]->var == 0);
	CHECK(cs.clauses[1]->concepts.size() == 2);
	CHECK(cs.clauses[1]->concepts[1]->concept._name == "t:Class2");
	CHECK(cs.clauses[1]->concepts[0]->neg == true);
	CHECK(cs.clauses[1]->concepts[1]->neg == false);
	CHECK(cs.clauses[1]->concepts[0]->var == 0);
	CHECK(cs.clauses[1]->concepts[1]->var == 0);
	CHECK(cs.clauses[2]->concepts.size() == 2);
	CHECK(cs.clauses[2]->concepts[1]->concept._name == "t:Class3");
	CHECK(cs.clauses[2]->concepts[0]->neg == true);
	CHECK(cs.clauses[2]->concepts[1]->neg == false);
	CHECK(cs.clauses[2]->concepts[0]->var == 0);
	CHECK(cs.clauses[2]->concepts[1]->var == 0);
	CHECK(cs.clauses[3]->concepts.size() == 2);
	CHECK(cs.clauses[3]->concepts[1]->concept._name == "t:Class1");
	CHECK(cs.clauses[3]->concepts[0]->neg == false);
	CHECK(cs.clauses[3]->concepts[1]->neg == true);
	CHECK(cs.clauses[3]->concepts[0]->var == 0);
	CHECK(cs.clauses[3]->concepts[1]->var == 0);
	CHECK(cs.clauses[4]->concepts.size() == 2);
	CHECK(cs.clauses[4]->concepts[0]->concept._name == "t:Class2");
	CHECK(cs.clauses[4]->concepts[1]->concept._name == "t:Class3");
	CHECK(cs.clauses[4]->concepts[0]->neg == false);
	CHECK(cs.clauses[4]->concepts[1]->neg == false);
	CHECK(cs.clauses[4]->concepts[0]->var == 0);
	CHECK(cs.clauses[4]->concepts[1]->var == 0);
	CHECK(ontology.concepts.at("t:Class1") == &cs.clauses[0]->concepts[0]->concept);
	CHECK(ontology.concepts.at("t:Class2") == &cs.clauses[0]->concepts[1]->concept);
	CHECK(ontology.concepts.at("t:Class3") == &cs.clauses[0]->concepts[2]->concept);
	CHECK(ontology.conceptsById.at(cs.clauses[0]->concepts[0]->concept.id()) == &cs.clauses[0]->concepts[0]->concept);
	CHECK(ontology.conceptsById.at(cs.clauses[0]->concepts[1]->concept.id()) == &cs.clauses[0]->concepts[1]->concept);
	CHECK(ontology.conceptsById.at(cs.clauses[0]->concepts[2]->concept.id()) == &cs.clauses[0]->concepts[2]->concept);
	CHECK(ontology.conceptCount == 6); // includes a concept that is created in the normalization process, plus Thing and Nothing
	CHECK(ontology.roleCount == 0);
	CHECK(ontology.instanceCount == 0);
}

/**
 * \brief Test the conversion of the ObjectIntersectionOf
 */
TEST(Owl2Conv_ObjectIntersecitonOf)
{
	ClauseSet cs;
	Owl2 owl2;
	string strOntology(
		"Prefix(:=<http://www.w3.org/2002/07/owl#>)\n"
		"Prefix(t:=<http://cin.ufpe.br/~dldmf/raccoon/test_subclassof.owl>)\n"
		"Ontology(<http://cin.ufpe.br/~dldmf/raccoon/test_subclassof.owl>\n"
		" SubClassOf(ObjectIntersectionOf(t:Class2 t:Class3) t:Class1)\n"
		")"
	);
	Ontology ontology;
	
	parse_result* pr = OWL2_parse_string((char*)strOntology.c_str());
	CHECK(pr != NULL);
	if (pr == NULL) return;
	
	owl2.parse(pr, &ontology, &cs, true);
	CHECK(cs.clauses.size() == 1);
	CHECK(cs.clauses[0]->concepts.size() == 3);
	CHECK(cs.clauses[0]->concepts[0]->concept._name == "t:Class2");
	CHECK(cs.clauses[0]->concepts[1]->concept._name == "t:Class3");
	CHECK(cs.clauses[0]->concepts[2]->concept._name == "t:Class1");
	CHECK(cs.clauses[0]->concepts[0]->neg == false);
	CHECK(cs.clauses[0]->concepts[1]->neg == false);
	CHECK(cs.clauses[0]->concepts[2]->neg == true);
	CHECK(cs.clauses[0]->concepts[0]->var == 0);
	CHECK(cs.clauses[0]->concepts[1]->var == 0);
	CHECK(cs.clauses[0]->concepts[2]->var == 0);
	CHECK(ontology.conceptsById.at(cs.clauses[0]->concepts[0]->concept.id()) == &cs.clauses[0]->concepts[0]->concept);
	CHECK(ontology.conceptsById.at(cs.clauses[0]->concepts[1]->concept.id()) == &cs.clauses[0]->concepts[1]->concept);
	CHECK(ontology.conceptsById.at(cs.clauses[0]->concepts[2]->concept.id()) == &cs.clauses[0]->concepts[2]->concept);
	CHECK(ontology.conceptCount == 5); // because owl:Thing and owl:Nothing are always there
	CHECK(ontology.roleCount == 0);
	CHECK(ontology.instanceCount == 0);
}

/**
 * \brief Test the conversion of the the Negated ObjectIntersectionOf
 */
TEST(Owl2Conv_ObjectIntersecitonOf_Negated)
{
	ClauseSet cs;
	Owl2 owl2;
	string strOntology(
		"Prefix(:=<http://www.w3.org/2002/07/owl#>)\n"
		"Prefix(t:=<http://cin.ufpe.br/~dldmf/raccoon/test_subclassof.owl>)\n"
		"Ontology(<http://cin.ufpe.br/~dldmf/raccoon/test_subclassof.owl>\n"
		" SubClassOf(t:Class1 ObjectIntersectionOf(t:Class2 t:Class3))\n"
		")"
	);
	Ontology ontology;
	
	parse_result* pr = OWL2_parse_string((char*)strOntology.c_str());
	CHECK(pr != NULL);
	if (pr == NULL) return;	
	owl2.parse(pr, &ontology, &cs, true);
	CHECK(cs.clauses.size() == 3);
	CHECK(cs.clauses[0]->concepts.size() == 2);
	CHECK(cs.clauses[0]->concepts[1]->concept._name == "t:Class2");
	CHECK(cs.clauses[0]->concepts[1]->neg == true);
	CHECK(cs.clauses[0]->concepts[0]->var == 0);
	CHECK(cs.clauses[0]->concepts[1]->var == 0);
	CHECK(cs.clauses[1]->concepts.size() == 2);
	CHECK(cs.clauses[1]->concepts[1]->concept._name == "t:Class3");
	CHECK(cs.clauses[1]->concepts[1]->neg == true);
	CHECK(cs.clauses[1]->concepts[0]->var == 0);
	CHECK(cs.clauses[1]->concepts[1]->var == 0);
	CHECK(cs.clauses[2]->concepts.size() == 2);
	CHECK(cs.clauses[2]->concepts[0]->concept._name == "t:Class1");
	CHECK(cs.clauses[2]->concepts[0]->neg == false);
	CHECK(cs.clauses[2]->concepts[0]->var == 0);
	CHECK(cs.clauses[2]->concepts[1]->var == 0);
	CHECK(ontology.conceptsById.at(cs.clauses[0]->concepts[1]->concept.id()) == &cs.clauses[0]->concepts[1]->concept);
	CHECK(ontology.conceptsById.at(cs.clauses[1]->concepts[1]->concept.id()) == &cs.clauses[1]->concepts[1]->concept);
	CHECK(ontology.conceptsById.at(cs.clauses[2]->concepts[0]->concept.id()) == &cs.clauses[2]->concepts[0]->concept);
	CHECK(ontology.conceptCount == 6); // because owl:Thing and owl:Nothing are always there
	CHECK(ontology.roleCount == 0);
	CHECK(ontology.instanceCount == 0);
}

/**
 * \brief Test the conversion of the ObjectUnionOf
 */
TEST(Owl2Conv_ObjectUnionOf)
{
	ClauseSet cs;
	Owl2 owl2;
	string strOntology(
		"Prefix(:=<http://www.w3.org/2002/07/owl#>)\n"
		"Prefix(t:=<http://cin.ufpe.br/~dldmf/raccoon/test_subclassof.owl>)\n"
		"Ontology(<http://cin.ufpe.br/~dldmf/raccoon/test_subclassof.owl>\n"
		" SubClassOf(ObjectUnionOf(t:Class2 t:Class3) t:Class1)\n"
		")"
	);
	Ontology ontology;
	
	parse_result* pr = OWL2_parse_string((char*)strOntology.c_str());
	CHECK(pr != NULL);
	if (pr == NULL) return;
	owl2.parse(pr, &ontology, &cs, true);
	CHECK(cs.clauses.size() == 3);
	CHECK(hasConcept(cs.clauses[0], "t:Class2", false, 0));
	CHECK(hasConcept(cs.clauses[1], "t:Class3", false, 0));
	CHECK(hasConcept(cs.clauses[2], "t:Class1", true, 0));
	CHECK(ontology.conceptCount == 6); // because owl:Thing and owl:Nothing are always there
	CHECK(ontology.roleCount == 0);
	CHECK(ontology.instanceCount == 0);
}

/**
 * \brief Test the conversion of the Negated ObjectUnionOf
 */
TEST(Owl2Conv_ObjectUnionOf_Negated)
{
	ClauseSet cs;
	Owl2 owl2;
	string strOntology(
		"Prefix(:=<http://www.w3.org/2002/07/owl#>)\n"
		"Prefix(t:=<http://cin.ufpe.br/~dldmf/raccoon/test_subclassof.owl>)\n"
		"Ontology(<http://cin.ufpe.br/~dldmf/raccoon/test_subclassof.owl>\n"
		" SubClassOf(t:Class1 ObjectUnionOf(t:Class2 t:Class3))\n"
		")"
	);
	Ontology ontology;
	
	parse_result* pr = OWL2_parse_string((char*)strOntology.c_str());
	CHECK(pr != NULL);
	if (pr == NULL) return;
	
	owl2.parse(pr, &ontology, &cs, true);
	CHECK(cs.clauses.size() == 1);
	CHECK(cs.clauses[0]->concepts.size() == 3);
	CHECK(hasConcept(cs.clauses[0], "t:Class2", true, 0));
	CHECK(hasConcept(cs.clauses[0], "t:Class3", true, 0));
	CHECK(hasConcept(cs.clauses[0], "t:Class1", false, 0));
	CHECK(ontology.conceptCount == 5); // because owl:Thing and owl:Nothing are always there
	CHECK(ontology.roleCount == 0);
	CHECK(ontology.instanceCount == 0);
}

/**
 * \brief Test the conversion of the ObjectComplementOf
 */
TEST(Owl2Conv_ObjectComplementOf)
{
	ClauseSet cs;
	Owl2 owl2;
	string strOntology(
		"Prefix(:=<http://www.w3.org/2002/07/owl#>)\n"
		"Prefix(t:=<http://cin.ufpe.br/~dldmf/raccoon/test_subclassof.owl>)\n"
		"Ontology(<http://cin.ufpe.br/~dldmf/raccoon/test_subclassof.owl>\n"
		" SubClassOf(ObjectComplementOf(t:Class2) t:Class1)\n"
		")"
	);
	Ontology ontology;
	
	parse_result* pr = OWL2_parse_string((char*)strOntology.c_str());
	CHECK(pr != NULL);
	if (pr == NULL) return;
	
	owl2.parse(pr, &ontology, &cs, true);
	CHECK(cs.clauses.size() == 1);
	CHECK(cs.clauses[0]->concepts.size() == 2);
	CHECK(hasConcept(cs.clauses[0], "t:Class2", true, 0));
	CHECK(hasConcept(cs.clauses[0], "t:Class1", true, 0));
	CHECK(ontology.conceptCount == 4); // because owl:Thing and owl:Nothing are always there
	CHECK(ontology.roleCount == 0);
	CHECK(ontology.instanceCount == 0);
}

/**
 * \brief Test the conversion of the Negated ObjectComplementOf
 */
TEST(Owl2Conv_ObjectComplementOf_Negated)
{
	ClauseSet cs;
	Owl2 owl2;
	string strOntology(
		"Prefix(:=<http://www.w3.org/2002/07/owl#>)\n"
		"Prefix(t:=<http://cin.ufpe.br/~dldmf/raccoon/test_subclassof.owl>)\n"
		"Ontology(<http://cin.ufpe.br/~dldmf/raccoon/test_subclassof.owl>\n"
		" SubClassOf(t:Class1 ObjectComplementOf(t:Class2))\n"
		")"
	);
	Ontology ontology;
	
	parse_result* pr = OWL2_parse_string((char*)strOntology.c_str());
	CHECK(pr != NULL);
	if (pr == NULL) return;
	
	owl2.parse(pr, &ontology, &cs, true);
	CHECK(cs.clauses.size() == 1);
	CHECK(cs.clauses[0]->concepts.size() == 2);
	CHECK(hasConcept(cs.clauses[0], "t:Class1", false, 0));
	CHECK(hasConcept(cs.clauses[0], "t:Class2", false, 0));
	CHECK(ontology.conceptCount == 4); // because owl:Thing and owl:Nothing are always there
	CHECK(ontology.roleCount == 0);
	CHECK(ontology.instanceCount == 0);
}

/**
 * \brief Test the conversion of the ObjectSomeValuesFrom
 */
TEST(Owl2Conv_ObjectSomeValuesFrom)
{
	ClauseSet cs;
	Owl2 owl2;
	string strOntology(
		"Prefix(:=<http://www.w3.org/2002/07/owl#>)\n"
		"Prefix(t:=<http://cin.ufpe.br/~dldmf/raccoon/test_subclassof.owl>)\n"
		"Ontology(<http://cin.ufpe.br/~dldmf/raccoon/test_subclassof.owl>\n"
		" SubClassOf(ObjectSomeValuesFrom(t:Role1 t:Class2) t:Class1)\n"
		")"
	);
	Ontology ontology;
	
	parse_result* pr = OWL2_parse_string((char*)strOntology.c_str());
	CHECK(pr != NULL);
	if (pr == NULL) return;	
	owl2.parse(pr, &ontology, &cs, true);
	CHECK(cs.clauses.size() == 1);
	CHECK(cs.clauses[0]->concepts.size() == 1);
	CHECK(cs.clauses[0]->existentials.size() == 1);
	for (auto clause: ontology.clauseSet)
	{
		CHECK(clause->values.size() == 0);
	}
	CHECK(hasConcept(cs.clauses[0], "t:Class1", true, 0));
    CHECK(hasExistential(cs.clauses[0], "t:Role1", "t:Class2", false, false, 0, 1));
	CHECK(ontology.conceptCount == 4); // because owl:Thing and owl:Nothing are always there
	CHECK(ontology.roleCount == 1);
	CHECK(ontology.instanceCount == 0);
}

/**
 * \brief Test the conversion of the Negated ObjectSomeValuesFrom
 */
TEST(Owl2Conv_ObjectSomeValuesFrom_Negated)
{
	ClauseSet cs;
	Owl2 owl2;
	string strOntology(
		"Prefix(:=<http://www.w3.org/2002/07/owl#>)\n"
		"Prefix(t:=<http://cin.ufpe.br/~dldmf/raccoon/test_subclassof.owl>)\n"
		"Ontology(<http://cin.ufpe.br/~dldmf/raccoon/test_subclassof.owl>\n"
		" SubClassOf(t:Class1 ObjectSomeValuesFrom(t:Role1 t:Class2))\n"
		")"
	);
	Ontology ontology;
	
	parse_result* pr = OWL2_parse_string((char*)strOntology.c_str());
	CHECK(pr != NULL);
	if (pr == NULL) return;	
	owl2.parse(pr, &ontology, &cs, true);
	CHECK(cs.clauses.size() == 1);
	CHECK(cs.clauses[0]->concepts.size() == 1);
	CHECK(cs.clauses[0]->universals.size() == 1);
	for (auto clause: ontology.clauseSet)
	{
		CHECK(clause->values.size() == 0);
	}
	CHECK(hasConcept(cs.clauses[0], "t:Class1", false, 0));
	CHECK(hasUniversal(cs.clauses[0], "t:Role1", "t:Class2", true, true, 0, 1));
	CHECK(ontology.conceptCount == 4); // because owl:Thing and owl:Nothing are always there
	CHECK(ontology.roleCount == 1);
	CHECK(ontology.instanceCount == 1);
}

/**
 * \brief Test the conversion of the ObjectAllValuesFrom
 */
TEST(Owl2Conv_ObjectAllValuesFrom)
{
	ClauseSet cs;
	Owl2 owl2;
	string strOntology(
		"Prefix(:=<http://www.w3.org/2002/07/owl#>)\n"
		"Prefix(t:=<http://cin.ufpe.br/~dldmf/raccoon/test_subclassof.owl>)\n"
		"Ontology(<http://cin.ufpe.br/~dldmf/raccoon/test_subclassof.owl>\n"
		" SubClassOf(ObjectAllValuesFrom(t:Role1 t:Class2) t:Class1)\n"
		")"
	);
	Ontology ontology;
	
	parse_result* pr = OWL2_parse_string((char*)strOntology.c_str());
	CHECK(pr != NULL);
	if (pr == NULL) return;	
	owl2.parse(pr, &ontology, &cs, true);
	CHECK(cs.clauses.size() == 1);
	CHECK(cs.clauses[0]->concepts.size() == 1);
	CHECK(cs.clauses[0]->universals.size() == 1);
	CHECK(hasConcept(cs.clauses[0], "t:Class1", true, 0));
	CHECK(hasUniversal(cs.clauses[0], "t:Role1", "t:Class2", true, false, 0, 1));
	CHECK(ontology.conceptCount == 4); // because owl:Thing and owl:Nothing are always there
	CHECK(ontology.roleCount == 1);
	CHECK(ontology.instanceCount == 1);
}

/**
 * \brief Test the conversion of the Negated ObjectAllValuesFrom
 */
TEST(Owl2Conv_ObjectAllValuesFrom_Negated)
{
	ClauseSet cs;
	Owl2 owl2;
	string strOntology(
		"Prefix(:=<http://www.w3.org/2002/07/owl#>)\n"
		"Prefix(t:=<http://cin.ufpe.br/~dldmf/raccoon/test_subclassof.owl>)\n"
		"Ontology(<http://cin.ufpe.br/~dldmf/raccoon/test_subclassof.owl>\n"
		" SubClassOf(t:Class1 ObjectAllValuesFrom(t:Role1 t:Class2))\n"
		")"
	);
	Ontology ontology;
	
	parse_result* pr = OWL2_parse_string((char*)strOntology.c_str());
	CHECK(pr != NULL);
	if (pr == NULL) return;	
	owl2.parse(pr, &ontology, &cs, true);
	CHECK(cs.clauses.size() == 1);
	CHECK(cs.clauses[0]->concepts.size() == 1);
	CHECK(cs.clauses[0]->existentials.size() == 1);
	CHECK(hasConcept(cs.clauses[0], "t:Class1", false, 0));
    CHECK(hasExistential(cs.clauses[0], "t:Role1", "t:Class2", false, true, 0, 1));
	CHECK(ontology.conceptCount == 4); // because owl:Thing and owl:Nothing are always there
	CHECK(ontology.roleCount == 1);
	CHECK(ontology.instanceCount == 0);
}

/**
 * \brief Test the conversion of the ClassAssertion
 */
TEST(Owl2Conv_ClassAssertion)
{
	ClauseSet cs;
	Owl2 owl2;
	string strOntology(
		"Prefix(:=<http://www.w3.org/2002/07/owl#>)\n"
		"Prefix(t:=<http://cin.ufpe.br/~dldmf/raccoon/test_subclassof.owl>)\n"
		"Ontology(<http://cin.ufpe.br/~dldmf/raccoon/test_subclassof.owl>\n"
		" ClassAssertion(t:Class1 t:Instance1)\n"
		")"
	);
	Ontology ontology;
	
	parse_result* pr = OWL2_parse_string((char*)strOntology.c_str());
	CHECK(pr != NULL);
	if (pr == NULL) return;	
	owl2.parse(pr, &ontology, &cs, true);
	cs.printClauses();
	CHECK(cs.clauses.size() == 1);
	CHECK(cs.clauses[0]->concepts.size() == 1);
	CHECK(hasConcept(cs.clauses[0], "t:Class1", true, 0));
	CHECK(cs.clauses[0]->values[0] == &ontology.assertInstance("t:Instance1"));
	CHECK(ontology.conceptCount == 3); // because owl:Thing and owl:Nothing are always there
	CHECK(ontology.roleCount == 0);
	CHECK(ontology.instanceCount == 1);
}

/**
 * \brief Test the conversion of the ObjectPropertyAssertion
 */
TEST(Owl2Conv_ObjectPropertyAssertion)
{
	ClauseSet cs;
	Owl2 owl2;
	string strOntology(
		"Prefix(owl:=<http://www.w3.org/2002/07/owl#>)\n"
		"Prefix(:=<http://cin.ufpe.br/~dldmf/raccoon/test_subclassof.owl>)\n"
		"Ontology(<http://cin.ufpe.br/~dldmf/raccoon/test_subclassof.owl>\n"
		" ObjectPropertyAssertion(:Role1 :Instance1 :Instance2)\n"
		")"
	);
	Ontology ontology;
	
	parse_result* pr = OWL2_parse_string((char*)strOntology.c_str());
	CHECK(pr != NULL);
	if (pr == NULL) return;	
	owl2.parse(pr, &ontology, &cs, true);
	CHECK(cs.clauses.size() == 1);
	CHECK(cs.clauses[0]->roles.size() == 1);
	CHECK(hasRole(cs.clauses[0], ":Role1", true, 0, 1));
	CHECK(cs.clauses[0]->values[0] == &ontology.assertInstance(":Instance1"));
	CHECK(cs.clauses[0]->values[1] == &ontology.assertInstance(":Instance2"));
	CHECK(ontology.conceptCount == 2); // because owl:Thing and owl:Nothing are always there
	CHECK(ontology.roleCount == 1);
	CHECK(ontology.instanceCount == 2);
}

/**
 * \brief Test the conversion of the NegativeObjectPropertyAssertion
 */
TEST(Owl2Conv_NegativeObjectPropertyAssertion)
{
	ClauseSet cs;
	Owl2 owl2;
	string strOntology(
		"Prefix(owl:=<http://www.w3.org/2002/07/owl#>)\n"
		"Prefix(:=<http://cin.ufpe.br/~dldmf/raccoon/test_subclassof.owl>)\n"
		"Ontology(<http://cin.ufpe.br/~dldmf/raccoon/test_subclassof.owl>\n"
		" NegativeObjectPropertyAssertion(:Role1 :Instance1 :Instance2)\n"
		")"
	);
	Ontology ontology;
	
	parse_result* pr = OWL2_parse_string((char*)strOntology.c_str());
	CHECK(pr != NULL);
	if (pr == NULL) return;	
	owl2.parse(pr, &ontology, &cs, true);
	CHECK(cs.clauses.size() == 1);
	CHECK(cs.clauses[0]->roles.size() == 1);
	CHECK(hasRole(cs.clauses[0], ":Role1", false, 0, 1));
	CHECK(cs.clauses[0]->values[0] == &ontology.assertInstance(":Instance1"));
	CHECK(cs.clauses[0]->values[1] == &ontology.assertInstance(":Instance2"));
	CHECK(ontology.conceptCount == 2); // because owl:Thing and owl:Nothing are always there
	CHECK(ontology.roleCount == 1);
	CHECK(ontology.instanceCount == 2);
}

