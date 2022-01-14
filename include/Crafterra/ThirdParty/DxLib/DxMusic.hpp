/*#######################################################################################
	Crafterra Library 🌏
	Copyright (c) 2017-2022 Kasugaccho
	Copyright (c) 2018-2022 As Project
	https://github.com/AsPJT/Crafterra
	wanotaitei@gmail.com
	Distributed under the CC0 1.0. (See accompanying
	file LICENSE_for_include_directory.txt or copy at https://creativecommons.org/publicdomain/zero/1.0/)
#######################################################################################*/

#ifndef INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_THIRD_PARTY_DXLIB_DXMUSIC_HPP
#define INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_THIRD_PARTY_DXLIB_DXMUSIC_HPP

#include <cstddef>

namespace Crafterra {

	class Music {
	private:

		LPCSTR music_path{};
		bool is_music = false;
		int m_music = -1;

	public:

		Music() {
			m_music = ::DxLib::LoadSoundMem("./../../../resource/Music/First Journey (takai).mp3");
		}

		~Music() {

		}

		int getMusic() const { return this->m_music; }

	};
}

#endif //Included Crafterra Library