#pragma once

#include <assert.h>
#include <memory> // for unique_ptr
//

#include "system/BinaryWriter.hpp"
#include "system/BitConverter.hpp"
#include "system/Buffer.hpp"
#include "system/IComparable.h"
#include "system/IEquatable.h"
#include "system/ISerializable.h"
#include "system/shelper.h"
#include "system/vhelper.hpp"

using neopt::byte;
using neopt::vbyte;

//template<class X>
//using uptr = std::unique_ptr<X>;