#ifndef __RACCOON_IR_CONNECTION_H
#define __RACCOON_IR_CONNECTION_H

// raccoon

using namespace std;
namespace raccoon
{
	class Clause;
	
	class Connection
	{
		public:
		Clause* clause;
		int var1;
		int var2;
		
		Connection(Clause* _clause, int _var1, int _var2)
		 : clause(_clause)
		 , var1(_var1)
		 , var2(_var2)
		{
		}
	};
}

#endif // __RACCOON_IR_CONNECTION_H
