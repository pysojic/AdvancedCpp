#include "IndentStream.h"

using std::cout;
using std::endl;

namespace mpcs {
// If not IndentStream, throw exception
ostream &indent(ostream &ostr)
{
    IndentStreamBuf &out = dynamic_cast<IndentStreamBuf &>(*ostr.rdbuf());
    out.myIndent += 4;
    return ostr;
}

// If not IndentStream, ignore
ostream &unindent(ostream &ostr)
{
    IndentStreamBuf *out = dynamic_cast<IndentStreamBuf *>(ostr.rdbuf());
    out->myIndent -= 4;
    return ostr;
}
}



