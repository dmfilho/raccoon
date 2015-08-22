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
 * This file contains the implementation of the Literal class.
 */
 
// STL
#include <string>
// raccoon
#include "Literal.h"
#include "Clause.h"

using namespace std;
namespace raccoon
{
	
	/**
	 * \brief Block all clauses containing this literal.
	 */
	int Literal::block()
	{
		int cblock = 0;
		static vector<Connection*> vconn;
		for (Connection* conn: pconn)
		{
			if (!conn->universal)
			{
				vconn.push_back(conn);
				++cblock;
			}
		}
		for (Connection* conn: nconn)
		{
			if (!conn->universal)
			{
				vconn.push_back(conn);
				++cblock;
			}
		}
		while (vconn.size() > 0)
		{
			Connection* conn = vconn.back();
			vconn.pop_back();
			conn->clause->block();
		}
		return cblock;
	}
	
	list<Connection*>::iterator Literal::addconn(Connection* conn, bool neg, bool hasInstance)
	{
		if (neg)
		{
			if (hasInstance)
			{
				nconn.push_front(conn);
				return nconn.begin();
			}
			else
			{
				nconn.push_back(conn);
				return --nconn.end();
			}
		}
		else
		{
			if (hasInstance)
			{
				pconn.push_front(conn);
				return pconn.begin();
			}
			else
			{
				pconn.push_back(conn);
				return --pconn.end();
			}
		}
	}
	
	void Literal::delconn(list<Connection*>::iterator conn_it, bool neg)
	{
		if (neg)
		{
			nconn.erase(conn_it);
		}
		else
		{
			pconn.erase(conn_it);
		}
	}
	
	/**
	 * Creates a new concept. The creator should provide the name and id of the concept.
	 * \param name a string containing the name of the concept.
	 * \param id an unsigned int containing the id of the concept.
	 */
	Literal::Literal(string& name, unsigned int id)
	 : _name(name)
	 , _id(id)
	 , original(true)
	{
	}

	/**
	 * Destructor. Currently does nothing.
	 */
	Literal::~Literal()
	{
	}
}

