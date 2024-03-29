//--------------------------------------------------------------------------------------
// File: ScreenGrab.h
//
// Function for capturing a 2D texture and saving it to a file (aka a 'screenshot'
// when used on a Direct3D Render Target).
//
// Note these functions are useful as a light-weight runtime screen grabber. For
// full-featured texture capture, DDS writer, and texture processing pipeline,
// see the 'Texconv' sample and the 'DirectXTex' library.
//
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
//
// http://go.microsoft.com/fwlink/?LinkID=615561
//--------------------------------------------------------------------------------------

#pragma once

#if defined(_XBOX_ONE) && defined(_TITLE)
#include <d3d12_x.h>
#else
#include <d3d12.h>
#endif
#include <wincodec.h>
#include <OCIdl.h>
#include <functional>
#pragma comment(lib,"uuid.lib")
#pragma comment(lib,"Windowscodecs.lib")

namespace DirectX
{

    namespace DXTKXAML12
    {
        
        class ScreenGrab
        {
            public:

                ScreenGrab() {}
                ~ScreenGrab() {}

            HRESULT __cdecl SaveDDSTextureToFile(
                _In_ ID3D12CommandQueue* pCommandQueue,
                _In_ ID3D12Resource* pSource,
                _In_z_
                Platform::String^ fileName,
                D3D12_RESOURCE_STATES beforeState = D3D12_RESOURCE_STATE_RENDER_TARGET,
                D3D12_RESOURCE_STATES afterState = D3D12_RESOURCE_STATE_RENDER_TARGET);

            HRESULT __cdecl SaveWICTextureToFile(
                _In_ ID3D12CommandQueue* pCommandQ,
                _In_ ID3D12Resource* pSource,
                REFGUID guidContainerFormat,
                _In_z_ const wchar_t* fileName,
                D3D12_RESOURCE_STATES beforeState = D3D12_RESOURCE_STATE_RENDER_TARGET,
                D3D12_RESOURCE_STATES afterState = D3D12_RESOURCE_STATE_RENDER_TARGET,
                _In_opt_ const GUID* targetFormat = nullptr,
                _In_opt_ std::function<void __cdecl(IPropertyBag2*)> setCustomProps = nullptr,
                bool forceSRGB = false);
        };

        
    }
    HRESULT SaveDDSTextureToFile(ID3D12CommandQueue* pCommandQ, 
        ID3D12Resource* pSource, 
        const wchar_t* fileName, 
        D3D12_RESOURCE_STATES beforeState, 
        D3D12_RESOURCE_STATES afterState) noexcept;

    HRESULT __cdecl SaveWICTextureToFile(
        _In_ ID3D12CommandQueue* pCommandQ,
        _In_ ID3D12Resource* pSource,
        REFGUID guidContainerFormat,
        _In_z_ const wchar_t* fileName,
        D3D12_RESOURCE_STATES beforeState = D3D12_RESOURCE_STATE_RENDER_TARGET,
        D3D12_RESOURCE_STATES afterState = D3D12_RESOURCE_STATE_RENDER_TARGET,
        _In_opt_ const GUID* targetFormat = nullptr,
        _In_opt_ std::function<void __cdecl(IPropertyBag2*)> setCustomProps = nullptr,
        bool forceSRGB = false);
}