#include <chrono>
#include <ctime>
#include "bfunc.cpp"

int main()
{
	srand(unsigned int(time(NULL)));

	//тестирование для 1

	//for (size_t i = 2; i < 32; i++)
	//{
	//    auto begin = std::chrono::steady_clock::now();
	//    BF x(2, 1 << i);
	//    auto end = std::chrono::steady_clock::now();
	//    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
	//    
	//    begin = std::chrono::steady_clock::now();
	//    uint64_t w = x.weight();
	//    end = std::chrono::steady_clock::now();
	//    auto ms_weight = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
	// }
	//BF x("0010010000100111010001000010010100110011110111110010110001101100");
	//std::cout << x << std::endl;
	//    std::cout << "vec_size =" << i << "   weight/vec_size =" << long double(w) / (uint64_t(1) << i) << "\tTime gen: " << ms.count() << "\tTime weight: "<<ms_weight.count()<< std::endl;

	//тестирование для 2

	//for (size_t i = 2; i < 32; i++)
	//{
	//    auto begin = std::chrono::steady_clock::now();
	//    BF x(0, 1 << i);
	//    auto end = std::chrono::steady_clock::now();
	//    auto t_gen = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
	//    BF y(0), z(0);
	//    begin = std::chrono::steady_clock::now();
	//    y = x.mebius();
	//    end = std::chrono::steady_clock::now();
	//    auto t_mebius = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
	//    z = y.mebius();
	//    std::cout << "Arg =" << i
	//        << "\tTime_gen =" << t_gen
	//        << "\tTime_mebius =" << t_mebius
	//        << "\tEqual after 2 mebius? =" << ((x == z) ? "true" : "No");
	//    std::cout << std::endl;
	//}
	//std::cout << std::endl;
	//for (size_t i = 2; i < 32; i++)
	//{
	//    auto begin = std::chrono::steady_clock::now();
	//    BF x(1, 1 << i);
	//    auto end = std::chrono::steady_clock::now();
	//    auto t_gen = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
	//    BF y(0), z(0);
	//    begin = std::chrono::steady_clock::now();
	//    y = x.mebius();
	//    end = std::chrono::steady_clock::now();
	//    auto t_mebius = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
	//    z = y.mebius();
	//    std::cout << "Arg =" << i
	//        << "\tTime_gen =" << t_gen
	//        << "\tTime_mebius =" << t_mebius
	//        << "\tEqual after 2 mebius? =" << ((x == z) ? "true" : "No");
	//    std::cout << std::endl;
	//}
	//std::cout << std::endl;
	//for (size_t i = 2; i < 32; i++)
	//{
	//    auto begin = std::chrono::steady_clock::now();
	//    BF x(2, 1 << i);
	//    auto end = std::chrono::steady_clock::now();
	//    auto t_gen = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
	//    BF y(0), z(0);
	//    begin = std::chrono::steady_clock::now();
	//    y = x.mebius();
	//    end = std::chrono::steady_clock::now();
	//    auto t_mebius = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
	//    z = y.mebius();
	//    std::cout << "Arg =" << i
	//        << "\tTime_gen =" << t_gen
	//        << "\tTime_mebius =" << t_mebius
	//        << "\tEqual after 2 mebius? =" << ((x == z) ? "true" : "No");
	//    std::cout << std::endl;
	//}
	//BF x("0001000100011110000100010001111000010001000111101110111011100001");
	//std::cout << x.anf() << std::endl;

	//тестирование для 3

	//for (size_t i = 2; i < 32; i++)
	//{
	//	auto begin = std::chrono::steady_clock::now();
	//	BF x(0, 1 << i);
	//	auto end = std::chrono::steady_clock::now();
	//	auto t_gen = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
	//	std::vector<int32_t>h;
	//	begin = std::chrono::steady_clock::now();
	//	h = x.yolsha();
	//	end = std::chrono::steady_clock::now();
	//	auto t_yolsha = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
	//	std::cout << "Arg =" << i
	//		<< "\tTime_gen =" << t_gen
	//		<< "\tTime_yolsha =" << t_yolsha;
	//	std::cout << std::endl;
	//}
	//std::cout << std::endl;
	//for (size_t i = 2; i < 32; i++)
	//{
	//	auto begin = std::chrono::steady_clock::now();
	//	BF x(1, 1 << i);
	//	auto end = std::chrono::steady_clock::now();
	//	auto t_gen = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
	//	std::vector<int32_t>h;
	//	begin = std::chrono::steady_clock::now();
	//	h = x.yolsha();
	//	end = std::chrono::steady_clock::now();
	//	auto t_yolsha = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
	//	std::cout << "Arg =" << i
	//		<< "\tTime_gen =" << t_gen
	//		<< "\tTime_yolsha =" << t_yolsha;
	//	std::cout << std::endl;
	//}
	//std::cout << std::endl;
	//for (size_t i = 2; i < 32; i++)
	//{
	//	auto begin = std::chrono::steady_clock::now();
	//	BF x(2, 1 << i);
	//	auto end = std::chrono::steady_clock::now();
	//	auto t_gen = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
	//	std::vector<int32_t>h;
	//	begin = std::chrono::steady_clock::now();
	//	h = x.yolsha();
	//	end = std::chrono::steady_clock::now();
	//	auto t_yolsha = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
	//	std::cout << "Arg =" << i
	//		<< "\tTime_gen =" << t_gen
	//		<< "\tTime_yolsha =" << t_yolsha;
	//	std::cout << std::endl;
	//}
	// 
	//BF x("0001000100011110000100010001111000010001000111101110111011100001");
	//std::cout << x.anf() << std::endl;
	// 
	//BF x("10110111");
	//std::vector<int32_t>h;
	//h = x.yolsha();
	//for (auto s : h)
	//{
	//    std::cout <<" "<< s;
	//}
	//std::cout << std::endl;

	//тестирование 4

	//for (size_t i = 2; i < 32; i++)
	//{
	//	auto begin = std::chrono::steady_clock::now();
	//	BF x(0, 1 << i);
	//	auto end = std::chrono::steady_clock::now();
	//	auto t_gen = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
	//	uint32_t r = 0;
	//	begin = std::chrono::steady_clock::now();
	//	r = x.cor_i();
	//	end = std::chrono::steady_clock::now();
	//	auto t_cor = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
	//	std::cout << "Arg =" << i
	//		<< "\tTime_gen =" << t_gen
	//		<< "\tTime_cor =" << t_cor
	//		<< "\tCor =" <<r;
	//	std::cout << std::endl;
	//}
	//BF x("01101001");
	//uint32_t r = x.cor_i();
	//std::cout << x << "\n cor=" << r << std::endl;

	BF x("10010110");
	std::cout << x.nf_nap();

	return 0;
}
