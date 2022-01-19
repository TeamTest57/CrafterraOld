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

#include <Crafterra/Map/HomogeneousConnection.hpp>


// 地形生成用 ( 後に削除予定 )
#include <DTL.hpp>

namespace Crafterra {

	unsigned int getDxColor(const int r_, const int g_, const int b_) {
		return (r_ * 256 + g_) * 256 + b_;
	}

	template<typename Matrix_>
	void perlinNoise(
		Matrix_& matrix_,
		const IndexUint chunk_index_x_, const IndexUint chunk_index_y_, const IndexUint one_chunk_width_, const IndexUint one_chunk_height_,
		const IndexUint start_x_, const IndexUint start_y_, const IndexUint end_x_, const IndexUint end_y_,
		::dtl::utility::PerlinNoise<double>& perlin, const double frequency_, const IndexUint octaves_,
		const ElevationUint max_height_, const ElevationUint min_height_ = 0) {

		for (IndexUint row_index{ start_y_ }, row{}; row_index < end_y_; ++row_index, ++row)
			for (IndexUint col_index{ start_x_ }, col{}; col_index < end_x_; ++col_index, ++col)
				matrix_[row_index][col_index] =
				min_height_ + static_cast<ElevationUint>(
				(max_height_ - min_height_) *
					perlin.octaveNoise(octaves_,
					(Uint64(chunk_index_x_) * Uint64(one_chunk_width_) + Uint64(col)) / frequency_,
						((Uint64(chunk_index_y_) * Uint64(one_chunk_height_) + Uint64(row)) / frequency_)
					)
					);
	}


	class Terrain {

		// 暫定的なマップデータ
		using MapMat = ::Crafterra::DataType::Matrix<MapChip, init_field_map_width, init_field_map_height>;
		using shape_t = ElevationUint;

		//温度
		std::unique_ptr<shape_t[][init_field_map_width] > temperature;
		//降水量
		std::unique_ptr<shape_t[][init_field_map_width] > amount_of_rainfall;
		//標高
		std::unique_ptr<shape_t[][init_field_map_width] > elevation;

		Uint32 temperature_seed;
		Uint32 amount_of_rainfall_seed;
		Uint32 elevation_seed;

		::dtl::utility::PerlinNoise<double> perlin_temperature_seed;
		::dtl::utility::PerlinNoise<double> perlin_amount_of_rainfall_seed;
		::dtl::utility::PerlinNoise<double> perlin_elevation_seed;

	public:

		Terrain(const Uint32 temperature_seed_, const Uint32 amount_of_rainfall_seed_, const Uint32 elevation_seed_)
			:temperature(CRAFTERRA_NEW shape_t[init_field_map_height][init_field_map_width])
			, amount_of_rainfall(CRAFTERRA_NEW shape_t[init_field_map_height][init_field_map_width])
			, elevation(CRAFTERRA_NEW shape_t[init_field_map_height][init_field_map_width])
			, temperature_seed(temperature_seed_)
			, amount_of_rainfall_seed(amount_of_rainfall_seed_)
			, elevation_seed(elevation_seed_)
			, perlin_temperature_seed(1)
			, perlin_amount_of_rainfall_seed(1)
			, perlin_elevation_seed(1)
		{

		}

