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

#ifndef INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_THIRD_PARTY_DXLIB_DXMAPCHIP_HPP
#define INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_THIRD_PARTY_DXLIB_DXMAPCHIP_HPP

#include <Crafterra/DataType/PrimitiveDataType.hpp>
#include <Crafterra/ThirdParty/DxLib/DxDataType.hpp>

namespace Crafterra {

	class MapChipImage {
	private:

		DxGraphArray<8 * 249> base_map{};
		DxGraphArray<4 * 8> cliff_top{};

	public:

		MapChipImage() {
			::DxLib::LoadDivGraph("./../../../resource/Picture/Chip/Map/Base(pipo).png", 8 * 249,
				8, 249,
				32, 32, base_map.getPtr());

			::DxLib::LoadDivGraph("./../../../resource/Picture/Chip/AutoTile/Cliff(pipoya).png", 4 * 10,
				4, 10,
				32, 32, cliff_top.getPtr());
		}

		~MapChipImage() {

		}

		DxGraphInt getMapChip(const IndexUint index_) const { return this->base_map.get(index_); }
		DxGraphInt getMapChipCliffTop(const IndexUint index_) const { return this->cliff_top.get(index_); }

	};
}

#endif //Included Crafterra Library