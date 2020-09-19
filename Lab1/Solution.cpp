#include "Solution.h"

__int32* func(__int8* a8, __int8* b8, __int8* c8, __int16* d16)
{
	__int32* result = new __int32[8];

	__int16* a16 = int8to16(a8);
	__int16* b16 = int8to16(b8);
	__int16* c16 = int8to16(c8);

	// we have 8 32-bit numbers (4 in each res) as result for a[i] * b[i]
	__int32* res1 = mul16(a16, b16);
	__int32* res2 = mul16(a16 + 4, b16 + 4);

	// result for c[i] * d[i]
	__int32* res3 = mul16(c16, d16);
	__int32* res4 = mul16(c16 + 4, d16 + 4);

	// calculating sum of 4 first elements and then 4 last
	res1 = sum32(res1, res3, new __int32[8]);
	res2 = sum32(res2, res4, res1 + 4);

	result = res1;
	return result;
}

__int32* mul16(__int16* a, __int16* b, __int32* result)
{
	if (result == nullptr)
		result = new __int32[4];

	__int64 buffer;

	__asm
	{
		mov eax, a
		mov ebx, b
		mov ecx, result

		movq mm0, qword ptr[eax]
		pmulhw mm0, qword ptr[ebx]

		movq mm1, qword ptr[eax]
		pmullw mm1, qword ptr[ebx]

		movq buffer, mm1
		punpcklwd mm1, mm0
		movq qword ptr[ecx], mm1

		movq mm1, buffer
		punpckhwd mm1, mm0
		movq qword ptr[ecx] + 8, mm1
	}

	return result;
}

__int32* sum32(__int32* a, __int32* b, __int32* result)
{
	if (result == nullptr)
		result = new __int32[4];

	__asm
	{
		mov eax, a
		mov ebx, b
		mov ecx, result

		movq mm0, qword ptr[eax]
		paddd mm0, qword ptr[ebx]
		movq qword ptr[ecx], mm0

		movq mm0, qword ptr[eax] + 8
		paddd mm0, qword ptr[ebx] + 8
		movq qword ptr[ecx] + 8, mm0
	}

	return result;
}

__int16* int8to16(__int8* x)
{
	__int16* result = new __int16[8];

	__asm
	{
		mov eax, x
		mov ebx, result

		movq mm0, qword ptr[eax]
		pxor mm1, mm1
		pcmpgtb mm1, mm0
		punpcklbw mm0, mm1

		movq qword ptr[ebx], mm0

		movq mm0, qword ptr[eax]
		pxor mm1, mm1
		pcmpgtb mm1, mm0
		punpckhbw mm0, mm1

		movq qword ptr[ebx] + 8, mm0
	}

	return result;
}
