#include "matrix_nn.hpp"

#define STEP_BY_STEP
#define SPL << "--------\n"

void test1()
{
	std::cout << "I) Constructors and Copy Tests"
			  		"(and Destructors -- check with Valgrind)\n" << std::endl;

	Matrix_NN a;
	Matrix_NN b(3);
	Matrix_NN c {1, 2, 3, 4};
	Matrix_NN d = {1, 2, 3, 4};
	Matrix_NN e {};
	Matrix_NN l1(2, 42);
	Matrix_NN l2(l1);
	Matrix_NN x(a);
	Matrix_NN y(b);
	Matrix_NN z(c);

	std::cout << "\n2 empty matrixes (orig and copy) -- expected 2 empty lines:"
																<< std::endl;
	std::cout << a SPL << x;

	std::cout << "2 Matrixes (orig and copy) 5x5 filled with default zero:"
																<< std::endl;
	std::cout << b SPL << y;

	std::cout << "2 Matrixes (orig and copy) 2x2 filled with value 42:"
																<< std::endl;
	std::cout << l1 SPL << l2;

	std::cout << "3 Matrixes (orig and copy, and next orig) 2x2 "
									  "filled from {1, 2, 3, 4}:" << std::endl;
	std::cout << c SPL << d SPL << d;;

	std::cout << "1 empty matrix from empty list {} -- "
			  							"expected 1 empty line:" << std::endl;
	std::cout << e;


	std::cout << "Next expected error"
			  		"(Inizialize matrix 2x2 with 3 size list): " << std::endl;
	try
	{
	    Matrix_NN f = {1, 2, 3};
	}
	catch (const std::exception& e)
	{
	    std::cerr << '\t' << e.what() << std::endl;
	}

	std::cout << "\n[SUCCESS]" << std::endl;
}

void test2()
{
	std::cout << "\n+=========================+\n";
	std::cout << "II) Copy and [] test\n" << std::endl;

	Matrix_NN a = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	Matrix_NN b(a);

	std::cout << "\nTwo matrixes (second is copy of first):" << std::endl;
	std::cout << a SPL << b;

	for (size_t i = 0; i < b.size(); i++)
		for (size_t j = 0; j < b.size(); j++)
			b[i][j] = i;

	std::cout << "\nTwo matrixes now"
			  	"(second was override with new elements with []):" << std::endl;
	std::cout << a SPL << b;

	std::cout << "\n[SUCCESS]" << std::endl;
}

void test3()
{
	std::cout << "\n+=========================+\n";
	std::cout << "III) Overloaded operators test with empty matrixes\n"
																<< std::endl;

	Matrix_NN a;
	Matrix_NN b;

	a = a;
	b = b;
	std::cout << "Next expected 2 empty lines (cout of 2 empty matrixes):"
																<< std::endl;
	std::cout << a SPL << b;
	std::cout << a + b;
	Matrix_NN c;
	c = a - b;
	c = a * b;
	c = b + a;
	c = b - a;
	c -= b;
	c += b;
	c *= b;

	c /= 9;
	c *= 5.;
	c = a * 5 + b * 10;

	std::cout << "Next expected:\n3 empty lines "
				  	"(invert and transposed empty matrixes and exp),\n"
		 			"3 nan (determinant) and 0 as trace:" << std::endl;
	std::cout << invert(c) SPL << transp(c) SPL << exp(c, 5);
	std::cout << det(a) << '\t' << det(b)
				<< '\t' << det(c) << '\t' << trace(c) << std::endl;

	std::cout << "\n[SUCCESS]" << std::endl;
}

void test4()
{
	std::cout << "\n+=========================+\n";
	std::cout << "IV) Overloaded operators test with different size  matrixes\n"
																<< std::endl;


	Matrix_NN a = {1};
	Matrix_NN b = {1, 2, 3, 4};

	a = a;
	b = b;
	std::cout << "\nOur two matrixes:" << std::endl;
	std::cout << a SPL << b;
	std::cout << "\nNext expected numbers of errors: 6" << std::endl;
	try
	{
		std::cout << a + b;
	}
	catch (const std::exception& e)
	{
		std::cerr << '\t' << e.what() << std::endl;
	}

	try
	{
		std::cout << a * b;
	}
	catch (const std::exception& e)
	{
		std::cerr << '\t' << e.what() << std::endl;
	}
	try
	{
		std::cout << a - b;
	}
	catch (const std::exception& e)
	{
		std::cerr << '\t' << e.what() << std::endl;
	}
	try
	{
		a += b;
	}
	catch (const std::exception& e)
	{
		std::cerr << '\t' << e.what() << std::endl;
	}
	try
	{
		a -= b;
	}
	catch (const std::exception& e)
	{
		std::cerr << '\t' << e.what() << std::endl;
	}
	try
	{
		a *= b;
	}
	catch (const std::exception& e)
	{
		std::cerr << '\t' << e.what() << std::endl;
	}

	std::cout << "\n[SUCCESS]" << std::endl;
}

