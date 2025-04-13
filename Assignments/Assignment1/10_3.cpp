#include <iostream>
#include <streambuf>
#include <ostream>

class IndentStreamBuf : public std::streambuf 
{
public:
    IndentStreamBuf(std::streambuf* dest)
        : dest_(dest), indentLevel(0), atLineStart(true) 
    { }

    void increaseIndent() { indentLevel += 4; }

    void decreaseIndent() { if (indentLevel >= 4) indentLevel -= 4; }

protected:
    // The overflow method is called for each character written to the stream
    virtual int overflow(int c) override 
    {
        if (c == EOF)
            return EOF;
        
        // If at the start of a new line, output the current indent (spaces)
        if (atLineStart) 
        {
            atLineStart = false;
            for (int i = 0; i < indentLevel; ++i)
                dest_->sputc(' ');
        }

        int result = dest_->sputc(c);

        // If we just output a newline, then flag the start of a new line
        if (c == '\n')
            atLineStart = true;

        return result;
    }

private:
    std::streambuf* dest_;  // pointer to the destination stream buffer
    int indentLevel;        // current indent level (number of spaces)
    bool atLineStart;       // true if next character is at start of a new line
};

class IndentStream : public std::ostream 
{
public:
    IndentStream(std::ostream& os)
        : std::ostream(&buf), buf(os.rdbuf()) 
    { }

    IndentStreamBuf* getIndentBuf() { return &buf; }

    IndentStream& operator<<(IndentStream& (*manip)(IndentStream&)) 
    {
        return manip(*this);
    }

private:
    IndentStreamBuf buf;
};

// I/O manipulator to increase indent level by 4
IndentStream& indent(IndentStream& is)
{
    is.getIndentBuf()->increaseIndent();
    return is;
}

// I/O manipulator to decrease indent level by 4
IndentStream& unindent(IndentStream& is) 
{
    is.getIndentBuf()->decreaseIndent();
    return is;
}

int main()
{
    IndentStream ins(std::cout);

    ins << "int" << std::endl;
    ins << "fib(int n) {" << std::endl;
    ins << indent; // Increase indent level
    ins << "if (n == 0) return 0;" << std::endl;
    ins << "if (n == 1) return 1;" << std::endl;
    ins << "return fib(n-2) + fib(n-1);" << std::endl;
    ins << unindent; // Decrease indent level
    ins << "}" << std::endl;

    return 0;
}
