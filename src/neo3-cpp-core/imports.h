#pragma once

// these are the 'imports', these come from outside world

extern "C"
{
   // this method is coming from the outside world... it could be 'js' (mergeInto), or 'cpp' (linking).
   extern int mycrypto(int x);

   // this method is coming from the outside world... it could be 'js' (mergeInto), or 'cpp' (linking).
   // returns the consumed size... 'bn_out' must be pre-allocated
   extern int bignum_add(const char* bn1, const char* bn2, const char* bn_out);
}