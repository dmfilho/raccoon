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
 * \date 2015-08-18
 * \file
 * This file contains the implementation of the Options Class. The Options class is responsible for parsing the command
 * line options and displaying help information to the user.
 */
 
// STL
#include <string>
#include <iostream>
#include <cstring>
// raccoon
#include "Options.h"

#define no_argument 0
#define required_argument 1

static const char* optopt = NULL;
static const char* optarg = NULL;

/**
 * \brief Implementation of getopt_long for compatibility with other Operating systems
 * \param argc number of elements on argv
 * \param argv list of arguments
 * \param opt the option structure array
 * \param opt_index (out) the index of the matched option.
 * @return the code of the matched option, '?' if some error happened or -1 if end of arguments was reached.
 */
int _getopt_long(int argc, const char* argv[], const struct option *opt, int *opt_index)
{
	static int a = 1;
	const struct option *copt = opt;
	int len;
	
	if (a >= argc)
	{
		return -1;
	}
	optopt = argv[a++];
	len = strlen(optopt);
	if (len <= 1 || *optopt != '-' || opt == NULL)
	{
		return '?';
	}
	++optopt;
	if (*optopt == '-') {
		++optopt;
		// full argument name
		*opt_index = 0;
		while (copt->name != 0)
		{
			if (strcmp(optopt, copt->name) == 0)
			{
				if (copt->has_arg)
				{
					if (a >= argc)
					{
						return '?';
					}
					optarg = argv[a++];
					return copt->val;
				} else {
					optarg = NULL;
					return copt->val;
				}				
			}
			++copt;
			++(*opt_index);
		}
	} else {
		// short argument name
		*opt_index = 0;
		while (copt->name != 0)
		{
			if (*optopt == (int) copt->val)
			{
				if (copt->has_arg)
				{
					if (a >= argc)
					{
						return '?';
					}
					optarg = argv[a++];
					return copt->val;
				} else {
					optarg = NULL;
					return copt->val;
				}				
			}
			++copt;
			++(*opt_index);
		}
	}
	return '?';
}

using namespace std;
namespace raccoon 
{
	struct option Options::long_options[] = {
		{"help",    no_argument,       0, 'h'},
		{"input",   required_argument, 0, 'i'},
		{"version", no_argument,       0,  0},
		{"warranty",no_argument,       0,  0},
		{"command", required_argument, 0, 'c'},
		{"quiet",   no_argument,       0, 'q'},
		{"reasoner",required_argument, 0, 'r'},
		{"pure",    no_argument,       0, 'p'},
		{0,	        0,                 0,  0}
	};
	
	Options::Options(int argc, const char* argv[])
	 : inputFileName(nullptr)
	 , command(invalid_command)
	 , reasoner(cmalc_rp)
	 , writeGetSymbolNameMethod(false)
	 , valid(true)
	 , quiet(false)
	 , pure(false)
	{
		int c;
		int opt_index;
		while ((c = _getopt_long(argc, argv, long_options, &opt_index)) != -1) 
		{
			switch (c) 
			{
			case 0:
				switch (opt_index) 
				{
				case 2: // version
					this->printVersion();
					return;
				case 3: // warranty
					this->printWarranty();
					return;
				}
				break;
			case 'i': // input
				this->inputFileName = new string(optarg);
				break;
			case 'h': // help
				this->printHelp();
				return;
			case 'c': // command
				if (strcmp(optarg, "consistency") == 0)
				{
					this->command = OptionCmd::consistency;
				}
				else if (strcmp(optarg, "classification") == 0)
				{
					this->command = OptionCmd::classification;
				}
				else if (strcmp(optarg, "realization") == 0)
				{
					this->command = OptionCmd::realization;
				}
				else if (strcmp(optarg, "info") == 0)
				{
					this->command = OptionCmd::info;
				}
				else if (strcmp(optarg, "matrix") == 0)
				{
					this->command = OptionCmd::matrix;
				}
				else 
				{
					cout << "Unknown command '" << optarg << "'." << endl;
					this->printHelp();
					return;
				}
				break;
			case 'q': // quiet
				this->quiet = true;
				break;
			case 'r': // reasoner (select a different reasoner)
				if (strcmp(optarg, "CMALCr") == 0)
				{
					this->reasoner = OptionReasoner::cmalc_r;
				}
				else if (strcmp(optarg, "CMALCrp") == 0)
				{
					this->reasoner = OptionReasoner::cmalc_rp;
				}
				else
				{
					cout << "Unknown reasoner '" << optarg << "'." << endl;
					this->printHelp();
					return;
				}
				break;
			case 'p': // enable pure reduction
				pure = true;
				break;
			case '?': // something is wrong
				if (strcmp(optopt,"i") == 0) 
				{
					cout << "The --input option requires a parameter (the input file name)." << endl;
				} 
				else if (strcmp(optopt,"c") == 0)
				{
					cout << "The --command option requires a parameter (the command/task name to execute)." << endl;
				}
				else if (strcmp(optopt,"r") == 0)
				{
					cout << "The --reasoner option requires a parameter (the name of the reasoner).\n"
							"Nonetheless, this option is not required to run the reasoner, try ignoring this option.\n";
				}
				else 
				{
					cout << "Unknown option '" << optopt << "'." << endl;
				}
				this->printHelp();
				return;
			}
		}
		if (this->inputFileName == nullptr)
		{
			cout << "You MUST specify an input file with the -i option." << endl;
			this->printHelp();
			return;
		}
		if (this->command == OptionCmd::invalid_command)
		{
			cout << "Invalid parameter" << endl;
			this->printHelp();
			return;
		}
	}

