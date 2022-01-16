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

#ifndef INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_GENERATION_FIELD_MAP_HPP
#define INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_GENERATION_FIELD_MAP_HPP

#include <Crafterra/DataType/ArrayDataType.hpp>
#include <Crafterra/Map/MapChip.hpp>

#include <Crafterra/DataType/PrimitiveDataType.hpp>
#include <Crafterra/DataType/CrafterraPrimitiveDataType.hpp>

#include <memory>
#include <Crafterra/Macro/New.hpp> // CRAFTERRA_NEW


// 地形生成用 ( 後に削除予定 )
#include <DTL.hpp>

namespace Crafterra {

	template<typename Matrix_>
	void perlinNoise(
		Matrix_& matrix_,
		const IndexUint chunk_x_, const IndexUint chunk_y_, const IndexUint chunk_max_x_, const IndexUint chunk_max_y_,
		const IndexUint start_x_, const IndexUint start_y_, const IndexUint end_x_, const IndexUint end_y_,
		const Uint32 rand_, const double frequency_, const IndexUint octaves_, 
		const ElevationUint max_height_, const ElevationUint min_height_ = 0) {

		const ::dtl::utility::PerlinNoise<double> perlin(rand_);
		const double frequency_x{ (end_x_ - start_x_) / frequency_ };
		const double frequency_y{ (end_y_ - start_y_) / frequency_ };

		for (::dtl::type::size row{ start_y_ }; row < end_y_; ++row)
			for (::dtl::type::size col{ start_x_ }; col < end_x_; ++col)
				matrix_[col][row] = 
					min_height_ + static_cast<ElevationUint>((max_height_ - min_height_) * 
						perlin.octaveNoise(octaves_, (chunk_x_ * chunk_max_x_ + col) / frequency_x, row / (chunk_y_ * chunk_max_y_ + frequency_y)));
	}