		void setTerrain(MapMat& field_map_matrix) const {


			//std::random_device seed_gen;
			//std::mt19937 engine(seed_gen());
			//std::bernoulli_distribution uid(0.01);

			for (::Crafterra::DataType::IndexUint row{}; row < init_field_map_height; ++row)
				for (::Crafterra::DataType::IndexUint col{}; col < init_field_map_width; ++col) {
					MapChip& field_map = field_map_matrix[row][col];

					const ElevationUint elevation2 = field_map.getBlockElevation();
					ElevationUint elevation3 = 0;
					for (::Crafterra::DataType::IndexUint row3{ row }; elevation3 <= elevation2; --row3, ++elevation3) {
						if (field_map_matrix[row3][col].getElevation3() < elevation3) field_map_matrix[row3][col].setElevation3(elevation3);
						if (row3 == 0) break;
					}

					switch (field_map.getBiome()) {
					case map_chip_type_biome_sea:
						field_map.setColor(getDxColor(33, 97, 124));
						break;
					case map_chip_type_biome_lake:
						field_map.setColor(getDxColor(88, 124, 139));
						break;
					case map_chip_type_biome_mountain:
						field_map.setColor(getDxColor(101, 100, 60));
						break;
					case map_chip_type_biome_desert:
						field_map.setColor(getDxColor(217, 195, 143));
						break;
					case map_chip_type_biome_forest:
						field_map.setColor(getDxColor(110, 149, 59));
						break;
					case map_chip_type_biome_rock:
						field_map.setColor(getDxColor(120, 125, 108));
						break;
					case map_chip_type_biome_hill:
						field_map.setColor(getDxColor(145, 177, 113));
						break;
					case map_chip_type_biome_savannah:
						field_map.setColor(getDxColor(144, 140, 73));
						break;
					case map_chip_type_biome_grass:
						field_map.setColor(getDxColor(90, 128, 63));
						break;
					case map_chip_type_biome_wall:
						field_map.setColor(getDxColor(200, 200, 200));
						break;
					case map_chip_type_biome_way:
						field_map.setColor(getDxColor(90, 128, 63));
						break;
					case map_chip_type_biome_room:
						field_map.setColor(getDxColor(50, 160, 70));
						break;
					case map_chip_type_biome_default:
						field_map.setColor(getDxColor(170, 160, 70));
						break;
					}

					//field_map_matrix[row][col].setDrawChip();

					const Int32 row2 = row - field_map_matrix[row][col].getBlockElevation();
					if (row2 >= 0) {
						if (!field_map_matrix[row][col].getIsCliff())
							//field_map_matrix[row2][col].setDrawChip(field_map_matrix[row][col].getDrawChip());
							field_map_matrix[row2][col].setColor(field_map_matrix[row][col].getColor());
						field_map_matrix[row2][col].setDrawBiome(field_map_matrix[row][col].getBiome());
					}

				}
			// どこが崖になっているか調べる
			for (::Crafterra::DataType::Int32 col{}; col < init_field_map_width; ++col)
				for (::Crafterra::DataType::Int32 row{ 1 }; row < init_field_map_height; ++row) {
					if (field_map_matrix[row][col].getElevation3() < field_map_matrix[row - 1][col].getElevation3()) {
						field_map_matrix[row][col].setIsCliff(true); // 崖
					}
				}
			// 崖のオートタイルを計算
			for (::Crafterra::DataType::Int32 col{ 1 }; col < init_field_map_width - 1; ++col)
				for (::Crafterra::DataType::Int32 row{}; row < init_field_map_height - 1; ++row) {
					field_map_matrix[row][col].setCliff(
						getHomogeneousConnectionCliff(
							field_map_matrix[row][col - 1].getIsCliff() || ((!field_map_matrix[row][col - 1].getIsCliff()) && field_map_matrix[row][col].getElevation3() < field_map_matrix[row][col - 1].getElevation3())
							, field_map_matrix[row][col + 1].getIsCliff() || ((!field_map_matrix[row][col + 1].getIsCliff()) && field_map_matrix[row][col].getElevation3() < field_map_matrix[row][col + 1].getElevation3())
							, field_map_matrix[row + 1][col].getIsCliff()
						)
					);
				}

			for (::Crafterra::DataType::Int32 col{ 1 }; col < init_field_map_width - 1; ++col)
				for (::Crafterra::DataType::Int32 row{ 1 }; row < init_field_map_height - 1; ++row) {
					if (field_map_matrix[row][col].getIsCliff()) continue;
					// 崖上のオートタイルを計算 ( 一部バグがあり、未完成 )
					field_map_matrix[row][col].setCliffTop(
						getHomogeneousConnectionValueElevation3(
							field_map_matrix[row][col].getElevation3()
							, field_map_matrix[row - 1][col].getElevation3()
							, field_map_matrix[row][col - 1].getElevation3()
							, field_map_matrix[row][col + 1].getElevation3()
							, field_map_matrix[row + 1][col].getElevation3()
							, field_map_matrix[row - 1][col - 1].getElevation3()
							, field_map_matrix[row - 1][col + 1].getElevation3()
							, field_map_matrix[row + 1][col - 1].getElevation3()
							, field_map_matrix[row + 1][col + 1].getElevation3()
						));
					// ウディタ規格オートタイルの計算
					// 同質接続の条件：同じバイオーム＆同じ標高＆崖ではない
					field_map_matrix[row][col].setAutoTile(
						getHomogeneousConnectionAutoTile(
							field_map_matrix[row - 1][col].getDrawBiome() == field_map_matrix[row][col].getDrawBiome() && field_map_matrix[row - 1][col].getElevation3() == field_map_matrix[row][col].getElevation3() && (!field_map_matrix[row - 1][col].getIsCliff())
							, field_map_matrix[row][col - 1].getDrawBiome() == field_map_matrix[row][col].getDrawBiome() && field_map_matrix[row][col - 1].getElevation3() == field_map_matrix[row][col].getElevation3() && (!field_map_matrix[row][col - 1].getIsCliff())
							, field_map_matrix[row][col + 1].getDrawBiome() == field_map_matrix[row][col].getDrawBiome() && field_map_matrix[row][col + 1].getElevation3() == field_map_matrix[row][col].getElevation3() && (!field_map_matrix[row][col + 1].getIsCliff())
							, field_map_matrix[row + 1][col].getDrawBiome() == field_map_matrix[row][col].getDrawBiome() && field_map_matrix[row + 1][col].getElevation3() == field_map_matrix[row][col].getElevation3() && (!field_map_matrix[row + 1][col].getIsCliff())
							, field_map_matrix[row - 1][col - 1].getDrawBiome() == field_map_matrix[row][col].getDrawBiome() && field_map_matrix[row - 1][col - 1].getElevation3() == field_map_matrix[row][col].getElevation3() && (!field_map_matrix[row - 1][col - 1].getIsCliff())
							, field_map_matrix[row - 1][col + 1].getDrawBiome() == field_map_matrix[row][col].getDrawBiome() && field_map_matrix[row - 1][col + 1].getElevation3() == field_map_matrix[row][col].getElevation3() && (!field_map_matrix[row - 1][col + 1].getIsCliff())
							, field_map_matrix[row + 1][col - 1].getDrawBiome() == field_map_matrix[row][col].getDrawBiome() && field_map_matrix[row + 1][col - 1].getElevation3() == field_map_matrix[row][col].getElevation3() && (!field_map_matrix[row + 1][col - 1].getIsCliff())
							, field_map_matrix[row + 1][col + 1].getDrawBiome() == field_map_matrix[row][col].getDrawBiome() && field_map_matrix[row + 1][col + 1].getElevation3() == field_map_matrix[row][col].getElevation3() && (!field_map_matrix[row + 1][col + 1].getIsCliff())
						)
					);
					// オブジェクトの自動配置の実験
					// 海でも崖でもない時
					//if (field_map_matrix[row][col].getBiome() != map_chip_type_biome_sea && (!field_map_matrix[row][col].getIsCliff())) {
					//	if (uid(engine)) {
					//		if (field_map_matrix[row][col].getBiome() == map_chip_type_biome_default) {
					//			field_map_matrix[row][col].setDrawChip(52); // 花を設置
					//		}
					//		else {
					//			field_map_matrix[row][col].setDrawChip(64); // 石を設置
					//		}
					//	}
					//}
				}
		}

