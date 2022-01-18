﻿/*##########################################################################################

	Crafterra Sample Source Code 🌏

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

#include <DxLib.h>

// Crafterra 
#include <Crafterra.hpp>

#include <memory>

#include <chrono>

namespace Crafterra {

	namespace System {
		void crafterraMain(::Crafterra::Resource& resource_) {

			ActorDirection cdt = ::Crafterra::Enum::actor_direction_down;
			int cd_anime = 0; // アニメーション
			int cd_anime_sea = 0; // アニメーション

			int time_count = 0;
			const int time_count_max = 5;

			::DxLib::PlaySoundMem(resource_.getMusic().getMusic(), DX_PLAYTYPE_LOOP, TRUE);


			CoordinateSystem cs(resource_.getWindowWidth(), resource_.getWindowHeight());


			using FieldMapMatrix = ::Crafterra::DataType::Matrix<MapChip, init_field_map_width, init_field_map_height>; // 世界
			using FieldMapMatrixPtr = ::std::unique_ptr<FieldMapMatrix>; // 世界

			FieldMapMatrixPtr map_chip_type_biome_map_matrix_ptr(CRAFTERRA_NEW FieldMapMatrix); // フィールドマップのポインタ
			if (!map_chip_type_biome_map_matrix_ptr) return; // メモリ確保できなかった時は return

			FieldMapMatrix& field_map_matrix = (*map_chip_type_biome_map_matrix_ptr); // フィールドマップ

			terrain(field_map_matrix);

			InputKey key;

			// OperationActorStateInFieldMap operation_actor_state_in_field = operation_actor_state_in_field_map_airship;
			OperationActorStateInFieldMap operation_actor_state_in_field = ::Crafterra::Enum::operation_actor_state_in_field_map_walking;
			cs.setMapChipSize(64.f);

			ElapsedTime elapsed_time;

			while (::Crafterra::System::Update()) {
				elapsed_time.update();
				const Int64 elapsed = elapsed_time.getMicroseconds();

				clsDx();
				printfDx("%d micro sec/f\n", int(elapsed));

				++time_count;
				if (time_count >= time_count_max) {
					time_count = 0;

					++cd_anime;
					if (cd_anime == 4) {
						cd_anime = 0;
					}
					++cd_anime_sea;
					if (cd_anime_sea == 8) {
						cd_anime_sea = 0;
					}
				}
				float key_displacement = 0.f;
				// フィールドマップにおける操作アクタの状態
				switch (operation_actor_state_in_field) {

					//----------------------------------------------------------------------------------------------------
					// 🚶 人間 ( 陸を歩行する者 ) 🚶 
				case ::Crafterra::Enum::operation_actor_state_in_field_map_walking:
					key_displacement = 0.2f;
					break;

					//----------------------------------------------------------------------------------------------------
					// 🛸 飛空艇 ( 空を飛んでいる者 ) 🛸 
				case ::Crafterra::Enum::operation_actor_state_in_field_map_airship:
					key_displacement = 2.f;
					break;
				}

				// キー関連
				{
					key.setKey();
					if(     key.getKey(KEY_INPUT_LSHIFT) == 0
						&& key.getKey(KEY_INPUT_RSHIFT) == 0
						&& key.getKey(KEY_INPUT_LCONTROL) == 0
						&& key.getKey(KEY_INPUT_RCONTROL) == 0
						&& key.getKey(KEY_INPUT_LALT) == 0
						&& key.getKey(KEY_INPUT_RALT) == 0
						&& key.getKey(KEY_INPUT_LWIN) == 0
						&& key.getKey(KEY_INPUT_RWIN) == 0
						)
					{
						{
							if (key.getKey(KEY_INPUT_A) >= 1 || key.getKey(KEY_INPUT_LEFT) >= 1) {
								cs.camera_size.moveX(-key_displacement);
								cdt = ::Crafterra::Enum::actor_direction_left;
							}
							if (key.getKey(KEY_INPUT_D) >= 1 || key.getKey(KEY_INPUT_RIGHT) >= 1) {
								cs.camera_size.moveX(key_displacement);
								cdt = ::Crafterra::Enum::actor_direction_right;
							}
							if (key.getKey(KEY_INPUT_W) >= 1 || key.getKey(KEY_INPUT_UP) >= 1) {
								cs.camera_size.moveY(-key_displacement);
								cdt = ::Crafterra::Enum::actor_direction_up;
							}
							if (key.getKey(KEY_INPUT_S) >= 1 || key.getKey(KEY_INPUT_DOWN) >= 1) {
								cs.camera_size.moveY(key_displacement);
								cdt = ::Crafterra::Enum::actor_direction_down;
							}
						}
						if (key.getKey(KEY_INPUT_G) == 1) {
							terrain(field_map_matrix);
						}
						if (key.getKey(KEY_INPUT_J) >= 1) {
							cs.setMapChipWidth(cs.map_chip_size.getWidth() * 0.995f);
							cs.setMapChipHeight(cs.map_chip_size.getHeight() * 0.995f);

							const float re_init_csx = float(cs.window_size.getWidth()) / cs.map_chip_size.getWidth();
							const float re_init_csy = float(cs.window_size.getHeight()) / cs.map_chip_size.getHeight();
							cs.camera_size.setWidth(re_init_csx);
							cs.camera_size.setHeight(re_init_csy);
						}
						if (key.getKey(KEY_INPUT_K) >= 1) {
							cs.setMapChipWidth(cs.map_chip_size.getWidth() * 1.005f);
							cs.setMapChipHeight(cs.map_chip_size.getHeight() * 1.005f);

							const float re_init_csx = float(cs.window_size.getWidth()) / cs.map_chip_size.getWidth();
							const float re_init_csy = float(cs.window_size.getHeight()) / cs.map_chip_size.getHeight();
							cs.camera_size.setWidth(re_init_csx);
							cs.camera_size.setHeight(re_init_csy);
						}
						if (key.getDownKey(KEY_INPUT_1)) {

							cs.setMapChipSize(6.f);

							operation_actor_state_in_field = ::Crafterra::Enum::operation_actor_state_in_field_map_airship;
						}
						if (key.getDownKey(KEY_INPUT_2)) {

							cs.setMapChipSize(64.f);

							operation_actor_state_in_field = ::Crafterra::Enum::operation_actor_state_in_field_map_walking;
						}
					}
				}
				{
					// 描画関数
					cs.updateCamera(
						[&](const float csx_, const float csy_, const float cw_, const float ch_, const ::Crafterra::DataType::IndexUint x_, const ::Crafterra::DataType::IndexUint y_) {

							const MapChip& field_map = field_map_matrix[y_][x_];

							const int start_x = int(csx_ + 0.5f);
							const int start_y = int(csy_ + 0.5f);
							const int center_x = int(csx_ + cw_ / 2.f + 0.5f);
							const int center_y = int(csy_ + ch_ / 2.f + 0.5f);
							const int end_x = int(csx_ + cw_ + 0.5f);
							const int end_y = int(csy_ + ch_ + 0.5f);

							// 崖を先に描画
							if (field_map.getIsCliff()) {
								if (resource_.getMapChip().getMapChipCliffTopAlpha(field_map.getCliff()) == 0) {
									::DxLib::DrawExtendGraph(start_x, start_y, end_x, end_y,
										resource_.getMapChip().getMapChip(0), TRUE);
								}
								::DxLib::DrawExtendGraph(start_x, start_y, end_x, end_y,
									resource_.getMapChip().getMapChipCliffTop(field_map.getCliff()), TRUE);
							}
							// 海を描画
							else if (field_map.getBiome() == map_chip_type_biome_sea) {
								if (
									resource_.getMapChip().getSeaAlpha(getAutoTileIndex(field_map.getAutoTile().auto_tile_upper_left, cd_anime_sea, 8)) == 0 ||
									resource_.getMapChip().getSeaAlpha(getAutoTileIndex(field_map.getAutoTile().auto_tile_upper_right, cd_anime_sea, 8)) == 0 ||
									resource_.getMapChip().getSeaAlpha(getAutoTileIndex(field_map.getAutoTile().auto_tile_lower_left, cd_anime_sea, 8)) == 0 ||
									resource_.getMapChip().getSeaAlpha(getAutoTileIndex(field_map.getAutoTile().auto_tile_lower_right, cd_anime_sea, 8)) == 0
									) {
									::DxLib::DrawExtendGraph(start_x, start_y, end_x, end_y,
										resource_.getMapChip().getMapChip(0), TRUE);
								}
								::DxLib::DrawExtendGraph(start_x, start_y, center_x, center_y,
									resource_.getMapChip().getSea(getAutoTileIndex(field_map.getAutoTile().auto_tile_upper_left, cd_anime_sea, 8)), TRUE);
								::DxLib::DrawExtendGraph(center_x, start_y, end_x, center_y,
									resource_.getMapChip().getSea(getAutoTileIndex(field_map.getAutoTile().auto_tile_upper_right, cd_anime_sea, 8)), TRUE);
								::DxLib::DrawExtendGraph(start_x, center_y, center_x, end_y,
									resource_.getMapChip().getSea(getAutoTileIndex(field_map.getAutoTile().auto_tile_lower_left, cd_anime_sea, 8)), TRUE);
								::DxLib::DrawExtendGraph(center_x, center_y, end_x, end_y,
									resource_.getMapChip().getSea(getAutoTileIndex(field_map.getAutoTile().auto_tile_lower_right, cd_anime_sea, 8)), TRUE);
							}
							// 崖上を描画
							else if (field_map.getCliffTop() != map_chip_type_homogeneous_connection_size) {
								if (resource_.getMapChip().getMapChipCliffTopAlpha(field_map.getCliffTop()) == 0) {
									::DxLib::DrawExtendGraph(start_x, start_y, end_x, end_y,
										resource_.getMapChip().getMapChip(0), TRUE);
								}

								::DxLib::DrawExtendGraph(start_x, start_y, end_x, end_y,
									resource_.getMapChip().getMapChipCliffTop(field_map.getCliffTop()), TRUE);
							}
							// ------------------------------------------------------------------------------------------------------------------------------------
							if (field_map.getIsCliff()) return;
							if (field_map.getBiome() == map_chip_type_biome_desert) {
								::DxLib::DrawExtendGraph(start_x, start_y, center_x, center_y,
									resource_.getMapChip().getDesert(getAutoTileIndex(field_map.getAutoTile().auto_tile_upper_left, 0, 2)), TRUE);
								::DxLib::DrawExtendGraph(center_x, start_y, end_x, center_y,
									resource_.getMapChip().getDesert(getAutoTileIndex(field_map.getAutoTile().auto_tile_upper_right, 0, 2)), TRUE);
								::DxLib::DrawExtendGraph(start_x, center_y, center_x, end_y,
									resource_.getMapChip().getDesert(getAutoTileIndex(field_map.getAutoTile().auto_tile_lower_left, 0, 2)), TRUE);
								::DxLib::DrawExtendGraph(center_x, center_y, end_x, end_y,
									resource_.getMapChip().getDesert(getAutoTileIndex(field_map.getAutoTile().auto_tile_lower_right, 0, 2)), TRUE);
							}
							::DxLib::DrawExtendGraph(start_x, start_y, end_x, end_y,
								resource_.getMapChip().getMapChip(field_map.getDrawChip()), TRUE);
							//else
							//	::DxLib::DrawBox(start_x, start_y, end_x, end_y, field_map.getColor(), TRUE);

						}
					);
				}
				// 飛空艇のアニメーションを計算
				int dir = 0;
				const int cd_anime2 = ((cd_anime == 3) ? 1 : cd_anime);
				switch (cdt) {
				case ::Crafterra::Enum::actor_direction_down:dir = 0 + cd_anime2; break;
				case ::Crafterra::Enum::actor_direction_left: dir = 3 + cd_anime2; break;
				case ::Crafterra::Enum::actor_direction_right:dir = 6 + cd_anime2; break;
				case ::Crafterra::Enum::actor_direction_up:   dir = 9 + cd_anime2; break;
				}
				// カメラの中心を描画
				//::DxLib::DrawCircle(cs.window_size.getWidth() / 2, cs.window_size.getHeight() / 2, cs.map_chip_size.getWidthHalf(), 0x00111111, TRUE);

				//----------------------------------------------------------------------------------------------------
				// フィールドマップにおける操作アクタの状態
				switch (operation_actor_state_in_field) {

					//----------------------------------------------------------------------------------------------------
					// 🚶 人間 ( 陸を歩行する者 ) 🚶 
				case ::Crafterra::Enum::operation_actor_state_in_field_map_walking:

					::DxLib::DrawRotaGraph(cs.window_size.getWidth() / 2, cs.window_size.getHeight() / 2,
						cs.map_chip_size.getWidthHalf() / 16, 0.0,
						resource_.getCharacterChip().getCharacterChip(1, dir), TRUE, FALSE);
					break;

					//----------------------------------------------------------------------------------------------------
					// 🚢 船 ( 海上に浮かんでいる者 ) 🚢 
				case ::Crafterra::Enum::operation_actor_state_in_field_map_ship:
					break;

					//----------------------------------------------------------------------------------------------------
					// 🛸 飛空艇 ( 空を飛んでいる者 ) 🛸 
				case ::Crafterra::Enum::operation_actor_state_in_field_map_airship:
					// 飛空艇の影を描画
					::DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
					::DxLib::DrawOval(int(cs.window_size.getWidth() / 2), int(cs.window_size.getHeight() / 2 + cs.map_chip_size.getHeight() * 32),
						int(cs.map_chip_size.getWidthHalf() * 8), int(cs.map_chip_size.getHeightHalf() * 4), 0x00111111, TRUE);
					::DxLib::SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

					// 飛空艇を描画
					::DxLib::DrawRotaGraph(cs.window_size.getWidth() / 2, cs.window_size.getHeight() / 2,
						cs.map_chip_size.getWidthHalf(), 0.0,
						resource_.getCharacterChip().getCharacterChip(0, dir), TRUE, FALSE);
					break;

				default:
					break;
				}
				//----------------------------------------------------------------------------------------------------

				// 座標を文字として出力
				//DrawFormatStringToHandle(10, 50, GetColor(255, 255, 255), resource_.getFont().getFont(),
				DrawBox(0, 0, 200, 180, 0x44444444, TRUE);
				printfDx(
					u8"カメラ中央X: %.2f\nカメラ中央Y: %.2f\nカメラ開始X: %.2f\nカメラ終了Y: %.2f\n1:飛空艇視点\n2:人間視点\nJ:カメラを遠ざける\nK:カメラを近づける\nバイオーム: %s\n%d"
					, cs.camera_size.getCenterX(), cs.camera_size.getCenterY()
					, cs.camera_size.getStartX(), cs.camera_size.getStartY()
					, MapChipTypeBiomeString[field_map_matrix[IndexUint(cs.camera_size.getCenterY())][IndexUint(cs.camera_size.getCenterX())].getBiome()].c_str()
					//, int(getAutoTileIndex(field_map_matrix[100][100].getAutoTile().auto_tile_lower_left, 0, 1))
					, resource_.getMapChip().getDesert(getAutoTileIndex(field_map_matrix[100][100].getAutoTile().auto_tile_lower_left, 0, 0))
					//, field_map_matrix[100][100].getCliffTop()
				);
			}

		}

	}
}