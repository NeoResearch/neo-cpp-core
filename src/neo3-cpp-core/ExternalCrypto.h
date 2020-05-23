#pragma once

// perform big1 >> big2 and return its size (in bytes). output vr must be pre-allocated
extern "C" int32
external_sha256(byte* big1, int sz_big1, byte* big2, int sz_big2, byte* vr, int sz_vr);

namespace External {

} // namespace External
