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
 * This file contains the declaration of the Path class.
 */

#ifndef __RACCOON_IR_PATH_H
#define __RACCOON_IR_PATH_H

// STL
#include <vector>
// raccoon
#include "ILiteralRealization.h"

using namespace std;
namespace raccoon
{
	class Path
	{
	private:
		/**
		 * Contains the list of items on the path.
		 * Each item is a pointer to a ILiteralRealization.
		 * The path does NOT own the pointers, thus it is not responsible for calling their destructors.
		 */
		vector<ILiteralRealization*> items;
		
	public:		
		/**
		 * Clears the list of items on the path.
		 */
		void clear();
		
		/**
		 * Tells wether the path contains a specific ILiteralRealization.
		 * \param lit the ILiteralRealization to check for.
		 */
		bool contains(ILiteralRealization* lit);
		
		/**
		 * Tells wether the path contains the negation of a specific ILiteralRealization.
		 * \param lit the ILiteralRealization to check for.
		 */
		bool containsNegationOf(ILiteralRealization* lit);
		
		/**
		 * Push a literal realization to the end of the path
		 */
		void push(ILiteralRealization* lit);
		
		/**
		 * Pop a literal realization from the end of the path.
		 */
		void pop();
		
		/**
		 * Print the current path.
		 */
		void print();
		
		/**
		 * Constructor. Currently does nothing.
		 */
		Path();
		
		/**
		 * Destructor. Currently does nothing.
		 */
		~Path();
	};
}

#endif // __RACCOON_IR_PATH_H
