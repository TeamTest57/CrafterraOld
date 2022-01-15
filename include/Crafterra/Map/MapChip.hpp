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

#ifndef INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_MAP_MAP_CHIP_HPP
#define INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_MAP_MAP_CHIP_HPP

#include <Crafterra/DataType/PrimitiveDataType.hpp>
#include <Crafterra/DataType/CrafterraPrimitiveDataType.hpp>

namespace Crafterra {

	// バイオームの種類
	enum MapChipTypeBiome : BiomeType {
		map_chip_type_biome_empty     // 無し
		, map_chip_type_biome_sea        // 海
		, map_chip_type_biome_lake       // 湖
		, map_chip_type_biome_mountain // 山
		, map_chip_type_biome_desert    // 砂漠
		, map_chip_type_biome_forest    // 森林
		, map_chip_type_biome_rock      // 岩山
		, map_chip_type_biome_hill       // 丘
		, map_chip_type_biome_savannah // サバンナ
		, map_chip_type_biome_grass     // 草原
		, map_chip_type_biome_wall     // 草原
		, map_chip_type_biome_way     // 草原
		, map_chip_type_biome_room     // 草原
		, map_chip_type_biome_default   // 通常の地面
		, map_chip_type_biome_size   // バイオームの数
	};

	// 148,185,32
	// 110,163,0
	// 170,212,43
	// 127,145,72
	// 201,196,119
	// 151,130,73
	// 234,226,135
	// 176,186,163

	// マップチップ情報を管理
	class MapChip {
	private:
		// マップチップの色
		::Crafterra::Color::Color3 rgb{};
		BiomeType biome{ map_chip_type_biome_empty };
		BlockType block{};
		ElevationUint elevation{};
		ElevationUint elevation2{};
		
		int draw_chip = -1;

	public:

		void setDrawChip(const int draw_chip_) {
			this->draw_chip = draw_chip_;
		}
		void setDrawChip() {
			if (block == 0) {
				if (biome == 0) {
					draw_chip = -1;
				}
				switch (biome)
				{
				case map_chip_type_biome_empty:
					draw_chip = -1;
					break;
				case map_chip_type_biome_default:
					draw_chip = 0;
					break;
				case map_chip_type_biome_mountain:
					draw_chip = 5;
					break;
				case map_chip_type_biome_desert:
					draw_chip = 6;
					break;
				}

			}
		}
		int getDrawChip() const {
			return this->draw_chip;
		}

		::Crafterra::Color::Color3 getColor() const {
			return this->rgb;
		}
		void setColor(const ::Crafterra::Color::Color3& rgb_) {
			this->rgb = rgb_;
		}
		BiomeType getBiome() const {
			return this->biome;
		}
		void setBiome(const BiomeType& biome_) {
			this->biome = biome_;
		}
		BlockType getBlock() const {
			return this->block;
		}
		void setBlock(const BlockType& block_) {
			this->block = block_;
		}
		ElevationUint getElevation() const {
			return this->elevation;
		}
		void setElevation(const ElevationUint& elevation_) {
			this->elevation = elevation_;
		}
		// 暫定
		ElevationUint getElevation2() const {
			return this->elevation2;
		}
		void setElevation2(const ElevationUint& elevation_) {
			this->elevation2 = elevation_;
		}

	};

}

#endif //Included Crafterra Library