/*##########################################################################################

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
#include <new>
#include <array>

#include <random>


namespace Crafterra {

	enum PlayerMode : unsigned int {
		player_mode_empty
		,player_mode_human
		,player_mode_airship
	};

	namespace System {
		void crafterraMain(::Crafterra::CrafterraManager& cm_) {

			using CameraDirType = unsigned int;
			CameraDirType cdt = camera_type_down;
			int cd_anime = 0; // アニメーション

			int time_count = 0;
			const int time_count_max = 5;

			::DxLib::PlaySoundMem(cm_.getMusic().getMusic(), DX_PLAYTYPE_LOOP, TRUE);


			CoordinateSystem cs(cm_.getWindowWidth(), cm_.getWindowHeight());


			using FieldMapMatrix = ::std::array<::std::array<MapChip, size_x>, size_y>; // 世界
			using FieldMapMatrixPtr = ::std::unique_ptr<FieldMapMatrix>; // 世界

			FieldMapMatrixPtr map_chip_type_biome_map_matrix_ptr(new(::std::nothrow) FieldMapMatrix); // フィールドマップのポインタ
			if (!map_chip_type_biome_map_matrix_ptr) return; // メモリ確保できなかった時は return

			FieldMapMatrix& field_map_matrix = (*map_chip_type_biome_map_matrix_ptr); // フィールドマップ

			terrain(field_map_matrix);

			InputKey key;

			PlayerMode player_mode = player_mode_airship;

			while (::Crafterra::System::Update()) {
				++time_count;
				if (time_count >= time_count_max) {
					time_count = 0;

					++cd_anime;
					if (cd_anime == 4) {
						cd_anime = 0;
					}
				}

				// キー関連
				{
					key.setKey();
					if (key.getKey(KEY_INPUT_A) >= 1 || key.getKey(KEY_INPUT_LEFT) >= 1) {
						cs.camera_size.moveX(-2);
						cdt = camera_type_left;
					}
					if (key.getKey(KEY_INPUT_D) >= 1 || key.getKey(KEY_INPUT_RIGHT) >= 1) {
						cs.camera_size.moveX(2);
						cdt = camera_type_right;
					}
					if (key.getKey(KEY_INPUT_W) >= 1 || key.getKey(KEY_INPUT_UP) >= 1) {
						cs.camera_size.moveY(-2);
						cdt = camera_type_up;
					}
					if (key.getKey(KEY_INPUT_S) >= 1 || key.getKey(KEY_INPUT_DOWN) >= 1) {
						cs.camera_size.moveY(2);
						cdt = camera_type_down;
					}
					if (key.getKey(KEY_INPUT_G) == 1) {
						terrain(field_map_matrix);
					}
					if (key.getKey(KEY_INPUT_J) >= 1) {
						cs.map_chip_size.setWidth(cs.map_chip_size.getWidth() * 0.995f);
						cs.map_chip_size.setHeight(cs.map_chip_size.getHeight() * 0.995f);

						const float re_init_csx = float(cs.window_size.getWidth()) / cs.map_chip_size.getWidth();
						const float re_init_csy = float(cs.window_size.getHeight()) / cs.map_chip_size.getHeight();
						cs.camera_size.setWidth(re_init_csx);
						cs.camera_size.setHeight(re_init_csy);
					}
					if (key.getKey(KEY_INPUT_K) >= 1) {
						cs.map_chip_size.setWidth(cs.map_chip_size.getWidth() * 1.005f);
						cs.map_chip_size.setHeight(cs.map_chip_size.getHeight() * 1.005f);

						const float re_init_csx = float(cs.window_size.getWidth()) / cs.map_chip_size.getWidth();
						const float re_init_csy = float(cs.window_size.getHeight()) / cs.map_chip_size.getHeight();
						cs.camera_size.setWidth(re_init_csx);
						cs.camera_size.setHeight(re_init_csy);
					}
					if (key.getDownKey(KEY_INPUT_1)) {

						cs.map_chip_size.setWidth(6.f);
						cs.map_chip_size.setHeight(6.f);

						player_mode = player_mode_airship;
					}
					if (key.getDownKey(KEY_INPUT_2)) {

						cs.map_chip_size.setWidth(64.f);
						cs.map_chip_size.setHeight(64.f);

						player_mode = player_mode_human;
					}
				}
				{
					// 描画関数
					cs.updateCamera(
						[&](const float csx_, const float csy_, const float cw_, const float ch_, const std::size_t x_, const std::size_t y_) {

							if (field_map_matrix[y_][x_].getDrawChip() >= 0) {
								::DxLib::DrawExtendGraph(int(csx_ + 0.5f), int(csy_ + 0.5f), int(csx_ + cw_ + 0.5f), int(csy_ + ch_ + 0.5f),
									cm_.getMapChip().getMapChip(field_map_matrix[y_][x_].getDrawChip()), TRUE);
							}
							else ::DxLib::DrawBox(int(csx_ + 0.5f), int(csy_ + 0.5f), int(csx_ + cw_ + 0.5f), int(csy_ + ch_ + 0.5f), field_map_matrix[y_][x_].getColor(), TRUE);
							
							//::DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
							//::DxLib::DrawBox(int(csx_ + 0.5f), int(csy_ + 0.5f), int(csx_ + cw_ + 0.5f), int(csy_ + ch_ + 0.5f), GetColor(
							//	(field_map_matrix[y_][x_].getElevation()>=255)?0: 255-field_map_matrix[y_][x_].getElevation(),
							//	(field_map_matrix[y_][x_].getElevation()>=255)?0: 255-field_map_matrix[y_][x_].getElevation(),
							//	(field_map_matrix[y_][x_].getElevation()>=255)?0: 255-field_map_matrix[y_][x_].getElevation()
							//), TRUE);
							//::DxLib::SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
						}
					);
				}
				// 飛空艇のアニメーションを計算
				int dir = 0;
				const int cd_anime2 = ((cd_anime == 3) ? 1 : cd_anime);
				switch (cdt) {
				case camera_type_down:dir = 0 + cd_anime2; break;
				case camera_type_left:dir = 3 + cd_anime2; break;
				case camera_type_right:dir = 6 + cd_anime2; break;
				case camera_type_up:dir = 9 + cd_anime2; break;
				}
				// カメラの中心を描画
				//::DxLib::DrawCircle(cs.window_size.getWidth() / 2, cs.window_size.getHeight() / 2, cs.map_chip_size.getWidthHalf(), 0x00111111, TRUE);
				switch (player_mode)
				{
				case Crafterra::player_mode_empty:
					break;
				case Crafterra::player_mode_human:
					// 人間を描画
					::DxLib::DrawRotaGraph(cs.window_size.getWidth() / 2, cs.window_size.getHeight() / 2,
						cs.map_chip_size.getWidthHalf() / 16, 0.0,
						cm_.getCharacterChip().getCharacterChip(1, dir), TRUE, FALSE);
					break;
				case Crafterra::player_mode_airship:
					// 飛空艇の影を描画
					::DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
					::DxLib::DrawOval(int(cs.window_size.getWidth() / 2), int(cs.window_size.getHeight() / 2 + cs.map_chip_size.getHeight() * 32),
						int(cs.map_chip_size.getWidthHalf() * 8), int(cs.map_chip_size.getHeightHalf() * 4), 0x00111111, TRUE);
					::DxLib::SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

					// 飛空艇を描画
					::DxLib::DrawRotaGraph(cs.window_size.getWidth() / 2, cs.window_size.getHeight() / 2,
						cs.map_chip_size.getWidthHalf(), 0.0,
						cm_.getCharacterChip().getCharacterChip(0, dir), TRUE, FALSE);
					break;
				default:
					break;
				}

				// 座標を文字として出力
				DrawFormatStringToHandle(10, 50, GetColor(255, 255, 255), cm_.getFont().getFont(),
					"Camera Center X: %.2f Y: %.2f\nCamera Start X: %.2f Y: %.2f"
					, cs.camera_size.getCenterX(), cs.camera_size.getCenterY()
					, cs.camera_size.getStartX(), cs.camera_size.getStartY()
				);
				//WaitKey();
			}

		}

	}
}