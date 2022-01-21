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

#ifndef INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_THIRD_PARTY_CRAFTERRA_FOR_DXLIB_HPP
#define INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_THIRD_PARTY_CRAFTERRA_FOR_DXLIB_HPP

// DxLib のメイン関数
#ifndef CRAFTERRA_FOR_DXLIB_MAIN_FUNCTION
#define CRAFTERRA_FOR_DXLIB_MAIN_FUNCTION

// Windows 版の場合
#ifdef __WINDOWS__

#include <Crafterra/Basic/InitRead.hpp>
#include <Crafterra/DataType/StringDataType.hpp>

#ifdef __WINDOWS__
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
#elif __APPLE__
int ios_main()
#endif // __WINDOWS__
{
	// 読み込む
	::Crafterra::InitRead init_read("Settings.txt");

	// ログ出力を行わない
	::DxLib::SetOutApplicationLogValidFlag(FALSE);
	// 背景色を指定
	::DxLib::SetBackgroundColor(75, 145, 230);
	// ウィンドウテキストにタイトル名を表示
	const ::Crafterra::DataType::String title_name = 
		::Crafterra::DataType::String("Crafterra v") + 
		::Crafterra::DataType::String(CRAFTERRA_LIBRARY_VERSION_NAME);
	::DxLib::SetMainWindowText(title_name.c_str());
	// フルスクリーンではなくウィンドウで表示
	if (!init_read.isFullscreen()) {
#ifdef __WINDOWS__
		::DxLib::ChangeWindowMode(TRUE);
#endif // __WINDOWS__
		::DxLib::SetGraphMode(
			init_read.getWindowWidth(), // Crafterra::System::init_window_width, 
			init_read.getWindowHeight(), // Crafterra::System::init_window_height, 
			32);
	}
	// UTF-8に変更
	::DxLib::SetUseCharCodeFormat(DX_CHARCODEFORMAT_UTF8);
	if (::DxLib::DxLib_Init() == -1) return -1;
	::DxLib::LoadGraphScreen(
		init_read.getWindowWidth() / 2 - 320, init_read.getWindowHeight() / 2 - 180,
		"./../../../resource/picture/Logo/Init Logo(As).png", FALSE);
	::DxLib::SetDrawScreen(DX_SCREEN_BACK);


	::Crafterra::Font font;
	::Crafterra::Music music;
	::Crafterra::MapChipImage map_chip_image;
	::Crafterra::CharacterChipImage character_chip_image;

	::Crafterra::Resource cm;

	cm.setFont(font);
	cm.setMusic(music);
	cm.setMapChip(map_chip_image);
	cm.setCharacterChip(character_chip_image);

	cm.setWindowWidth(init_read.getWindowWidth());
	cm.setWindowHeight(init_read.getWindowHeight());

	Crafterra::System::crafterraMain(cm);
	return ::DxLib::DxLib_End();
}

#endif // __WINDOWS__

#endif // CRAFTERRA_FOR_DXLIB_MAIN_FUNCTION

// 描画更新関数
#ifndef CRAFTERRA_FOR_DXLIB_UPDATE_FUNCTION
#define CRAFTERRA_FOR_DXLIB_UPDATE_FUNCTION
namespace Crafterra {
	namespace System {
		bool Update() {
			return (::DxLib::ScreenFlip() != -1 && ::DxLib::ClearDrawScreen() != -1 && ::DxLib::ProcessMessage() != -1);
		}
	}
}
#endif // CRAFTERRA_FOR_DXLIB_UPDATE_FUNCTION

#endif //Included Crafterra Library