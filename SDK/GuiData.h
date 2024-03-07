#pragma once
class GuiData {
private:
	char pad_0x0000[0x30]; //0x0000
public:
	float WindowWidth; //0x0030 
	float WindowHeight; //0x0034
	float w_inf_1; //0x0038 
	float w_inf_2; //0x003C 
	float w_inf_3; //0x0040 
	float w_inf_4; //0x0044
private:
	char pad_0x0001[0x8]; //0x0000
public:
	float GuiScale; //0x0050 
private:
	char pad_0x0058[0x14]; //0x0058
public:
	__int16 idk2; //0x0068 
	__int16 MouseX; //0x006A 
	__int16 MouseY; //0x006C 
	__int16 idk3; //0x006E 

	Vector2 getScaledWindowDimensions() {
		return Vector2(WindowWidth * GuiScale, WindowHeight * GuiScale);
	}

	Vector2 getScaledMousePos() {
		return Vector2(MouseX * GuiScale, MouseY * GuiScale);
	}
};