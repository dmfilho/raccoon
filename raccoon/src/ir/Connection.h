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
		bool universal;
		
		/**
		 * \brief Creates a new connection object.
		 * @param _clause The connection clause
		 * @param _var1 The first connected variable
		 * @param _var2 The second connected variable
		 * @param _universal true when this is connecting to an universal restriction.
		 * @return 
		 */
		Connection(Clause* _clause, int _var1, int _var2, bool _universal)
		 : clause(_clause)
		 , var1(_var1)
		 , var2(_var2)
		 , universal(_universal)
		{
		}
	};
}

#endif // __RACCOON_IR_CONNECTION_H
