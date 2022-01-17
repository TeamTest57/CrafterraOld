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
#include <Crafterra/DataType/ArrayDataType.hpp>
#include <Crafterra/DataType/StringDataType.hpp>

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
	::Crafterra::DataType::Array<::Crafterra::DataType::String, map_chip_type_biome_size>
		MapChipTypeBiomeString{ {
				u8"無し",u8"海",u8"湖",u8"山",u8"砂漠",u8"森林",u8"岩山",u8"丘",u8"サバンナ",u8"草原",u8"壁",u8"道",u8"部屋",u8"通常"
	} };

	// 同じ性質のブロックとの接続タイプ ( 通常 + 崖 )
	enum MapChipTypeHomogeneousConnection : Uint8 {
		map_chip_type_homogeneous_connection_nothing
		, map_chip_type_homogeneous_connection_all
		, map_chip_type_homogeneous_connection_up_down
		, map_chip_type_homogeneous_connection_left_right
		, map_chip_type_homogeneous_connection_up
		, map_chip_type_homogeneous_connection_left
		, map_chip_type_homogeneous_connection_right
		, map_chip_type_homogeneous_connection_down
		, map_chip_type_homogeneous_connection_up_left_0
		, map_chip_type_homogeneous_connection_up_right_0
		, map_chip_type_homogeneous_connection_left_down_0
		, map_chip_type_homogeneous_connection_right_down_0
		, map_chip_type_homogeneous_connection_up_left_1
		, map_chip_type_homogeneous_connection_up_right_1
		, map_chip_type_homogeneous_connection_left_down_1
		, map_chip_type_homogeneous_connection_right_down_1
		, map_chip_type_homogeneous_connection_up_left_right_0
		, map_chip_type_homogeneous_connection_up_left_down_0
		, map_chip_type_homogeneous_connection_up_right_down_0
		, map_chip_type_homogeneous_connection_left_right_down_0
		, map_chip_type_homogeneous_connection_up_left_right_1
		, map_chip_type_homogeneous_connection_up_left_down_1
		, map_chip_type_homogeneous_connection_up_right_down_1
		, map_chip_type_homogeneous_connection_left_right_down_1
		, map_chip_type_homogeneous_connection_up_left_right_2
		, map_chip_type_homogeneous_connection_up_left_down_2
		, map_chip_type_homogeneous_connection_up_right_down_2
		, map_chip_type_homogeneous_connection_left_right_down_2
		, map_chip_type_homogeneous_connection_up_left_right_3
		, map_chip_type_homogeneous_connection_up_left_down_3
		, map_chip_type_homogeneous_connection_up_right_down_3
		, map_chip_type_homogeneous_connection_left_right_down_3
		, map_chip_type_homogeneous_connection_right_down_cliff
		, map_chip_type_homogeneous_connection_left_right_down_cliff
		, map_chip_type_homogeneous_connection_left_down_cliff
		, map_chip_type_homogeneous_connection_down_cliff
		, map_chip_type_homogeneous_connection_right_up_cliff
		, map_chip_type_homogeneous_connection_left_right_up_cliff
		, map_chip_type_homogeneous_connection_left_up_cliff
		, map_chip_type_homogeneous_connection_up_cliff
		, map_chip_type_homogeneous_connection_size
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

		MapChipTypeHomogeneousConnection cliff_top{ map_chip_type_homogeneous_connection_size };
		MapChipTypeHomogeneousConnection cliff{ map_chip_type_homogeneous_connection_size };
		bool is_cliff = false;

		ElevationUint elevation{}; // 元の標高値
		ElevationUint block_elevation{}; // ブロックの高さに合わせた標高値
		ElevationUint elevation3{}; // カメラの位置にずらした、ブロックの高さに合わせた標高値
		
		int draw_chip = -1;

	public:

		// 同じ性質のブロックとの接続タイプ ( 崖 )
		MapChipTypeHomogeneousConnection getHomogeneousConnectionCliff(
			  const bool left_
			, const bool right_
			, const bool down_
		) const {
			if (down_) {
				if (left_) {
					if (right_) return map_chip_type_homogeneous_connection_left_right_down_cliff;
					else        return map_chip_type_homogeneous_connection_left_down_cliff;
				}
				else {
					if (right_) return map_chip_type_homogeneous_connection_right_down_cliff;
					else        return map_chip_type_homogeneous_connection_down_cliff;
				}
			}
			else {
				if (left_) {
					if (right_) return map_chip_type_homogeneous_connection_left_right_up_cliff;
					else        return map_chip_type_homogeneous_connection_left_up_cliff;
				}
				else {
					if (right_) return map_chip_type_homogeneous_connection_right_up_cliff;
					else        return map_chip_type_homogeneous_connection_up_cliff;
				}
			}
		}
		// 同じ性質のブロックとの接続タイプ ( 通常 )
		MapChipTypeHomogeneousConnection getHomogeneousConnection(
			  const bool up_
			, const bool left_
			, const bool right_
			, const bool down_
			, const bool upper_left_
			, const bool upper_right_
			, const bool lower_left_
			, const bool lower_right_
		) const {
			MapChipTypeHomogeneousConnection mcthc = map_chip_type_homogeneous_connection_all;

			if (up_) {
				if (left_) {
					if (right_) {
						if (down_) return   map_chip_type_homogeneous_connection_all;
						else        mcthc = map_chip_type_homogeneous_connection_up_left_right_0;
					}
					else {
						if (down_) mcthc = map_chip_type_homogeneous_connection_up_left_down_0;
						else        mcthc = map_chip_type_homogeneous_connection_up_left_0;
					}
				}
				else {
					if (right_) {
						if (down_) mcthc = map_chip_type_homogeneous_connection_up_right_down_0;
						else        mcthc = map_chip_type_homogeneous_connection_up_right_0;
					}
					else {
						if (down_) return   map_chip_type_homogeneous_connection_up_down;
						else        return   map_chip_type_homogeneous_connection_up;
					}
				}
			}
			else {
				if (left_) {
					if (right_) {
						if (down_) mcthc = map_chip_type_homogeneous_connection_left_right_down_0;
						else        return   map_chip_type_homogeneous_connection_left_right;
					}
					else {
						if (down_) mcthc = map_chip_type_homogeneous_connection_left_down_0;
						else        return   map_chip_type_homogeneous_connection_left;
					}
				}
				else {
					if (right_) {
						if (down_) mcthc = map_chip_type_homogeneous_connection_right_down_0;
						else        return   map_chip_type_homogeneous_connection_right;
					}
					else {
						if (down_) return   map_chip_type_homogeneous_connection_down;
						else        return   map_chip_type_homogeneous_connection_nothing;
					}
				}
			}
			return mcthc;
		}


		template<typename Type_>
		MapChipTypeHomogeneousConnection getHomogeneousConnectionValueElevation3(
			  const Type_ center_
			, const Type_ up_
			, const Type_ left_
			, const Type_ right_
			, const Type_ down_
			, const Type_ upper_left_
			, const Type_ upper_right_
			, const Type_ lower_left_
			, const Type_ lower_right_
		) const {
			return getHomogeneousConnection(
				center_ == up_
				, center_ == left_
				, center_ == right_
				, center_ <= down_
				, center_ == upper_left_
				, center_ == upper_right_
				, center_ == lower_left_
				, center_ == lower_right_
			);
		}

		template<typename Type_>
		MapChipTypeHomogeneousConnection getHomogeneousConnectionCliffValueElevation3(
			  const Type_ center_
			, const Type_ left_
			, const Type_ right_
			, const Type_ down_
		) const {
			return getHomogeneousConnectionCliff(
				center_ == left_
				, center_ == right_
				, center_ == down_
			);
		}

		template<typename Type_>
		MapChipTypeHomogeneousConnection getHomogeneousConnectionValue(
			const Type_ center_
			, const Type_ up_
			, const Type_ left_
			, const Type_ right_
			, const Type_ down_
			, const Type_ upper_left_
			, const Type_ upper_right_
			, const Type_ lower_left_
			, const Type_ lower_right_
		) const {
			return getHomogeneousConnection(
				center_ == up_
				, center_ == left_
				, center_ == right_
				, center_ == down_
				, center_ == upper_left_
				, center_ == upper_right_
				, center_ == lower_left_
				, center_ == lower_right_
			);
		}

		template<typename Matrix_, typename Type_>
		MapChipTypeHomogeneousConnection getHomogeneousConnectionArray(
			const Matrix_ matrix_
			, const Type_ x_
			, const Type_ y_
		) const {
			return getHomogeneousConnectionValue(
				matrix_[y_ - 1][x_]
				, matrix_[y_][x_ - 1]
				, matrix_[y_][x_ + 1]
				, matrix_[y_ + 1][x_]
				, matrix_[y_ - 1][x_ - 1]
				, matrix_[y_ - 1][x_ + 1]
				, matrix_[y_ + 1][x_ - 1]
				, matrix_[y_ + 1][x_ + 1]
			);
		}

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
				case map_chip_type_biome_forest:
					draw_chip = 1;
					break;
				case map_chip_type_biome_rock:
					draw_chip = 7;
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
		ElevationUint getBlockElevation() const {
			return this->block_elevation;
		}
		void setBlockElevation(const ElevationUint& elevation_) {
			this->block_elevation = elevation_;
		}
		// 暫定
		ElevationUint getElevation3() const {
			return this->elevation3;
		}
		void setElevation3(const ElevationUint& elevation_) {
			this->elevation3 = elevation_;
		}


		// 暫定
		MapChipTypeHomogeneousConnection getCliffTop() const {
			return this->cliff_top;
		}
		void setCliffTop(const MapChipTypeHomogeneousConnection& cliff_top_) {
			this->cliff_top = cliff_top_;
		}
		MapChipTypeHomogeneousConnection getCliff() const {
			return this->cliff;
		}
		void setCliff(const MapChipTypeHomogeneousConnection& cliff_) {
			this->cliff = cliff_;
		}
		// 崖であるかどうか？
		bool getIsCliff() const {
			return this->is_cliff;
		}
		void setIsCliff(const bool is_cliff_) {
			this->is_cliff = is_cliff_;
		}

	};

}

#endif //Included Crafterra Library