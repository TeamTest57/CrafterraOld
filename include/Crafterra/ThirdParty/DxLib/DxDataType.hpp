/*##########################################################################################

	Crafterra Library 🌏

	[Planning and Production]
	2017-2022 Kasugaccho
	2018-2022 As Project

	[Contact Us]
	wanotaitei@gmail.com
	https://github.com/AsPJT/Crafterra

	[License]
	Distributed under the CC0 1.0.
	https://creativecommons.org/publicdomain/zero/1.0/

##########################################################################################*/

#ifndef INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_THIRD_PARTY_DXLIB_DX_DATA_TYPE_HPP
#define INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_THIRD_PARTY_DXLIB_DX_DATA_TYPE_HPP

#include <Crafterra/DataType/PrimitiveDataType.hpp>

namespace Crafterra {

	using DxGraphInt = int;

	class DxGraph {
	private:
		DxGraphInt graph = -1;
	public:
		void set (const DxGraphInt graph_) { this->graph = graph_; }
		DxGraphInt get () const { return this->graph; }
	};

	template<IndexUint Index_>
	class DxGraphArray {
	private:
		DxGraphInt graph[Index_]{};
	public:
		void set(const IndexUint index_, const DxGraphInt graph_) { this->graph[index_] = graph_; }
		int get (const IndexUint index_) const { return this->graph[index_]; }
		DxGraphInt* getPtr () { return this->graph; }
	};


}

#endif //Included Crafterra Library