/*#######################################################################################
	Crafterra Library 🌏
	Copyright (c) 2017-2022 Kasugaccho
	Copyright (c) 2018-2022 As Project
	https://github.com/AsPJT/Crafterra
	wanotaitei@gmail.com
	Distributed under the CC0 1.0. (See accompanying
	file LICENSE_for_include_directory.txt or copy at https://creativecommons.org/publicdomain/zero/1.0/)
#######################################################################################*/

#ifndef INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_THIRD_PARTY_DXLIB_DXFONT_HPP
#define INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_THIRD_PARTY_DXLIB_DXFONT_HPP

#include <cstddef>

namespace Crafterra {

	class Font {
	private:

		LPCSTR font_path{};
		bool is_font = false;
		int m_font = -1;

	public:

		Font() {
			font_path = "./../../../resource/Font/Misaki Gothic.ttf"; // 読み込むフォントファイルのパス
			is_font = (AddFontResourceEx(font_path, FR_PRIVATE, nullptr) != 0);

			if(is_font) m_font = CreateFontToHandle(u8"美咲ゴシック", 20, -1, -1, DX_CHARSET_SHFTJIS);
		}

		~Font() {
			// フォントのアンロード
			if (is_font) {
				(RemoveFontResourceEx(font_path, FR_PRIVATE, nullptr));
			}
		}

		int getFont() const { return this->m_font; }

	};
}

#endif //Included Crafterra Library