#pragma once
#include <map>

enum class EKeyCode
{
	A = 0x41,
	B = 0x42,
	C = 0x43,
	D = 0x44,
	E = 0x45,
	F = 0x46,
	G = 0x47,
	H = 0x48,
	I = 0x49,
	J = 0x4A,
	K = 0x4B,
	L = 0x4C,
	M = 0x4D,
	N = 0x4E,
	O = 0x4F,
	P = 0x50,
	Q = 0x51,
	R = 0x52,
	S = 0x53,
	T = 0x54,
	U = 0x55,
	V = 0x56,
	W = 0x57,
	X = 0x58,
	Y = 0x59,
	Z = 0x5A,
	One = 0x31,
	Two = 0x32,
	Three = 0x33,
	Four = 0x34,
	Five = 0x35,
	Six = 0x36,
	Seven = 0x37,
	Eight = 0x38,
	Nine = 0x39,
	Zero = 0x30,
	F1 = 0x70,
	F2 = 0x71,
	F3 = 0x72,
	F4 = 0x73,
	F5 = 0x74,
	F6 = 0x75,
	F7 = 0x76,
	F8 = 0x77,
	F9 = 0x78,
	F10 = 0x79,
	F11 = 0x7A,
	F12 = 0x7B,
	CapsLock = 0x14,
	Escape = 0x1B,
	Space = 0x20,
	Tab = 0x09,
	LeftShift = 0xA0,
	Console = 0x7E,
	LeftCtrl = 0xA2,
	LeftAlt = 0x12,
	RightShift = 0xA1,
	RightCtrl = 0xA3,
	Shift = 0x10,
	Alt = 0x12,
	Ctrl = 0x11,
	Up = 0x26,
	Right = 0x27,
	Down = 0x28,
	Left = 0x25,
	BackSpace = 0x08,
	Enter = 0x0D,
	Delete = 0x2E,
	Insert = 0x2D,
	Home = 0x24,
	End = 0x23,
	PgUp = 0x21,
	PgDown = 0x22,
	PrintScrn = 0x2C,
	ScrollLock = 0x91,
	NumLock = 0x90,
	NumPad1 = 0x60,
	NumPad2 = 0x61,
	NumPad3 = 0x62,
	NumPad4 = 0x63,
	NumPad5 = 0x64,
	NumPad6 = 0x65,
	NumPad7 = 0x66,
	NumPad8 = 0x67,
	NumPad9 = 0x68,
	NumPad0 = 0x69,
	MouseLeft = 0x01,
	MouseMiddle = 0x04,
	MouseRight = 0x02
};

enum class EKeyState
{
	Down,
	Up
};

