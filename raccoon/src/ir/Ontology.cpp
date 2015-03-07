
// STL
#include <sstream>
// raccoon
#include "Literal.h"
#include "Ontology.h"


namespace raccoon
{
	/**
	 * Asserts that an instance is on the ontology instance map.
	 * If it is not, it gets added to it.
	 * \param name the name of the instance.
	 * \return the id of the existing instance, or the id of the newly mapped instance.
	 */
	Instance& Ontology::assertInstance(string& name)
	{
		auto search = instances.find(name);
		unsigned int id;
		if (search == instances.end())
		{
			id = instanceCount++;
			Instance* instance = new Instance(name, id);
			instances[name] = instance;
			instancesById[id] = instance;
			return *instance;
		}
		else
		{
			return *reinterpret_cast<Instance*>(search->second);
		}
	}
	
	/**
	 * Asserts that an instance is on the ontology instance map.
	 * If it is not, it gets added to it.
	 * \param name the name of the instance.
	 * \return the id of the existing instance, or the id of the newly mapped instance.
	 */
	Instance& Ontology::assertInstance(char* name)
	{
		string strName(name);
		return assertInstance(strName);
	}
	
	/**
	 * Asserts that a concept is on the ontology concept map.
	 * If it is not, it gets added to it.
	 * \param name the name of the concept.
	 * \return the id of the existing concept, or the id of the newly mapped concept.
	 */
	Literal& Ontology::assertConcept(string& name)
	{
		auto search = concepts.find(name);
		unsigned int id;
		if (search == concepts.end())
		{
			id = conceptCount++;
			Literal* concept = new Literal(name, id);
			concepts[name] = concept;
			conceptsById[id] = concept;
			return *concept;
		}
		else
		{
			return *reinterpret_cast<Literal*>(search->second);
		}
	}
	
	/**
	 * Asserts that a concept is on the ontology concept map.
	 * If it is not, it gets added to it.
	 * \param name the name of the concept.
	 * \return the id of the existing concept, or the id of the newly mapped concept.
	 */
	Literal& Ontology::assertConcept(char* name)
	{
		string strName(name);
		return assertConcept(strName);
	}
	
	/**
	 * Asserts that a role is on the ontology role map.
	 * If it is not, it gets added to it.
	 * \param name the name of the role.
	 * \return the id of the existing role, or the id of the newly mapped role.
	 */
	Literal& Ontology::assertRole(string& name)
	{
		auto search = roles.find(name);
		unsigned int id;
		if (search == roles.end())
		{
			id = roleCount++;
			Literal* role = new Literal(name, id);
			roles[name] = role;
			rolesById[id] = role;
			return *role;
		}
		else
		{
			return *reinterpret_cast<Literal*>(search->second);
		}
	}
	
	/**
	 * Asserts that a role is on the ontology role map.
	 * If it is not, it gets added to it.
	 * \param name the name of the role.
	 * \return the id of the existing role, or the id of the newly mapped role.
	 */
	Literal& Ontology::assertRole(char* name)
	{
		string strName(name);
		return assertRole(strName);
	}
	
	/**
	 * Creates an unique new Concept.
	 */
	Literal& Ontology::newConcept()
	{
		stringstream s;
		s << "$RC_" << conceptCount++;
		string conceptName = s.str();
		return assertConcept(conceptName);
	}
	
	/**
	 * Creates an unique new Role.
	 */
	Literal& Ontology::newRole()
	{
		stringstream s;
		s << "$RC_" << roleCount++;
		string roleName = s.str();
		return assertRole(roleName);
	}
}