		void perlinNoiseGeneration(const IndexUint chunk_index_x_, const IndexUint chunk_index_y_, const Uint32 start_x_, const Uint32 start_y_, const Uint32 end_x_, const Uint32 end_y_) {
			//温度
			perlinNoise(
				temperature,
				chunk_index_x_, chunk_index_y_, init_field_map_width / 2, init_field_map_height / 2,
				start_x_, start_y_, end_x_, end_y_,
				perlin_temperature_seed, 120.0, 6,
				240, 100
			);

			//降水量
			perlinNoise(
				amount_of_rainfall,
				chunk_index_x_, chunk_index_y_, init_field_map_width / 2, init_field_map_height / 2,
				start_x_, start_y_, end_x_, end_y_,
				perlin_amount_of_rainfall_seed, 120.0, 6,
				225, 0
			);

			//標高
			perlinNoise(
				elevation,
				chunk_index_x_, chunk_index_y_, init_field_map_width / 2, init_field_map_height / 2,
				start_x_, start_y_, end_x_, end_y_,
				perlin_elevation_seed, 70.0, 6,
				195, 0
			);
		}

		//void moveTerrain(MapMat& field_map_matrix, const Uint32 field_width_half_, const Uint32 start_x_, const Uint32 start_y_, const Uint32 end_x_, const Uint32 end_y_) {
		//	for (::Crafterra::DataType::IndexUint row{ start_y_ }; row < end_y_; ++row)
		//		for (::Crafterra::DataType::IndexUint col{ start_x_  }; col < end_x_; ++col) {
		//			field_map_matrix[row][col] = field_map_matrix[row][col];
		//		}
		//}

