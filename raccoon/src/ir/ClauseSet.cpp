#include <unordered_map>
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
}

