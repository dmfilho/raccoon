#ifndef __RACCOON_IR_KB_H
#define __RACCOON_IR_KB_H

// STL
#include <iterator>
#include <vector>
#include <unordered_map>
#include <array>
// raccoon
#include "Clause.h"
#include "Connection.h"

using namespace std;
namespace raccoon
{
	class ClauseSet
	{
	private:
		vector<Clause*> clauses;
	public:
	
		ClauseSet();
		~ClauseSet();
		
		inline void add(Clause* clause)
		{
			clauses.push_back(clause);
		}
		
		inline void clear()
		{
			clauses.clear();
		}
		
		inline int blockClausesWithPureUniversal()
		{
			int blocked = 0; 
			for (Clause* clause: clauses)
			{
				blocked += clause->blockIfhasPureUniversal();
			}
			return blocked;
		}
		
		inline vector<Clause*>::iterator begin()
		{
			return clauses.begin();
		}
		
		inline vector<Clause*>::iterator end()
		{
			return clauses.end();
		}
		
		inline unsigned int size()
		{
			return clauses.size();
		}
		
		void printClauses();
	};
}

#endif // __RACCOON_IR_KB_H
