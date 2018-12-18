#include "test.hpp"

test::tests_type test::_tests;


int main(int _argc, char ** _argv)
{
	return test::test_main(_argc > 1 ? _argv[1] : nullptr) ? 0 : 1;
}
