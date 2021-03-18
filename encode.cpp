#include "main_template.hpp"
#include "lz77.hpp"

int encode(std::istream& in, std::ostream& out)
{
	std::list<Lz77Code> lista;
	std::string str;
	size_t i;

	std::getline(in, str, (char) EOF);

	lista = lz77_encode(str);

	i = 0;

	for (const auto& t : lista)
	{
		out << t;
		if (++i != lista.size())
			out << ' ';
	}
	out << "\n";

	return 0;
}

int main(int argc, char *argv[])
{
	return main_template<encode>(argc, argv);
}