void test5()
{
	std::cout << "\n+=========================+\n";
	std::cout << "V) Overloaded operators test with same size matrixes\n"
																<< std::endl;

	Matrix_NN a = {1,2,3,4};
	Matrix_NN b(a);

	std::cout << "\nOur two matrixes:" << std::endl;
	std::cout << a SPL << b << std::endl;
	
	std::cout << "A + B:\n" << a + b SPL << std::endl;
	std::cout << "A - B:\n" << a - b SPL << std::endl;
	std::cout << "A * B:\n" << a * b SPL << std::endl;
	std::cout << "A * 5:\n" << a * 5. SPL << std::endl;
	std::cout << "A / 5:\n" << a / 5. SPL << std::endl;

	Matrix_NN tmp(a);
	std::cout << "[C = A]" << std::endl;
	std::cout << "C += B:\n" << (tmp += b) SPL << std::endl;
	std::cout << "C -= B:\n" << (tmp -= b) SPL << std::endl;
	std::cout << "C *= B:\n" << (tmp *= b) SPL << std::endl;
	std::cout << "C *= 5:\n" << (tmp *= 5.) SPL << std::endl;
	std::cout << "C /= 5:\n" << (tmp /= 5.) SPL << std::endl;

	std::cout << "det(A)\tdet(B)\tdet(C)\n" << det(a) << '\t'
				<< det(b) << '\t' << det(tmp) << std::endl;
	std::cout << "trace(A)\ttrace(B)\ttrace(C)\n" << trace(a) << '\t'
				<< trace(b) << '\t'  << trace(tmp) << std::endl;

	Matrix_NN inv_a = invert(a);
	Matrix_NN inv_b = invert(b);
	Matrix_NN inv_tmp = invert(tmp);

	std::cout << "\nA^-1 with check A * A^-1:\n" << inv_a SPL
												<< a * inv_a SPL << std::endl;
	std::cout << "B^-1 with check B * B^-1:\n" << inv_b SPL
												<< b * inv_b SPL<< std::endl;
	std::cout << "C^-1 with check C * C^-1:\n" << inv_tmp SPL
												<< tmp * inv_tmp SPL<< std::endl;

	Matrix_NN exp_a = exp(a, 5);
	Matrix_NN exp_b = exp(b, 5);
	Matrix_NN exp_tmp = exp(tmp, 5);

	std::cout << "\nexp(A) with k = 5:\n" << exp_a SPL << std::endl;
	std::cout << "exp(B) with k = 5:\n" << exp_b SPL << std::endl;
	std::cout << "exp(C) with k = 5:\n" << exp_tmp SPL << std::endl;

	std::cout << "\n[SUCCESS]" << std::endl;
}

void test6()
{
	std::cout << "\n+=========================+\n";
	std::cout << "VI) Equals matrixes\n" << std::endl;

	Matrix_NN a = {1,2,3,4,5,6,7,8,9};
	Matrix_NN b(a);

	std::cout << "Expected A equals B (B is copy of A):\n" << a SPL
				<< b SPL << "Equals:" << (a == b) << std::endl;

	a = {1,2,3,4};
	b = {1,2,3,-4};
	std::cout << "\nExpected A NOT equals B:\n" << a SPL
			  << b SPL << "Equals:" << (a == b) << std::endl;

	a = {1,2,3,4};
	b = {1 + 1e-3, 2, 3, 4};
	std::cout << "\nExpected A NOT equals B (A[0][0] = B[0][0] + 1e-3):\n" << a SPL
			  << b SPL << "Equals:" << (a == b) << std::endl;

	a = {1,2,3,4};
	b = {1 + 1e-7, 2, 3, 4};
	std::cout << "\nExpected A equals B (A[0][0] = B[0][0] + 1e-7, i.e. diff < EPS):\n" << a SPL
			  << b SPL << "Equals:" << (a == b) << std::endl;

	std::cout << "\n[SUCCESS]" << std::endl;
}

void test7()
{
	std::cout << "\n+=========================+\n";
	std::cout << "VII) Manual input\n" << std::endl;

	std::cout << "Enter size N for matrix NxN below:\n"
			<< "[warn]: n >= 0 (using size_t)! beware overflows :)"<< std::endl;

	size_t n;
	std::cin >> n;

	Matrix_NN m(n);
	std::cout << "Input N*N numbers for matrix (row by row):" << std::endl;
	std::cin >> m;

	std::cout << "\nGJ! here your matrix:\n" << m SPL
						<< "and it's TeX code:\n" << m.convert() << std::endl;

	std::cout << "\n[SUCCESS]" << std::endl;
}

int main()
{
	test1();
#ifdef STEP_BY_STEP
	std::cout << "Press enter for next test." << std::endl;
	std::cin.get();
#endif

	test2();
#ifdef STEP_BY_STEP
	std::cout << "Press enter for next test." << std::endl;
	std::cin.get();
#endif

	test3();
#ifdef STEP_BY_STEP
	std::cout << "Press enter for next test." << std::endl;
	std::cin.get();
#endif
	
	test4();
#ifdef STEP_BY_STEP
	std::cout << "Press enter for next test." << std::endl;
	std::cin.get();
#endif
	
	test5();
#ifdef STEP_BY_STEP
	std::cout << "Press enter for next test." << std::endl;
	std::cin.get();
#endif

	test6();
#ifdef STEP_BY_STEP
	std::cout << "Press enter for next test." << std::endl;
	std::cin.get();
#endif

	test7();
}
