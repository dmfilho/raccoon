/*
 * ElementManager.h
 *
 *  Created on: Apr 12, 2014
 *      Author: Dimas Melo Filho
 */

#ifndef ELEMENTMANAGER_H_
#define ELEMENTMANAGER_H_

namespace rep {
	namespace element {
		enum Type {
			Concept = 0,
			Role = 1,
			Instance = 2,
			NewConcept = 3
		};
	}
}

#include <unordered_map>
#include <vector>
#include <string>
#include "Clause.h"

using namespace std;

namespace rep {
namespace element {

class Manager {
private:
	/**
	 * Counts the number of elements in elementId and elementName.
	 */
	int count;
	/**
	 * Stores the number of the next internal element to be created by
	 * the create method.
	 */
	int createNext;
public:
	/**
	 * Maps each element name to an unique integer id.
	 * Elements can be either concepts, roles or instances.
	 */
	unordered_map<string, int> id;
	/**
	 * List of element names, each index represents the integer identifier, and
	 * maps to a string.
	 */
	vector<string> name;
	/**
	 * List the positive use count of an identifier.
	 */
	vector<int> posUse;
	/**
	 * List the negative use count of an identifier.
	 */
	vector<int> negUse;
	/**
	 * List of connections to the elements (positive and negative).
	 */
	vector<vector<Clause*>*> posConnections;
	vector<vector<Clause*>*> negConnections;
	/**
	 * Default Constructor
	 */
	Manager();
	/**
	 * Destructor
	 */
	virtual ~Manager();
	/**
	 * Adds an element and returns its unique integer identifier.
	 * If the element already exists, it returns the identifier of that element.
	 */
	int add(const string& element, Type type);
	int add(const char* element, Type type);
	/**
	 * Creates a new element, for internal use.
	 * This function is meant to be used during the normalization process.
	 */
	int create();
	/**
	 * Register an usage of the element.
	 */
	void use(int id, Clause* clause);
	/**
	 * Unregister an usage of the element.
	 */
	void disuse(int id, Clause* clause);
	/**
	 * Sort connection lists by pointer address.
	 * After the sort, the connection lists of each element is sorted.
	 */
	void sort();
	/**
	 * Return an element name by id.
	 */
	string& operator[](const int idx);
	/**
	 * Removes a clause from all parts of the manager.
	 */
	void removeClause(Clause* c);

	vector<Clause*>* connections(int id);

};
}
}

#endif /* ELEMENTMANAGER_H_ */
