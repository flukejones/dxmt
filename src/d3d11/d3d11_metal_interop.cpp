#include "d3d11_metal_interop.hpp"
#include "d3d11_fence.hpp"
#include "d3d11_resource.hpp"

namespace dxmt {

HRESULT STDMETHODCALLTYPE
MTLD3D11InteropDevice::ImportMTLTexture2D(
    const D3D11_TEXTURE2D_DESC1 *pDesc, uint64_t mtlTexture, ID3D11Texture2D **ppTexture2D
) {
  return dxmt::ImportMTLTexture2D(device_, pDesc, mtlTexture, ppTexture2D);
}

HRESULT STDMETHODCALLTYPE
MTLD3D11InteropDevice::GetFenceSharedEvent(ID3D11Fence *pFence, uint64_t *pMtlSharedEvent) {
  if (!pMtlSharedEvent)
    return E_POINTER;
  *pMtlSharedEvent = 0;
  if (!pFence)
    return E_POINTER;

  Com<MTLD3D11Fence> fence;
  HRESULT hr = pFence->QueryInterface(IID_MTLD3D11Fence, (void **)&fence);
  if (FAILED(hr))
    return hr;

  Com<ID3D11Device> device;
  fence->GetDevice(&device);
  if (device != static_cast<ID3D11Device *>(device_))
    return E_INVALIDARG;

  *pMtlSharedEvent = fence->event.handle;
  return S_OK;
}

} // namespace dxmt