	Options::~Options() 
	{
		if (inputFileName != NULL) 
		{ 
			delete inputFileName;
		}
	}

	void Options::printHelp() 
	{
		cout << 
		"Usage: raccoon -i <input_file> -c <command> [options]\n"
		"Options:\n"
		"  -h, --help               display this help information.\n"
		"  -i, --input FILENAME     the input file.\n"
		"  -c, --command CMD        perform the CMD action.\n"
		"                           CMD can be one of the following:\n"
		"                           * consistency\n"
		"                           * classification\n"
		"                           * realization\n"
		"                           * info\n"
		"                           * matrix\n\n"
		"  -r, --reasoner REASONER  use the selected REASONER.\n"
		"                           REASONER can be one of the following:\n"
		"                           * CMALCr - CM-ALC with regularity.\n"
		"                           * CMALCrp - CM-ALC with regularity and PURE reduciton.\n"
		"  -q, --quiet              Do not display any information but the result itself.\n"
		"  -p, --pure               Enable PURE reduction.\n"
		"      --version            display the program's version information.\n\n";		
		this->valid = false;
	}
	
	void Options::printVersion()
	{
		cout << 
		"raccoon 0.1.5\n"
		"Copyright (C) 2017 Dimas Melo Filho.\n"
		"raccoon comes with ABSOLUTELY NO WARRANTY; for details\n"
		"run raccoon --warranty. This is free software, and you are\n"
		"welcome to redistribute it under certain conditions;\n"
		"check <http://www.gnu.org/licenses/gpl-2.0.html> for details.\n\n";
		this->valid = false;
	}
	
	void Options::printWarranty()
	{
		cout <<
		"BECAUSE THE PROGRAM IS LICENSED FREE OF CHARGE, THERE IS NO\n"
		"WARRANTY FOR THE PROGRAM, TO THE EXTENT PERMITTED BY\n"
		"APPLICABLE LAW. EXCEPT WHEN OTHERWISE STATED IN WRITING THE\n"
		"COPYRIGHT HOLDERS AND/OR OTHER PARTIES PROVIDE THE PROGRAM\n"
		"\"AS IS\" WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR\n"
		"IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED\n"
		"WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR\n"
		"PURPOSE. THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE\n"
		"OF THE PROGRAM IS WITH YOU. SHOULD THE PROGRAM PROVE\n"
		"DEFECTIVE, YOU ASSUME THE COST OF ALL NECESSARY SERVICING,\n"
		"REPAIR OR CORRECTION.\n\n"
		"IN NO EVENT UNLESS REQUIRED BY APPLICABLE LAW OR AGREED TO\n"
		"IN WRITING WILL ANY COPYRIGHT HOLDER, OR ANY OTHER PARTY\n"
		"WHO MAY MODIFY AND/OR REDISTRIBUTE THE PROGRAM AS PERMITTED\n"
		"ABOVE, BE LIABLE TO YOU FOR DAMAGES, INCLUDING ANY GENERAL,\n"
		"SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES ARISING OUT OF\n"
		"THE USE OR INABILITY TO USE THE PROGRAM (INCLUDING BUT NOT\n"
		"LIMITED TO LOSS OF DATA OR DATA BEING RENDERED INACCURATE\n"
		"OR LOSSES SUSTAINED BY YOU OR THIRD PARTIES OR A FAILURE OF\n"
		"THE PROGRAM TO OPERATE WITH ANY OTHER PROGRAMS), EVEN IF\n"
		"SUCH HOLDER OR OTHER PARTY HAS BEEN ADVISED OF THE\n"
		"POSSIBILITY OF SUCH DAMAGES.\n\n"
		"Check <http://www.gnu.org/licenses/gpl-2.0.html> for details.\n\n";
		this->valid = false;
	}

} /* namespace raccoon */
