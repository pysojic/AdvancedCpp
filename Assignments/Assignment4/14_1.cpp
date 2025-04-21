#include <iostream>
#include <vector>
#include <algorithm>
#include <ostream>
#include <string>
#include <iterator>

template<typename CharT, typename Traits = std::char_traits<CharT>>
class ostream_joiner 
{
public:
    using ostream_type = std::basic_ostream<CharT, Traits>;
    using string_type  = std::basic_string<CharT, Traits>;

    ostream_joiner(ostream_type& os, const CharT* delim)
        : os_(&os), delim_(delim), first_(true)
    {}
    ostream_joiner(ostream_type& os, const string_type& delim)
        : os_(&os), delim_(delim), first_(true)
    {}

    struct proxy 
    {
        ostream_joiner* parent;
        template<typename T>
        proxy& operator=(T&& value) 
        {
            if (!parent->first_) 
            {
                *parent->os_ << parent->delim_;
            }
            parent->first_ = false;
            *parent->os_ << std::forward<T>(value);
            return *this;
        }
    };

    proxy operator*()        { return proxy{this}; }
    ostream_joiner& operator++()   { return *this; }
    ostream_joiner  operator++(int){ return *this; }

private:
    ostream_type* os_;
    string_type   delim_;
    bool          first_;
};

template<typename CharT, typename Traits>
ostream_joiner(std::basic_ostream<CharT, Traits>&, const CharT*)
    -> ostream_joiner<CharT, Traits>;

template<typename CharT, typename Traits>
ostream_joiner(std::basic_ostream<CharT, Traits>&, const std::basic_string<CharT, Traits>&)
    -> ostream_joiner<CharT, Traits>;

template<typename T, typename Alloc>
std::ostream& operator<<(std::ostream& os, const std::vector<T,Alloc>& v) 
{
    os << '[';
    std::copy(v.begin(), v.end(),
              ostream_joiner(os, ", "));
    return os << ']';
}


int main() 
{
    std::vector<int> v = {1, 2, 3, 4};

    // CORRECT: pass begin() and end() to std::copy
    std::copy(v.begin(), v.end(),
                ostream_joiner(std::cout, ", "));
    std::cout << "\n";

    // operator<< overload for vectors
    std::vector<std::string> words = {"hello", "world"};
    std::cout << words << "\n";
}