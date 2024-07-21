#ifndef __LIB_H__
#define __LIB_H__

// Tell the compiler to export this function definition.
// By using dumpbin /exports <dll_name>, you can check if this function is
// actually exported.
__declspec(dllexport) float multiply_float(float x, float y);

#endif
