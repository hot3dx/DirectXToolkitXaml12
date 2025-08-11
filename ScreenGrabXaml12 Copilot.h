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

#include "pch.h"

#include "Graphics/DirectXHelpersXaml12.h"
#include "Graphics/PlatformHelpersXaml12.h"
#include "Graphics/DDSXaml12.h"
#include "Graphics/LoaderHelpersXaml12.h"
#include <DirectXMath.h>
#include "wrl.h"

#if defined(_XBOX_ONE) && defined(_TITLE)
#include <d3d12_x.h>
#else
#include "Graphics/d3dx12/include/directx/d3d12.h"
#endif

#if defined(_XBOX_ONE) && defined(_TITLE)
#include <d3d12_x.h>
#else
#include "Graphics/d3dx12/include/directx/d3d12.h"
#include "Graphics/d3dx12/include/directx/d3dx12.h"
#endif
#include <wincodec.h>
#include <OCIdl.h>
#include <functional>
#pragma comment(lib,"uuid.lib")
#pragma comment(lib,"Windowscodecs.lib")

using namespace Microsoft::WRL;

namespace DirectX
{

    namespace DXTKXAML12
    {
        
        class ScreenGrab
        {
            public:

                ScreenGrab() {}
                ~ScreenGrab() {}

            HRESULT __cdecl CaptureTexture(_In_ ID3D12Device* device,
                    _In_ ID3D12CommandQueue* pCommandQ,
                    _In_ ID3D12Resource* pSource,
                    UINT64 srcPitch,
                    const D3D12_RESOURCE_DESC& desc,
                    ComPtr<ID3D12Resource>& pStaging,
                    D3D12_RESOURCE_STATES beforeState,
                    D3D12_RESOURCE_STATES afterState);

            HRESULT __cdecl SaveDDSTextureToFile(
                _In_ ID3D12CommandQueue* pCommandQueue,
                _In_ ID3D12Resource* pSource,
                _In_z_ Platform::String^ fileName,
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

            // NEW: Create a texture from a WIC-supported stream (PNG, JPG, ICO, TIFF, BMP, GIF, etc.)
            static HRESULT __cdecl CreateFromStream(
                _In_ ID3D12Device* device,
                _In_ ID3D12GraphicsCommandList* commandList,
                _In_ IStream* stream,
                _Out_ ID3D12Resource** texture,
                _Out_opt_ D3D12_SUBRESOURCE_DATA* subresource = nullptr,
                D3D12_RESOURCE_STATES initialState = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
                bool forceSRGB = false);

            // Overload for WinRT IRandomAccessStream^
            static HRESULT __cdecl CreateFromStream(
                _In_ ID3D12Device* device,
                _In_ ID3D12GraphicsCommandList* commandList,
                _In_ Windows::Storage::Streams::IRandomAccessStream^ randomAccessStream,
                _Out_ ID3D12Resource** texture,
                _Out_opt_ D3D12_SUBRESOURCE_DATA* subresource = nullptr,
                D3D12_RESOURCE_STATES initialState = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
                bool forceSRGB = false);

            // Save DDS texture to a COM IStream
            static HRESULT __cdecl SaveDDSTextureToStream(
                _In_ ID3D12CommandQueue* pCommandQueue,
                _In_ ID3D12Resource* pSource,
                _In_ IStream* stream,
                D3D12_RESOURCE_STATES beforeState = D3D12_RESOURCE_STATE_RENDER_TARGET,
                D3D12_RESOURCE_STATES afterState = D3D12_RESOURCE_STATE_RENDER_TARGET);

            // Save WIC texture to a COM IStream
            static HRESULT __cdecl SaveWICTextureToStream(
                _In_ ID3D12CommandQueue* pCommandQ,
                _In_ ID3D12Resource* pSource,
                REFGUID guidContainerFormat,
                _In_ IStream* stream,
                D3D12_RESOURCE_STATES beforeState = D3D12_RESOURCE_STATE_RENDER_TARGET,
                D3D12_RESOURCE_STATES afterState = D3D12_RESOURCE_STATE_RENDER_TARGET,
                _In_opt_ const GUID* targetFormat = nullptr,
                _In_opt_ std::function<void __cdecl(IPropertyBag2*)> setCustomProps = nullptr,
                bool forceSRGB = false);

            // Overload for WinRT IRandomAccessStream^ (for UWP/XAML)
            static HRESULT __cdecl SaveWICTextureToStream(
                _In_ ID3D12CommandQueue* pCommandQ,
                _In_ ID3D12Resource* pSource,
                REFGUID guidContainerFormat,
                _In_ Windows::Storage::Streams::IRandomAccessStream^ randomAccessStream,
                D3D12_RESOURCE_STATES beforeState = D3D12_RESOURCE_STATE_RENDER_TARGET,
                D3D12_RESOURCE_STATES afterState = D3D12_RESOURCE_STATE_RENDER_TARGET,
                _In_opt_ const GUID* targetFormat = nullptr,
                _In_opt_ std::function<void __cdecl(IPropertyBag2*)> setCustomProps = nullptr,
                bool forceSRGB = false);
        };

        HRESULT __cdecl SaveDDSTextureToStreamImp(ID3D12CommandQueue* pCommandQueue,
            ID3D12Resource* pSource,
            IStream* stream,
            D3D12_RESOURCE_STATES beforeState = D3D12_RESOURCE_STATE_RENDER_TARGET,
            D3D12_RESOURCE_STATES afterState = D3D12_RESOURCE_STATE_RENDER_TARGET);

        HRESULT __cdecl SaveDDSTextureToFileEx(ID3D12CommandQueue* pCommandQ,
            ID3D12Resource* pSource,
            const wchar_t* fileName,
            D3D12_RESOURCE_STATES beforeState,
            D3D12_RESOURCE_STATES afterState) noexcept;

        HRESULT __cdecl SaveWICTextureToFileEx(
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

  
}