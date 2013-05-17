#ifndef		__CONVERT_HH__
# define	__CONVERT_HH__

#include	<iostream>
#include	<sstream>

template<typename Ret, typename Type>
class		Convert
{
public:
  static const Ret	convert(const Type &value)
  {
    Ret			ret;
    std::stringstream	cv;

    cv << value;
    cv >> ret;
    return (ret);
  }
};

# define		intToString(x)		Convert<std::string, int>::convert(x)
# define		stringToInt(x)		Convert<int, std::string>::convert(x)

#endif
