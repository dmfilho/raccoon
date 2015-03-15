
// STL
#include <string>
#include <string.h>
// UnitTest++
#include <unittest++/UnitTest++.h>
// raccoon
extern "C" {
#include "../parsers/owl2/owl2_parser.h"
}

using namespace std;

/**
 * \brief Test the SubClassOf parsing.
 */
TEST(ParserOwl2P_SubClassOf)
{
	string owl2(
		"Prefix(:=<http://www.w3.org/2002/07/owl#>)\n"
		"Prefix(t:=<http://cin.ufpe.br/~dldmf/raccoon/test_subclassof.owl>)\n"
		"Ontology(<http://cin.ufpe.br/~dldmf/raccoon/test_subclassof.owl>\n"
		" SubClassOf(t:Class1 t:Class2)\n"
		")"
	);
	parse_result* pr = OWL2_parse_string((char*)owl2.c_str());
	CHECK(pr != NULL);
	if (pr == NULL) return;
	CHECK_EQUAL(OWL2_ontologyDocument, pr->ast->tokenId);
	CHECK_EQUAL(OWL2_prefixDeclaration, pr->ast->firstChild->tokenId);
	ast_node* ontology = pr->ast->firstChild->nextSibling;
	CHECK_EQUAL(OWL2_Ontology, ontology->tokenId);
	ast_node* axioms = ontology->firstChild->nextSibling->nextSibling->nextSibling->nextSibling->nextSibling;
	CHECK_EQUAL(OWL2_axioms, axioms->tokenId); 
	ast_node* classAxiom = axioms->firstChild->firstChild;
	CHECK_EQUAL(OWL2_ClassAxiom, classAxiom->tokenId);
	ast_node* subClassOf = classAxiom->firstChild;
	CHECK_EQUAL(OWL2_SubClassOf, subClassOf->tokenId);
	ast_node* class1 = subClassOf->firstChild->nextSibling->nextSibling->nextSibling->firstChild->firstChild;
	ast_node* class2 = subClassOf->firstChild->nextSibling->nextSibling->nextSibling->nextSibling->firstChild->firstChild;
	CHECK_EQUAL(OWL2_Class, class1->tokenId);
	CHECK_EQUAL(OWL2_Class, class2->tokenId);
	CHECK(strcmp(class1->firstChild->firstChild->data, "t:Class1") == 0);
	CHECK(strcmp(class2->firstChild->firstChild->data, "t:Class2") == 0);
}

/**
 * \brief Test the EquivalentClasses parsing.
 */
TEST(ParserOwl2P_EquivalentClasses)
{
	string owl2(
		"Prefix(:=<http://www.w3.org/2002/07/owl#>)\n"
		"Prefix(t:=<http://cin.ufpe.br/~dldmf/raccoon/test_subclassof.owl>)\n"
		"Ontology(<http://cin.ufpe.br/~dldmf/raccoon/test_subclassof.owl>\n"
		" EquivalentClasses(t:Class1 t:Class2 t:Class3)\n"
		")"
	);
	parse_result* pr = OWL2_parse_string((char*)owl2.c_str());
	CHECK(pr != NULL);
	if (pr == NULL) return;
	CHECK_EQUAL(OWL2_ontologyDocument, pr->ast->tokenId);
	CHECK_EQUAL(OWL2_prefixDeclaration, pr->ast->firstChild->tokenId);
	ast_node* ontology = pr->ast->firstChild->nextSibling;
	CHECK_EQUAL(OWL2_Ontology, ontology->tokenId);
	ast_node* axioms = ontology->firstChild->nextSibling->nextSibling->nextSibling->nextSibling->nextSibling;
	CHECK_EQUAL(OWL2_axioms, axioms->tokenId); 
	ast_node* classAxiom = axioms->firstChild->firstChild;
	CHECK_EQUAL(OWL2_ClassAxiom, classAxiom->tokenId);
	ast_node* eqClasses = classAxiom->firstChild;
	CHECK_EQUAL(OWL2_EquivalentClasses, eqClasses->tokenId);
	ast_node* class1 = eqClasses->firstChild->nextSibling->nextSibling->nextSibling->firstChild;
	ast_node* class2 = eqClasses->firstChild->nextSibling->nextSibling->nextSibling->nextSibling->firstChild;
	ast_node* class3 = eqClasses->firstChild->nextSibling->nextSibling->nextSibling->nextSibling->nextSibling->
		firstChild->firstChild;
	CHECK_EQUAL(OWL2_Class, class1->tokenId);
	CHECK_EQUAL(OWL2_Class, class2->tokenId);
	CHECK_EQUAL(OWL2_Class, class3->tokenId);
	CHECK(strcmp(class1->firstChild->firstChild->data, "t:Class1") == 0);
	CHECK(strcmp(class2->firstChild->firstChild->data, "t:Class2") == 0);
	CHECK(strcmp(class3->firstChild->firstChild->data, "t:Class3") == 0);
}

