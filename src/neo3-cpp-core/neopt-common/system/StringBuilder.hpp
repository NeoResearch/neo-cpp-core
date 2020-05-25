#pragma once

#include<sstream>

namespace neopt {

class StringBuilder
{
private:
   std::string s;

public:

   StringBuilder()
   {
   }

   void Insert(int index, char c)
   {
      s.insert(s.begin()+index, c);
   }

   std::string ToString()
   {
      return s;
   }

}; // class StringBuilder

} // namespace neopt