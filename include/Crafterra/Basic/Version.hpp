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

#ifndef INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_BASIC_VERSION_HPP
#define INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_BASIC_VERSION_HPP

// Crafterra 宣言マクロ
#ifndef CRAFTERRA_LIBRARY
#define CRAFTERRA_LIBRARY
#endif

// 正式バージョン数値
#ifndef CRAFTERRA_LIBRARY_VERSION
#define CRAFTERRA_LIBRARY_VERSION (20220114L)
#endif

// AsDungeon 世代 ( Crafterra 第五世代 )
#ifndef CRAFTERRA_LIBRARY_GENERATION
#define CRAFTERRA_LIBRARY_GENERATION (5)
#endif

/*##########################################################################################
	AsDungeon 世代とは？
	
	As Project が開発する地形またはダンジョン生成システムの管理番号である。

	第一世代： AsRogueLike_C (First Generation AsDungeon)
	第二世代： AsRogueLike_C++ (Second Generation AsDungeon)
	第三世代： AsLib (Third Generation AsDungeon)
	第四世代： DungeonTemplateLibrary (Fourth Generation AsDungeon)
	第五世代： Crafterra (Fifth Generation AsDungeon)

	詳しくはこちら
	https://github.com/AsPJT/DungeonTemplateLibrary/wiki/Version-History
##########################################################################################*/

// AsDungeon 世代微修正バージョン
#ifndef CRAFTERRA_LIBRARY_GENERATION_PATCHLEVEL
#define CRAFTERRA_LIBRARY_GENERATION_PATCHLEVEL (0)
#endif

// Crafterra 主要バージョン
#ifndef CRAFTERRA_LIBRARY_MAJOR
#define CRAFTERRA_LIBRARY_MAJOR (0)
#endif

// Crafterra 補助バージョン
#ifndef CRAFTERRA_LIBRARY_MINOR
#define CRAFTERRA_LIBRARY_MINOR (1)
#endif

// Crafterra 微修正バージョン
#ifndef CRAFTERRA_LIBRARY_PATCHLEVEL
#define CRAFTERRA_LIBRARY_PATCHLEVEL (2)
#endif

// 正式バージョン名
#ifndef CRAFTERRA_LIBRARY_VERSION_NAME
#define CRAFTERRA_LIBRARY_VERSION_NAME "5.0.0.1.2 (https://github.com/AsPJT/Crafterra)"
#endif

/*##########################################################################################
	更新履歴
	バージョン |     更新日    |           概要
	5.0.0.1.X  | 2022/0X/XX | コピペ用
	5.0.0.1.1  | 2022/01/12 | Crafterra をライブラリ化
	5.0.0.1.0  | 2022/01/08 | Crafterra をリニューアル
##########################################################################################*/

namespace Crafterra {

	namespace Version {

		constexpr long crafterra_library_version                = (CRAFTERRA_LIBRARY_VERSION);
		constexpr int  crafterra_library_generation             = (CRAFTERRA_LIBRARY_GENERATION);
		constexpr int  crafterra_library_generation_patchlevel = (CRAFTERRA_LIBRARY_GENERATION_PATCHLEVEL);
		constexpr int  crafterra_library_major                  = (CRAFTERRA_LIBRARY_MAJOR);
		constexpr int  crafterra_library_minor                  = (CRAFTERRA_LIBRARY_MINOR);
		constexpr int  crafterra_library_patchlevel             = (CRAFTERRA_LIBRARY_PATCHLEVEL);

	}

}

#endif //Included Crafterra Library