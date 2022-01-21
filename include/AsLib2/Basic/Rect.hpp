/*##########################################################################################

	AsLib2 🌏

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

#ifndef INCLUDED_ASLIB2_ASLIB2_BASIC_RECT_HPP
#define INCLUDED_ASLIB2_ASLIB2_BASIC_RECT_HPP

namespace AsLib2 {

	struct Rect {
		using Rect_ = int;
		Rect_ start_x{};
		Rect_ start_y{};
		Rect_ width{};
		Rect_ height{};
	};

}

#endif //Included AsLib2