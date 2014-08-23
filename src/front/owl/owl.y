%start DOCUMENT

%token TOKEN_PREFIX

%{
	#include <cstdlib>
	#include <iostream>
	#include "ASTNode.h"
	#include "defs.h"

	extern "C" int yylex();
	extern "C" int yyparse();
	void yyerror(const char *s);
	#include "KB.h"
	#include "DLTree.h"
%}
%left '|'
%left '&'
%left '!'
%left '?'
%left '.'

%error-verbose

%%

DOCUMENT : PREFIXES ONTOLOGY
PREFIXES : PREFIX PREFIXES 
		 | %empty
PREFIX : TOKEN_PREFIX '(' PREFIX_NAME '=' TOKEN_FULL_IRI ')'
PREFIX_NAME : ':'
			| PN_PREFIX ':'
PN_PREFIX : 

KB : GCI	 										{ DL::addClause($1); }
   | ASSIGNMENT 									{ DL::addClause($1); }
   | %empty											{ DL::empty(); }
GCI : CONCEPT '<' CONCEPT 							{ $$ = DL::subsumption($1, $3); }
	| CONCEPT '=' CONCEPT 							{ $$ = DL::equivalence($1, $3); }
CONCEPT : '!' ROLE '.' CONCEPT						{ $$ = DL::all($2, $4); }
		| '?' ROLE '.' CONCEPT						{ $$ = DL::some($2, $4); }
		| '-' CONCEPT								{ $$ = DL::negation($2); }
		| CONCEPT '&' CONCEPT 						{ $$ = DL::conjunction($1,$3); }
		| CONCEPT '|' CONCEPT 						{ $$ = DL::disjunction($1,$3); }
		| '(' CONCEPT ')'							{ $$ = $2; }
		| TOKEN_IDENT								{ $$ = DL::concept($1); }
ROLE : TOKEN_IDENT									{ $$ = DL::role($1); }
ASSIGNMENT : '-' ASSIGNMENT							{ $$ = DL::negation($2); }
		   | TOKEN_IDENT '(' TOKEN_IDENT ')'		{ $$ = DL::assignConcept($1, $3); }
		   | TOKEN_IDENT '(' TOKEN_IDENT ',' TOKEN_IDENT ')' { $$ = DL::assignRole($1,$3,$5); }
%%

void yyerror(const char *s) {
	std::cout << "Erro de Análise (Linha " << DL::line << "):" << s << std::endl;
	std::exit(-1);
}


#include "Matrix.h"	
#include "Reasoner.h"
#include "Options.h"
#include "Reduction.h"
#include "connDL.yy.cc"
#include "main.cc"
