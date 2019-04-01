#pragma once
#include "FieldColor.h"
enum class Moves { /**<Enum odpowiedzialny za reprezentowanie koloru graczy*/
	WHITE_MOVE = static_cast<int>(FieldColor::WHITE),
	BLACK_MOVE = static_cast<int>(FieldColor::BLACK)
};