/**
 * \brief Test the DisjointClasses parsing.
 */
TEST(ParserOwl2P_DisjointClasses)
{
	string owl2(
		"Prefix(:=<http://www.w3.org/2002/07/owl#>)\n"
		"Prefix(t:=<http://cin.ufpe.br/~dldmf/raccoon/test_subclassof.owl>)\n"
		"Ontology(<http://cin.ufpe.br/~dldmf/raccoon/test_subclassof.owl>\n"
		" DisjointClasses(t:Class1 t:Class2 t:Class3)\n"
		")"
	);
	parse_result* pr = OWL2_parse_string((char*)owl2.c_str());
	CHECK(pr != NULL);
	if (pr == NULL) return;
	CHECK_EQUAL(OWL2_ontologyDocument, pr->ast->tokenId);
	CHECK_EQUAL(OWL2_prefixDeclaration, pr->ast->firstChild->tokenId);
	ast_node* ontology = pr->ast->firstChild->nextSibling;
	CHECK_EQUAL(OWL2_Ontology, ontology->tokenId);
	ast_node* axioms = ontology->firstChild->nextSibling->nextSibling->nextSibling->nextSibling->nextSibling;
	CHECK_EQUAL(OWL2_axioms, axioms->tokenId); 
	ast_node* classAxiom = axioms->firstChild->firstChild;
	CHECK_EQUAL(OWL2_ClassAxiom, classAxiom->tokenId);
	ast_node* disClasses = classAxiom->firstChild;
	CHECK_EQUAL(OWL2_DisjointClasses, disClasses->tokenId);
	ast_node* class1 = disClasses->firstChild->nextSibling->nextSibling->nextSibling->firstChild;
	ast_node* class2 = disClasses->firstChild->nextSibling->nextSibling->nextSibling->nextSibling->firstChild;
	ast_node* class3 = disClasses->firstChild->nextSibling->nextSibling->nextSibling->nextSibling->nextSibling->
		firstChild->firstChild;
	CHECK_EQUAL(OWL2_Class, class1->tokenId);
	CHECK_EQUAL(OWL2_Class, class2->tokenId);
	CHECK_EQUAL(OWL2_Class, class3->tokenId);
	CHECK(strcmp(class1->firstChild->firstChild->data, "t:Class1") == 0);
	CHECK(strcmp(class2->firstChild->firstChild->data, "t:Class2") == 0);
	CHECK(strcmp(class3->firstChild->firstChild->data, "t:Class3") == 0);
}

/**
 * \brief Test the DisjointUnion parsing.
 */
