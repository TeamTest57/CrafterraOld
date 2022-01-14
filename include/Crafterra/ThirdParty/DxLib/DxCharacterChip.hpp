/*#######################################################################################
	Crafterra Library 🌏
	Copyright (c) 2017-2022 Kasugaccho
	Copyright (c) 2018-2022 As Project
	https://github.com/AsPJT/Crafterra
	wanotaitei@gmail.com
	Distributed under the CC0 1.0. (See accompanying
	file LICENSE_for_include_directory.txt or copy at https://creativecommons.org/publicdomain/zero/1.0/)
#######################################################################################*/

#ifndef INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_THIRD_PARTY_DXLIB_DX_CHARACTER_CHIP_HPP
#define INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_THIRD_PARTY_DXLIB_DX_CHARACTER_CHIP_HPP

#include <vector>

namespace Crafterra {

	// キャラチップの状態
	struct CharacterChipStatus {
		int move_num = 4;
		int animation_num = 3;
		int size_x = 32;
		int size_y = 32;
	};

	class CharacterChipImage {
	private:

		// 0 1 2
		// 3 4 5
		// 6 7 8
		// 9 a b
		::std::vector<int> character_chip{};
		::std::vector<int> character_start_index_chip{};
		int start_index = 0;
		//int player_index = 0;

		void add(const int move_num_, const int animation_num_, const std::string& file_name_) {
			const int all_num = move_num_ * animation_num_;
			character_chip.resize(character_chip.size() + all_num);
			::DxLib::LoadDivGraph(file_name_.c_str(),
				all_num, animation_num_, move_num_, 32, 32, &character_chip[start_index]);
			// そのキャラの開始インデックスを格納
			character_start_index_chip.emplace_back(start_index);
			start_index += all_num;
		}

	public:

		CharacterChipImage() {
			this->add(4, 3, "./../../../resource/Picture/Chip/Character/pipo-airship01.png");
			this->add(4, 3, "./../../../resource/Picture/Chip/Character/pipo-charachip026c.png");
		}

		~CharacterChipImage() {

		}

		int getCharacterChip(const int character_id, const int index) const {
			return this->character_chip[this->character_start_index_chip[character_id] + index];
		}

	};
}

#endif //Included Crafterra Library