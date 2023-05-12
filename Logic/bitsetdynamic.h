#pragma once
#include <vector>

namespace std
{
	class bitsetdynamic
	{
	private:
		vector<unsigned long long> bits;
		size_t size;
	public:
		bitsetdynamic(size_t n)
		{
			size = n;
			bits.resize((n + 63) / 64); // Round
		}
        void set(int i, bool value) {
            int block = i / 64;
            int bit = i % 64;

            unsigned long long mask = 1ULL << bit;

            if (value) {
                bits[block] |= mask;
            }
            else {
                bits[block] &= ~mask;
            }
        }

        bool get(int i) {
            int block = i / 64;
            int bit = i % 64;

            unsigned long long mask = 1ULL << bit;

            return (bits[block] & mask) != 0;
        }
        size_t length()
        {
            return size;
        }
	};
}