TEST(ParserOwl2P_DisjointUnion)
{
	string owl2(
		"Prefix(:=<http://www.w3.org/2002/07/owl#>)\n"
		"Prefix(t:=<http://cin.ufpe.br/~dldmf/raccoon/test_subclassof.owl>)\n"
		"Ontology(<http://cin.ufpe.br/~dldmf/raccoon/test_subclassof.owl>\n"
		" DisjointUnion(t:Class1 t:Class2 t:Class3)\n"
		")"
	);
	parse_result* pr = OWL2_parse_string((char*)owl2.c_str());
	CHECK(pr != NULL);
	if (pr == NULL) return;
	CHECK_EQUAL(OWL2_ontologyDocument, pr->ast->tokenId);
	CHECK_EQUAL(OWL2_prefixDeclaration, pr->ast->firstChild->tokenId);
	ast_node* ontology = pr->ast->firstChild->nextSibling;
	CHECK_EQUAL(OWL2_Ontology, ontology->tokenId);
	ast_node* axioms = ontology->firstChild->nextSibling->nextSibling->nextSibling->nextSibling->nextSibling;
	CHECK_EQUAL(OWL2_axioms, axioms->tokenId); 
	ast_node* classAxiom = axioms->firstChild->firstChild;
	CHECK_EQUAL(OWL2_ClassAxiom, classAxiom->tokenId);
	ast_node* disClasses = classAxiom->firstChild;
	CHECK_EQUAL(OWL2_DisjointUnion, disClasses->tokenId);
	ast_node* class1 = disClasses->firstChild->nextSibling->nextSibling->nextSibling;
	ast_node* duList = disClasses->firstChild->nextSibling->nextSibling->nextSibling->nextSibling->firstChild;
	ast_node* class2 = duList->firstChild;
	ast_node* class3 = duList->nextSibling->firstChild;
	CHECK_EQUAL(OWL2_Class, class1->tokenId);
	CHECK_EQUAL(OWL2_Class, class2->tokenId);
	CHECK_EQUAL(OWL2_Class, class3->tokenId);
	CHECK(strcmp(class1->firstChild->firstChild->data, "t:Class1") == 0);
	CHECK(strcmp(class2->firstChild->firstChild->data, "t:Class2") == 0);
	CHECK(strcmp(class3->firstChild->firstChild->data, "t:Class3") == 0);
}

/**
 * \brief Test the ObjectIntersectionOf parsing.
 */
TEST(ParserOwl2P_ObjectIntersectionOf)
{
	string owl2(
		"Prefix(:=<http://www.w3.org/2002/07/owl#>)\n"
		"Prefix(t:=<http://cin.ufpe.br/~dldmf/raccoon/test_subclassof.owl>)\n"
		"Ontology(<http://cin.ufpe.br/~dldmf/raccoon/test_subclassof.owl>\n"
		" SubClassOf(ObjectIntersectionOf(t:Class1 t:Class2 t:Class3) t:Class4)\n"
		")"
	);
	parse_result* pr = OWL2_parse_string((char*)owl2.c_str());
	CHECK(pr != NULL);
	if (pr == NULL) return;
	CHECK_EQUAL(OWL2_ontologyDocument, pr->ast->tokenId);
	CHECK_EQUAL(OWL2_prefixDeclaration, pr->ast->firstChild->tokenId);
	ast_node* ontology = pr->ast->firstChild->nextSibling;
	CHECK_EQUAL(OWL2_Ontology, ontology->tokenId);
	ast_node* axioms = ontology->firstChild->nextSibling->nextSibling->nextSibling->nextSibling->nextSibling;
	CHECK_EQUAL(OWL2_axioms, axioms->tokenId); 
	ast_node* classAxiom = axioms->firstChild->firstChild;
	CHECK_EQUAL(OWL2_ClassAxiom, classAxiom->tokenId);
	ast_node* subClassOf = classAxiom->firstChild;
	CHECK_EQUAL(OWL2_SubClassOf, subClassOf->tokenId);
	ast_node* interOf = subClassOf->firstChild->nextSibling->nextSibling->nextSibling->firstChild->firstChild;
	ast_node* class1 = interOf->firstChild->nextSibling->nextSibling;
	ast_node* class2 = class1->nextSibling;
	ast_node* class3 = class2->nextSibling->firstChild;
	ast_node* class4 = subClassOf->firstChild->nextSibling->nextSibling->nextSibling->nextSibling->firstChild;
	
	CHECK_EQUAL(OWL2_ObjectIntersectionOf, interOf->tokenId);
	CHECK_EQUAL(OWL2_Class, class1->firstChild->tokenId);
	CHECK_EQUAL(OWL2_Class, class2->firstChild->tokenId);
	CHECK_EQUAL(OWL2_Class, class3->firstChild->tokenId);
	CHECK_EQUAL(OWL2_Class, class4->firstChild->tokenId);
	CHECK(strcmp(class1->firstChild->firstChild->firstChild->data, "t:Class1") == 0);
	CHECK(strcmp(class2->firstChild->firstChild->firstChild->data, "t:Class2") == 0);
	CHECK(strcmp(class3->firstChild->firstChild->firstChild->data, "t:Class3") == 0);
	CHECK(strcmp(class4->firstChild->firstChild->firstChild->data, "t:Class4") == 0);
}

