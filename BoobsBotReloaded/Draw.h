#pragma once
#include <map>

namespace Draw
{
	class ScreenLocation
	{
	public:
		float X;
		float Y;

		ScreenLocation(float x, float y)
		{
			X = x;
			Y = y;
		}

		ScreenLocation(float* screen_location)
		{
			X = screen_location[0];
			Y = screen_location[1];
		}
	};

	class WorldLocation
	{
	public:
		float X;
		float Y;
		float Z;

		WorldLocation(float x, float y, float z)
		{
			X = x;
			Y = y;
			Z = z;
		}

		WorldLocation(float* world_location)
		{
			X = world_location[0];
			Y = world_location[1];
			Z = world_location[2];
		}
	};


	class ScreenSize
	{
	public:
		float Width;
		float Height;

		ScreenSize(float width, float height)
		{
			Width = width;
			Height = height;
		}
	};

	class Color
	{
	public:
		float R;
		float B;
		float G;
		float Alpha;

		Color(float r, float b, float g, float alpha)
		{
			R = r;
			B = b;
			G = g;
			Alpha = alpha;
		}
	};

	enum Font : int
	{
		SmallDev,
		BigDev,
		Console,
		Big,
		Small,
		Bold,
		Normal,
		ExtraBig,
		Objective
	};

	enum Shader : int
	{
		White
	};

	namespace internal
	{
		static std::map<int, int*> Fonts;
		static std::map<int, int*> Shaders;

		void InitializeFonts();
		void InitializeShaders();

		class ScreenMatrix
		{
		public:
			char matrix[0xDC];
		};

		using GetScreenMatrixPrototype = ScreenMatrix*(__cdecl*)();
		using WorldToScreenPrototype = char(__cdecl*)(int local_client_number, ScreenMatrix* screen_matrix, float world_position[3], float screen_position[2]);

		using RegisterShaderPrototype = int*(__cdecl*)(char* shader);
		using RegisterFontPrototype = int*(__cdecl*)(char* font);

		using DrawStringPrototype = int(__cdecl*)(char* string, int string_size, int* font, float x, float y, float scale_x, float scale_y, float unknown_0, float color[4], int unknown_1);
		using DrawRotatedPicturePrototype = int(__cdecl*)(ScreenMatrix* screen_matrix, float x, float y, float w, float h, float angle, float color[4], int* shader);

		static auto GetScreenMatrix = (GetScreenMatrixPrototype)0x004B6350;
		static auto WorldToScreen = (WorldToScreenPrototype)0x004E5FC0;

		static auto RegisterShader = (RegisterShaderPrototype)0x0041B6B0;
		static auto RegisterFont = (RegisterFontPrototype)0x004FB960;

		static auto DrawString = (DrawStringPrototype)0x0042C970;
		static auto DrawRotatedPicture = (DrawRotatedPicturePrototype)0x0042F420;
	}

	ScreenLocation WorldToScreen(WorldLocation world_location);
	void DrawString(char* string, ScreenLocation screen_location, Font font, Color color);
	void DrawShader(Shader shader, ScreenLocation screen_location, ScreenSize screen_size, float angle, Color color);

	void Initialize();
}
