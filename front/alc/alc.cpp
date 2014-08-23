/*
 * alc.cpp
 *
 *  Created on: Apr 15, 2014
 *      Author: Dimas Melo Filho
 */

#include "alc.h"
#include "../Parser.h"
#include <axe.h>
#include "../axe_utf8.h"
#include "../../ast/Node.h"
#include "../../ast/NodeType.h"
#include <iostream>
#include "../../rep/KB.h"
#include <typeinfo>
#include <fstream>
#include <string>
#include <cerrno>

#ifdef _DEBUG
#define fp(a,b) ((a | r_fail([&](...){ cout << "*FAIL LINE: " << __LINE__ << " POP: " << b << " STACK_SIZE: " << nodes.size() << endl; pop(b); })))
#else
#define fp(a,b) ((a | r_fail([&](...){ pop(b); })))
#endif
namespace front {

Alc::Alc():
lines(0){ }

Alc::~Alc() { }

void Alc::pop(int n) {
	for (int i = 0; i<n; i++) {
		delete nodes.back();
		nodes.pop_back();
	}
}

void Alc::fromFile(const std::string& fileName, rep::KB& kb) {
	std::ifstream in(fileName, std::ios::in | std::ios::binary);
	if (in) {
		std::string text;
		in.seekg(0, std::ios::end);
		text.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&text[0], text.size());
		in.close();
		parse(text, kb);
	}
	in.close();
}