/**
 * \brief Test the ObjectUnionOf parsing.
 */
TEST(ParserOwl2P_ObjectUnionOf)
{
	string owl2(
		"Prefix(:=<http://www.w3.org/2002/07/owl#>)\n"
		"Prefix(t:=<http://cin.ufpe.br/~dldmf/raccoon/test_subclassof.owl>)\n"
		"Ontology(<http://cin.ufpe.br/~dldmf/raccoon/test_subclassof.owl>\n"
		" SubClassOf(ObjectUnionOf(t:Class1 t:Class2 t:Class3) t:Class4)\n"
		")"
	);
	parse_result* pr = OWL2_parse_string((char*)owl2.c_str());
	CHECK(pr != NULL);
	if (pr == NULL) return;
	CHECK_EQUAL(OWL2_ontologyDocument, pr->ast->tokenId);
	CHECK_EQUAL(OWL2_prefixDeclaration, pr->ast->firstChild->tokenId);
	ast_node* ontology = pr->ast->firstChild->nextSibling;
	CHECK_EQUAL(OWL2_Ontology, ontology->tokenId);
	ast_node* axioms = ontology->firstChild->nextSibling->nextSibling->nextSibling->nextSibling->nextSibling;
	CHECK_EQUAL(OWL2_axioms, axioms->tokenId); 
	ast_node* classAxiom = axioms->firstChild->firstChild;
	CHECK_EQUAL(OWL2_ClassAxiom, classAxiom->tokenId);
	ast_node* subClassOf = classAxiom->firstChild;
	CHECK_EQUAL(OWL2_SubClassOf, subClassOf->tokenId);
	ast_node* unionOf = subClassOf->firstChild->nextSibling->nextSibling->nextSibling->firstChild->firstChild;
	ast_node* class1 = unionOf->firstChild->nextSibling->nextSibling;
	ast_node* class2 = class1->nextSibling;
	ast_node* class3 = class2->nextSibling->firstChild;
	ast_node* class4 = subClassOf->firstChild->nextSibling->nextSibling->nextSibling->nextSibling->firstChild;
	
	CHECK_EQUAL(OWL2_ObjectUnionOf, unionOf->tokenId);
	CHECK_EQUAL(OWL2_Class, class1->firstChild->tokenId);
	CHECK_EQUAL(OWL2_Class, class2->firstChild->tokenId);
	CHECK_EQUAL(OWL2_Class, class3->firstChild->tokenId);
	CHECK_EQUAL(OWL2_Class, class4->firstChild->tokenId);
	CHECK(strcmp(class1->firstChild->firstChild->firstChild->data, "t:Class1") == 0);
	CHECK(strcmp(class2->firstChild->firstChild->firstChild->data, "t:Class2") == 0);
	CHECK(strcmp(class3->firstChild->firstChild->firstChild->data, "t:Class3") == 0);
	CHECK(strcmp(class4->firstChild->firstChild->firstChild->data, "t:Class4") == 0);
}

