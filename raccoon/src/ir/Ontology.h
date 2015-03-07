#ifndef __RACCOON_IR_ONTOLOGY_H
#define __RACCOON_IR_ONTOLOGY_H

// STL
#include <string>
#include <unordered_map>
// raccoon
#include "ClauseSet.h"
#include "Instance.h"
#include "Literal.h"

using namespace std;
namespace raccoon
{
	class Ontology
	{
	private:
		unsigned int instanceCount;
		unsigned int conceptCount;
		unsigned int roleCount;
	public:
		ClauseSet clauseSet;
		unordered_map<string, Instance*> instances;
		unordered_map<string, Literal*> concepts;
		unordered_map<string, Literal*> roles;
		unordered_map<unsigned int, Instance*> instancesById;
		unordered_map<unsigned int, Literal*> conceptsById;
		unordered_map<unsigned int, Literal*> rolesById;
		
		/**
		 * Asserts that an instance is on the ontology instance map.
		 * If it is not, it gets added to it.
		 * \param name the name of the instance.
		 * \return the id of the existing instance, or the id of the newly mapped instance.
		 */
		Instance& assertInstance(string& name);
		Instance& assertInstance(char* name);
		Literal& assertConcept(string& name);
		Literal& assertConcept(char* name);
		Literal& assertRole(string& name);
		Literal& assertRole(char* name);
		Literal& newConcept();
		Literal& newRole();
		
		Ontology()
		 : instanceCount(0)
		 , conceptCount(0)
		 , roleCount(0)
		{
		}
		
		~Ontology()
		{
		}
	};
}

#endif // __RACCOON_IR_ONTOLOGY_H
