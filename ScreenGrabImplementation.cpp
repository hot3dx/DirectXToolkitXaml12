//
// By CoPilot
//--------------------------------------------------------------------------------------
#include "ScreenGrabXaml12.h"

#include "pch.h"
#include "Graphics/d3dx12/include/directx/d3d12.h"
#pragma comment(lib,"uuid.lib")
#include "ScreenGrabXaml12.h"
#include "DirectXHelpersXaml12.h"

#include "PlatformHelpersXaml12.h"
#include "DDSXaml12.h"
#include "LoaderHelpersXaml12.h"
#include <wincodec.h>
#include <shcore.h>
#include <shlwapi.h>

using namespace Concurrency;


using Microsoft::WRL::ComPtr;
using namespace DirectX;
using namespace DirectX::DXTKXAML12;
using namespace DirectX::DXTKXAML12::LoaderHelpers;
using namespace Windows::Foundation::Collections;
using namespace Windows::Storage;
using namespace Windows::Storage::Pickers;
using namespace Windows::Storage::Streams;
using namespace Concurrency;

//--------------------------------------------------------------------------------------
namespace DirectX
{
    extern IWICImagingFactory2* _GetWIC();

}

namespace DirectX::DXTKXAML12
{
    HRESULT ScreenGrab::SaveDDSTextureToStream(
        ID3D12CommandQueue* pCommandQueue,
        ID3D12Resource* pSource,
        IStream* stream,
        D3D12_RESOURCE_STATES beforeState,
        D3D12_RESOURCE_STATES afterState)
    {
        if (!stream)
            return E_INVALIDARG;

        // (1) Capture texture to staging resource (reuse your existing logic)  
        // (2) Build DDS header and pixel data (reuse your existing logic)  
        // (3) Write header and pixel data to stream  

        // Example: Write header  
        ULONG written = 0;
        // Define fileHeader and headerSize before their usage in the SaveDDSTextureToStream method.  
        // Assuming fileHeader is a pointer to the DDS header and headerSize is the size of the header.  

        BYTE fileHeader[128] = {}; // Example size for DDS header, adjust as needed.  
        size_t headerSize = sizeof(fileHeader)/* actual size of your DDS header, e.g. sizeof(fileHeader) or as calculated */;

        // Ensure these definitions are placed before the line where they are used:  
        HRESULT hr = stream->Write(fileHeader, static_cast<ULONG>(headerSize), &written);
        // Define fileHeader and headerSize before their usage in the SaveDDSTextureToStream method.  

        if (FAILED(hr) || written != headerSize)
            return E_FAIL;

        // Write pixel data  
         // Define the missing variables "pixels" and "slicePitch" before their usage in the SaveDDSTextureToStream method.  
        // Assuming "pixels" is a unique_ptr to BYTE and "slicePitch" is a size_t representing the pitch of the slice.  

        std::unique_ptr<BYTE[]> pixels;
        size_t slicePitch = 0;

        // Initialize "pixels" and "slicePitch" based on the captured texture data.  
        // Example initialization logic:  

        // ... (existing includes and code above)
        UINT64 totalResourceSize = 0;
        UINT64 fpRowPitch = 0;
        UINT fpRowCount = 0;

        pixels = std::make_unique<BYTE[]>(totalResourceSize);
        slicePitch = static_cast<size_t>(fpRowPitch * fpRowCount);
        hr = stream->Write(pixels.get(), static_cast<ULONG>(slicePitch), &written);


        // Ensure these definitions are placed before the line where they are used:  
        hr = stream->Write(pixels.get(), static_cast<ULONG>(slicePitch), &written);
        if (FAILED(hr) || written != slicePitch)
            return E_FAIL;

        return S_OK;
//    }
//}// namespace DirectX::DXTKXAML12

    if (!pCommandQueue || !pSource || !stream)
        return E_INVALIDARG;
    ComPtr<ID3D12Device> device;
    pCommandQueue->GetDevice(IID_GRAPHICS_PPV_ARGS(device.GetAddressOf()));
    // Get the size of the image
    const auto desc = pSource->GetDesc();
    if (desc.Width > UINT32_MAX)
        return E_INVALIDARG;
    //UINT64 totalResourceSize = 0;
   // UINT64 fpRowPitch = 0;
   // UINT fpRowCount = 0;
    // Get the rowcount, pitch and size of the top mip
    device->GetCopyableFootprints(
        &desc,
        0,
        1,
        0,
        nullptr,
        &fpRowCount,
        &fpRowPitch,
		&totalResourceSize);
    #if defined(_XBOX_ONE) && defined(_TITLE)
    // Round up the srcPitch to multiples of 1024
	UINT64 dstRowPitch = (fpRowPitch + static_cast<uint64_t>(D3D12XBOX_TEXTURE_DATA_PITCH_ALIGNMENT) - 1u) & ~(static_cast<uint64_t>(D3D12XBOX_TEXTURE_DATA_PITCH_ALIGNMENT) - 1u);
    #else
	// Round up the srcPitch to multiples of 256
    UINT64 dstRowPitch = (fpRowPitch + 255) & ~0xFFu;
    #endif
    if (dstRowPitch > UINT32_MAX)
        return HRESULT_FROM_WIN32(ERROR_ARITHMETIC_OVERFLOW);
    ComPtr<ID3D12Resource> pStaging;
     hr = CaptureTexture(device.Get(), pCommandQueue, pSource, dstRowPitch, desc, pStaging, beforeState, afterState);
    if (FAILED(hr))
        return hr;
    // Write to stream
	return SaveDDSTextureToStream(pCommandQueue, pStaging.Get(), stream, beforeState, afterState);
	} // namespace DXTKXAML12

