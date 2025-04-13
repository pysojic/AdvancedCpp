#ifndef INDENT_STREAM_H
#  define INDENT_STREAM_H

#include <streambuf>
#include <iostream>
#include <fstream>
#include <memory>
using std::ostream;
using std::streambuf;

namespace mpcs {
using std::ostream;
using std::streambuf;
using std::cout;
using std::cin;
using std::endl;
class IndentStreamBuf : public streambuf
{
public:
    IndentStreamBuf(ostream &stream) : wrappedStreambuf(*stream.rdbuf()) {}
	virtual int overflow(traits_type::int_type outputVal) override
	{
		if (outputVal == traits_type::eof())
			return traits_type::eof();
        if(outputVal == '\n') {
            isLineStart = true;
        } else if(isLineStart) {
            for(size_t i = 0; i < myIndent; i++) {
               wrappedStreambuf.sputc(' ');
            }
            isLineStart = false;
        }
        wrappedStreambuf.sputc(static_cast<char>(outputVal));
		return outputVal;
	}
protected:
    streambuf &wrappedStreambuf;
    bool isLineStart = true;
public:
    size_t myIndent = 0;
};

class IndentStream : public ostream
{
public:
    IndentStream(ostream &wrappedStream)
      : ostream(new IndentStreamBuf(wrappedStream)) {
    }
    ~IndentStream() { delete this->rdbuf(); }
};


ostream &indent(ostream &ostr);

ostream &unindent(ostream &ostr);

}
#endif
