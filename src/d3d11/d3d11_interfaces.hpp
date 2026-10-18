#pragma once
#include "com/com_guid.hpp"
#include <d3d11_3.h>

struct MTL_TEMPORAL_UPSCALE_D3D11_DESC {
  UINT InputContentWidth; // can be 0, which means full width
  UINT InputContentHeight; // can be 0, which means full height
  BOOL AutoExposure;
  BOOL InReset;
  BOOL DepthReversed;
  BOOL MotionVectorInDisplayRes;
  ID3D11Resource *Color;
  ID3D11Resource *Depth;
  ID3D11Resource *MotionVector;
  ID3D11Resource *Output;
  FLOAT MotionVectorScaleX;
  FLOAT MotionVectorScaleY;
  FLOAT PreExposure;
  ID3D11Resource *ExposureTexture;
  FLOAT JitterOffsetX;
  FLOAT JitterOffsetY;
};

DEFINE_COM_INTERFACE("43ace3ce-1956-448b-a4eb-aee68bdeb283",
                     IMTLD3D11ContextExt)
    : public IUnknown{
   virtual void STDMETHODCALLTYPE TemporalUpscale(const MTL_TEMPORAL_UPSCALE_D3D11_DESC *pDesc) = 0;
   virtual void STDMETHODCALLTYPE BeginUAVOverlap() = 0;
   virtual void STDMETHODCALLTYPE EndUAVOverlap() = 0;
};

typedef enum MTL_FEATURE {
  MTL_FEATURE_METALFX_TEMPORAL_SCALER = 0,
} MTL_FEATURE;

DEFINE_COM_INTERFACE("19a8e35a-38be-418f-94e3-9f7323936870", IMTLD3D11ContextExt1) : public IMTLD3D11ContextExt {
  virtual HRESULT STDMETHODCALLTYPE CheckFeatureSupport(
      MTL_FEATURE Feature, void *pFeatureSupportData, UINT FeatureSupportDataSize
  ) = 0;
};

DEFINE_COM_INTERFACE("efc77ae6-2179-4c0a-b844-7661ca0dcde7", IMTLD3D11DeviceExt)
    : public IUnknown {
  virtual void STDMETHODCALLTYPE SetShaderExtensionSlot(UINT Slot) = 0;
};

DEFINE_COM_INTERFACE("8b6fc874-7429-430d-8253-522e296cd8e2", IMTLD3D11InteropDevice) : public IUnknown {
  // Imports a texture from the same Metal device without copying pixels. The returned resource retains
  // the texture; the caller keeps its own reference and must synchronize external GPU access.
  virtual HRESULT STDMETHODCALLTYPE ImportMTLTexture2D(
      const D3D11_TEXTURE2D_DESC1 *pDesc, uint64_t mtlTexture, ID3D11Texture2D **ppTexture2D
  ) = 0;
  // Returns a borrowed event: keep the fence and its device alive, or retain the event separately.
  // Null arguments return E_POINTER, non-DXMT fences E_NOINTERFACE, and other-device fences E_INVALIDARG.
  // A writable output is cleared on failure.
  virtual HRESULT STDMETHODCALLTYPE GetFenceSharedEvent(ID3D11Fence * pFence, uint64_t *pMtlSharedEvent) = 0;
};

DEFINE_COM_INTERFACE("cd310930-fc58-4a35-aa51-2065e37a83e7", IMTLD3D11InteropDevice1) : public IMTLD3D11InteropDevice {
  // Returns a borrowed Metal device; keep this COM device alive or retain the native object.
  virtual HRESULT STDMETHODCALLTYPE GetMetalDevice(uint64_t *pMtlDevice) = 0;
};