	//
	//--------------------------------------------------------------------------------------
	// SaveWICTextureToStream
    HRESULT ScreenGrab::SaveWICTextureToStream(
    ID3D12CommandQueue* pCommandQueue,
    ID3D12Resource* pSource,
    REFGUID guidContainerFormat,
    IStream* stream,
    D3D12_RESOURCE_STATES beforeState,
    D3D12_RESOURCE_STATES afterState,
    const GUID* targetFormat,
    std::function<void __cdecl(IPropertyBag2*)> setCustomProps,
		bool forceSRGB)
            
        {
    if (!stream)
        return E_INVALIDARG;

    auto pWIC = _GetWIC();
    if (!pWIC)
        return E_NOINTERFACE;

    // (1) Capture texture to staging resource (reuse your existing logic)
    // (2) Create WIC encoder for guidContainerFormat
    ComPtr<IWICBitmapEncoder> encoder;
    HRESULT hr = pWIC->CreateEncoder(guidContainerFormat, nullptr, encoder.GetAddressOf());
    if (FAILED(hr))
        return hr;
    hr = encoder->Initialize(stream, WICBitmapEncoderNoCache);
    if (FAILED(hr))
        return hr;
    // (3) Continue as in your file-based method: create frame, set properties, write pixels, commit, etc.
	return S_OK;
	} // namespace DXTKXAML12
	//
	//--------------------------------------------------------------------------------------
    // SaveWICTextureToFile
    HRESULT ScreenGrab::SaveWICTextureToFile(
        ID3D12CommandQueue* pCommandQ,
        ID3D12Resource* pSource,
        REFGUID guidContainerFormat,
        const wchar_t* fileName,
        D3D12_RESOURCE_STATES beforeState,
        D3D12_RESOURCE_STATES afterState,
        const GUID* targetFormat,
        std::function<void __cdecl(IPropertyBag2*)> setCustomProps,
        bool forceSRGB)
    {
        if (!fileName)
            return E_INVALIDARG;
        ComPtr<IStream> stream;
        HRESULT hr = SHCreateStreamOnFileEx(fileName, STGM_CREATE | STGM_WRITE | STGM_SHARE_DENY_WRITE, FILE_ATTRIBUTE_NORMAL, TRUE, nullptr, stream.GetAddressOf());
        if (FAILED(hr))
            return hr;
        return SaveWICTextureToStream(pCommandQ, pSource, guidContainerFormat, stream.Get(), beforeState, afterState, targetFormat, setCustomProps, forceSRGB);
	}
	//--------------------------------------------------------------------------------------
	// SaveDDSTextureToFile
    HRESULT ScreenGrab::SaveDDSTextureToFile(
    ID3D12CommandQueue* pCommandQueue,
    ID3D12Resource* pSource,
    Platform::String^ fileName,
    D3D12_RESOURCE_STATES beforeState,
		D3D12_RESOURCE_STATES afterState)
        {
    if (!fileName)
        return E_INVALIDARG;
    ComPtr<ID3D12Device> device;
    pCommandQueue->GetDevice(IID_GRAPHICS_PPV_ARGS(device.GetAddressOf()));
    // Get the size of the image
    const auto desc = pSource->GetDesc();
    if (desc.Width > UINT32_MAX)
        return E_INVALIDARG;
    UINT64 totalResourceSize = 0;
    UINT64 fpRowPitch = 0;
    UINT fpRowCount = 0;
    // Get the rowcount, pitch and size of the top mip
    device->GetCopyableFootprints(
        &desc,
        0,
        1,
        0,
        nullptr,
        &fpRowCount,
        &fpRowPitch,
		&totalResourceSize);    
    #if defined(_XBOX_ONE) && defined(_TITLE)
    // Round up the srcPitch to multiples of 1024
	UINT64 dstRowPitch = (fpRowPitch + static_cast<uint64_t>(D3D12XBOX_TEXTURE_DATA_PITCH_ALIGNMENT) - 1u) & ~(static_cast<uint64_t>(D3D12XBOX_TEXTURE_DATA_PITCH_ALIGNMENT) - 1u);
#else
    // Round up the srcPitch to multiples of 256
	UINT64 dstRowPitch = (fpRowPitch + 255) & ~0xFFu;
    #endif
    if (dstRowPitch > UINT32_MAX)
        return HRESULT_FROM_WIN32(ERROR_ARITHMETIC_OVERFLOW);
    ComPtr<ID3D12Resource> pStaging;
    HRESULT hr = CaptureTexture(device.Get(), pCommandQueue, pSource, dstRowPitch, desc, pStaging, beforeState, afterState);
    if (FAILED(hr))
        return hr;
    // Create file
    ScopedHandle hFile(safe_handle(CreateFile2(
        fileName->Data(),
        GENERIC_WRITE, 0, CREATE_ALWAYS,
        nullptr)));
    if (!hFile)
        return HRESULT_FROM_WIN32(GetLastError());

    ComPtr<IStream> stream;
    HRESULT hr = SHCreateStreamOnFileEx(
        fileName->Data(),
        STGM_CREATE | STGM_WRITE | STGM_SHARE_DENY_WRITE,
        FILE_ATTRIBUTE_NORMAL,
        TRUE, // create file if it doesn't exist
        nullptr,
        &stream);
    if (FAILED(hr))
        return hr;
    // Write to file
    return SaveDDSTextureToStream(pCommandQueue, pStaging.Get(), stream.Get()/*hFile.get()*/, beforeState, afterState);
	} // namespace DXTKXAML12
    //--------------------------------------------------------------------------------------
    // CreateFromStream
    HRESULT ScreenGrab::CreateFromStream(
        ID3D12Device* device,
        ID3D12GraphicsCommandList* commandList,
        IStream* stream,
        ID3D12Resource** texture,
        D3D12_SUBRESOURCE_DATA* subresource,
        D3D12_RESOURCE_STATES initialState,
        bool forceSRGB)
    {
        if (!device || !commandList || !stream || !texture)
            return E_INVALIDARG;
        // Implement the logic to create a texture from the stream
        // This will involve reading the stream, decoding the image format, and creating a D3D12 resource
        return S_OK; // Placeholder for actual implementation
	}
    //--------------------------------------------------------------------------------------
    // CreateFromStream (WinRT IRandomAccessStream^ overload)
    HRESULT ScreenGrab::CreateFromStream(
        ID3D12Device* device,
        ID3D12GraphicsCommandList* commandList,
        Windows::Storage::Streams::IRandomAccessStream^ randomAccessStream,
        ID3D12Resource** texture,
        D3D12_SUBRESOURCE_DATA* subresource,
        D3D12_RESOURCE_STATES initialState,
        bool forceSRGB)
    {
        if (!device || !commandList || !randomAccessStream || !texture)
            return E_INVALIDARG;
        // Implement the logic to create a texture from the WinRT stream
        // This will involve reading the stream, decoding the image format, and creating a D3D12 resource
        return S_OK; // Placeholder for actual implementation
	}
    HRESULT __cdecl DirectX::DXTKXAML12::ScreenGrab::SaveWICTextureToStream(ID3D12CommandQueue* pCommandQ, ID3D12Resource* pSource, REFGUID guidContainerFormat, Windows::Storage::Streams::IRandomAccessStream^ randomAccessStream, D3D12_RESOURCE_STATES beforeState, D3D12_RESOURCE_STATES afterState, const GUID* targetFormat, std::function<void __cdecl(IPropertyBag2*)> setCustomProps, bool forceSRGB)
    {
        return E_NOTIMPL;
    }
} // namespace DXTKXAML12
