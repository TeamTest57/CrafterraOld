/*#######################################################################################
	Crafterra Library 🌏
	Copyright (c) 2017-2022 Kasugaccho
	Copyright (c) 2018-2022 As Project
	https://github.com/AsPJT/Crafterra
	wanotaitei@gmail.com
	Distributed under the CC0 1.0. (See accompanying
	file LICENSE_for_include_directory.txt or copy at https://creativecommons.org/publicdomain/zero/1.0/)
#######################################################################################*/

#ifndef INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_BASIC_TYPE_HPP
#define INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_BASIC_TYPE_HPP

#include <cstddef> // size_t
#include <cstdint> // [,u]int[8,16,32,64]_t

namespace Crafterra {

	// 配列の添え字に使用する型
	using IndexUint = ::std::size_t;
	using Int32 = ::std::int_fast32_t;
	using Uint32 = ::std::uint_fast32_t;

}

#endif //Included Crafterra Library