void Alc::parse(std::string& text, rep::KB& kb) {
	using namespace axe;
	using namespace std;
	using namespace ast;
	// TOKENS
	auto semicolon = r_char(';');
	auto newline = r_char('\n') >> e_ref([&](...){ this->lines++; });
	auto space = r_any(" \t\r") | newline;
	auto w = ~space;
	auto lpar = r_char('(');
	auto rpar = r_char(')');
	auto neg = r_char('-');
	auto comma = r_char(',');
	auto dot = r_char('.');
	auto amp = r_char('&');
	auto all = r_char('!');
	auto some = r_char('?');
	auto bar = r_char('|');
	auto lt = r_char('<');
	auto eq = r_char('=');
	auto ATOM = (r_alpha() & *r_alnum()) >>
		e_ref([&](string::iterator i1, string::iterator i2){
			string *s = new string(i1,i2);
			nodes.push_back((Node*)s);
		});
	auto TOP = r_str("$T") >>
		e_ref([&](string::iterator i1, string::iterator i2){
			string *s = new string(i1,i2);
			nodes.push_back((Node*)s);
		});
	auto BOTTOM = r_str("$B") >>
		e_ref([&](string::iterator i1, string::iterator i2){
			string *s = new string(i1,i2);
			nodes.push_back((Node*)s);
		});
	// GRAMMAR
	// LITERAL
	auto LITERAL = TOP | BOTTOM | ATOM;

	// CONCEPT ASSIGNMENT (ABOX)
	auto CONCEPT_ASSIGNMENT = (~neg & LITERAL &w& fp(lpar,1) &w& fp(ATOM,1) &w& fp(rpar,2)) >>
		e_ref([&](string::iterator i1, string::iterator i2){
			Node *instance, *assertion;
			instance = new Node(NodeType::Instance, nodes.back());
			nodes.pop_back();
			assertion = new Node(NodeType::ConceptAssertion, nodes.back(), instance);
			nodes.pop_back();
			nodes.push_back(assertion);
#ifdef _DEBUG
			cout << "C.ASS" << endl;
#endif
		});

	// ROLE ASSIGNMENT (ABOX)
	auto ROLE_ASSIGNMENT = (~neg & LITERAL &w& fp(lpar,1) &w& fp(ATOM,1) &w& fp(comma,2) &w& fp(ATOM,2) &w& fp(rpar,3)) >>
		e_ref([&](string::iterator i1, string::iterator i2){
			Node *instanceX, *instanceY, *assertion;
			instanceY = nodes.back(); nodes.pop_back();
			instanceX = nodes.back(); nodes.pop_back();
			instanceX = new Node(NodeType::Instance, instanceX, instanceY);
			assertion = new Node(NodeType::ConceptAssertion, nodes.back(), instanceX);
			nodes.pop_back();
			nodes.push_back(assertion);
#ifdef _DEBUG
			cout << "R.ASS" << endl;
#endif
		});

	r_rule<string::iterator> ASSIGNMENT;
	// ABOX ASSIGNMENT
	ASSIGNMENT =  ((neg &w& ASSIGNMENT) >>
		e_ref([&](string::iterator i1, string::iterator i2){
			Node *c1, *n;
			c1 = nodes.back(); nodes.pop_back();
			n = new Node(NodeType::Negation, c1);
			nodes.push_back(n);
#ifdef _DEBUG
			cout << "NEG.ASSIGNMENT" << endl;
#endif
		}))
			| CONCEPT_ASSIGNMENT
			| ROLE_ASSIGNMENT;

	// ROLE
	auto ROLE = ATOM >>
		e_ref([&](string::iterator i1, string::iterator i2){
			Node *str, *r1;
			str = nodes.back(); nodes.pop_back();
			r1 = new Node(NodeType::Role, str);
			nodes.push_back(r1);
#ifdef _DEBUG
			cout << "ROLE " << (string&)*str << endl;
#endif
		});

	auto SIMPLE_CONCEPT = (LITERAL) >>
		e_ref([&](string::iterator i1, string::iterator i2){
			Node *str, *c1;
			str = nodes.back(); nodes.pop_back();
			c1 = new Node(NodeType::Concept, str);
			nodes.push_back(c1);
#ifdef _DEBUG
			cout << "SIMPLE_CONCEPT " << (string&) *str << endl;
#endif
		});

	// CONCEPT (and CONCEPTR to avoid left recursion)
	r_rule<string::iterator> CONCEPT;
	r_rule<string::iterator> CONCEPTR;
	// CONJUNCTION
	CONCEPTR = (w& amp &w& CONCEPT & fp(CONCEPTR,1)) >>
		e_ref([&](string::iterator i1, string::iterator i2){
			Node *c1, *c2, *conj;
			c2 = nodes.back(); nodes.pop_back();
			c1 = nodes.back(); nodes.pop_back();
			conj = new Node(NodeType::Conjunction, c1, c2);
			nodes.push_back(conj);
#ifdef _DEBUG
			cout << "CONJ" << endl;
#endif
		})
	// DISJUNCTION
		| (w& bar &w& CONCEPT & fp(CONCEPTR,1)) >>
			e_ref([&](string::iterator i1, string::iterator i2){
				Node *c1, *c2, *disj;
				c2 = nodes.back(); nodes.pop_back();
				c1 = nodes.back(); nodes.pop_back();
				disj = new Node(NodeType::Disjunction, c1, c2);
				nodes.push_back(disj);
#ifdef _DEBUG
				cout << "DISJ" << endl;
#endif
			})
		| r_empty();

	CONCEPT =
	// CONCEPT BETWEEN PARENTHESIS
			((lpar &w& CONCEPT &w& fp(rpar,1)) >>
		e_ref([&](string::iterator i1, string::iterator i2){
#ifdef _DEBUG
		cout << "PAREN" << endl;
#endif
		}) & fp(CONCEPTR,1))
	// LITERAL AS CONCEPT
			| (SIMPLE_CONCEPT & fp(CONCEPTR,1))
	// ALL WITH SIMPLE CONCEPT
			| ((all &w& ROLE &w& fp(dot,1) &w& fp(SIMPLE_CONCEPT,1)) >>
		e_ref([&](string::iterator i1, string::iterator i2){
			Node *c1, *r1, *q;
			c1 = nodes.back(); nodes.pop_back();
			r1 = nodes.back(); nodes.pop_back();
			q = new Node(NodeType::All, r1, c1);
			nodes.push_back(q);
#ifdef _DEBUG
			cout << "ALL.SIMPLE" << endl;
#endif
		}) & fp(CONCEPTR,2))
	// ALL WITH COMPLEX CONCEPT
			| ((all &w& ROLE &w& fp(dot,1) &w& fp(lpar,1) &w& fp(CONCEPT,1) &w& fp(rpar,2)) >>
		e_ref([&](string::iterator i1, string::iterator i2){
			Node *c1, *r1, *q;
			c1 = nodes.back(); nodes.pop_back();
			r1 = nodes.back(); nodes.pop_back();
			q = new Node(NodeType::All, r1, c1);
			nodes.push_back(q);
#ifdef _DEBUG
			cout << "ALL.COMPLEX" << endl;
#endif
		}) & fp(CONCEPTR,2))
	// SOME WITH SIMPLE CONCEPT
			| ((some &w& ROLE &w& fp(dot,1) &w& fp(SIMPLE_CONCEPT,1)) >>
		e_ref([&](string::iterator i1, string::iterator i2){
			Node *c1, *r1, *q;
			c1 = nodes.back(); nodes.pop_back();
			r1 = nodes.back(); nodes.pop_back();
			q = new Node(NodeType::Some, r1, c1);
			nodes.push_back(q);
#ifdef _DEBUG
			cout << "SOME.SIMPLE" << endl;
#endif
		}) & fp(CONCEPTR,2))
	// SOME WITH COMPLEX CONCEPT
			| ((some &w& ROLE &w& fp(dot,1) &w& fp(lpar,1) &w& fp(CONCEPT,1) &w& fp(rpar,2)) >>
		e_ref([&](string::iterator i1, string::iterator i2){
			Node *c1, *r1, *q;
			c1 = nodes.back(); nodes.pop_back();
			r1 = nodes.back(); nodes.pop_back();
			q = new Node(NodeType::Some, r1, c1);
			nodes.push_back(q);
#ifdef _DEBUG
			cout << "SOME.COMPLEX" << endl;
#endif
		}) & fp(CONCEPTR,2))
	// NEGATION OF SIMPLE CONCEPT
			| ((neg &w& SIMPLE_CONCEPT) >>
		e_ref([&](string::iterator i1, string::iterator i2){
			Node *c1, *n;
			c1 = nodes.back(); nodes.pop_back();
			n = new Node(NodeType::Negation, c1);
			nodes.push_back(n);
#ifdef _DEBUG
			cout << "NEG.SIMPLE" << endl;
#endif
		}) & fp(CONCEPTR,1))
	// NEGATION OF COMPLEX CONCEPT
			| ((neg &w& lpar &w& CONCEPT &w& fp(rpar,1)) >>
		e_ref([&](string::iterator i1, string::iterator i2){
			Node *c1, *n;
			c1 = nodes.back(); nodes.pop_back();
			n = new Node(NodeType::Negation, c1);
			nodes.push_back(n);
#ifdef _DEBUG
			cout << "NEG.COMPLEX" << endl;
#endif
		}) & fp(CONCEPTR,1));

	// INCLUSION
	auto INCLUSION = (CONCEPT &w& fp(lt,1) &w& fp(CONCEPT,1)) >>
		e_ref([&](string::iterator i1, string::iterator i2){
			Node *c1, *c2, *incl;
			c2 = nodes.back(); nodes.pop_back();
			c1 = nodes.back(); nodes.pop_back();
			incl = new Node(NodeType::Inclusion, c1, c2);
			nodes.push_back(incl);
#ifdef _DEBUG
			cout << "INCLUSION" << endl;
#endif
		});

	// EQUIVALENCE
	auto EQUIVALENCE = (CONCEPT &w& fp(eq,1) &w& fp(CONCEPT,1)) >>
		e_ref([&](string::iterator i1, string::iterator i2){
			Node *c1, *c2, *equiv;
			c2 = nodes.back(); nodes.pop_back();
			c1 = nodes.back(); nodes.pop_back();
			equiv = new Node(NodeType::Equivalence, c1, c2);
			nodes.push_back(equiv);
#ifdef _DEBUG
			cout << "EQUIVALENCE" << endl;
#endif
		});

	// GCI
	auto GCI = INCLUSION | EQUIVALENCE;

	// AXIOM
	auto AXIOM = (w& (GCI | ASSIGNMENT) &w& fp(semicolon,1)) >>
		e_ref([&](string::iterator i1, string::iterator i2){
			Node *axiom = nodes.back(); nodes.pop_back();
			kb.add(axiom, true);
#ifdef _DEBUG
			cout << "*AXIOM this:" << axiom << " Type:" << axiom->type << endl;
#endif
			delete axiom;
		});

	// EMPTY LINE
	auto EMPTY_LINE = (w & semicolon);
	auto KB = w& +(AXIOM | EMPTY_LINE);
	KB(text.begin(),text.end());

}

} /* namespace front */
