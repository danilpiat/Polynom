#include <iostream>

#include "acutest.h"
#include "Polynom.h"

void Test_OpIntSet(void)
{
	OpIntSet s1, s2, s3;

	std::cout << "\nstddialog for show purposes\n\n";

	std::cout << "s1:\n";

	std::cin >> s1;
	std::cout << "\n";

	std::cout << "s2:\n";

	std::cin >> s2;
	std::cout << "\n";

	s3 = s2 & s1;

	s3 += 1221;

	int elems[] = { 3, 172, 4 };

	OpIntSet s4(3, elems);

	OpIntSet sdiff = s2 - s1;

	(s4 += 23) += 42;

	std::cout << "s1: " << s1 << "\n";
	std::cout << "s2: " << s2 << "\n";
	std::cout << "s3: " << s3 << "\n";
	std::cout << "s4: " << s4 << "\n";

	std::cout << "sdiff: " << sdiff << "\n";

	std::cout << "\n";
}

TEST_LIST = {
	{ "Test_OpIntSet",  Test_OpIntSet },
	{         nullptr,  nullptr       }
};
