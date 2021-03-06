#pragma once

// ===========================================================
// These are the 'imports', these come from outside world
//
// It could be 'js' (mergeInto/emscripten), or 'cpp' (linking)
// See:
//    - src/libcore-js/libcore_exports.js
//    - src/libcore-cpp/libcore_exports.cpp
// -----------------------------------------------------------

extern "C"
{
   // =============================
   // just some initial experiments
   // -----------------------------

   // this method is coming from the outside world... it could be 'js' (mergeInto), or 'cpp' (linking).
   extern int mycrypto(int x);

   // this method is coming from the outside world... it could be 'js' (mergeInto), or 'cpp' (linking).
   // returns the consumed size... 'bn_out' must be pre-allocated
   extern int bignum_add(const char* bn1, const char* bn2, const char* bn_out);

   // ========================
   //    "serious" methods
   // ------------------------

   //
}