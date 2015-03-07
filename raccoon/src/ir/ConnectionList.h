#ifndef __RACCOON_IR_CONNECTIONLIST_H
#define __RACCOON_IR_CONNECTIONLIST_H

// STL
#include <unordered_set>
// raccoon
#include "Clause.h"

using namespace std;
namespace raccoon
{
	class ConnectionList
	 : public unordered_set<Clause*>
	{
	public:
		ConnectionList();
		~ConnectionList();
	};
}

#endif // __RACCOON_IR_CONNECTIONLIST_H
