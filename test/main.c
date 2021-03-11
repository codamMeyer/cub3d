// #define CTEST_MAIN
// #define CTEST_SEGFAULT
// #define CTEST_COLOR_OK
// #include "ctest.h"
// #include <stdio.h>

// CTEST(s, d)
// {
// 	ASSERT_EQUAL(5, 78);
// }

// int main(int argc, const char *argv[])
// {
// 	printf("AAAAAAAAAAAAAAAAAAAAAA");
// 	return ctest_main(argc, argv);
// }

#include <stdio.h>

#define CTEST_MAIN

// uncomment lines below to enable/disable features. See README.md for details
// #define CTEST_SEGFAULT
//#define CTEST_NO_COLORS
#define CTEST_COLOR_OK

#include "ctest.h"

// basic test without setup/teardown

int main(int argc, const char *argv[])
{
	return ctest_main(argc, argv);
}