		void moveUpTerrain(MapMat& field_map_matrix, const Uint32 field_width_half_, const Uint32 start_x_, const Uint32 start_y_, const Uint32 end_x_, const Uint32 end_y_) {
			for (::Crafterra::DataType::IndexUint row{ start_y_ }; row < end_y_; ++row)
				for (::Crafterra::DataType::IndexUint col{ start_x_ }; col < end_x_; ++col) {
					field_map_matrix[row][col] = field_map_matrix[row + field_width_half_][col];
				}
		}
		void moveDownTerrain(MapMat& field_map_matrix, const Uint32 field_width_half_, const Uint32 start_x_, const Uint32 start_y_, const Uint32 end_x_, const Uint32 end_y_) {
			for (::Crafterra::DataType::IndexUint row{ start_y_ }; row < end_y_; ++row)
				for (::Crafterra::DataType::IndexUint col{ start_x_ }; col < end_x_; ++col) {
					field_map_matrix[row + field_width_half_][col] = field_map_matrix[row][col];
				}
		}
		void moveLeftTerrain(MapMat& field_map_matrix, const Uint32 field_height_half_) {
			for (::Crafterra::DataType::IndexUint row{}; row < init_field_map_height; ++row)
				for (::Crafterra::DataType::IndexUint col{}; col < field_height_half_; ++col) {
					field_map_matrix[row][col] = MapChip(); // フィールドマップの全ての値を初期化
					field_map_matrix[row][col].setBiome(field_map_matrix[row][col + field_height_half_].getBiome());
					field_map_matrix[row][col].setElevation(field_map_matrix[row][col + field_height_half_].getElevation());
					field_map_matrix[row][col].setBlockElevation(field_map_matrix[row][col + field_height_half_].getBlockElevation());
				}
		}
		void moveRightTerrain(MapMat& field_map_matrix, const Uint32 field_height_half_, const Uint32 start_x_, const Uint32 start_y_, const Uint32 end_x_, const Uint32 end_y_) {
			for (::Crafterra::DataType::IndexUint row{ start_y_ }; row < end_y_; ++row)
				for (::Crafterra::DataType::IndexUint col{ start_x_ }; col < end_x_; ++col) {
					field_map_matrix[row][col] = field_map_matrix[row + field_height_half_][col];
				}
		}

		// フィールドマップを生成
		void generation(MapMat& field_map_matrix, const IndexUint chunk_index_x_, const IndexUint chunk_index_y_, const Uint32 start_x_, const Uint32 start_y_, const Uint32 end_x_, const Uint32 end_y_) {

			perlinNoiseGeneration(chunk_index_x_, chunk_index_y_, start_x_, start_y_, end_x_, end_y_);

			//バイオームの分類分け
			for (::Crafterra::DataType::IndexUint row{ start_y_ }; row < end_y_; ++row)
				for (::Crafterra::DataType::IndexUint col{ start_x_ }; col < end_x_; ++col) {
					MapChip& field_map = field_map_matrix[row][col];
					field_map = MapChip(); // フィールドマップの全ての値を初期化

					temperature[row][col] -= elevation[row][col] / 2;
					if (elevation[row][col] < 110) {
						field_map.setBiome(map_chip_type_biome_sea);
					}
					else
						if (temperature[row][col] < 45) field_map.setBiome(map_chip_type_biome_rock);
						else if (amount_of_rainfall[row][col] < 25) field_map.setBiome(map_chip_type_biome_savannah);
						else if (amount_of_rainfall[row][col] < 75) {
							if (temperature[row][col] < 120) field_map.setBiome(map_chip_type_biome_desert);
							else field_map.setBiome(map_chip_type_biome_desert);
						}
						else if (temperature[row][col] < 69) field_map.setBiome(map_chip_type_biome_grass);
						else if (temperature[row][col] < 96) field_map.setBiome(map_chip_type_biome_default);
						else if (temperature[row][col] < 120) field_map.setBiome(map_chip_type_biome_forest);
						else if (amount_of_rainfall[row][col] < 125) field_map.setBiome(map_chip_type_biome_mountain);
						else if (temperature[row][col] < 132) field_map.setBiome(map_chip_type_biome_mountain);
						else field_map.setBiome(map_chip_type_biome_mountain);

					// 海
					if (field_map.getBiome() == map_chip_type_biome_sea) {
						field_map.setElevation(110);
						field_map.setBlockElevation(110 / 16);
					}
					else {
						field_map.setElevation(elevation[row][col]);
						field_map.setBlockElevation(elevation[row][col] / 16);
					}
				}
			setTerrain(field_map_matrix);
		}
		void initialGeneration(MapMat& field_map_matrix_) {
			generation(field_map_matrix_, 0, 0, 0, 0, init_field_map_width, init_field_map_height);
		}
		void initialGeneration2(MapMat& field_map_matrix_, const IndexUint chunk_index_x_, const IndexUint chunk_index_y_) {
			generation(field_map_matrix_, chunk_index_x_, chunk_index_y_, 0, 0, init_field_map_width, init_field_map_height);
		}

	};

}

#endif //Included Crafterra Library