#pragma once
#include <map>
#include "SFML/Window/Keyboard.hpp"

using namespace sf;

enum class EKeyCode
{
	A = Keyboard::A,
	B = Keyboard::B,
	C = Keyboard::C,
	D = Keyboard::D,
	E = Keyboard::E,
	F = Keyboard::F,
	G = Keyboard::G,
	H = Keyboard::H,
	I = Keyboard::I,
	J = Keyboard::J,
	K = Keyboard::K,
	L = Keyboard::L,
	M = Keyboard::M,
	N = Keyboard::N,
	O = Keyboard::O,
	P = Keyboard::P,
	Q = Keyboard::Q,
	R = Keyboard::R,
	S = Keyboard::S,
	T = Keyboard::T,
	U = Keyboard::U,
	V = Keyboard::V,
	W = Keyboard::W,
	X = Keyboard::X,
	Y = Keyboard::Y,
	Z = Keyboard::Z,
	One = Keyboard::Num1,
	Two = Keyboard::Num2,
	Three = Keyboard::Num3,
	Four = Keyboard::Num4,
	Five = Keyboard::Num5,
	Six = Keyboard::Num6,
	Seven = Keyboard::Num7,
	Eight = Keyboard::Num8,
	Nine = Keyboard::Num9,
	Zero = Keyboard::Num0,
	F1 = Keyboard::F1,
	F2 = Keyboard::F2,
	F3 = Keyboard::F3,
	F4 = Keyboard::F4,
	F5 = Keyboard::F5,
	F6 = Keyboard::F6,
	F7 = Keyboard::F7,
	F8 = Keyboard::F8,
	F9 = Keyboard::F9,
	F10 = Keyboard::F10,
	F11 = Keyboard::F11,
	F12 = Keyboard::F12,
	Escape = Keyboard::Escape,
	Space = Keyboard::Space,
	Tab = Keyboard::Tab,
	LeftShift = Keyboard::LShift,
	Console = Keyboard::Tilde,
	LeftCtrl = Keyboard::LControl,
	LeftAlt = Keyboard::LAlt,
	RightShift = Keyboard::RShift,
	RightCtrl = Keyboard::RControl,
	RightAlt = Keyboard::RAlt,
	Up = Keyboard::Up,
	Right = Keyboard::Right,
	Down = Keyboard::Down,
	Left = Keyboard::Left,
	BackSpace = Keyboard::BackSpace,
	Enter = Keyboard::Enter,
	Delete = Keyboard::Delete,
	Insert = Keyboard::Insert,
	Home = Keyboard::Home,
	End = Keyboard::End,
	PgUp = Keyboard::PageUp,
	PgDown = Keyboard::PageDown,
	NumPad1 = Keyboard::Numpad1,
	NumPad2 = Keyboard::Numpad2,
	NumPad3 = Keyboard::Numpad3,
	NumPad4 = Keyboard::Numpad4,
	NumPad5 = Keyboard::Numpad5,
	NumPad6 = Keyboard::Numpad6,
	NumPad7 = Keyboard::Numpad7,
	NumPad8 = Keyboard::Numpad8,
	NumPad9 = Keyboard::Numpad9,
	NumPad0 = Keyboard::Numpad0,
	Comma = Keyboard::Comma,
	Period = Keyboard::Period,
	MouseLeft = 201,
	MouseMiddle = 202,
	MouseRight = 203
};

enum class EKeyState
{
	Down,
	Up
};

static void CreateKeyStates(std::map<EKeyCode, EKeyState>& aKeyStates)
{
	for (int i = 0; i < 256; ++i)
	{
		aKeyStates.insert(std::make_pair(static_cast<EKeyCode>(i), EKeyState::Up));
	}
}