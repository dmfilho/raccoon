
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
			if (negated) this->pconnections[id] = connList;
			else this->nconnections[id] = connList;
		}
		return connList;
	}
	
	ConnectionList* ClauseSet::cacheConnectionsOf(unsigned int id, bool negated)
	{
		int var1, var2;
		ConnectionList* connList = new ConnectionList();
		for (Clause* clause: this->clauses)
		{
			if (clause->contains(id, !negated, &var1, &var2))
			{
				Connection* conn = new Connection;
				conn->clause = clause;
				conn->var1 = var1;
				conn->var2 = var2;
				connList->insert(conn);
			}
		}
		return connList;
	}
	
	ClauseSet::ClauseSet()
	{
	}

	ClauseSet::~ClauseSet()
	{
		for (auto it = nconnections.begin(); it != nconnections.end(); ++it)
		{
			for (Connection* it2: *(it->second))
			{
				delete it2;
			}
		}
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

