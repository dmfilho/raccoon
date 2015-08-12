#ifndef __RACCOON_IR_CONNECTIONLIST_H
#define __RACCOON_IR_CONNECTIONLIST_H

// STL
#include <unordered_set>
// raccoon
#include "Clause.h"

using namespace std;
namespace raccoon
{
	typedef struct _Connection
	{
		Clause* clause;
		int var1;
		int var2;
	} Connection;
	
	class ConnectionList
	 : public unordered_set<Connection*>
	{
	};
}

#endif // __RACCOON_IR_CONNECTIONLIST_H