/**
 * \brief Test the ObjectComplementOf parsing.
 */
TEST(ParserOwl2P_ObjectComplementOf)
{
	string owl2(
		"Prefix(:=<http://www.w3.org/2002/07/owl#>)\n"
		"Prefix(t:=<http://cin.ufpe.br/~dldmf/raccoon/test_subclassof.owl>)\n"
		"Ontology(<http://cin.ufpe.br/~dldmf/raccoon/test_subclassof.owl>\n"
		" SubClassOf(ObjectComplementOf(t:Class1) t:Class2)\n"
		")"
	);
	parse_result* pr = OWL2_parse_string((char*)owl2.c_str());
	CHECK(pr != NULL);
	if (pr == NULL) return;
	CHECK_EQUAL(OWL2_ontologyDocument, pr->ast->tokenId);
	CHECK_EQUAL(OWL2_prefixDeclaration, pr->ast->firstChild->tokenId);
	ast_node* ontology = pr->ast->firstChild->nextSibling;
	CHECK_EQUAL(OWL2_Ontology, ontology->tokenId);
	ast_node* axioms = ontology->firstChild->nextSibling->nextSibling->nextSibling->nextSibling->nextSibling;
	CHECK_EQUAL(OWL2_axioms, axioms->tokenId); 
	ast_node* classAxiom = axioms->firstChild->firstChild;
	CHECK_EQUAL(OWL2_ClassAxiom, classAxiom->tokenId);
	ast_node* subClassOf = classAxiom->firstChild;
	CHECK_EQUAL(OWL2_SubClassOf, subClassOf->tokenId);
	ast_node* complOf = subClassOf->firstChild->nextSibling->nextSibling->nextSibling->firstChild->firstChild;
	ast_node* class1 = complOf->firstChild->nextSibling->nextSibling;
	ast_node* class2 = subClassOf->firstChild->nextSibling->nextSibling->nextSibling->nextSibling->firstChild;
	
	CHECK_EQUAL(OWL2_ObjectComplementOf, complOf->tokenId);
	CHECK_EQUAL(OWL2_Class, class1->firstChild->tokenId);
	CHECK_EQUAL(OWL2_Class, class2->firstChild->tokenId);
	CHECK(strcmp(class1->firstChild->firstChild->firstChild->data, "t:Class1") == 0);
	CHECK(strcmp(class2->firstChild->firstChild->firstChild->data, "t:Class2") == 0);
}

/**
 * \brief Test the ObjectSomeValuesFrom parsing.
 */
TEST(ParserOwl2P_ObjectSomeValuesFrom)
{
	string owl2(
		"Prefix(:=<http://www.w3.org/2002/07/owl#>)\n"
		"Prefix(t:=<http://cin.ufpe.br/~dldmf/raccoon/test_subclassof.owl>)\n"
		"Ontology(<http://cin.ufpe.br/~dldmf/raccoon/test_subclassof.owl>\n"
		" SubClassOf(ObjectSomeValuesFrom(t:Role1 t:Class1) t:Class2)\n"
		")"
	);
	parse_result* pr = OWL2_parse_string((char*)owl2.c_str());
	CHECK(pr != NULL);
	if (pr == NULL) return;
	CHECK_EQUAL(OWL2_ontologyDocument, pr->ast->tokenId);
	CHECK_EQUAL(OWL2_prefixDeclaration, pr->ast->firstChild->tokenId);
	ast_node* ontology = pr->ast->firstChild->nextSibling;
	CHECK_EQUAL(OWL2_Ontology, ontology->tokenId);
	ast_node* axioms = ontology->firstChild->nextSibling->nextSibling->nextSibling->nextSibling->nextSibling;
	CHECK_EQUAL(OWL2_axioms, axioms->tokenId); 
	ast_node* classAxiom = axioms->firstChild->firstChild;
	CHECK_EQUAL(OWL2_ClassAxiom, classAxiom->tokenId);
	ast_node* subClassOf = classAxiom->firstChild;
	CHECK_EQUAL(OWL2_SubClassOf, subClassOf->tokenId);
	ast_node* expr = subClassOf->firstChild->nextSibling->nextSibling->nextSibling->firstChild->firstChild;
	ast_node* role1 = expr->firstChild->nextSibling->nextSibling;
	ast_node* class1 = role1->nextSibling;
	ast_node* class2 = subClassOf->firstChild->nextSibling->nextSibling->nextSibling->nextSibling->firstChild;
	
	CHECK_EQUAL(OWL2_ObjectSomeValuesFrom, expr->tokenId);
	CHECK_EQUAL(OWL2_ObjectProperty, role1->firstChild->tokenId);
	CHECK_EQUAL(OWL2_Class, class1->firstChild->tokenId);
	CHECK_EQUAL(OWL2_Class, class2->firstChild->tokenId);
	CHECK(strcmp(role1->firstChild->firstChild->firstChild->data, "t:Role1") == 0);
	CHECK(strcmp(class1->firstChild->firstChild->firstChild->data, "t:Class1") == 0);
	CHECK(strcmp(class2->firstChild->firstChild->firstChild->data, "t:Class2") == 0);
}

