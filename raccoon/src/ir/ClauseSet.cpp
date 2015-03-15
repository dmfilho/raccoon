
// STL
#include <iostream>
#include <unordered_map>
// raccoon
#include "ClauseSet.h"

using namespace std;
namespace raccoon
{	
	ConnectionList* ClauseSet::getConnections(unsigned int id, bool negated)
	{
		ConnectionList* connList = nullptr;
		try
		{
			connList = (negated ? this->pconnections.at(id) : this->nconnections.at(id));
		}
		catch (out_of_range ex)
		{
			connList = this->cacheConnectionsOf(id, negated);
		}
		return connList;
	}
	
	ConnectionList* ClauseSet::cacheConnectionsOf(unsigned int id, bool negated)
	{
		ConnectionList* connList = new ConnectionList();
		for (Clause* clause: this->clauses)
		{
			if (clause->contains(id, !negated))
			{
				connList->insert(clause);
			}
		}
		return connList;
	}
	
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
			for (auto concept: c->concepts)
			{
				if (concept->neg) 
				{
					cout << '-';
				}
				cout << concept->concept.name() << ", ";
			}
			for (auto role: c->roles)
			{
				if (role->neg)
				{
					cout << '-';
				}
				cout << role->role.name();
			}
			for (auto universal: c->universals)
			{
				cout << '[';
				if (universal->concept.neg)
				{
					cout << '-';
				}
				cout << universal->concept.concept.name() << " | ";
				if (universal->role.neg)
				{
					cout << '-';
				}
				cout << universal->role.role.name() << "], ";
			}
			cout << endl;
		}	
		cout << flush;
	}
}

