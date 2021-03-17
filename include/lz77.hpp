#ifndef LZ77_HPP
#define LZ77_HPP

#include <list>
#include <string>
#include <ostream>
#include <istream>

struct Lz77Code
{
    size_t p;
    size_t l;
    char c;
};

std::ostream& operator<<(std::ostream& out, const Lz77Code& t);
std::istream& operator>>(std::istream& in, Lz77Code& t);

std::list<Lz77Code> lz77_encode(const std::string& s);
std::string lz77_decode(const std::list<Lz77Code>& code);

#endif // LZ77_HPP
