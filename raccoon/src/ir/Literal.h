/**
 * raccoon, (Rac)iocinador baseado em (Co)nexões para (On)tologias
 * 			Connection based Reasoner for Ontologies
 * 
 * Copyright (C) 2015 Dimas Melo Filho
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA. 
 * 
 * The author can be reached by e-mail: dldmf@cin.ufpe.br.
 * 
 * \author Dimas Melo Filho <dldmf@cin.ufpe.br>
 * \date 2015-02-17
 * \file
 * This file contains the definition of the Literal class.
 */

#ifndef __RACCOON_IR_LITERAL_H
#define __RACCOON_IR_LITERAL_H

namespace raccoon
{
	class Connection;
}

// STL
#include <string>
#include <vector>
// raccoon
#include "Connection.h"

using namespace std;
namespace raccoon
{
	class Literal
	{
	private:
		/**
		 * Represents the concept name.
		 */
		string _name;
		
		/**
		 * Represents the concept id.
		 */
		unsigned int _id;
		
	public:
		/**
		 * True when the literal is original from the ontology. False when it was created during normalization.
		 */
		bool original;
		
		vector<Connection*> pconn;
		
		vector<Connection*> nconn;
		
		inline void addconn(Connection* conn, bool neg)
		{
			if (neg)
			{
				nconn.push_back(conn);
			}
			else
			{
				pconn.push_back(conn);
			}
		}
		
		inline vector<Connection*> * getconns(bool neg)
		{
			return (neg ? &pconn : &nconn);
		}
		
		/**
		 * Gets the concept name.
		 * \returns the concept name.
		 */
		inline string name() const 
		{ 
			return _name; 
		}
		
		/**
		 * Gets the concept id.
		 * \returns the concept id.
		 */
		inline unsigned int id() const
		{
			return _id;
		}
		
		/**
		 * Returns true when this Literal's id is the same as the given Literal's id.
		 */
		inline bool operator==(const Literal& L) const
		{
			return this->_id == L._id;
		}
		
		/**
		 * Returns true when this Literal's id is different from the given Literal's id.
		 */
		inline bool operator!=(const Literal& L) const
		{
			return this->_id != L._id;
		}
		
		/**
		 * Creates a new concept. The creator should provide the name and id of the concept.
		 * \param name a string containing the name of the concept.
		 * \param id an unsigned int containing the id of the concept.
		 */
		Literal(string& name, unsigned int id);
		
		/**
		 * Destructor. Currently does nothing.
		 */
		~Literal();
	};
}

#endif // __RACCOON_IR_CONCEPT_H
