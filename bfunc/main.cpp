#include <chrono>
#include <ctime>
#include "bfunc.cpp"

int main()
{
    srand(unsigned int(time(NULL)));
    
    for (size_t i = 2; i < 32; i++)
    {
        auto begin = std::chrono::steady_clock::now();
        BF x(2, 1 << i);
        auto end = std::chrono::steady_clock::now();
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        
        begin = std::chrono::steady_clock::now();
        uint64_t w = x.weight();
        end = std::chrono::steady_clock::now();
        auto ms_weight = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);

        std::cout << "vec_size =" << i << "   weight/vec_size =" << long double(w) / (uint64_t(1) << i) << "\tTime gen: " << ms.count() << "\tTime weight: "<<ms_weight.count()<< std::endl;
    }


    //BF x("0010010000100111010001000010010100110011110111110010110001101100");
    //std::cout << x << std::endl;

    //std::bitset<32> st(vec[0]);
    //std::string str = st.to_string();
    //std::cout << str << " " << std::endl;
    return 0;
}
