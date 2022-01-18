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
		DxGraphArray<4 * 10> cliff_top{};
		DxGraphArray<16 * 10> sea{};
		DxGraphArray<4 * 10> desert{};
		Uint8 sea_alpha[16 * 10] = {
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
			,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
			,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
			,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
			,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
			,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
			,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
			,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
			,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
			,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
		};

		Uint8 cliff_top_alpha[4 * 10] = {
			0,1,1,0
			,1,0,0,0
			,1,1,0,0
			,1,1,0,0
			,1,1,1,0
			,1,1,1,0
			,1,1,1,0
			,1,1,1,0
			,1,1,1,1
			,0,0,0,0
		};

	public:

		MapChipImage() {
			::DxLib::LoadDivGraph("./../../../resource/Picture/Chip/Map/Base(pipo).png", 8 * 249,
				8, 249,
				32, 32, base_map.getPtr());

			::DxLib::LoadDivGraph("./../../../resource/Picture/Chip/AutoTile/Cliff(pipoya).png", 4 * 10,
				4, 10,
				32, 32, cliff_top.getPtr());

			::DxLib::LoadDivGraph("./../../../resource/Picture/Chip/AutoTile/Water1(pipoya).png", 16 * 10,
				16, 10,
				16, 16, sea.getPtr());
			::DxLib::LoadDivGraph("./../../../resource/Picture/Chip/AutoTile/[A]Dirt3_pipo.png", 4 * 10,
				4, 10,
				16, 16, desert.getPtr());
		}

		~MapChipImage() {

		}

		DxGraphInt getMapChip(const IndexUint index_) const { return this->base_map.get(index_); }
		DxGraphInt getSea(const IndexUint index_) const { return this->sea.get(index_); }
		DxGraphInt getDesert(const IndexUint index_) const { return this->desert.get(index_); }
		Uint8 getSeaAlpha(const IndexUint index_) const { return this->sea_alpha[index_]; }
		DxGraphInt getMapChipCliffTop(const IndexUint index_) const { return this->cliff_top.get(index_); }
		Uint8 getMapChipCliffTopAlpha(const IndexUint index_) const { return this->cliff_top_alpha[index_]; }

	};
}

#endif //Included Crafterra Library