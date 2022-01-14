/*#######################################################################################
	Crafterra Library 🌏
	Copyright (c) 2017-2022 Kasugaccho
	Copyright (c) 2018-2022 As Project
	https://github.com/AsPJT/Crafterra
	wanotaitei@gmail.com
	Distributed under the CC0 1.0. (See accompanying
	file LICENSE_for_include_directory.txt or copy at https://creativecommons.org/publicdomain/zero/1.0/)
#######################################################################################*/

#ifndef INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_MAP_MAP_CHIP_HPP
#define INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_MAP_MAP_CHIP_HPP

namespace Crafterra {

	using BiomeType = unsigned int;
	using BlockType = unsigned int;

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
		BiomeType biome{};
		BlockType block{};
		

	public:
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

	};

}

#endif //Included Crafterra Library