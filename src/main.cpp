/*
 * main.cpp
 *
 *  Created on: Apr 13, 2014
 *      Author: Dimas Melo Filho
 */

#include "front/alc/alc.h"
#include "rep/KB.h"
#include "back/fm1/fm1.h"
#include "util/exit_codes.h"
#include <string>
#include <axe.h>
#include <iostream>
#include <iterator>
#include <sstream>

using namespace std;

int main(int argc, char* argv[]) {
	rep::KB kb;
	front::Alc alcParser;
	if (argc < 2) {
		cout << "Use: raccoon <file.dl>" << endl << "\t file.dl is a knowledge base with a query." << endl << endl;
		return EXIT_WRONG_USAGE;
	}
	alcParser.fromFile(argv[1], kb);
	kb.printCSV(cout);
	back::fm1* reasoner = new back::fm1();
	cout << "CONSISTENCY: " << (reasoner->Consistency(kb) == 1 ? "INCONSISTENT" : "CONSISTENT") << endl;
	delete reasoner;
}


