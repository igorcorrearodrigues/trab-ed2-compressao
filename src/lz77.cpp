#include "lz77.hpp"

#define BUFF_MAX 4
#define DICIO_MAX 8

std::ostream& operator<<(std::ostream& out, const Lz77Code& t)
{
    return out << "(" << t.p << "," << t.l << "," << t.c << ")";
}

std::istream& operator>>(std::istream& in, Lz77Code& t)
{
	char c;

	if (!(
		(in >> c && c == '(')   &&
		(in >> t.p)             &&
		(in >> c && c == ',')   &&
		(in >> t.l)             &&
		(in >> c && c == ',')   &&
		((t.c=in.get()) != EOF) &&
		(in >> c && c == ')')
	)) {
		in.setstate(std::ios_base::failbit);
	}
	return in;
}

bool verifica_no_dicionario(const std::string& dicionario,
							const std::string& str, size_t& pos_ref)
{
	size_t pos = 0;

	for (pos = 0; pos < dicionario.length(); ++pos)
	{
		size_t dpos = pos;
		size_t spos = 0;
		size_t len = 0;

		while (str[spos] && str[spos] == dicionario[dpos])
		{
			++len, ++spos, ++dpos;
			if (dpos == dicionario.length())
				dpos = pos;
		}
		if (str[spos] == '\0')
		{
			pos_ref = pos;
			return true;
		}
	}
	pos_ref = 0;
	return false;
}

static size_t encontra_maior_sequencia(const std::string& dicionario, const std::string& buffer, size_t& pos)
{
	for (size_t len = buffer.length(); len > 0; --len)
		if (verifica_no_dicionario(dicionario, buffer.substr(0, len), pos))
			return len;
	return 0;
}

std::list<Lz77Code> lz77_encode(const std::string& s)
{
	std::string buffer;
	std::string dicionario;
	std::list<Lz77Code> code;

	size_t i = 0;

	while (i < s.length())
	{
		Lz77Code t;

		if (i <= DICIO_MAX)
			dicionario = s.substr(0, i);
		else
		{
			size_t pos = i - DICIO_MAX;
			dicionario = s.substr(pos, i - pos);
		}
		buffer = s.substr(i, BUFF_MAX);

		t.l = encontra_maior_sequencia(dicionario, buffer, t.p);

		if (t.l != 0)
			t.p = dicionario.size() - t.p;
		else
			t.p = 0;

		t.c = (i + t.l == s.length()) ? '\0' : s[i + t.l];

		code.push_back(t);

		i += t.l + 1;
	}
	return code;
}

std::string lz77_decode(const std::list<Lz77Code>& code)
{
	std::string result = "";

	for (const auto& t : code)
	{
		size_t p = result.size() - t.p;
		size_t len = 0;

		while (len < t.l)
		{
			result.push_back(result[p]);
			++len, ++p;
		}
		if (t.c != '\0')
			result.push_back(t.c);
	}
	return result;
}
