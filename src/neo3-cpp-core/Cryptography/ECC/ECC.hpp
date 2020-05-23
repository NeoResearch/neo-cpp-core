#pragma once

// this defines the loading order for "internal" classes
#define NEO3_CRYPTOGRAPHY_ECC_ECC_HPP

// expected order
#include "ECCurve.hpp"
//
#include "ECPoint.hpp"
//
#include "ECFieldElement.hpp"

