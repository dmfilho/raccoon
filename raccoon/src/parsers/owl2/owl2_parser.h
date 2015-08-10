#ifndef __OWL2__H
#define __OWL2__H

typedef struct _ast_node {
 int tokenId;
 char* data;
 struct _ast_node* nextSibling;
 struct _ast_node* firstChild;
} ast_node;

typedef struct _token {
 int type;
 char* value;
} token;

typedef struct _token_list {
 token* items;
 char* data;
 int count;
 char* data_ptr;
} token_list;

typedef struct _parse_result {
 token_list* tokens;
 ast_node* ast;
} parse_result;

ast_node* ast_new_node();
void ast_add_child(ast_node* parent, ast_node* child);
void ast_add_sibling(ast_node* sibling, ast_node* sibling_new);
void ast_free(ast_node* node);
void ast_clear(ast_node* node);
ast_node* ast_invert_siblings(ast_node* node, ast_node* newNextSibling);
void token_list_free(token_list* tokens);
parse_result* parse_result_new();
void parse_result_free(parse_result* pr);

parse_result* OWL2_parse_file(const char* fileName);
parse_result* OWL2_parse_string(const char* buffer);

#define OWL2_IRI 1000000000
#define OWL2_ontologyDocument 1000000001
#define OWL2_prefixDeclaration 1000000002
#define OWL2_Ontology 1000000003
#define OWL2_ontologyIRI 1000000004
#define OWL2_versionIRI 1000000005
#define OWL2_directlyImportsDocuments 1000000006
#define OWL2_ontologyAnnotations 1000000007
#define OWL2_axioms 1000000008
#define OWL2_Annotation 1000000009
#define OWL2_annotationAnnotations 1000000010
#define OWL2_AnnotationProperty 1000000011
#define OWL2_AnnotationValue 1000000012
#define OWL2_AnonymousIndividual 1000000013
#define OWL2_Literal 1000000014
#define OWL2_typedLiteral 1000000015
#define OWL2_stringLiteralNoLanguage 1000000016
#define OWL2_stringLiteralWithLanguage 1000000017
#define OWL2_lexicalForm 1000000018
#define OWL2_Datatype 1000000019
#define OWL2_Axiom 1000000020
#define OWL2_Declaration 1000000021
#define OWL2_ClassAxiom 1000000022
#define OWL2_ObjectPropertyAxiom 1000000023
#define OWL2_DataPropertyAxiom 1000000024
#define OWL2_DatatypeDefinition 1000000025
#define OWL2_HasKey 1000000026
#define OWL2_Assertion 1000000027
#define OWL2_AnnotationAxiom 1000000028
#define OWL2_axiomAnnotations 1000000029
#define OWL2_Entity 1000000030
#define OWL2_SubClassOf 1000000031
#define OWL2_subClassExpression 1000000032
#define OWL2_superClassExpression 1000000033
#define OWL2_EquivalentClasses 1000000034
#define OWL2_ClassExpressionList 1000000035
#define OWL2_ClassExpression 1000000036
#define OWL2_DisjointClasses 1000000037
#define OWL2_DisjointUnion 1000000038
#define OWL2_SubObjectPropertyOf 1000000039
#define OWL2_EquivalentObjectProperties 1000000040
#define OWL2_DisjointObjectProperties 1000000041
#define OWL2_InverseObjectProperties 1000000042
#define OWL2_ObjectPropertyDomain 1000000043
#define OWL2_ObjectPropertyRange 1000000044
#define OWL2_FunctionalObjectProperty 1000000045
#define OWL2_InverseFunctionalObjectProperty 1000000046
#define OWL2_ReflexiveObjectProperty 1000000047
#define OWL2_IrreflexiveObjectProperty 1000000048
#define OWL2_SymmetricObjectProperty 1000000049
#define OWL2_AsymmetricObjectProperty 1000000050
#define OWL2_TransitiveObjectProperty 1000000051
#define OWL2_ObjectPropertyExpressionList 1000000052
#define OWL2_SubDataPropertyOf 1000000053
#define OWL2_EquivalentDataProperties 1000000054
#define OWL2_DisjointDataProperties 1000000055
#define OWL2_DataPropertyDomain 1000000056
#define OWL2_DataPropertyRange 1000000057
#define OWL2_FunctionalDataProperty 1000000058
#define OWL2_DataPropertyExpressionList 1000000059
#define OWL2_DataRange 1000000060
#define OWL2_SameIndividual 1000000061
#define OWL2_DifferentIndividuals 1000000062
#define OWL2_ClassAssertion 1000000063
#define OWL2_ObjectPropertyAssertion 1000000064
#define OWL2_NegativeObjectPropertyAssertion 1000000065
#define OWL2_DataPropertyAssertion 1000000066
#define OWL2_NegativeDataPropertyAssertion 1000000067
#define OWL2_IndividualList 1000000068
#define OWL2_AnnotationAssertion 1000000069
#define OWL2_SubAnnotationPropertyOf 1000000070
#define OWL2_AnnotationPropertyDomain 1000000071
#define OWL2_AnnotationPropertyRange 1000000072
#define OWL2_Class 1000000073
#define OWL2_ObjectProperty 1000000074
#define OWL2_DataProperty 1000000075
#define OWL2_NamedIndividual 1000000076
#define OWL2_ObjectIntersectionOf 1000000077
#define OWL2_ObjectUnionOf 1000000078
#define OWL2_ObjectComplementOf 1000000079
#define OWL2_ObjectOneOf 1000000080
#define OWL2_ObjectSomeValuesFrom 1000000081
#define OWL2_ObjectAllValuesFrom 1000000082
#define OWL2_ObjectHasValue 1000000083
#define OWL2_ObjectHasSelf 1000000084
#define OWL2_ObjectMinCardinality 1000000085
#define OWL2_ObjectMaxCardinality 1000000086
#define OWL2_ObjectExactCardinality 1000000087
#define OWL2_DataSomeValuesFrom 1000000088
#define OWL2_DataAllValuesFrom 1000000089
#define OWL2_DataHasValue 1000000090
#define OWL2_DataMinCardinality 1000000091
#define OWL2_DataMaxCardinality 1000000092
#define OWL2_DataExactCardinality 1000000093
#define OWL2_disjointClassExpressions 1000000094
#define OWL2_subObjectPropertyExpression 1000000095
#define OWL2_propertyExpressionChain 1000000096
#define OWL2_superObjectPropertyExpression 1000000097
#define OWL2_ObjectPropertyExpression 1000000098
#define OWL2_InverseObjectProperty 1000000099
#define OWL2_subDataPropertyExpression 1000000100
#define OWL2_superDataPropertyExpression 1000000101
#define OWL2_DataPropertyExpression 1000000102
#define OWL2_DataIntersectionOf 1000000103
#define OWL2_DataUnionOf 1000000104
#define OWL2_DataComplementOf 1000000105
#define OWL2_DataOneOf 1000000106
#define OWL2_DatatypeRestriction 1000000107
#define OWL2_DataRangeList 1000000108
#define OWL2_LiteralList 1000000109
#define OWL2_crList 1000000110
#define OWL2_constrainingFacet 1000000111
#define OWL2_restrictionValue 1000000112
#define OWL2_Individual 1000000113
#define OWL2_sourceIndividual 1000000114
#define OWL2_targetIndividual 1000000115
#define OWL2_targetValue 1000000116
#define OWL2_AnnotationSubject 1000000117
#define OWL2_ABBREVIATEDIRI 9
#define OWL2_ANNOTATION 18
#define OWL2_ANNOTATIONASSERTION 13
#define OWL2_ANNOTATIONPROPERTY 17
#define OWL2_ANNOTATIONPROPERTYDOMAIN 15
#define OWL2_ANNOTATIONPROPERTYRANGE 16
#define OWL2_ASYMMETRICOBJECTPROPERTY 56
#define OWL2_CLASS 35
#define OWL2_CLASSASSERTION 34
#define OWL2_DATAALLVALUESFROM 22
#define OWL2_DATACOMPLEMENTOF 29
#define OWL2_DATAEXACTCARDINALITY 26
#define OWL2_DATAHASVALUE 23
#define OWL2_DATAINTERSECTIONOF 27
#define OWL2_DATAMAXCARDINALITY 25
#define OWL2_DATAMINCARDINALITY 24
#define OWL2_DATAONEOF 30
#define OWL2_DATAPROPERTY 44
#define OWL2_DATAPROPERTYASSERTION 20
#define OWL2_DATAPROPERTYDOMAIN 42
#define OWL2_DATAPROPERTYRANGE 43
#define OWL2_DATASOMEVALUESFROM 21
#define OWL2_DATATYPE 36
#define OWL2_DATATYPEDEFINITION 32
#define OWL2_DATATYPERESTRICTION 31
#define OWL2_DATAUNIONOF 28
#define OWL2_DECLARATION 19
#define OWL2_DHAT 5
#define OWL2_DIFFERENTINDIVIDUALS 63
#define OWL2_DISJOINTCLASSES 81
#define OWL2_DISJOINTDATAPROPERTIES 60
#define OWL2_DISJOINTOBJECTPROPERTIES 50
#define OWL2_DISJOINTUNION 82
#define OWL2_EQ 2
#define OWL2_EQUIVALENTCLASSES 47
#define OWL2_EQUIVALENTDATAPROPERTIES 59
#define OWL2_EQUIVALENTOBJECTPROPERTIES 49
#define OWL2_FULLIRI 12
#define OWL2_FUNCTIONALDATAPROPERTY 61
#define OWL2_FUNCTIONALOBJECTPROPERTY 51
#define OWL2_HASKEY 33
#define OWL2_IMPORT 80
#define OWL2_INVERSEFUNCTIONALOBJECTPROPERTY 52
#define OWL2_INVERSEOBJECTPROPERTIES 83
#define OWL2_IRREFLEXIVEOBJECTPROPERTY 54
#define OWL2_LPAR 3
#define OWL2_NAMEDINDIVIDUAL 45
#define OWL2_NEGATIVEDATAPROPERTYASSERTION 65
#define OWL2_NEGATIVEOBJECTPROPERTYASSERTION 64
#define OWL2_NODEID 10
#define OWL2_OBJECTALLVALUESFROM 71
#define OWL2_OBJECTCOMPLEMENTOF 68
#define OWL2_OBJECTEXACTCARDINALITY 76
#define OWL2_OBJECTHASSELF 73
#define OWL2_OBJECTHASVALUE 72
#define OWL2_OBJECTINTERSECTIONOF 66
#define OWL2_OBJECTINVERSEOF 77
#define OWL2_OBJECTMAXCARDINALITY 75
#define OWL2_OBJECTMINCARDINALITY 74
#define OWL2_OBJECTONEOF 69
#define OWL2_OBJECTPROPERTY 41
#define OWL2_OBJECTPROPERTYASSERTION 38
#define OWL2_OBJECTPROPERTYCHAIN 37
#define OWL2_OBJECTPROPERTYDOMAIN 39
#define OWL2_OBJECTPROPERTYRANGE 40
#define OWL2_OBJECTSOMEVALUESFROM 70
#define OWL2_OBJECTUNIONOF 67
#define OWL2_ONTOLOGY 79
#define OWL2_PREFIX 78
#define OWL2_PREFIXNAME 11
#define OWL2_REFLEXIVEOBJECTPROPERTY 53
#define OWL2_RPAR 4
#define OWL2_SAMEINDIVIDUAL 62
#define OWL2_SUBANNOTATIONPROPERTYOF 14
#define OWL2_SUBCLASSOF 46
#define OWL2_SUBDATAPROPERTYOF 58
#define OWL2_SUBOBJECTPROPERTYOF 48
#define OWL2_SYMMETRICOBJECTPROPERTY 55
#define OWL2_TRANSITIVEOBJECTPROPERTY 57
#define OWL2_languageTag 8
#define OWL2_nonNegativeInteger 6
#define OWL2_quotedString 7
#endif /* __OWL2__H */
