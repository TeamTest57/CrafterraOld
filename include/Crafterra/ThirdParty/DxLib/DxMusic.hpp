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

#ifndef INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_THIRD_PARTY_DXLIB_DXMUSIC_HPP
#define INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_THIRD_PARTY_DXLIB_DXMUSIC_HPP

namespace Crafterra {

	class Music {
	private:

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