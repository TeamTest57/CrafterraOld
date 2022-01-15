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