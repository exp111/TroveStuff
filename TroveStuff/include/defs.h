#pragma once
#include <Windows.h>
#include <cstdint>
#include "offsets.h"

#define max(a,b)            (((a) > (b)) ? (a) : (b))
#define min(a,b)            (((a) < (b)) ? (a) : (b))

struct Color
{
	int r, g, b, a;
	Color(int r, int g, int b, int a = 255) : r{ r }, g{ g }, b{ b }, a{ a } {}
};

template <typename T>
struct Vector2
{
	T x = 0;
	T y = 0;
	Vector2() {}
	Vector2(T x, T y) : x(x), y(y) {}

	inline bool IsNull() const
	{
		return x == 0 && y == 0;
	}

	Vector2<T> operator-(Vector2<T>& k)
	{
		return Vector2<T>(x - k.x, y - k.y);
	}

	Vector2<T> operator+(Vector2<T>& k)
	{
		return Vector2<T>(x + k.x, y + k.y);
	}

	T Distance()
	{
		return std::sqrt(x * x + y * y); //sqrt(x^2 + y^2)
	}
};

struct Vector3
{
	float x,y,z = 0.f;
	Vector3() {}
	Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
	Vector3 operator-(Vector3& k)
	{
		return Vector3(x - k.x, y - k.y, z - k.z);
	}
};

static float clamp(float x, float upper, float lower)
{
	return min(upper, max(x, lower));
}
#define GetIsKeyDown(k) (GetAsyncKeyState(k) & 0x8000)


class EntitySoldier
{
public:
	char pad_0004[4]; //0x0004
	class EntitySoldierClass* EntityClass; //0x0008
	char pad_000C[12]; //0x000C
	Vector3 position; //0x0018
	char pad_0024[288]; //0x0024
	float health; //0x0144
	float maxHealth; //0x0148
	char pad_014C[2248]; //0x014C
	float energy; //0x0A14
	char pad_0A18[1464]; //0x0A18

	virtual void Function0();
	virtual void Function1();
	virtual void Function2();
	virtual void Function3();
	virtual void Function4();
	virtual void Function5();
	virtual void Function6();
	virtual void Function7();
	virtual void Function8();
	virtual void Function9();
}; //Size: 0x0FD0

class EntitySoldierClass
{
public:
	char pad_0004[28]; //0x0004
	wchar_t* Name; //0x0020
	char pad_0024[48]; //0x0024

	virtual void Function0();
	virtual void Function1();
	virtual void Function2();
	virtual void Function3();
	virtual void Function4();
	virtual void Function5();
	virtual void Function6();
	virtual void Function7();
	virtual void Function8();
	virtual void Function9();
}; //Size: 0x0054

class Character
{
public:
	char pad_0004[44]; //0x0004
	wchar_t name[50]; //0x0030
	char pad_0094[28]; //0x0094
	wchar_t name2[50]; //0x00B0
	char pad_0114[36]; //0x0114
	class Team* Team; //0x0138
	char pad_013C[4]; //0x013C
	class EntitySoldierClass* EntityClass; //0x0140
	char pad_0144[4]; //0x0144
	class PlayerEntity* Entity; //0x0148
	char pad_014C[100]; //0x014C

private:
	virtual void Function0();
	virtual void Function1();
	virtual void Function2();
	virtual void Function3();
	virtual void Function4();
	virtual void Function5();
	virtual void Function6();
	virtual void Function7();
	virtual void Function8();
	virtual void Function9();

public:
	static Character* GetCharacter(int i)
	{
		int charList = *(int*)GetRelativeOffset(Offsets::characterList);
		if (charList == 0) //can get nulled
			return nullptr;
		return (Character*)(charList + i * sizeof(Character));
	}
}; //Size: 0x01B0

