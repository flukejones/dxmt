#pragma once
#include "d3d11_device.hpp"
#include "util_d3dkmt.h"

namespace dxmt {

constexpr GUID IID_MTLD3D11Fence = guid::make_guid("e43100ac-1d19-4fc6-9833-87a532ae0722");

struct MTLD3D11Fence : public ID3D11Fence {
  WMT::Reference<WMT::SharedEvent> event;
  D3DKMT_HANDLE local_kmt = 0;
};

HRESULT
CreateFence(MTLD3D11Device *pDevice, UINT64 InitialValue,
            D3D11_FENCE_FLAG Flags, REFIID riid, void **ppFence);

HRESULT
OpenSharedFence(MTLD3D11Device *pDevice, HANDLE hResource,
                REFIID riid, void **ppFence);

} // namespace dxmt
