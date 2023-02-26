#include <chrono>
#include <ctime>
#include "bfunc.cpp"

int main()
{
    srand(unsigned int(time(NULL)));
    
    //for (size_t i = 1; i < 33; i++)
    //{
    //    auto begin = std::chrono::steady_clock::now();
    //    BF x(2, 1<<i);
    //    uint64_t w = x.weight();
    //    auto end = std::chrono::steady_clock::now();
    //    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    //    std::cout << "vec_size =" << i << "   weight/vec_size =" << long double(w) / (uint64_t(1) << i) << "\tTime : " << ms.count() << std::endl;
    //}

    BF x("11110100");
    std::cout << x << std::endl;
    return 0;
}
