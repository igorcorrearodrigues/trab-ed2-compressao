#ifndef MAIN_TEMPLATE_HPP
#define MAIN_TEMPLATE_HPP

#include <iostream>
#include <fstream>
#include <cstring>

#define ERR_OPT_REQUIRES_ARG 1
#define ERR_INVAL_ARGUMENT   2
#define ERR_FILE_FAIL        3

#define GET_FILE_NAME(file_name, option)                                  \
	do                                                                    \
	{                                                                     \
		if (argc == 1)                                                    \
		{                                                                 \
			std::cerr << progname;                                        \
			std::cerr << ": opção requer um argumento -- '" option "'\n"; \
			return ERR_OPT_REQUIRES_ARG;                                  \
		}                                                                 \
		--argc;                                                           \
		file_name = *++argv;                                              \
	} while (0)

#define OPEN_FILE(stream, file_name, file_ptr)                                             \
	do                                                                                     \
	{                                                                                      \
		stream.open(file_name);                                                            \
                                                                                           \
		if (!stream.is_open())                                                             \
		{                                                                                  \
			std::cerr << progname << ": falha ao abrir o arquivo `" << file_name << "`\n"; \
			return ERR_FILE_FAIL;                                                          \
		}                                                                                  \
		file_ptr = &stream;                                                                \
	} while (0)

inline void print_usage(const std::string& progname, std::ostream& out);

template<int (*action)(std::istream&, std::ostream&)>
int main_template(int argc, char *argv[])
{
	std::ostream *out_file_ptr = &std::cout;
	std::istream *in_file_ptr = &std::cin;
	char *out_file_name = nullptr;
	char *in_file_name = nullptr;
	char *progname = *argv;

	while (--argc > 0)
	{
		++argv;

		if (std::strcmp(*argv, "-i") == 0)
			GET_FILE_NAME(in_file_name, "i");
		else if (std::strcmp(*argv, "-o") == 0)
			GET_FILE_NAME(out_file_name, "o");	
		else
		{
			print_usage(progname, std::cerr);
			return ERR_INVAL_ARGUMENT;
		}
	}

	std::ofstream outfile;
	std::ifstream infile;

	if (in_file_name)
		OPEN_FILE(infile, in_file_name, in_file_ptr);
	if (out_file_name)
		OPEN_FILE(outfile, out_file_name, out_file_ptr);

	return action(*in_file_ptr, *out_file_ptr);
}

inline void print_usage(const std::string& progname, std::ostream& out)
{
	out << "Uso: " << progname << " [-i ARQUIVO_DE_ENTRADA] [-o ARQUIVO_DE_SAIDA]\n";
}

#endif // MAIN_TEMPLATE_HPP
