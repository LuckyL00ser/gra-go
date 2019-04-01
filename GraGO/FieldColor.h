#pragma once
//! Enum reprezentujacy możliwe kolory pola planszy gry.

enum class FieldColor {
	BLACK = 0,
	WHITE=1,
	EMPTY=-1,
	TERRITORITY_CHECKED=2 //dla podliczania punktow
};
