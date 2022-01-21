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

#ifndef INCLUDED_ASLIB2_ASLIB2_ASLIB2_HPP
#define INCLUDED_ASLIB2_ASLIB2_ASLIB2_HPP

//##########################################################################################
#ifdef CRAFTERRA_USE_DXLIB
#include <Crafterra/ThirdParty/DxLib/DxDataType.hpp>
// 入力系
#include <Crafterra/ThirdParty/DxLib/DxKeyboard.hpp>
#include <Crafterra/ThirdParty/DxLib/DxFont.hpp>
#include <Crafterra/ThirdParty/DxLib/DxMusic.hpp>
#include <Crafterra/ThirdParty/DxLib/DxMapChip.hpp>
#include <Crafterra/ThirdParty/DxLib/DxCharacterChip.hpp>

// DxLib 系の中でも 1 番遅く include する
#include <Crafterra/ThirdParty/DxLib/CrafterraForDxLib.hpp>

#else

#endif // CRAFTERRA_USE_DXLIB
//##########################################################################################

#include <AsLib2/Macro/ThirdParty.hpp>
#include <AsLib2/Basic/Color.hpp>
#include <AsLib2/Basic/Rect.hpp>
#include <AsLib2/Graphic/DrawRect.hpp>

#endif //Included Crafterra Library