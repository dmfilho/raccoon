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
 * This file contains the implementation of the Path class.
 */

#include "Path.h"

namespace raccoon
{
	/**
	 * Clears the list of items on the path.
	 */
	void Path::clear()
	{
		this->items.clear();
	}
	
	/**
	 * Tells wether the path contains a specific ILiteralRealization.
	 * \param lit the ILiteralRealization to check for.
	 */
	bool Path::contains(ILiteralRealization* lit)
	{
		for (ILiteralRealization* plit: this->items)
		{
			if (plit->equivalentTo(lit)) return true;
		}
		return false;
	}
	
	/**
	 * Tells wether the path contains the negation of a specific ILiteralRealization.
	 * \param lit the ILiteralRealization to check for.
	 */
	bool Path::containsNegationOf(ILiteralRealization* lit)
	{
		for (ILiteralRealization* plit: this->items)
		{
			if (plit->complementOf(lit)) return true;
		}
		return false;
	}
	
	/**
	 * Push a literal realization to the end of the path
	 */
	void Path::push(ILiteralRealization* lit)
	{
		this->items.push_back(lit);
	}
	
	/**
	 * Pop a literal realization from the end of the path.
	 */
	void Path::pop()
	{
		this->items.pop_back();
	}
	
	/**
	 * Constructor. Currently does nothing.
	 */
	Path::Path()
	{
	}
	
	/**
	 * Destructor. Currently does nothing.
	 */
	Path::~Path()
	{
	}
}

