#ifndef MAIN_TEMPLATE_HPP
#define MAIN_TEMPLATE_HPP

#include <iostream>
#include <fstream>
#include <cstring>

#include "lz77.hpp"

#define ERR_OPT_REQUIRES_ARG 1
#define ERR_INVAL_ARGUMENT   2
#define ERR_FILE_FAIL        3

void print_usage(const std::string& progname, std::ostream& out);

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
		char *cur_arg = *++argv;

		if (std::strcmp(cur_arg, "-i") == 0)
		{
			if (argc == 1)
			{
				std::cerr << progname << ": opção requer um argumento -- 'i'\n";
				return ERR_OPT_REQUIRES_ARG;
			}
			--argc;
			in_file_name = *++argv;
		}
		else if (std::strcmp(cur_arg, "-o") == 0)
		{
			if (argc == 1)
			{
				std::cerr << progname << ": opção requer um argumento -- 'o'\n";
				return ERR_OPT_REQUIRES_ARG;
			}
			--argc;
			out_file_name = *++argv;
		}
		else
		{
			print_usage(progname, std::cerr);
			return ERR_INVAL_ARGUMENT;
		}
	}

	std::ofstream outfile;
	std::ifstream infile;

	if (in_file_name)
	{
		infile.open(in_file_name);

		if (!infile.is_open())
		{
			std::cerr << progname << ": falha ao abrir o arquivo `" << in_file_name << "`\n";
			return ERR_FILE_FAIL;
		}
		in_file_ptr = &infile;
	}
	if (out_file_name)
	{
		outfile.open(out_file_name);

		if (!outfile.is_open())
		{
			std::cerr << progname << ": falha ao abrir o arquivo `" << out_file_name << "`\n";
			return ERR_FILE_FAIL;
		}
		out_file_ptr = &outfile;
	}
	return action(*in_file_ptr, *out_file_ptr);
}

void print_usage(const std::string& progname, std::ostream& out)
{
	out << "Uso: " << progname << " [-i ARQUIVO_DE_ENTRADA] [-o ARQUIVO_DE_SAIDA]\n";
}

#endif // MAIN_TEMPLATE_HPP
