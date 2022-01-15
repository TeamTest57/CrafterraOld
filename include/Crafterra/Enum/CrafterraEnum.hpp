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

#ifndef INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_ENUM_CRAFTERRA_ENUM_HPP
#define INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_ENUM_CRAFTERRA_ENUM_HPP

#include <Crafterra/DataType/CrafterraPrimitiveDataType.hpp>

namespace Crafterra {
	inline namespace Enum {

		// アクタの向き
		enum ActorDirection : ::Crafterra::DataType::ActorDirectionUint {
			actor_direction_empty
			, actor_direction_down
			, actor_direction_left
			, actor_direction_right
			, actor_direction_up
			, actor_direction_lower_left
			, actor_direction_lower_right
			, actor_direction_upper_left
			, actor_direction_upper_right
			, actor_direction_size
		};
		// フィールドマップにおける操作アクタの状態
		enum OperationActorStateInFieldMap : ::Crafterra::DataType::OperationActorStateInFieldMapUint {
			operation_actor_state_in_field_map_empty
			, operation_actor_state_in_field_map_walking // 陸路の歩行
			, operation_actor_state_in_field_map_ratite_bird // 飛べない鳥 ( 地上の高速移動 )
			, operation_actor_state_in_field_map_ship // 船
			, operation_actor_state_in_field_map_airship // 飛空艇
			, operation_actor_state_in_field_map_size
		};

	}
}

#endif //Included Crafterra Library