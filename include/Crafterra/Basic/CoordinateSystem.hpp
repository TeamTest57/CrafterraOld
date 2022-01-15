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

#ifndef INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_BASIC_COORDINATE_SYSTEM_HPP
#define INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_BASIC_COORDINATE_SYSTEM_HPP

#include <Crafterra/DataType/PrimitiveDataType.hpp>

namespace Crafterra {

	class CoordinateSystem {
	public:

		using cs_uint = IndexUint;
		using cs_f32 = float;

		using UintSize2D = ::Crafterra::Size2D<cs_uint>;
		using FloatSize2D = ::Crafterra::Size2D<cs_f32>;

		// ウィンドウの大きさ
		UintSize2D window_size;
		// フィールドマップの大きさ
		UintSize2D field_map_size;
		// マップチップの大きさ
		FloatSize2D map_chip_size;
		// カメラの大きさ
		FloatSize2D camera_size;
		// マップグリッドの大きさ
		UintSize2D map_grid_size;

		CoordinateSystem(const int ww_, const int wh_) :
			window_size(ww_, wh_)
			, field_map_size(size_x, size_y)
			, map_chip_size(4.f, 4.f)
			, camera_size(
				field_map_size.getCenterX() - (cs_f32(window_size.getWidth()) / map_chip_size.getWidth()) / 2,
				field_map_size.getCenterY() - (cs_f32(window_size.getHeight()) / map_chip_size.getHeight()) / 2,
				(cs_f32(window_size.getWidth()) / map_chip_size.getWidth()), (cs_f32(window_size.getHeight()) / map_chip_size.getHeight()))
			, map_grid_size(1, 1)
		{
		}

		// 2D カメラ ( マップのピクセル数が一律の場合のみ使用可能 )
		template<typename Draw_>
		void updateCamera(Draw_ drawRect_) {
			const cs_uint sy = cs_uint((::std::int32_t(this->camera_size.getStartY()) < ::std::int32_t(this->field_map_size.getStartY())) ?
				cs_uint(this->field_map_size.getStartY()) : cs_uint(this->camera_size.getStartY()));

			cs_f32 camera_y =
				((::std::int32_t(this->camera_size.getStartY()) >= ::std::int32_t(this->field_map_size.getStartY())) ?
				((cs_f32(::std::int32_t(this->camera_size.getStartY())) - this->camera_size.getStartY()) * cs_f32(this->map_chip_size.getHeight())) :
					(cs_f32(this->window_size.getHeightHalf()) - (this->camera_size.getCenterY() - cs_f32(this->field_map_size.getStartY())) * cs_f32(this->map_chip_size.getHeight())));

			for (cs_uint y = sy; y < this->field_map_size.getEndY(); ++y) {

				const cs_uint sx = cs_uint((::std::int32_t(this->camera_size.getStartX()) < ::std::int32_t(this->field_map_size.getStartX())) ?
					cs_uint(this->field_map_size.getStartX()) : cs_uint(this->camera_size.getStartX()));

				cs_f32 camera_x =
					((::std::int32_t(this->camera_size.getStartX()) >= ::std::int32_t(this->field_map_size.getStartX())) ?
					((cs_f32(::std::int32_t(this->camera_size.getStartX())) - this->camera_size.getStartX()) * cs_f32(this->map_chip_size.getWidth())) :
						(cs_f32(this->window_size.getWidthHalf()) - (this->camera_size.getCenterX() - cs_f32(this->field_map_size.getStartX())) * cs_f32(this->map_chip_size.getWidth())));

				for (cs_uint x = sx; x < this->field_map_size.getEndX(); ++x) {

					drawRect_(
						camera_x, camera_y, // 描画開始位置
						this->map_chip_size.getWidth(), this->map_chip_size.getHeight(), // 描画幅・長さ
						x, y
					);

					camera_x += this->map_chip_size.getWidth();
					if (camera_x >= this->window_size.getEndX()) break;
				}
				camera_y += this->map_chip_size.getHeight();
				if (camera_y >= this->window_size.getEndY()) break;
			}
		}

	};

}

#endif //Included Crafterra Library