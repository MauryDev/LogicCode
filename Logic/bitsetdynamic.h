#pragma once
#include <vector>

namespace std
{
	class bitsetdynamic
	{
	private:
		vector<unsigned long long> _bits;
		size_t _size;
        void Validate(int i)
        {
            if (i >= _size)
                throw "i >= size";
            if (i < 0)
            {
                throw "i < 0";
            }
        }
	public:
		bitsetdynamic(size_t n)
		{
			_size = n;
			_bits.resize((n + 63) / 64); // Round
		}
        bitsetdynamic()
        {
            _size = 0;
        }
        bitsetdynamic(bitsetdynamic& v)
        {
            _size = v._size;
            _bits = v._bits;
        }
        bitsetdynamic(bitsetdynamic&& v) noexcept
        {
            _size = v._size;
            _bits = v._bits;
        }
        void set(int i, bool value) {
            Validate(i);
            int block = i / 64;
            int bit = i % 64;

            unsigned long long mask = 1ULL << bit;

            if (value) {
                _bits[block] |= mask;
            }
            else {
                _bits[block] &= ~mask;
            }
        }
        
        bool get(int i) {
            Validate(i);

            int block = i / 64;
            int bit = i % 64;

            unsigned long long mask = 1ULL << bit;

            return (_bits[block] & mask) != 0;
        }
        size_t size()
        {
            return _size;
        }
	};
}


