#include "main_template.hpp"

int decode(std::istream& in, std::ostream& out)
{
	std::list<Lz77Code> code;
	Lz77Code t;

	while (in >> t)
		code.push_back(t);

	out << lz77_decode(code) << '\n';

	return 0;
}

int main(int argc, char *argv[])
{
	return main_template<decode>(argc, argv);
}
