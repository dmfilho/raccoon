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
	public:
		unsigned int instanceCount;
		unsigned int conceptCount;
		unsigned int roleCount;
		unsigned int newInstanceCount;
		unsigned int newConceptCount;
		unsigned int newRoleCount;
		unsigned int skolemInstanceCount;
		
		ClauseSet clauseSet;
		unordered_map<string, Instance*> instances;
		unordered_map<string, Literal*> concepts;
		unordered_map<string, Literal*> roles;
		unordered_map<unsigned int, Instance*> instancesById;
		unordered_map<unsigned int, Literal*> conceptsById;
		unordered_map<unsigned int, Literal*> rolesById;

		void pureReduction();
		/**
		 * Asserts that an instance is on the ontology instance map.
		 * If it is not, it gets added to it.
		 * \param name the name of the instance.
		 * \return the id of the existing instance, or the id of the newly mapped instance.
		 */
		Instance& assertInstance(string& name);
		Instance& assertInstance(const char* name);
		Instance& newUniqueInstance();
		Literal& assertConcept(string& name);
		Literal& assertConcept(const char* name);
		Literal& assertRole(string& name);
		Literal& assertRole(const char* name);
		Literal& newConcept();
		Literal& newRole();
		
		Ontology()
		 : instanceCount(0)
		 , conceptCount(0)
		 , roleCount(0)
		 , newInstanceCount(0)
		 , newConceptCount(0)
		 , newRoleCount(0)
		 , skolemInstanceCount(0)
		{
            assertConcept("owl:Thing");
            assertConcept("owl:Nothing");
		}
		
		~Ontology()
		{
		}
	};
}

#endif // __RACCOON_IR_ONTOLOGY_H
