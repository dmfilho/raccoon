
// STL
#include <iostream>
#include <unordered_map>
// raccoon
#include "ClauseSet.h"

using namespace std;
namespace raccoon
{	
	
	ClauseSet::ClauseSet()
	{
	}

	ClauseSet::~ClauseSet()
	{
		for (Clause* c: clauses)
		{
			delete c;
		}
		clauses.clear();
	}
	
	void ClauseSet::printClauses()
	{
		for (auto c: this->clauses)
		{
			c->print();
			cout << endl;
		}	
		cout << flush;
	}
}