static void CreateKeyStates(std::map<EKeyCode, EKeyState>& aKeyStates)
{
	aKeyStates.insert(std::make_pair(EKeyCode::A, EKeyState::Up));
	aKeyStates.insert(std::make_pair(EKeyCode::B, EKeyState::Up));
	aKeyStates.insert(std::make_pair(EKeyCode::C, EKeyState::Up));
	aKeyStates.insert(std::make_pair(EKeyCode::D, EKeyState::Up));
	aKeyStates.insert(std::make_pair(EKeyCode::E, EKeyState::Up));
	aKeyStates.insert(std::make_pair(EKeyCode::F, EKeyState::Up));
	aKeyStates.insert(std::make_pair(EKeyCode::G, EKeyState::Up));
	aKeyStates.insert(std::make_pair(EKeyCode::H, EKeyState::Up));
	aKeyStates.insert(std::make_pair(EKeyCode::I, EKeyState::Up));
	aKeyStates.insert(std::make_pair(EKeyCode::J, EKeyState::Up));
	aKeyStates.insert(std::make_pair(EKeyCode::K, EKeyState::Up));
	aKeyStates.insert(std::make_pair(EKeyCode::L, EKeyState::Up));
	aKeyStates.insert(std::make_pair(EKeyCode::M, EKeyState::Up));
	aKeyStates.insert(std::make_pair(EKeyCode::N, EKeyState::Up));
	aKeyStates.insert(std::make_pair(EKeyCode::O, EKeyState::Up));
	aKeyStates.insert(std::make_pair(EKeyCode::P, EKeyState::Up));
	aKeyStates.insert(std::make_pair(EKeyCode::Q, EKeyState::Up));
	aKeyStates.insert(std::make_pair(EKeyCode::R, EKeyState::Up));
	aKeyStates.insert(std::make_pair(EKeyCode::S, EKeyState::Up));
	aKeyStates.insert(std::make_pair(EKeyCode::T, EKeyState::Up));
	aKeyStates.insert(std::make_pair(EKeyCode::U, EKeyState::Up));
	aKeyStates.insert(std::make_pair(EKeyCode::V, EKeyState::Up));
	aKeyStates.insert(std::make_pair(EKeyCode::W, EKeyState::Up));
	aKeyStates.insert(std::make_pair(EKeyCode::X, EKeyState::Up));
	aKeyStates.insert(std::make_pair(EKeyCode::Y, EKeyState::Up));
	aKeyStates.insert(std::make_pair(EKeyCode::Z, EKeyState::Up));
	aKeyStates.insert(std::make_pair(EKeyCode::One, EKeyState::Up));
	aKeyStates.insert(std::make_pair(EKeyCode::Two, EKeyState::Up));
	aKeyStates.insert(std::make_pair(EKeyCode::Three, EKeyState::Up));
	aKeyStates.insert(std::make_pair(EKeyCode::Four, EKeyState::Up));
	aKeyStates.insert(std::make_pair(EKeyCode::Five, EKeyState::Up));
	aKeyStates.insert(std::make_pair(EKeyCode::Six, EKeyState::Up));
	aKeyStates.insert(std::make_pair(EKeyCode::Seven, EKeyState::Up));
	aKeyStates.insert(std::make_pair(EKeyCode::Eight, EKeyState::Up));
	aKeyStates.insert(std::make_pair(EKeyCode::Nine, EKeyState::Up));
	aKeyStates.insert(std::make_pair(EKeyCode::Zero, EKeyState::Up));
	aKeyStates.insert(std::make_pair(EKeyCode::F1, EKeyState::Up));
	aKeyStates.insert(std::make_pair(EKeyCode::F2, EKeyState::Up));
	aKeyStates.insert(std::make_pair(EKeyCode::F3, EKeyState::Up));
	aKeyStates.insert(std::make_pair(EKeyCode::F4, EKeyState::Up));
	aKeyStates.insert(std::make_pair(EKeyCode::F5, EKeyState::Up));
	aKeyStates.insert(std::make_pair(EKeyCode::F6, EKeyState::Up));
	aKeyStates.insert(std::make_pair(EKeyCode::F7, EKeyState::Up));
	aKeyStates.insert(std::make_pair(EKeyCode::F8, EKeyState::Up));
	aKeyStates.insert(std::make_pair(EKeyCode::F9, EKeyState::Up));
	aKeyStates.insert(std::make_pair(EKeyCode::F10, EKeyState::Up));
	aKeyStates.insert(std::make_pair(EKeyCode::F11, EKeyState::Up));
	aKeyStates.insert(std::make_pair(EKeyCode::F12, EKeyState::Up));
	aKeyStates.insert(std::make_pair(EKeyCode::CapsLock, EKeyState::Up));
	aKeyStates.insert(std::make_pair(EKeyCode::Escape, EKeyState::Up));
	aKeyStates.insert(std::make_pair(EKeyCode::Space, EKeyState::Up));
	aKeyStates.insert(std::make_pair(EKeyCode::Tab, EKeyState::Up));
	aKeyStates.insert(std::make_pair(EKeyCode::LeftShift, EKeyState::Up));
	aKeyStates.insert(std::make_pair(EKeyCode::Console, EKeyState::Up));
	aKeyStates.insert(std::make_pair(EKeyCode::LeftCtrl, EKeyState::Up));
	aKeyStates.insert(std::make_pair(EKeyCode::LeftAlt, EKeyState::Up));
	aKeyStates.insert(std::make_pair(EKeyCode::RightShift, EKeyState::Up));
	aKeyStates.insert(std::make_pair(EKeyCode::RightCtrl, EKeyState::Up));
	aKeyStates.insert(std::make_pair(EKeyCode::Shift, EKeyState::Up));
	aKeyStates.insert(std::make_pair(EKeyCode::Alt, EKeyState::Up));
	aKeyStates.insert(std::make_pair(EKeyCode::Ctrl, EKeyState::Up));
	aKeyStates.insert(std::make_pair(EKeyCode::Up, EKeyState::Up));
	aKeyStates.insert(std::make_pair(EKeyCode::Right, EKeyState::Up));
	aKeyStates.insert(std::make_pair(EKeyCode::Down, EKeyState::Up));
	aKeyStates.insert(std::make_pair(EKeyCode::Left, EKeyState::Up));
	aKeyStates.insert(std::make_pair(EKeyCode::BackSpace, EKeyState::Up));
	aKeyStates.insert(std::make_pair(EKeyCode::Enter, EKeyState::Up));
	aKeyStates.insert(std::make_pair(EKeyCode::Delete, EKeyState::Up));
	aKeyStates.insert(std::make_pair(EKeyCode::Insert, EKeyState::Up));
	aKeyStates.insert(std::make_pair(EKeyCode::Home, EKeyState::Up));
	aKeyStates.insert(std::make_pair(EKeyCode::End, EKeyState::Up));
	aKeyStates.insert(std::make_pair(EKeyCode::PgUp, EKeyState::Up));
	aKeyStates.insert(std::make_pair(EKeyCode::PgDown, EKeyState::Up));
	aKeyStates.insert(std::make_pair(EKeyCode::PrintScrn, EKeyState::Up));
	aKeyStates.insert(std::make_pair(EKeyCode::ScrollLock, EKeyState::Up));
	aKeyStates.insert(std::make_pair(EKeyCode::NumLock, EKeyState::Up));
	aKeyStates.insert(std::make_pair(EKeyCode::NumPad1, EKeyState::Up));
	aKeyStates.insert(std::make_pair(EKeyCode::NumPad2, EKeyState::Up));
	aKeyStates.insert(std::make_pair(EKeyCode::NumPad3, EKeyState::Up));
	aKeyStates.insert(std::make_pair(EKeyCode::NumPad4, EKeyState::Up));
	aKeyStates.insert(std::make_pair(EKeyCode::NumPad5, EKeyState::Up));
	aKeyStates.insert(std::make_pair(EKeyCode::NumPad6, EKeyState::Up));
	aKeyStates.insert(std::make_pair(EKeyCode::NumPad7, EKeyState::Up));
	aKeyStates.insert(std::make_pair(EKeyCode::NumPad8, EKeyState::Up));
	aKeyStates.insert(std::make_pair(EKeyCode::NumPad9, EKeyState::Up));
	aKeyStates.insert(std::make_pair(EKeyCode::NumPad0, EKeyState::Up));
	aKeyStates.insert(std::make_pair(EKeyCode::MouseLeft, EKeyState::Up));
	aKeyStates.insert(std::make_pair(EKeyCode::MouseMiddle, EKeyState::Up));
	aKeyStates.insert(std::make_pair(EKeyCode::MouseRight, EKeyState::Up));
}