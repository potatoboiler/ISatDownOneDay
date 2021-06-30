#ifndef DIMACStype
#define DIMACStype

#include <vector>
#include <string>

class DIMACS {
public:
	// constructors
	DIMACS () = default;
	DIMACS (std::string const & filename);

	// file i/o
	void clear_cnf() noexcept;
	void write_to_file(std::string const & filename); // writes cnf to file
private:
	unsigned int n_vars = 0;
	unsigned int n_clauses = 0;
	std::vector<std::vector<int>> _cnf{};
};

#endif // DIMACStype
