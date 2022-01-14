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

namespace Crafterra {

	class CharacterChipImage {
	private:

// 0 1 2
// 3 4 5
// 6 7 8
// 9 a b
		int ship[12]{};

	public:

		CharacterChipImage() {
			::DxLib::LoadDivGraph("./../../../resource/Picture/Chip/Character/pipo-airship01.png", 12,
				3, 4,
				32, 32, ship);
		}

		~CharacterChipImage() {

		}

		int getCharacterChip(const int i) const { return this->ship[i]; }

	};
}

#endif //Included Crafterra Library