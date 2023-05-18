#pragma once
#include <vector>
#include <string>
#include "refcount_ptr.h"
namespace std
{

	class bitsetdynamic
	{
    public:
        typedef unsigned long long Bits;
	private:
		size_t _size;
        inline Bits* _bits()
        {
            return (Bits*)(this + 1);
        }
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
        using refcount_elem = std::RefCount<bitsetdynamic>;
        using refcount_ptr_elem = std::refcount_ptr<bitsetdynamic, bitsetdynamic>;
        inline bitsetdynamic()
        {
            _size = 0;
        }
        inline ~bitsetdynamic()
        {
            _size = 0;
        }
        inline Bits* data()
        {
            return _bits();
        }
        void set(int i, bool value) {

            Validate(i);
            int block = i / 64;
            int bit = i % 64;

            unsigned long long mask = 1ULL << bit;

            if (value) {
                _bits()[block] |= mask;
            }
            else {
                _bits()[block] &= ~mask;
            }
        }
        
        bool get(int i) {
            Validate(i);


            int block = i / 64;
            int bit = i % 64;

            unsigned long long mask = 1ULL << bit;

            return (_bits()[block] & mask) != 0;
        }
        size_t inline size()
        {
            return _size;
        }
        std::string to_string()
        {
            auto len = _size;
            std::string str;
            str.reserve(len);
            int ir = len - 1;

            for (size_t i = 0; i < len; i++)
            {
                str.push_back(get(ir) == true ? '1' : '0');
                ir--;
            }
            return str;
        }
        static refcount_elem* New(bool v)
        {
            auto lenmalloc = sizeof(refcount_elem) + sizeof(Bits);
            auto ret = malloc_t<refcount_elem>(lenmalloc);
            memset(ret, 0, lenmalloc);
            ret->count = 0;
            ret->obj._size = 1;
            ret->obj.set(0, v);
            
            return ret;
        }
        static refcount_elem* New(size_t len)
        {
            auto lenarr = (len + 63) / 64;
            auto lenmalloc = sizeof(refcount_elem) + sizeof(Bits) * lenarr;
            auto ret = malloc_t<refcount_elem>(lenmalloc);
            memset(ret,0,lenmalloc);
            ret->count = 0;
            ret->obj._size = len;
            return ret;
        }
        static refcount_elem* New(Bits* v, size_t n)
        {
            if (v == NULL)
            {
                return NULL;
            }
            auto lenarr = (n + 63) / 64;

            auto lenmalloc = sizeof(refcount_elem) + sizeof(Bits) * lenarr;
            auto ret = malloc_t<refcount_elem>(lenmalloc);
            ret->count = 0;
            ret->obj._size = n;

            memcpy(ret->obj._bits(), v, lenarr);

            return ret;

        }
        static refcount_elem* New()
        {
            auto lenmalloc = sizeof(refcount_elem);
            auto ret = malloc_t<refcount_elem>(lenmalloc);
            ret->count = 0;
            ret->obj._size = 0;

            return ret;

        }
        static inline refcount_ptr_elem Make()
        {
            return refcount_ptr_elem::make();
        }
        static inline refcount_ptr_elem Make(bool v)
        {
            return refcount_ptr_elem::make(v);
        }
        static inline refcount_ptr_elem Make(size_t len)
        {
            return refcount_ptr_elem::make(len);
        }
        static inline refcount_ptr_elem Make(Bits* v, size_t n)
        {
            return refcount_ptr_elem::make(v,n);
        }
        static inline void Free(refcount_elem* _this)
        {
            if (_this != NULL)
            {
                free(_this);
            }
        }
        static inline refcount_ptr_elem Copy(refcount_ptr_elem&& v)
        {
            return Make(v->data(), v->size());
        }
        static inline refcount_ptr_elem Copy(refcount_ptr_elem& v)
        {
            return Make(v->data(), v->size());
        }
	};
}


