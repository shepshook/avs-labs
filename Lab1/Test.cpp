#include "Test.h"
#include "Solution.h"

bool test1()
{
	__int8 A[] = { 1, 1, 1, 1, 1, 1, 1, 1 };
	__int8 B[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
	__int8 C[] = { 2, 2, 2, 2, 2, 2, 2, 2 };
	__int16 D[] = { 0, 2, 4, 6, 8, 10, 12, 14 };

	__int32* expected = true_func(A, B, C, D);
	__int32* actual = func(A, B, C, D);

	return verify_equal(expected, actual);
}

bool test2()
{
	__int8 A[] = { -1, 1, -1, 1, -1, 1, -1, 1 };
	__int8 B[] = { 0, -1, 2, -3, 4, -5, 6, -7 };
	__int8 C[] = { -2, 2, -2, 2, -2, 2, -2, 2 };
	__int16 D[] = { 0, -2, 4, -6, 8, -10, 12, -14 };

	__int32* expected = true_func(A, B, C, D);
	__int32* actual = func(A, B, C, D);

	return verify_equal(expected, actual);
}

bool verify_equal(__int32* a, __int32* b)
{
	bool flag = true;
	for (int i = 0; i < 8; i++)
		if (a[i] != b[i])
		{
			flag = false;
			break;
		}

	return flag;
}

__int32* true_func(__int8* a8, __int8* b8, __int8* c8, __int16* d16)
{
	__int32* result = new __int32[8];
	for (int i = 0; i < 8; i++)
		result[i] = a8[i] * b8[i] + c8[i] * d16[i];

	return result;
}
