#pragma once
#include "GeoReveal/Math/Math.h"
namespace GV {
	enum class TextureFormat : uint32_t {
		RGBA = 0, RGB = 1, RG = 2, R = 3, 
		SRGB = 4, SRGBA = 5, 
		RGBA16F = 6, RGB16F = 7, RG16F = 21, R16F = 22,
		RGBA32F = 9, RGB32F = 19, RG32F = 8, R32F = 20,
		Auto = 10, None = 11,
		Depth16 = 12, Depth24 = 13, Depth32 = 14, Depth32F = 15, 
		Depth24_Stencil8 = 16, Depth32F_Stencil8 = 17, Stencil8 = 18

		//MAX: 22
	};
	enum class TextureWrap : uint32_t {
		ClampToEdge, Repeat, ClampToBorder
	};
	enum class TextureFiltering : uint32_t {
		Linear,
		Nearest,
		Trilinear,

		Bilinear = Linear,
	};
	struct TextureSettings {
		TextureFormat format = TextureFormat::Auto;
		TextureWrap wrap = TextureWrap::Repeat;
		glm::vec2 tiling = { 1.0f,1.0f };
		uint32_t levels = 1;
		glm::vec4 border = glm::vec4(1.0f);
		TextureFiltering filtering = TextureFiltering::Linear;

		TextureSettings(TextureFormat format = TextureFormat::Auto, TextureWrap wrap = TextureWrap::Repeat, 
			const glm::vec2& tiling = { 1.0f,1.0f }, uint32_t levels = 1, glm::vec4 border = glm::vec4(1.0f),
			TextureFiltering filtering = TextureFiltering::Linear)
			:format(format), wrap(wrap), tiling(tiling), levels(levels), border(border), filtering(filtering) {}
	};
	class Texture
	{
	public:
		virtual ~Texture() = default;

		virtual void bind(uint32_t slot = 0) const = 0;
		virtual void* getNativeRendererObject() const = 0;

		virtual uint32_t getWidth() const = 0;
		virtual uint32_t getHeight() const = 0;

		virtual bool operator == (const Texture & other) const = 0;
		virtual operator int() = 0;

		virtual TextureSettings& getSettings() = 0;
	};
	class Texture2D : public Texture {
	public:
		virtual void setData(const void* data, uint32_t size, uint32_t mipLevel = 0) = 0;
		virtual void setPixel(uint32_t hexData, uint32_t posX, uint32_t posY, uint32_t mipLevel = 0) = 0;
		virtual void getData(void* data, uint32_t size, uint32_t mipLevel = 0) const = 0;
		virtual uint32_t getPixel(uint32_t posX, uint32_t posY, uint32_t mipLevel = 0) const = 0;
		virtual void update() = 0;
		//only TextureFiltering,TextureWrap and border color
		virtual void updateParameters() = 0;

		virtual uint32_t getMipWidth(uint32_t level) const = 0;
		virtual uint32_t getMipHeight(uint32_t level) const = 0;

		virtual std::string getPath() const = 0;
	};
}