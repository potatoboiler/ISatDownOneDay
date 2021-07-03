#include <iostream>
#include <sstream> 
#include <fstream>

#include "DIMACS.hpp"

DIMACS::DIMACS(std::string const & filename) {
	using namespace std;

	fstream input;
	input.open(filename, ios_base::in);

	if (input.is_open()) {
		string line;

		int index = 0;
		while (getline(input, line)) {
			if (line.starts_with('c')) { // check for comment line
				continue;
			} else if (line.starts_with('p')) { // check for parameter line
				line = line.substr(6, line.length());

				istringstream iss(line);

				iss >> this->n_vars >> this->n_clauses;

				continue;
			} else { // feed clauses into this->_cnf
				int var;
				istringstream iss(line);

				while (iss >> var) {
					if(var) {
						this->_cnf[index].push_back(var);
					}
				}
				index++;
			}
		}
		input.close();
	}
}

void DIMACS::clear_cnf() noexcept {
	this->_cnf.clear();
	return;
}

void DIMACS::write_to_file(std::string const & filename) const {
	using namespace std;

	// may or may not create file
	fstream output;
	output.open(filename, ios_base::out | ios_base::app);
	
	output << "p cnf " << this->n_vars << " " << this->n_clauses << endl;
	
	for (auto & clause : this->_cnf) {
		for (auto var : clause) {
			output << var << " ";
		}
		output << "0" << endl;
	}

	output.close();
}
void DIMACS::get_vec_cnf(std::vector<std::vector<int>>& cnf) noexcept {
	// I believe this will unconditionally copy the input vector
	// could be made better by moving, but maybe i want to preserve the original vector
	this->_cnf = cnf;
}
