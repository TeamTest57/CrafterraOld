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

#ifndef INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_BASIC_RESOURCE_HPP
#define INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_BASIC_RESOURCE_HPP

#include <Crafterra/DataType/PrimitiveDataType.hpp>

namespace Crafterra {

	class Font;
	class Music;
	class MapChipImage;
	class CharacterChipImage;

	class Resource {

		// 各種素材のポインタ
	private:
		Font* font = nullptr;
		Music* music = nullptr;
		MapChipImage* map_chip = nullptr;
		CharacterChipImage* character_chip = nullptr;

	public:
		void setFont(Font& font_) { this->font = &font_; }
		Font& getFont() { return *(this->font); }
		void setMusic(Music& music_) { this->music = &music_; }
		Music& getMusic() { return *(this->music); }
		void setMapChip(MapChipImage& map_chip_) { this->map_chip = &map_chip_; }
		MapChipImage& getMapChip() { return *(this->map_chip); }
		void setCharacterChip(CharacterChipImage& character_chip_) { this->character_chip = &character_chip_; }
		CharacterChipImage& getCharacterChip() { return *(this->character_chip); }

	private:
		IndexUint window_width = 0;
		IndexUint window_height = 0;

	public:
		void setWindowWidth(const ::Crafterra::DataType::IndexUint window_width_) { this->window_width = window_width_; }
		void setWindowHeight(const ::Crafterra::DataType::IndexUint window_height_) { this->window_height = window_height_; }
		::Crafterra::DataType::IndexUint getWindowWidth() const { return this->window_width; }
		::Crafterra::DataType::IndexUint getWindowHeight() const { return this->window_height; }
	};

}

#endif //Included Crafterra Library