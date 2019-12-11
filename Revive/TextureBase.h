#pragma once

#include "OVR_CAPI.h"
#include "openvr.h"

#include <memory>

#define REV_SWAPCHAIN_MAX_LENGTH 3

class TextureBase
{
public:
	TextureBase() { }
	virtual ~TextureBase() { };

	virtual void ToVRTexture(vr::Texture_t& out) = 0;
	virtual bool Init(ovrTextureType type, int width, int height, int mipLevels, int arraySize,
		ovrTextureFormat format, unsigned int miscFlags, unsigned int bindFlags) = 0;
};

struct ovrTextureSwapChainData
{
	ovrTextureSwapChainDesc Desc;
	vr::VROverlayHandle_t Overlay;

	unsigned int Identifier;
	int Length, CurrentIndex, SubmitIndex;
	std::unique_ptr<TextureBase> Textures[REV_SWAPCHAIN_MAX_LENGTH];

	bool Full() { return (CurrentIndex + 1) % Length == SubmitIndex; }
	void Commit() { SubmitIndex = CurrentIndex++; CurrentIndex %= Length; };
	TextureBase* Submit() { return Textures[SubmitIndex].get(); };

	ovrTextureSwapChainData(ovrTextureSwapChainDesc desc);
	~ovrTextureSwapChainData();
};

struct ovrMirrorTextureData
{
	ovrMirrorTextureDesc Desc;
	std::unique_ptr<TextureBase> Texture;

	ovrMirrorTextureData(ovrMirrorTextureDesc desc);
	~ovrMirrorTextureData();
};
