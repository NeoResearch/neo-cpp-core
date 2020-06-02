#pragma once

namespace neopt {

class Version
{
public:
   int Major{ 0 };
   int Minor{ 0 };

   Version(int Major = 0, int Minor = 0)
     : Major{ Major }
     , Minor{ Minor }
   {
   }

   static Version Parse(std::string str)
   {
      std::cout << "TODO: Parse Version!!!" << std::endl;
      return Version{};
   }
};

} // namespace neopt