class PlayerEntity
{
public:
	char pad_0000[328]; //0x0000
	Vector3 headPos; //0x0148
	Vector3 camRotation; //0x0154
	char pad_0160[4]; //0x0160
	class EntitySoldier* FocusedEntity; //0x0164
	char pad_0168[152]; //0x0168
	class EntitySoldierClass* EntityClass; //0x0200
	char pad_0204[148]; //0x0204
	class EntitySoldier* entity; //0x0298
	char pad_029C[624]; //0x029C
	float timeSinceLastStaminaUse; //0x050C
	char pad_0510[20]; //0x0510
	Vector3 position; //0x0524
	char pad_0530[40]; //0x0530
}; //Size: 0x0558

class CameraManager
{
public:
	char pad_0000[32]; //0x0000
	class Camera* Current; //0x0020
	class BaseCamera* BaseCamera; //0x0024
	class Camera* ChaseCamera; //0x0028
	class Camera* FreeCamera; //0x002C
	class Camera* DeathCamera; //0x0030
	class Camera* MapCamera; //0x0034
	char pad_0038[4]; //0x0038
	Vector3 position; //0x003C
}; //Size: 0x0048


class Camera
{
public:
	class CameraManager* manager; //0x0004
	char pad_0008[56]; //0x0008
	Vector3 position; //0x0040
	char pad_004C[12]; //0x004C

	virtual void Function0();
	virtual void Function1();
	virtual void Function2();
	virtual void Function3();
	virtual void Function4();
	virtual void Function5();
	virtual void Function6();
	virtual void Function7();
	virtual void Function8();
	virtual void Function9();
}; //Size: 0x0058


class BaseCamera
{
public:
	char pad_0004[44]; //0x0004
	float matrix1[16]; //0x0030
	float matrix2[16]; //0x0070
	char pad_00B0[64]; //0x00B0
	float worldMatrix[16]; //0x00F0

	virtual void Function0();
	virtual void Function1();
	virtual void Function2();
	virtual void Function3();
	virtual void Function4();
	virtual void Function5();
	virtual void Function6();
	virtual void Function7();
	virtual void Function8();
	virtual void Function9();
}; //Size: 0x0130



class Team
{
public:
	char pad_0004[4]; //0x0004
	int32_t index; //0x0008
	wchar_t* name; //0x000C
	char pad_0010[52]; //0x0010

	virtual void Function0();
	virtual void Function1();
	virtual void Function2();
	virtual void Function3();
	virtual void Function4();
	virtual void Function5();
}; //Size: 0x0044


// Functions
static Vector2<float> GetScreenResolution()
{
	return Vector2<float>(*(float*)GetRelativeOffset(Offsets::ScreenResX),
		*(float*)GetRelativeOffset(Offsets::ScreenResY));
}

static Vector2<float> WorldToScreen(Vector3 pos)
{
	CameraManager* camManager = *(CameraManager**)GetRelativeOffset(Offsets::cameraManager);
	Vector2<float> scrRes = GetScreenResolution();
	Vector3 eyePos = camManager->Current->position;
	Vector3 Position = pos - eyePos;
	Vector3 transform;

	float* viewMatrix = (float*)GetRelativeOffset(Offsets::viewMatrix);
	transform.x = pos.x * viewMatrix[0] + pos.y * viewMatrix[4] + pos.z * viewMatrix[8] + viewMatrix[12];
	transform.y = pos.x * viewMatrix[1] + pos.y * viewMatrix[5] + pos.z * viewMatrix[9] + viewMatrix[13];
	transform.z = pos.x * viewMatrix[3] + pos.y * viewMatrix[7] + pos.z * viewMatrix[11] + viewMatrix[15];

	// make sure it is in front of us
	if (transform.z < 0.1f)
		return Vector2<float>(0.f, 0.f);

	transform.x /= transform.z;
	transform.y /= transform.z;

	Vector2<float> screen = Vector2<float>();
	screen.x = (scrRes.x / 2 * transform.x) + (transform.x + scrRes.x / 2);
	screen.y = -(scrRes.y / 2 * transform.y) + (transform.y + scrRes.y / 2);

	if (screen.x <= 0 || screen.x >= scrRes.x || screen.y <= 0 || screen.y >= scrRes.y)
		return Vector2<float>(0.f, 0.f);

	return screen;
}