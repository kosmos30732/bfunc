#include <chrono>
#include "bfunc.cpp"


int main()
{
    srand(unsigned int(time(NULL)));
    
    for (size_t i = 1; i < 24; i++)
    {
        auto begin = std::chrono::steady_clock::now();
        BF x(2, 1<<i);
        uint32_t w = x.weight();
        auto end = std::chrono::steady_clock::now();
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        std::cout << "vec_size =" << i << "   weight/vec_size =" << float(w) / (1 << i) << "\tTime : " << ms.count() << std::endl;
    }

    //BF x("0001101100100101101011101110110000011011001001011010111011101100");
    //std::cout << x << std::endl;
    return 0;
}
