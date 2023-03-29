#include <string>
#include <iostream>
#include <cmath>
#include <bitset>
#include <vector>


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
		//for (size_t i = 0; i < vec_len; i++)
		//{
		//	std::bitset<32> st(vec[i]);
		//	std::string str = st.to_string();
		//	std::cout << str << " " << i << std::endl;
		//}
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
		vec_len = ((uint64_t(1) << uint64_t(log2(len))) + uint64_t(31)) >> 5;
		vec = new uint32_t[vec_len];

		if (type == 2)
		{
			if (len <= 16)
			{
				vec[0] = 0;
				vec[0] |= uint16_t(rand() - rand()) >> (16 - len);
			}
			else
			{
				for (uint32_t i = 0; i < vec_len; i++)
				{
					vec[i] = uint16_t(rand() - rand());
					vec[i] = vec[i] << 16;
					vec[i] |= uint16_t(rand() - rand());
				}
			}
		}

		if (type == 1)
		{
			if (len <= 16)
			{
				vec[0] = UINT16_MAX;
				vec[0] = vec[0] >> (16 - len);
			}
			else
			{
				for (size_t i = 0; i < vec_len; i++)
				{
					vec[i] = UINT32_MAX;
				}
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

		for (size_t i = 0; i < vec_len; i++)
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

		for (size_t i = 0; i < vec_len; i++)
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
			str.erase(0, size_t(32) - other.len);
			out << str;
		}
		else
		{
			for (size_t i = 0; i < other.vec_len; i++)
			{
				std::bitset<32> st(other.vec[other.vec_len - i - 1]);
				std::string str = st.to_string();
				out << str;
			}
		}
		return out;
	}

	//взвешивание булевой функции
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

		for (size_t i = 0; i < vec_len; i++)
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

	void printByVec()
	{
		for (size_t i = 0; i < vec_len; i++)
		{
			std::bitset<32> s(vec[i]);
			std::cout << s.to_string() << " " << i << std::endl;
		}
	}

	BF mebius()
	{
		BF g(0);
		g = *this;
		if (len == 2)
		{
			g.vec[0] = g.vec[0] ^ ((g.vec[0] >> 1) & 0x55555555);
			return g;
		}
		if (len == 4)
		{
			g.vec[0] = g.vec[0] ^ ((g.vec[0] >> 1) & 0x55555555);
			g.vec[0] = g.vec[0] ^ ((g.vec[0] >> 2) & 0x33333333);
			return g;
		}
		if (len == 8)
		{
			g.vec[0] = g.vec[0] ^ ((g.vec[0] >> 1) & 0x55555555);
			g.vec[0] = g.vec[0] ^ ((g.vec[0] >> 2) & 0x33333333);
			g.vec[0] = g.vec[0] ^ ((g.vec[0] >> 4) & 0x0f0f0f0f);
			return g;
		}
		if (len == 16)
		{
			g.vec[0] = g.vec[0] ^ ((g.vec[0] >> 1) & 0x55555555);
			g.vec[0] = g.vec[0] ^ ((g.vec[0] >> 2) & 0x33333333);
			g.vec[0] = g.vec[0] ^ ((g.vec[0] >> 4) & 0x0f0f0f0f);
			g.vec[0] = g.vec[0] ^ ((g.vec[0] >> 8) & 0x00ff00ff);
			return g;
		}
		if (len >= 32)
		{
			for (size_t i = 0; i < vec_len; i++)
			{
				g.vec[i] ^= ((g.vec[i] >> 1) & 0x55555555);
				g.vec[i] ^= ((g.vec[i] >> 2) & 0x33333333);
				g.vec[i] ^= ((g.vec[i] >> 4) & 0x0f0f0f0f);
				g.vec[i] ^= ((g.vec[i] >> 8) & 0x00ff00ff);
				g.vec[i] ^= ((g.vec[i] >> 16) & 0x0000ffff);
			}

			uint32_t l_2 = log2(len);
			for (uint32_t k = 0; k < l_2 - 5; k++)
			{
				for (uint32_t l = 0; l < (1 << (l_2 - 6 - k)); l++)
				{
					for (uint32_t i = l * (1 << (k + 1)), j = i + (1 << k), p = 0; p < (1 << k); p++, i++, j++)
					{
						g.vec[i] ^= g.vec[j];
					}
				}
			}
			return g;
		}
		return  g;
	}

	/*
	* Вывод АНФ
	* при result = 3 — вывод АНФ и степени
	* при result = 2 — вывод АНФ
	* при result = 1 — вывод степени
	*/
	std::string anf(uint8_t result = 3)
	{
		std::string res;
		uint32_t n = log2(len);
		uint8_t power = 0, tmp_p = 0;
		BF y(0), z_0(0, len);
		y = this->mebius();
		if (y == z_0)
		{
			res += '0';
			goto skip;
		}
		if (y.len < 32)
		{
			std::bitset<32> st(y.vec[0]);
			std::string str = st.to_string();
			str.erase(0, size_t(32) - y.len);
			if (str[0] == '1')
			{
				res += "1+";
			}
			for (size_t i = 1; i < str.length(); i++)
			{
				if (str[i] == '1')
				{
					std::bitset<32> st2(i);
					std::string str2 = st2.to_string();
					str2.erase(0, size_t(32) - n);
					for (size_t j = 0; j < str2.length(); j++)
					{
						if (str2[j] == '1')
						{
							tmp_p++;
							res += "X";
							res += std::to_string((j + 1));
						}
					}
					if (tmp_p > power)
					{
						power = tmp_p;
					}
					tmp_p = 0;
					if (res[res.length() - 1] != '+')
					{
						res += "+";
					}
				}
			}
		}
		else
		{
			if ((y.vec[y.vec_len - 1] >> 31) & 1)
			{
				res += "1+";
			}
			for (size_t k = 0; k < y.vec_len; k++)
			{
				std::bitset<32> st(y.vec[y.vec_len - k - 1]);
				std::string str = st.to_string();
				for (size_t i = 0; i < str.length(); i++)
				{
					if (str[i] == '1')
					{
						std::bitset<32> st2((i + (1 << 5) * k));
						std::string str2 = st2.to_string();
						str2.erase(0, size_t(32) - n);
						for (size_t j = 0; j < str2.length(); j++)
						{
							if (str2[j] == '1')
							{
								tmp_p++;
								res += "X";
								res += std::to_string((j + 1));
							}
						}
						if (tmp_p > power)
						{
							power = tmp_p;
						}
						tmp_p = 0;
						if (res[res.length() - 1] != '+')
						{
							res += "+";
						}
					}
				}
			}
		}

		if (res[res.length() - 1] == '+')
		{
			res.erase(res.length() - 1, 1);
		}
	skip:
		if (result == 3)
		{
			res += "\npower = " + std::to_string(power);
			return res;
		}
		if (result == 2)
		{
			return res;
		}
		if (result == 1)
		{
			res = "power = " + std::to_string(power);
			return res;
		}
		return res;
	}

	std::vector<int32_t> yolsha()
	{
		std::vector<int32_t> f(len);
		if (len < 32)
		{
			for (size_t i = 0; i < len; i++)
			{
				if (vec[0] & (1 << (len - i - 1)))
				{
					f[i] = -1;
				}
				else
				{
					f[i] = 1;
				}
			}
		}
		else
		{
			for (size_t i = 0; i < vec_len; i++)
			{
				for (size_t j = 0; j < 32; j++)
				{
					if (vec[vec_len - 1 - i] & (1 << (31 - j)))
					{
						f[j + 32 * i] = -1;
					}
					else
					{
						f[j + 32 * i] = 1;
					}
				}
			}
		}

		uint32_t l_2 = log2(len);
		for (uint32_t k = 0; k < l_2; k++)
		{
			for (uint32_t l = 0; l < (1 << (l_2 - 1 - k)); l++)
			{
				for (uint32_t i = l * (1 << (k + 1)), j = i + (1 << k), p = 0; p < (1 << k); p++, i++, j++)
				{
					f[i] = f[i] + f[j];
				}
				for (uint32_t i = l * (1 << (k + 1)), j = i + (1 << k), p = 0; p < (1 << k); p++, i++, j++)
				{
					f[j] = f[i] - f[j] - f[j];
				}
			}
		}
		return f;
	}
	
	uint32_t cor_i()
	{
		std::vector<int32_t>_f = this->yolsha();
		uint32_t n = log2(_f.size()), a = 0, b = 0, c = 0, tmp = 0, tmp_a = 0, res = 0;
		for (size_t k = 1; k <= n; k++)
		{
			a = ((1 << k) - 1) << (n - k);
			tmp_a = a;
			while (true)
			{
				if (_f[a] != 0)
				{
					return res;
				}
				b = (a + 1) & a;
				tmp = (b - 1) ^ a;
				tmp = (tmp & 0x55555555L) + ((tmp >> 1) & 0x55555555L);
				tmp = (tmp & 0x33333333L) + ((tmp >> 2) & 0x33333333L);
				tmp = (tmp + (tmp >> 4)) & 0x0F0F0F0FL;
				tmp = tmp + (tmp >> 8);
				c = (uint8_t)(tmp + (tmp >> 16)) & 0x3F;
				c -= 2;
				a = (((((a + 1) ^ a) << 1) + 1) << c) ^ b;
				if (a > tmp_a)
				{
					break;
				}
				tmp_a = a;
			}
			res++;
		}
		return res;
	}
};

