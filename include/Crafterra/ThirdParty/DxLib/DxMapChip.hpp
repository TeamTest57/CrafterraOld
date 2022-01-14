/*#######################################################################################
	Crafterra Library 🌏
	Copyright (c) 2017-2022 Kasugaccho
	Copyright (c) 2018-2022 As Project
	https://github.com/AsPJT/Crafterra
	wanotaitei@gmail.com
	Distributed under the CC0 1.0. (See accompanying
	file LICENSE_for_include_directory.txt or copy at https://creativecommons.org/publicdomain/zero/1.0/)
#######################################################################################*/

#ifndef INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_THIRD_PARTY_DXLIB_DXMAPCHIP_HPP
#define INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_THIRD_PARTY_DXLIB_DXMAPCHIP_HPP

#include <cstddef>

namespace Crafterra {

	class MapChipImage {
	private:

		int base_map[8 * 249]{};

	public:

		MapChipImage() {
			::DxLib::LoadDivGraph("./../../../resource/Picture/Chip/Map/Base(pipo).png", 8 * 249,
				8, 249,
				32, 32, base_map);
		}

		~MapChipImage() {

		}

		int getMapChip(const int i) const { return this->base_map[i]; }

	};
}

#endif //Included Crafterra Library