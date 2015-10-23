#include <iostream>
#include <exception>

using namespace std;

class SafeArrayOutOfBoundsException: public exception
{
  virtual const char* what() const throw(){
    return "SafeArrayOutOfBoundsException thrown";
  }
};

class SafeArrayTooSmallException : public exception
{
  virtual const char* what() const throw(){
    return "SafeArrayTooSmallException thrown";
  }
};
