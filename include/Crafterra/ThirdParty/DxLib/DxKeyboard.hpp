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

#ifndef INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_THIRD_PARTY_DXLIB_KEYBOARD_HPP
#define INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_THIRD_PARTY_DXLIB_KEYBOARD_HPP

#include <cstddef>

namespace Crafterra {

	class InputKey {
	private:

		bool up_key[256]{};    // キーが離された瞬間
		bool down_key[256]{}; // キーが押された瞬間
		int key[256]{};        // キーが押されているフレーム数

		char tmp_key[256]{}; // 現在のキーの入力状態

	public:
		void setKey() {
			::DxLib::GetHitKeyStateAll(this->tmp_key); // 全てのキーの入力状態を取得
			for (int i = 0; i < 256; ++i) {
				if (this->tmp_key[i] != 0) {
					this->up_key[i] = false;
					this->down_key[i] = (this->key[i] == 0);
					// i 番のキーコードに対応するキーが押されていたら加算
					++(this->key[i]);
				}
				else {
					this->down_key[i] = false;
					this->up_key[i] = (this->key[i] != 0);
					this->key[i] = 0;
				}
			}
		}

		// キー出力
		int getKey(const ::std::size_t key_num_) const {
			return this->key[key_num_];
		}
		int getUpKey(const ::std::size_t key_num_) const {
			return this->up_key[key_num_];
		}
		int getDownKey(const ::std::size_t key_num_) const {
			return this->down_key[key_num_];
		}

	};
}

#endif //Included Crafterra Library