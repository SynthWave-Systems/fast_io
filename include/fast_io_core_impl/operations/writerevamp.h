#pragma once

namespace fast_io
{
namespace details
{

template<typename outstmtype>
#if __has_cpp_attribute(__gnu__::__cold__)
[[__gnu__::__cold__]]
#endif
inline constexpr ::std::byte const* write_some_bytes_cold_impl(outstmtype outsm,::std::byte const *first,::std::byte const *last);

template<typename outstmtype>
#if __has_cpp_attribute(__gnu__::__cold__)
[[__gnu__::__cold__]]
#endif
inline constexpr void write_all_bytes_cold_impl(outstmtype outsm,::std::byte const *first,::std::byte const *last);

template<typename outstmtype>
#if __has_cpp_attribute(__gnu__::__cold__)
[[__gnu__::__cold__]]
#endif
inline constexpr typename outstmtype::output_char_type const* write_some_cold_impl(outstmtype outsm,
	typename outstmtype::output_char_type const *first,typename outstmtype::output_char_type const *last)
{
	using char_type = typename outstmtype::output_char_type;
	if constexpr(::fast_io::details::streamreflect::has_write_some_overflow_define<outstmtype>)
	{
		return write_some_overflow_define(outsm,first,last);
	}
	else if constexpr(::fast_io::details::streamreflect::has_scatter_write_some_overflow_define<outstmtype>)
	{
		basic_io_scatter_t<char_type> sc{first,static_cast<::std::size_t>(last-first)};
		return scatter_write_some_bytes_overflow_define(outsm,__builtin_addressof(sc),1).total_size+first;		
	}
	else if constexpr(::fast_io::details::streamreflect::has_write_all_overflow_define<outstmtype>)
	{
		write_all_overflow_define(outsm,first,last);
		return last;
	}
	else if constexpr(::fast_io::details::streamreflect::has_scatter_write_all_overflow_define<outstmtype>)
	{
		basic_io_scatter_t<char_type> sc{first,static_cast<::std::size_t>(last-first)};
		return scatter_write_all_overflow_define(outsm,__builtin_addressof(sc),1).total_size+first;
	}
	else
	{
		if constexpr(sizeof(typename outstmtype::output_char_type)==1)
		{
			::std::byte const* firstptr{reinterpret_cast<::std::byte const*>(first)};
			::std::byte const* ptr{write_some_bytes_cold_impl(outsm,
			firstptr,reinterpret_cast<::std::byte const*>(last))};
			return ptr-firstptr+first;
		}
		else
		{
			::std::byte const* firstptr{reinterpret_cast<::std::byte const*>(first)};
			::std::byte const* ptr{write_some_bytes_cold_impl(outsm,
			firstptr,reinterpret_cast<::std::byte const*>(last))};
			::std::size_t diff{static_cast<::std::size_t>(ptr-firstptr)};
			::std::size_t v{diff/sizeof(char_type)};
			::std::size_t remain{diff%sizeof(char_type)};
			if(remain!=0)
			{
				write_all_bytes_cold_impl(outsm,ptr,ptr+remain);
			}
			return first+v;
		}
	}
}

template<typename outstmtype>
#if __has_cpp_attribute(__gnu__::__cold__)
[[__gnu__::__cold__]]
#endif
inline constexpr ::std::byte const* write_some_bytes_cold_impl(outstmtype outsm,::std::byte const *first,::std::byte const *last)
{
	using char_type = typename outstmtype::output_char_type;
	if constexpr(::fast_io::details::streamreflect::has_write_some_bytes_overflow_define<outstmtype>)
	{
		return write_some_bytes_overflow_define(outsm,first,last);
	}
	else if constexpr(::fast_io::details::streamreflect::has_scatter_write_some_bytes_overflow_define<outstmtype>)
	{
		io_scatter_t sc{first,static_cast<::std::size_t>(last-first)};
		return scatter_write_some_bytes_overflow_define(outsm,__builtin_addressof(sc),1).total_size+first;
	}
	else if constexpr(sizeof(char_type)==1&&
		::fast_io::details::streamreflect::has_write_some_overflow_define<outstmtype>)
	{
		using char_type_const_ptr
#if __has_cpp_attribute(__gnu__::__may_alias__)
		[[__gnu__::__may_alias__]]
#endif
		=
		char_type const*;
		return write_some_overflow_define(outsm,
			reinterpret_cast<char_type_const_ptr>(first),
			reinterpret_cast<char_type_const_ptr>(last));
	}
	else if constexpr(sizeof(char_type)==1&&
		::fast_io::details::streamreflect::has_scatter_write_some_overflow_define<outstmtype>)
	{
		using char_type_const_ptr
#if __has_cpp_attribute(__gnu__::__may_alias__)
		[[__gnu__::__may_alias__]]
#endif
		= char_type const*;
		basic_io_scatter_t<char_type> sc{reinterpret_cast<char_type_const_ptr>(first),static_cast<::std::size_t>(last-first)};
		return scatter_write_some_bytes_overflow_define(outsm,__builtin_addressof(sc),1).total_size+first;
	}
	else if constexpr(::fast_io::details::streamreflect::has_write_all_bytes_overflow_define<outstmtype>)
	{
		write_all_bytes_overflow_define(outsm,first,last);
		return last;
	}
	else if constexpr(::fast_io::details::streamreflect::has_scatter_write_all_bytes_overflow_define<outstmtype>)
	{
		io_scatter_t sc{first,static_cast<::std::size_t>(last-first)};
		scatter_write_all_bytes_overflow_define(outsm,__builtin_addressof(sc),1);
		return last;
	}
	else if constexpr(sizeof(char_type)==1&&
		::fast_io::details::streamreflect::has_write_all_overflow_define<outstmtype>)
	{
		using char_type_const_ptr
#if __has_cpp_attribute(__gnu__::__may_alias__)
		[[__gnu__::__may_alias__]]
#endif
		=
		char_type const*;
		write_all_overflow_define(outsm,
			reinterpret_cast<char_type_const_ptr>(first),
			reinterpret_cast<char_type_const_ptr>(last));
		return last;
	}
	else if constexpr(sizeof(char_type)==1&&
		::fast_io::details::streamreflect::has_scatter_write_all_overflow_define<outstmtype>)
	{
		io_scatter_t sc{first,static_cast<::std::size_t>(last-first)};
		scatter_write_all_bytes_overflow_define(outsm,__builtin_addressof(sc),1);
		return last;
	}
#if 0
	else if constexpr(::fast_io::details::has_output_stream_seek_bytes_define<outstmtype>)
	{
		::std::byte const* ret{::fast_io::details::pwrite_some_bytes_cold_impl(outsm,first,last)};
		output_stream_seek_bytes_define(outsm,ret-first,::fast_io::seekdir::cur);
		return ret;
	}
#endif
}

template<typename outstmtype>
#if __has_cpp_attribute(__gnu__::__cold__)
[[__gnu__::__cold__]]
#endif
inline constexpr void write_all_cold_impl(outstmtype outsm,typename outstmtype::output_char_type const *first,typename outstmtype::output_char_type const *last)
{
	using char_type = typename outstmtype::output_char_type;
	if constexpr(::fast_io::details::streamreflect::has_write_all_overflow_define<outstmtype>)
	{
		write_all_overflow_define(outsm,first,last);
	}
	else if constexpr(::fast_io::details::streamreflect::has_scatter_write_all_overflow_define<outstmtype>)
	{
		basic_io_scatter_t<char_type> sc{first,static_cast<::std::size_t>(last-first)};
		scatter_write_all_overflow_define(outsm,__builtin_addressof(sc),1);
	}
	else if constexpr(::fast_io::details::streamreflect::has_write_some_overflow_define<outstmtype>)
	{
		if constexpr(::fast_io::details::streamreflect::has_obuffer_ops<outstmtype>)
		{
			while((first=write_some_overflow_define(outsm,first,last))!=last)
			{
				char_type *curr{obuffer_curr(outsm)};
				char_type *ed{obuffer_end(outsm)};
				::std::ptrdiff_t bfddiff{ed-curr};
				::std::ptrdiff_t itdiff{last-first};
				if(itdiff<bfddiff)
				{
					obuffer_set_curr(outsm,non_overlapped_copy_n(first,static_cast<::std::size_t>(itdiff),curr));
					return;
				}
			}
		}
		else
		{
			while((first=write_some_overflow_define(outsm,first,last))!=last);
		}
	}
	else if constexpr(::fast_io::details::streamreflect::has_scatter_write_some_overflow_define<outstmtype>)
	{
		if constexpr(::fast_io::details::streamreflect::has_obuffer_ops<outstmtype>)
		{
			for(;;)
			{
				basic_io_scatter_t<char_type> sc{first,static_cast<::std::size_t>(last-first)};
				first+=scatter_write_some_bytes_overflow_define(outsm,__builtin_addressof(sc),1).total_size;
				if(first!=last)
				{
					return;
				}
				char_type *curr{obuffer_curr(outsm)};
				char_type *ed{obuffer_end(outsm)};
				::std::ptrdiff_t bfddiff{ed-curr};
				::std::ptrdiff_t itdiff{last-first};
				if(itdiff<bfddiff)
				{
					obuffer_set_curr(outsm,non_overlapped_copy_n(first,static_cast<::std::size_t>(itdiff),curr));
					return;
				}
			}
		}
		else
		{
			for(;;)
			{
				basic_io_scatter_t<char_type> sc{first,static_cast<::std::size_t>(last-first)};
				first+=scatter_write_some_bytes_overflow_define(outsm,__builtin_addressof(sc),1).total_size;
				if(first!=last)
				{
					return;
				}
			}
		}
	}
	else if constexpr(
		(::fast_io::details::streamreflect::has_write_all_bytes_overflow_define<outstmtype>||
		::fast_io::details::streamreflect::has_scatter_write_all_bytes_overflow_define<outstmtype>||
		::fast_io::details::streamreflect::has_write_some_bytes_overflow_define<outstmtype>||
		::fast_io::details::streamreflect::has_scatter_write_some_bytes_overflow_define<outstmtype>))
	{
		write_all_bytes_cold_impl(outsm,
			reinterpret_cast<::std::byte const*>(first),
			reinterpret_cast<::std::byte const*>(last));
	}
}

template<typename outstmtype>
#if __has_cpp_attribute(__gnu__::__cold__)
[[__gnu__::__cold__]]
#endif
inline constexpr void write_all_bytes_cold_impl(outstmtype outsm,::std::byte const *first,::std::byte const *last)
{
	using char_type = typename outstmtype::output_char_type;
	if constexpr(::fast_io::details::streamreflect::has_write_all_bytes_overflow_define<outstmtype>)
	{
		write_all_bytes_overflow_define(outsm,first,last);
	}
	else if constexpr(::fast_io::details::streamreflect::has_scatter_write_all_bytes_overflow_define<outstmtype>)
	{
		io_scatter_t sc{first,static_cast<::std::size_t>(last-first)};
		scatter_write_all_bytes_overflow_define(outsm,__builtin_addressof(sc),1);
	}
	else if constexpr(::fast_io::details::streamreflect::has_write_some_bytes_overflow_define<outstmtype>)
	{
		if constexpr(::fast_io::details::streamreflect::has_obuffer_ops<outstmtype>&&sizeof(char_type)==1)
		{
			while((first=write_some_bytes_overflow_define(outsm,first,last))!=last)
			{
				char_type *curr{obuffer_curr(outsm)};
				char_type *ed{obuffer_end(outsm)};
				::std::ptrdiff_t bfddiff{ed-curr};
				::std::ptrdiff_t itdiff{last-first};
				if(itdiff<bfddiff)
				{
					obuffer_set_curr(outsm,non_overlapped_copy_n(first,static_cast<::std::size_t>(itdiff),curr));
					return;
				}
			}
		}
		else
		{
			while((first=write_some_bytes_overflow_define(outsm,first,last))!=last);
		}
	}
	else if constexpr(::fast_io::details::streamreflect::has_scatter_write_some_bytes_overflow_define<outstmtype>)
	{
		if constexpr(::fast_io::details::streamreflect::has_obuffer_ops<outstmtype>)
		{
			for(;;)
			{
				io_scatter_t sc{first,static_cast<::std::size_t>(last-first)};
				first+=scatter_write_some_bytes_overflow_define(outsm,__builtin_addressof(sc),1).total_size;
				if(first!=last)
				{
					return;
				}
				char_type *curr{obuffer_curr(outsm)};
				char_type *ed{obuffer_end(outsm)};
				::std::ptrdiff_t bfddiff{ed-curr};
				::std::ptrdiff_t itdiff{last-first};
				if(itdiff<bfddiff)
				{
					obuffer_set_curr(outsm,non_overlapped_copy_n(first,static_cast<::std::size_t>(itdiff),curr));
					return;
				}
			}
		}
		else
		{
			for(;;)
			{
				io_scatter_t sc{first,static_cast<::std::size_t>(last-first)};
				first+=scatter_write_some_bytes_overflow_define(outsm,__builtin_addressof(sc),1).total_size;
				if(first!=last)
				{
					return;
				}
			}
		}
	}
	else if constexpr(sizeof(char_type)==1&&
		(::fast_io::details::streamreflect::has_write_all_overflow_define<outstmtype>||
		::fast_io::details::streamreflect::has_write_some_overflow_define<outstmtype>||
		::fast_io::details::streamreflect::has_scatter_write_some_overflow_define<outstmtype>||
		::fast_io::details::streamreflect::has_scatter_write_all_overflow_define<outstmtype>))
	{
		using char_type_const_ptr
#if __has_cpp_attribute(__gnu__::__may_alias__)
		[[__gnu__::__may_alias__]]
#endif
		=
		char_type const*;
		char_type_const_ptr firstcptr{reinterpret_cast<char_type_const_ptr>(first)};
		char_type_const_ptr lastcptr{reinterpret_cast<char_type_const_ptr>(last)};
		::fast_io::details::write_all_cold_impl(outsm,firstcptr,lastcptr);
	}
}

template<typename outstmtype>
inline constexpr typename outstmtype::output_char_type const* write_some_impl(outstmtype outsm,typename outstmtype::output_char_type const *first,typename outstmtype::output_char_type const *last)
{
	using char_type = typename outstmtype::output_char_type;
	if constexpr(::fast_io::details::mutex_unlocked_buffer_output_stream_impl<outstmtype>)
	{
		::fast_io::operations::stream_ref_lock_guard lg{output_stream_mutex_ref_impl(outsm)};
		return ::fast_io::details::write_some_impl(::fast_io::details::output_stream_unlocked_ref_impl(outsm),first,last);
	}
	if constexpr(::fast_io::details::streamreflect::has_obuffer_ops<outstmtype>)
	{
		char_type *curr{obuffer_curr(outsm)};
		char_type *ed{obuffer_end(outsm)};
		::std::ptrdiff_t bfddiff{ed-curr};
		::std::ptrdiff_t itdiff{last-first};
		if(itdiff<bfddiff)
#if __has_cpp_attribute(__gnu__::__may_alias__)
[[likely]]
#endif
		{
			obuffer_set_curr(outsm,non_overlapped_copy_n(first,static_cast<::std::size_t>(itdiff),curr));
			return last;
		}
	}
	return ::fast_io::details::write_some_cold_impl(outsm,first,last);
}

template<typename outstmtype>
inline constexpr void write_all_impl(outstmtype outsm,
	typename outstmtype::output_char_type const *first,
	typename outstmtype::output_char_type const *last)
{
	if constexpr(::fast_io::details::mutex_unlocked_buffer_output_stream_impl<outstmtype>)
	{
		::fast_io::operations::stream_ref_lock_guard lg{output_stream_mutex_ref_impl(outsm)};
		return ::fast_io::details::write_all_impl(::fast_io::details::output_stream_unlocked_ref_impl(outsm),first,last);
	}
	using char_type = typename outstmtype::output_char_type;
	if constexpr(::fast_io::details::streamreflect::has_obuffer_ops<outstmtype>)
	{
		char_type *curr{obuffer_curr(outsm)};
		char_type *ed{obuffer_end(outsm)};
		::std::ptrdiff_t bfddiff{ed-curr};
		::std::ptrdiff_t itdiff{last-first};
		if(itdiff<bfddiff)
#if __has_cpp_attribute(__gnu__::__may_alias__)
[[likely]]
#endif
		{
			obuffer_set_curr(outsm,non_overlapped_copy_n(first,static_cast<::std::size_t>(itdiff),curr));
			return;
		}
	}
	::fast_io::details::write_all_cold_impl(outsm,first,last);
}

template<typename outstmtype>
inline constexpr ::std::byte const* write_some_bytes_impl(outstmtype outsm,::std::byte const *first,::std::byte const *last)
{
	using char_type = typename outstmtype::output_char_type;
	if constexpr(::fast_io::details::mutex_unlocked_buffer_output_stream_impl<outstmtype>)
	{
		::fast_io::operations::stream_ref_lock_guard lg{output_stream_mutex_ref_impl(outsm)};
		return ::fast_io::details::write_some_bytes_impl(::fast_io::details::output_stream_unlocked_ref_impl(outsm),first,last);
	}
	if constexpr(::fast_io::details::streamreflect::has_obuffer_ops<outstmtype>&&sizeof(char_type)==1)
	{
		char_type *curr{obuffer_curr(outsm)};
		char_type *ed{obuffer_end(outsm)};
		::std::ptrdiff_t bfddiff{ed-curr};
		::std::ptrdiff_t itdiff{last-first};
		if(itdiff<bfddiff)
#if __has_cpp_attribute(__gnu__::__may_alias__)
[[likely]]
#endif
		{
			obuffer_set_curr(outsm,non_overlapped_copy_n(first,static_cast<::std::size_t>(itdiff),curr));
			return last;
		}
	}
	return ::fast_io::details::write_some_bytes_cold_impl(outsm,first,last);
}

template<typename outstmtype>
inline constexpr void write_all_bytes_impl(outstmtype outsm,
	::std::byte const *first,::std::byte const *last)
{
	if constexpr(::fast_io::details::mutex_unlocked_buffer_output_stream_impl<outstmtype>)
	{
		::fast_io::operations::stream_ref_lock_guard lg{output_stream_mutex_ref_impl(outsm)};
		return ::fast_io::details::write_all_bytes_impl(::fast_io::details::output_stream_unlocked_ref_impl(outsm),first,last);
	}
	using char_type = typename outstmtype::output_char_type;
	if constexpr(::fast_io::details::streamreflect::has_obuffer_ops<outstmtype>&&sizeof(char_type)==1)
	{
		char_type *curr{obuffer_curr(outsm)};
		char_type *ed{obuffer_end(outsm)};
		::std::ptrdiff_t bfddiff{ed-curr};
		::std::ptrdiff_t itdiff{last-first};
		if(itdiff<bfddiff)
#if __has_cpp_attribute(__gnu__::__may_alias__)
[[likely]]
#endif
		{
			obuffer_set_curr(outsm,non_overlapped_copy_n(first,static_cast<::std::size_t>(itdiff),curr));
			return;
		}
	}
	::fast_io::details::write_all_bytes_cold_impl(outsm,first,last);
}

}

}
