#ifndef JOBJECT_HPP
#define JOBJECT_HPP

// c++ standard part
#include <cmath> // NAN
#include <map>
#include <vector>

// neopt core part
#include "../numbers/UIntBase.hpp"
#include "../system/IComparable.h"
#include "../system/IEquatable.h"
#include "../system/ISerializable.h"
#include "../system/ITextReader.h"
#include "../system/StringReader.hpp"
#include "../system/mhelper.h"
#include "../system/shelper.h"

namespace neopt {

// forward declaration
class JString;

class JObject
{
public:
   //static JObject Null() = null;
   //private:
public:
   map<string, JObject*> properties;

public:
   virtual ~JObject()
   {
   }

   JObject& operator[](string name)
   {
      return *properties[name];
   }

   const JObject& operator[](string name) const
   {
      return at(name);
   }

   const JObject& at(string name) const
   {
      const JObject* pobj = properties.at(name);
      return *pobj;
   }


   // pointer get (like "optional")
   JObject* pget(string name)
   {
      if (properties.count(name))
         return properties.at(name);
      else
         return nullptr;
   }

   const bool HasKey(string name) const
   {
      return (properties.count(name));
   }

   // unique pointer get with clone
   const uptr<JObject> upget(string name) const
   {
      if (properties.count(name))
         return uptr<JObject>{ properties.at(name)->clone() };
      else
         return nullptr;
   }

   // pointer set (safe memory)
   void pset(string name, uptr<JObject>&& obj)
   {
      // only OWNED memory (no cycles!!)

      // free if exists
      auto el = properties.find(name);
      if (el != properties.end()) {
         delete properties[name];
         properties.erase(el);
      }

      properties[name] = obj.release();
   }

   const map<string, JObject*> Properties()
   {
      return properties;
   }

   virtual bool AsBoolean() const
   {
      return true;
   }

   virtual double AsNumber() const
   {
      return NAN;
   }

   virtual string AsString() const
   {
      return "[object Object]";
   }

   virtual std::string getValue() const
   {
      return this->ToString();
   }

   bool ContainsProperty(string key)
   {
      return mhelper::ContainsKey(properties, key);
   }

public:
   virtual std::string ToString() const
   {
      //StringBuilder sb = new StringBuilder();
      std::stringstream sb;
      //sb.Append('{');
      sb << '{';
      //foreach (KeyValuePair<string, JObject> pair in properties)
      for (auto pair = properties.begin(); pair != properties.end(); ++pair) {
         sb << '"';
         sb << pair->first;
         sb << '"';
         sb << ':';
         if (pair->second == nullptr) {
            sb << "null";
         } else {
            sb << pair->second->getValue();
         }
         sb << ',';
      }
      std::string sf = sb.str();
      if (properties.size() == 0) {
         sf.append("}");
      } else {
         sf[sf.size() - 1] = '}';
      }
      return sf;
   }

   /*
           public virtual T TryGetEnum<T>(T defaultValue = default, bool ignoreCase = false) where T : Enum
           {
               return defaultValue;
           }

           public static implicit operator JObject(Enum value)
           {
               return new JString(value.ToString());
           }

           public static implicit operator JObject(JObject[] value)
           {
               return new JArray(value);
           }

           public static implicit operator JObject(bool value)
           {
               return new JBoolean(value);
           }

           public static implicit operator JObject(double value)
           {
               return new JNumber(value);
           }
*/
   // return value == null ? null : new JString(value);
public:
   operator std::string() const
   {
      return this->ToString();
   }

public:
   JObject& operator=(const string value)
   {
      NEOPT_EXCEPTION("Not implemented: operator= JObject string")
      return *this;
   }

public:
   virtual neopt::uptr<JObject> clone() const
   {
      JObject* other = new JObject();
      // iterate over map, cloning every element
      std::cout << "TODO: MUST ITERATE OVER MAP!!! " << std::endl;
      return neopt::uptr<JObject>{ other };
   }
};
//
} // namespace neopt

#endif
