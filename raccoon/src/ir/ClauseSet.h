#ifndef __RACCOON_IR_KB_H
#define __RACCOON_IR_KB_H

// STL
#include <iterator>
#include <vector>
#include <unordered_map>
#include <array>
// raccoon
#include "Clause.h"
#include "ConnectionList.h"

using namespace std;
namespace raccoon
{
	class ClauseSet
	{
	private:
		vector<Clause*> clauses;
		unordered_map<unsigned int, ConnectionList*> pconnections;
		unordered_map<unsigned int, ConnectionList*> nconnections;
	public:
		ConnectionList* getConnections(unsigned int id, bool negated);
		ConnectionList* cacheConnectionsOf(unsigned int id, bool negated);
	
		ClauseSet();
		~ClauseSet();
		
		inline void add(Clause* clause)
		{
			clauses.push_back(clause);
		}
		
		inline vector<Clause*>::iterator begin()
		{
			return clauses.begin();
		}
		
		inline vector<Clause*>::iterator end()
		{
			return clauses.end();
		}
	};
}

#endif // __RACCOON_IR_KB_H