	// フィールドマップを生成
	void terrain(::Crafterra::DataType::Matrix<MapChip, init_field_map_width, init_field_map_height>& field_map_matrix) {
		using shape_t = ElevationUint;

		std::random_device seed_gen;
		std::mt19937 engine(seed_gen());

		//温度
		std::unique_ptr<shape_t[][init_field_map_width] > temperature(CRAFTERRA_NEW shape_t[init_field_map_height][init_field_map_width]);
		//dtl::shape::PerlinIsland<shape_t>(12.0, 6, 240, 100).draw(temperature, init_field_map_width, init_field_map_height);
		perlinNoise(
			temperature,
			0, 0, init_field_map_width, init_field_map_height,
			0, 0, init_field_map_width, init_field_map_height,
			engine(), 12.0, 6,
			240, 100
		);

		//降水量
		std::unique_ptr<shape_t[][init_field_map_width] > amount_of_rainfall(CRAFTERRA_NEW shape_t[init_field_map_height][init_field_map_width]);
		// dtl::shape::PerlinIsland<shape_t>(12.0, 6, 225).draw(amount_of_rainfall, init_field_map_width, init_field_map_height);
		perlinNoise(
			amount_of_rainfall,
			0, 0, init_field_map_width, init_field_map_height,
			0, 0, init_field_map_width, init_field_map_height,
			engine(), 12.0, 6,
			225, 0
		);

		//標高
		std::unique_ptr<shape_t[][init_field_map_width] > elevation(CRAFTERRA_NEW shape_t[init_field_map_height][init_field_map_width]);
		// dtl::shape::PerlinIsland<shape_t>(7.0, 6, 195).draw(elevation, init_field_map_width, init_field_map_height);
		perlinNoise(
			elevation,
			0, 0, init_field_map_width, init_field_map_height,
			0, 0, init_field_map_width, init_field_map_height,
			engine(), 7.0, 6,
			195, 0
		);
		//dtl::shape::PerlinSolitaryIsland<shape_t>(0.3, 0.4, 7.0, 6, 155).draw(elevation, init_field_map_width, init_field_map_height);

		//std::unique_ptr<shape_t[][init_field_map_width] > land(CRAFTERRA_NEW shape_t[init_field_map_height][init_field_map_width]);

		//バイオーム
		//std::unique_ptr<shape_t[][init_field_map_width] > biome(new(std::nothrow) shape_t[init_field_map_height][init_field_map_width]);

		//バイオームの分類分け
		for (::Crafterra::DataType::IndexUint row{}; row < init_field_map_height; ++row)
			for (::Crafterra::DataType::IndexUint col{}; col < init_field_map_width; ++col) {

				temperature[row][col] -= elevation[row][col] / 2;
				//land[row][col] = 1;
				if (elevation[row][col] < 110) {
					field_map_matrix[row][col].setBiome(map_chip_type_biome_sea);
					//land[row][col] = 0;
				}
				else 
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

		// dtl::retouch::Bucket<shape_t>(1, 0, 0).draw(land, init_field_map_width, init_field_map_height);

		//dtl::shape::RogueLike<shape_t>(map_chip_type_biome_sea,
		//	map_chip_type_biome_wall, map_chip_type_biome_room, map_chip_type_biome_way, map_chip_type_biome_way, 100,
		//	dtl::base::MatrixRange(7, 7, 2, 2),
		//	dtl::base::MatrixRange(7, 7, 4, 4)).draw(biome, init_field_map_width, init_field_map_height);

		//dtl::shape::RogueLike<shape_t>(map_chip_type_biome_lake,
		//	map_chip_type_biome_wall, map_chip_type_biome_room, map_chip_type_biome_way, map_chip_type_biome_way, 100,
		//	dtl::base::MatrixRange(7, 7, 2, 2),
		//	dtl::base::MatrixRange(7, 7, 4, 4)).draw(biome, init_field_map_width, init_field_map_height);

		for (::Crafterra::DataType::IndexUint row{}; row < init_field_map_height; ++row)
			for (::Crafterra::DataType::IndexUint col{}; col < init_field_map_width; ++col) {
				//if (elevation[row][col] < 110 && land[row][col] == 0) {
				//	field_map_matrix[row][col].setBiome(map_chip_type_biome_lake);
				//}
				// 海
				if (elevation[row][col] < 110) {
					field_map_matrix[row][col].setElevation(110);
					field_map_matrix[row][col].setElevation2(110 / 8);
				}
				else {
					field_map_matrix[row][col].setElevation(elevation[row][col]);
					field_map_matrix[row][col].setElevation2(elevation[row][col] / 8);
				}

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

				field_map_matrix[row][col].setDrawChip();

			}

		for (::Crafterra::DataType::IndexUint col{ 1 }; col < init_field_map_width - 1; ++col)
			for (::Crafterra::DataType::IndexUint row{ 1 }; row < init_field_map_height - 1; ++row) {

				// for (::Crafterra::DataType::IndexUint row2{ row + 1 }, count = 1; row2 < init_field_map_height; ++row2, ++count) {
				for (::Crafterra::DataType::IndexUint row2{ init_field_map_height - 1 - 1 }, count = init_field_map_height - row - 1; row2 > 0; --row2, --count) {
					if (field_map_matrix[row2][col].getElevation2() >= count) {

						// 下が崖の場合
						if (field_map_matrix[row2][col].getElevation2() > count) {
							field_map_matrix[row][col].setDrawChip(8 * 12 + 1);
						}
						// 下がちょうど地面の場合
						else if (field_map_matrix[row2][col].getElevation2() == count) {
							field_map_matrix[row][col].setDrawChip(field_map_matrix[row2][col].getDrawChip());
							field_map_matrix[row][col].setColor(field_map_matrix[row2][col].getColor());

							// 実験
							// field_map_matrix[row][col].setDrawChip(field_map_matrix[row2][col].getElevation()/8);
						}
						// 実験
						//field_map_matrix[row][col].setElevation(field_map_matrix[row2][col].getElevation());
						break;
					}
				}
			}

	}

}

#endif //Included Crafterra Library