/*#######################################################################################
	Crafterra Library 🌏
	Copyright (c) 2017-2022 Kasugaccho
	Copyright (c) 2018-2022 As Project
	https://github.com/AsPJT/Crafterra
	wanotaitei@gmail.com
	Distributed under the CC0 1.0. (See accompanying
	file LICENSE_for_include_directory.txt or copy at https://creativecommons.org/publicdomain/zero/1.0/)
#######################################################################################*/

#ifndef INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_GENERATION_FIELD_MAP_HPP
#define INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_GENERATION_FIELD_MAP_HPP

#include <array>
#include <Crafterra/Map/MapChip.hpp>

#include <memory>
#include <new>


// 地形生成用 ( 後に削除予定 )
#include <DTL.hpp>

namespace Crafterra {

	// フィールドマップを生成
	void terrain(::std::array<::std::array<MapChip, size_x>, size_y>& field_map_matrix) {
		using shape_t = std::uint_fast16_t;

		//温度
		std::unique_ptr<shape_t[][size_x] > temperature(new(std::nothrow) shape_t[size_y][size_x]);
		dtl::shape::PerlinIsland<shape_t>(12.0, 6, 240, 100).draw(temperature, size_x, size_y);

		//降水量
		std::unique_ptr<shape_t[][size_x] > amount_of_rainfall(new(std::nothrow) shape_t[size_y][size_x]);
		dtl::shape::PerlinIsland<shape_t>(12.0, 6, 225).draw(amount_of_rainfall, size_x, size_y);

		//標高
		std::unique_ptr<shape_t[][size_x] > elevation(new(std::nothrow) shape_t[size_y][size_x]);
		dtl::shape::PerlinIsland<shape_t>(7.0, 6, 195).draw(elevation, size_x, size_y);
		//dtl::shape::PerlinSolitaryIsland<shape_t>(0.3, 0.4, 7.0, 6, 155).draw(elevation, size_x, size_y);

		std::unique_ptr<shape_t[][size_x] > land(new(std::nothrow) shape_t[size_y][size_x]);

		//バイオーム
		//std::unique_ptr<shape_t[][size_x] > biome(new(std::nothrow) shape_t[size_y][size_x]);

		//バイオームの分類分け
		for (std::size_t row{}; row < size_y; ++row)
			for (std::size_t col{}; col < size_x; ++col) {

				temperature[row][col] -= elevation[row][col] / 2;
				land[row][col] = 1;
				//if (elevation[row][col] < 110) {
				//	field_map_matrix[row][col].setBiome(map_chip_type_biome_sea);
				//	land[row][col] = 0;
				//}
				//else 
					if (temperature[row][col] < 45) field_map_matrix[row][col].setBiome(map_chip_type_biome_rock);
				else if (amount_of_rainfall[row][col] < 25) field_map_matrix[row][col].setBiome(map_chip_type_biome_savannah);
				else if (amount_of_rainfall[row][col] < 75) {
					if (temperature[row][col] < 120) field_map_matrix[row][col].setBiome(map_chip_type_biome_desert);
					else field_map_matrix[row][col].setBiome(map_chip_type_biome_desert);
				}
				else if (temperature[row][col] < 69) field_map_matrix[row][col].setBiome(map_chip_type_biome_grass);
				else if (temperature[row][col] < 96) field_map_matrix[row][col].setBiome(map_chip_type_biome_default);
				else if (temperature[row][col] < 120) field_map_matrix[row][col].setBiome(map_chip_type_biome_forest);
				else if (amount_of_rainfall[row][col] < 125) field_map_matrix[row][col].setBiome(map_chip_type_biome_mountain);
				else if (temperature[row][col] < 132) field_map_matrix[row][col].setBiome(map_chip_type_biome_mountain);
				else field_map_matrix[row][col].setBiome(map_chip_type_biome_mountain);
			}

		dtl::retouch::Bucket<shape_t>(1, 0, 0).draw(land, size_x, size_y);

		//dtl::shape::RogueLike<shape_t>(map_chip_type_biome_sea,
		//	map_chip_type_biome_wall, map_chip_type_biome_room, map_chip_type_biome_way, map_chip_type_biome_way, 100,
		//	dtl::base::MatrixRange(7, 7, 2, 2),
		//	dtl::base::MatrixRange(7, 7, 4, 4)).draw(biome, size_x, size_y);

		//dtl::shape::RogueLike<shape_t>(map_chip_type_biome_lake,
		//	map_chip_type_biome_wall, map_chip_type_biome_room, map_chip_type_biome_way, map_chip_type_biome_way, 100,
		//	dtl::base::MatrixRange(7, 7, 2, 2),
		//	dtl::base::MatrixRange(7, 7, 4, 4)).draw(biome, size_x, size_y);

		for (std::size_t row{}; row < size_y; ++row)
			for (std::size_t col{}; col < size_x; ++col) {
				if (elevation[row][col] < 110 && land[row][col] == 0) field_map_matrix[row][col].setBiome(map_chip_type_biome_lake);


				switch (field_map_matrix[row][col].getBiome()) {
				case map_chip_type_biome_sea:
					field_map_matrix[row][col].setColor(::DxLib::GetColor(33, 97, 124));
					break;
				case map_chip_type_biome_lake:
					field_map_matrix[row][col].setColor(::DxLib::GetColor(88, 124, 139));
					break;
				case map_chip_type_biome_mountain:
					field_map_matrix[row][col].setColor(::DxLib::GetColor(101, 100, 60));
					break;
				case map_chip_type_biome_desert:
					field_map_matrix[row][col].setColor(::DxLib::GetColor(217, 195, 143));
					break;
				case map_chip_type_biome_forest:
					field_map_matrix[row][col].setColor(::DxLib::GetColor(110, 149, 59));
					break;
				case map_chip_type_biome_rock:
					field_map_matrix[row][col].setColor(::DxLib::GetColor(120, 125, 108));
					break;
				case map_chip_type_biome_hill:
					field_map_matrix[row][col].setColor(::DxLib::GetColor(145, 177, 113));
					break;
				case map_chip_type_biome_savannah:
					field_map_matrix[row][col].setColor(::DxLib::GetColor(144, 140, 73));
					break;
				case map_chip_type_biome_grass:
					field_map_matrix[row][col].setColor(::DxLib::GetColor(90, 128, 63));
					break;
				case map_chip_type_biome_wall:
					field_map_matrix[row][col].setColor(::DxLib::GetColor(200, 200, 200));
					break;
				case map_chip_type_biome_way:
					field_map_matrix[row][col].setColor(::DxLib::GetColor(90, 128, 63));
					break;
				case map_chip_type_biome_room:
					field_map_matrix[row][col].setColor(::DxLib::GetColor(50, 160, 70));
					break;
				case map_chip_type_biome_default:
					field_map_matrix[row][col].setColor(::DxLib::GetColor(170, 160, 70));
					break;
				}

			}

	}

}

#endif //Included Crafterra Library