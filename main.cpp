//== C++ includes ==
#include <iostream>
//== Project includes ==
#include "dtvariant.h"



int main ()
{
	{
		DTVar dtvar_1;
		DTVar dtvar_2;

		std::cout << "Enter string:" << std::endl;
		std::cin >> dtvar_1;

		dtvar_2 << "Input string: " << dtvar_1 << " ";
		dtvar_2[dtvar_2.g_len()-1] = '\n';
		dtvar_2 += "Input string: ";
		dtvar_2 += dtvar_1;

		std::cout << "Input string: " << dtvar_1 << std::endl;
		std::cout << dtvar_2 << std::endl;
	}
	std::cout << "-------------------------------------" << std::endl;

	{
		const char string_of_numbers[] = "2147483647";
		int int_var;
		int int_dtvar_increm;
		DTVar dtvar_1;
		DTVar dtvar_2;

		dtvar_1(string_of_numbers);
		int_var = dtvar_1.toInt32();

		dtvar_2 = dtvar_1;
		dtvar_2.getLastSymb()++;
		int_dtvar_increm = dtvar_2.toInt32();

		std::cout << "String:    " << string_of_numbers << std::endl;
		std::cout << "Variant:   " << dtvar_1 << std::endl;
		std::cout << "Integer:   " << int_var << std::endl;
		std::cout << "Variant+1: " << dtvar_2 << std::endl;
		std::cout << "Integer+1: " << int_dtvar_increm << std::endl;
	}
	std::cout << "-------------------------------------" << std::endl;

	{
		struct {unsigned int member = 12345;} object_var;
		DTVar dtvar_1;
		int int_var;
		float float_var;
		char string_var[256];
		int object_point;
		unsigned int member_var;

		dtvar_1.toFormat("Input formating:  int=%d, float=%f, object=%p, object_member=%u, string=[%s]",
					   12345, 123.45, object_var, object_var.member, "12345");
		dtvar_1.fromFormat("Input formating:  int=%d, float=%f, object=0x%x, object_member=%u, string=[%s]",
						 &int_var, &float_var, &object_point, &member_var, string_var);

		std::cout << dtvar_1 << std::endl;
		std::cout << "Output formating: int=" << int_var << ", "
				  << "float=" << float_var << ", "
				  << "object=" << "0x" << std::hex << object_point << std::dec  << ", "
				  << "object_member=" << member_var << ", "
				  << "string=[" << string_var << "]"
				  << std::endl;
	}
	std::cout << "-------------------------------------" << std::endl;

	{
		DTVar dtvar_1 = std::vector<int>{1, 2, 3, 4, 56789, 0};
		std::vector<int> vector_var;

		vector_var = dtvar_1.toVector<int>();

		std::cout << "Input vector:  " << dtvar_1 << std::endl;
		std::cout << "Output vector: ";
		for (auto iter_vector : vector_var) {
			std::cout << iter_vector << " ";

		}
		std::cout << std::endl;
	}
	std::cout << "-------------------------------------" << std::endl;

	return 0;
}
