/*#######################################################################################
	Crafterra Library 🌏
	Copyright (c) 2017-2022 Kasugaccho
	Copyright (c) 2018-2022 As Project
	https://github.com/AsPJT/Crafterra
	wanotaitei@gmail.com
	Distributed under the Boost Software License, Version 1.0. (See accompanying
	file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#######################################################################################*/

#ifndef INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_HPP
#define INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_HPP

// マクロ定義 重要度：高
#include <Crafterra/Basic/Version.hpp>

#include <Crafterra/Basic/Size2D.hpp>

namespace Crafterra {

	class Font;
	class Music;
	class MapChipImage;
	class CharacterChipImage;

	class CrafterraManager {

		// 各種素材のポインタ
	private:
		Font* font = nullptr;
		Music* music = nullptr;
		MapChipImage* map_chip = nullptr;
		CharacterChipImage* character_chip = nullptr;

	public:
		void setFont(Font* font_) { this->font = font_; }
		Font& getFont() { return *(this->font); }
		void setMusic(Music* music_) { this->music = music_; }
		Music& getMusic() { return *(this->music); }
		void setMapChip(MapChipImage* map_chip_) { this->map_chip = map_chip_; }
		MapChipImage& getMapChip() { return *(this->map_chip); }
		void setCharacterChip(CharacterChipImage* character_chip_) { this->character_chip = character_chip_; }
		CharacterChipImage& getCharacterChip() { return *(this->character_chip); }

	private:
		int window_width = 0;
		int window_height = 0;

	public:
		void setWindowWidth(const int window_width_) { this->window_width = window_width_; }
		void setWindowHeight(const int window_height_) { this->window_height = window_height_; }
		int getWindowWidth() const { return this->window_width; }
		int getWindowHeight() const { return this->window_height; }

	};

	// キャラの向き
	enum CameraDir : unsigned int {
		camera_type_empty
		, camera_type_up
		, camera_type_down
		, camera_type_left
		, camera_type_right
		, camera_type_size
	};

}


// Crafterra のメイン関数を宣言
#ifndef CRAFTERRA_MAIN_FUNCTION
#define CRAFTERRA_MAIN_FUNCTION
namespace Crafterra {
	namespace System {
		void crafterraMain(::Crafterra::CrafterraManager&);
	}
}
#endif // CRAFTERRA_MAIN_FUNCTION


namespace Crafterra {
	namespace System {
		// 初期のウィンドウの幅
		constexpr int init_window_width = 1280;
		// 初期のウィンドウの高さ
		constexpr int init_window_height = 720;
	}

	// マップサイズ
	constexpr std::size_t size_x{ 1024 };
	constexpr std::size_t size_y{ 1024 };

}



// 初回読み込み
#include <Crafterra/Basic/InitRead.hpp>


namespace Crafterra {
	namespace Color {
		// 色クラス ( 暫定 )
		using Color3 = unsigned int;
	}
}

#include <Crafterra/Basic/CoordinateSystem.hpp>

#include <Crafterra/Map/MapChip.hpp>

#ifdef __DXLIB
#include <Crafterra/ThirdParty/DxLib/DxKeyboard.hpp>
#include <Crafterra/ThirdParty/DxLib/DxFont.hpp>
#include <Crafterra/ThirdParty/DxLib/DxMusic.hpp>
#include <Crafterra/ThirdParty/DxLib/DxMapChip.hpp>
#include <Crafterra/ThirdParty/DxLib/DxCharacterChip.hpp>

// DxLib 系の中でも 1 番遅く include する
#include <Crafterra/ThirdParty/DxLib/CrafterraForDxLib.hpp>

#else

namespace Crafterra {
	class Font {};
	class Music {};
	class MapChipImage {};

}

#endif

#include <Crafterra/Generation/FieldMap.hpp>

#endif //Included Crafterra Library