/**
 * \brief Test the ObjectAllValuesFrom parsing.
 */
TEST(ParserOwl2P_ObjectAllValuesFrom)
{
	string owl2(
		"Prefix(:=<http://www.w3.org/2002/07/owl#>)\n"
		"Prefix(t:=<http://cin.ufpe.br/~dldmf/raccoon/test_subclassof.owl>)\n"
		"Ontology(<http://cin.ufpe.br/~dldmf/raccoon/test_subclassof.owl>\n"
		" SubClassOf(ObjectAllValuesFrom(t:Role1 t:Class1) t:Class2)\n"
		")"
	);
	parse_result* pr = OWL2_parse_string((char*)owl2.c_str());
	CHECK(pr != NULL);
	if (pr == NULL) return;
	CHECK_EQUAL(OWL2_ontologyDocument, pr->ast->tokenId);
	CHECK_EQUAL(OWL2_prefixDeclaration, pr->ast->firstChild->tokenId);
	ast_node* ontology = pr->ast->firstChild->nextSibling;
	CHECK_EQUAL(OWL2_Ontology, ontology->tokenId);
	ast_node* axioms = ontology->firstChild->nextSibling->nextSibling->nextSibling->nextSibling->nextSibling;
	CHECK_EQUAL(OWL2_axioms, axioms->tokenId); 
	ast_node* classAxiom = axioms->firstChild->firstChild;
	CHECK_EQUAL(OWL2_ClassAxiom, classAxiom->tokenId);
	ast_node* subClassOf = classAxiom->firstChild;
	CHECK_EQUAL(OWL2_SubClassOf, subClassOf->tokenId);
	ast_node* expr = subClassOf->firstChild->nextSibling->nextSibling->nextSibling->firstChild->firstChild;
	ast_node* role1 = expr->firstChild->nextSibling->nextSibling;
	ast_node* class1 = role1->nextSibling;
	ast_node* class2 = subClassOf->firstChild->nextSibling->nextSibling->nextSibling->nextSibling->firstChild;
	
	CHECK_EQUAL(OWL2_ObjectAllValuesFrom, expr->tokenId);
	CHECK_EQUAL(OWL2_ObjectProperty, role1->firstChild->tokenId);
	CHECK_EQUAL(OWL2_Class, class1->firstChild->tokenId);
	CHECK_EQUAL(OWL2_Class, class2->firstChild->tokenId);
	CHECK(strcmp(role1->firstChild->firstChild->firstChild->data, "t:Role1") == 0);
	CHECK(strcmp(class1->firstChild->firstChild->firstChild->data, "t:Class1") == 0);
	CHECK(strcmp(class2->firstChild->firstChild->firstChild->data, "t:Class2") == 0);
}
