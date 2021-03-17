#ifndef LZ77_HPP
#define LZ77_HPP

#include <list>
#include <string>
#include <ostream>
#include <istream>

struct MyTuple
{
    size_t p;
    size_t l;
    char c;
};

std::ostream& operator<<(std::ostream& out, const MyTuple& t);
std::istream& operator>>(std::istream& in, MyTuple& t);

std::list<MyTuple> lz77_encode(const std::string& s);
std::string lz77_decode(const std::list<MyTuple>& code);

#endif // LZ77_HPP