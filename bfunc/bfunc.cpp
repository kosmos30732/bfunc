#include <string>
#include <iostream>
#include <cmath>
#include <ctime>
#include <bitset>

class BF
{
	uint32_t  len = 0;          //используемая память
	uint32_t  vec_len = 0;      //выделеная память
	uint32_t* vec = nullptr;	//массив коэфициентов
public:

	//конструктор от строки
	BF(std::string s)
	{
		uint32_t str_len = s.length();
		if (vec != nullptr)
		{
			delete[]vec;
			vec = nullptr;
		}
		if (str_len & (str_len - 1))
		{
			std::cout << "The length can only be a power of 2\n";
			exit(1);
		}
		len = str_len;
		vec_len = ((1 << int(log2(len))) + 31) >> 5;
		vec = new uint32_t[vec_len];

		for (size_t i = 0; i < vec_len; i++)
		{
			vec[i] = 0;
		}

		for (size_t i = 0; i < len; i++)
		{
			vec[vec_len - (i >> 5) - 1] <<= 1;
			if (s[i] == '1')
			{
				vec[vec_len - (i >> 5) - 1] |= 1;
			}
		}
	}

	/*
	* конструктор
	* при type == 2 — случайный набор
	* при type == 1 — константа 1
	* при type == 0 — константа 0
	*/
	BF(uint8_t type, uint32_t _len = sizeof(uint32_t) * 8)
	{
		if (_len & (_len - 1))
		{
			std::cout << "The length can only be a power of 2\n";
			exit(1);
		}

		len = _len;
		vec_len = ((1 << int(log2(len))) + 31) >> 5;
		vec = new uint32_t[vec_len];

		if (type == 2)
		{
			for (size_t i = 0; i < vec_len; i++)
			{
				vec[i] = 0;
			}
			for (uint32_t i = 0; i < len; i++)
			{
				if (rand() % 2)
				{
					vec[i >> 5] |= (1 << (i % 32));
				}
			}
		}

		if (type == 1)
		{
			for (size_t i = 0; i < vec_len; i++)
			{
				vec[i] = UINT32_MAX;
			}
		}

		if (type == 0)
		{
			for (size_t i = 0; i < vec_len; i++)
			{
				vec[i] = 0;
			}
		}
	}

	~BF()
	{
		if (vec != nullptr)
		{
			delete[] vec;
			vec = nullptr;
		}
	}

	BF(const BF& other)
	{
		len = other.len;
		vec_len = other.vec_len;
		vec = new uint32_t[vec_len];

		for (int i = 0; i < vec_len; i++)
		{
			vec[i] = other.vec[i];
		}
	}

	BF& operator = (const BF& other)
	{
		//самоприсваивание
		if (this == &other)
		{
			return *this;
		}

		//чистим мусор
		if (vec != nullptr)
		{
			delete[] vec;
		}

		len = other.len;
		vec_len = other.vec_len;
		vec = new uint32_t[vec_len];

		for (int i = 0; i < vec_len; i++)
		{
			vec[i] = other.vec[i];
		}

		return *this;
	}

	friend std::ostream& operator <<(std::ostream& out, BF& other)
	{
		if (other.len <= 32)
		{
			std::bitset<32> st(other.vec[0]);
			std::string str = st.to_string();
			str.erase(0, 32 - other.len);
			out << str;
		}
		else
		{
			for (int i = 0; i < other.vec_len; i++)
			{
				std::bitset<32> st(other.vec[other.vec_len - i - 1]);
				std::string str = st.to_string();
				out << str;
			}
		}

		return out;
	}

	uint32_t weight()
	{
		uint32_t res = 0;
		for (size_t i = 0; i < vec_len; i++)
		{
			uint32_t tmp = vec[i];
			tmp = (tmp & 0x55555555L) + ((tmp >> 1) & 0x55555555L);
			tmp = (tmp & 0x33333333L) + ((tmp >> 2) & 0x33333333L);
			tmp = (tmp + (tmp >> 4)) & 0x0F0F0F0FL;
			tmp = tmp + (tmp >> 8);
			res += (uint8_t)(tmp + (tmp >> 16)) & 0x3F;
		}

		return res;
	}

	bool operator == (const BF other)
	{
		if (len != other.len)
		{
			return false;
		}

		for (int i = 0; i < vec_len; i++)
		{
			if (other.vec[i] != vec[i])
			{
				return false;
			}
		}

		return true;
	}

	bool operator != (const BF other)
	{
		return !(*this == other);
	}
};

