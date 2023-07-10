#ifndef Logic_refcount_ptr_HPP
#define Logic_refcount_ptr_HPP
#include <malloc.h>
#include <utility>
namespace std
{
	
	template<typename T>
	struct RefCount {
		size_t count;
		T obj;
	};
	template <typename T>
	inline T* malloc_t(size_t size)
	{
		return (T*)malloc(size);
	}
	template <typename T>
	inline T* malloc_t()
	{
		return (T*)malloc(sizeof(T));
	}

	template <typename T>
	struct Allocator_Std
	{
		using T_ref = std::RefCount<T>;
		template <typename ...TArgs>
		static inline T_ref* New(TArgs... args)
		{
			
			T_ref* v = new T_ref{ 0, T(std::forward<TArgs>(args)...) };
			
			return v;
		}
		static inline void Free(T_ref* _this)
		{
			delete _this;
		}
	};
	template<typename T,typename Allocator = Allocator_Std<T>>
	class refcount_ptr
	{
	public:
		typedef RefCount<T> elem_count;
		typedef T* t_ptr;
		typedef refcount_ptr<T, Allocator> refcount_ptr_t;
	private:
		elem_count* ptr;
	public:
		refcount_ptr()
		{
			this->ptr = NULL;
		}
		refcount_ptr(refcount_ptr_t&& v) noexcept
		{
			ptr = v.ptr;
			v.ptr = NULL;
		}
		refcount_ptr(refcount_ptr_t& v)
		{
			v.inc_ref();
			ptr = v.ptr;
		}

		refcount_ptr(const refcount_ptr_t& v)
		{
			v.inc_ref();
			ptr = v.ptr;
		}
		inline refcount_ptr_t& operator=(refcount_ptr_t& other)
		{
			if (other.ptr != this->ptr)
			{
				this->dec_ref();
				other.inc_ref();

				ptr = other.ptr;
			}
			return *this;
			
		}
		inline refcount_ptr_t& operator=(refcount_ptr_t&& other) noexcept
		{
			if (other.ptr != this->ptr)
			{
				this->dec_ref();
				ptr = other.ptr;
				
			}
			other.ptr = NULL;
			return *this;

		}
		inline t_ptr operator->()
		{
			return &ptr->obj;
		}
		inline T operator*()
		{
			return ptr->obj;
		}
		inline operator bool()
		{
			return ptr != NULL;
		}
		
		
		inline t_ptr get()
		{
			return &ptr->obj;
		}
		template<typename ...Args>
		static inline refcount_ptr<T,Allocator> make(Args... args)
		{
			refcount_ptr_t ret;
			elem_count* refcount = Allocator::New(std::forward<Args>(args)...);
			ret.ptr = refcount;
			return ret;
		}
		inline void dec_ref()
		{
			if (ptr != nullptr &&ptr->count != 0)
			{
				ptr->count--;

			}
			
		}
		inline void inc_ref()
		{
			if (ptr != nullptr)
			{
				ptr->count++;

			}

		}
		inline void inc_ref() const
		{
			if (ptr != nullptr)
			{
				ptr->count++;

			}

		}
		~refcount_ptr()
		{
			if (ptr != nullptr)
			{
				if (ptr->count == 0)
				{
					Allocator::Free(ptr);
					ptr = nullptr;
				}
				else
				{
					ptr->count--;
				}
				
			}
		}
	};
	
}

#endif