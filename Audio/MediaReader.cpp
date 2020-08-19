//// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//// PARTICULAR PURPOSE.
////
//// Copyright (c) Microsoft Corporation. All rights reserved

#include "pch.h"
#include "MediaReader.h"
#include "..\Graphics\PlatformHelpers.h"

#pragma comment(lib, "mfplat.lib")
#pragma comment(lib, "mfreadwrite.lib")
#pragma comment(lib, "mfuuid.lib")

using namespace Microsoft::WRL;
using namespace Windows::Storage;
using namespace Windows::Storage::Streams;
using namespace Windows::Foundation;
using namespace Windows::ApplicationModel;

MediaReader::MediaReader()
{
    ZeroMemory(&m_waveFormat, sizeof(m_waveFormat));
    m_installedLocation = Package::Current->InstalledLocation;
    m_installedLocationPath = Platform::String::Concat(m_installedLocation->Path, "\\");
}

WAVEFORMATEX* MediaReader::GetOutputWaveFormatEx()
{
    return &m_waveFormat;
}

Platform::Array<BYTE>^ MediaReader::LoadMedia(_In_ Platform::String^ filename)
{
    DirectX::ThrowIfFailed(
        MFStartup(MF_VERSION)
        );

    ComPtr<IMFSourceReader> reader;
    Platform::String^ file = Platform::String::Concat(m_installedLocationPath, filename)->ToString();
    DirectX::ThrowIfFailed(
        MFCreateSourceReaderFromURL(
            file->Data(),
            nullptr,
            &reader
            )
        );

    // Set the decoded output format as PCM.
    // XAudio2 on Windows can process PCM and ADPCM-encoded buffers.
    // When using MediaFoundation, this sample always decodes into PCM.
    Microsoft::WRL::ComPtr<IMFMediaType> mediaType;
    DirectX::ThrowIfFailed(
        MFCreateMediaType(&mediaType)
        );

    DirectX::ThrowIfFailed(
        mediaType->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Audio)

        );

    DirectX::ThrowIfFailed(
        mediaType->SetGUID(MF_MT_SUBTYPE, MFAudioFormat_PCM)
        );

    DirectX::ThrowIfFailed(
        reader->SetCurrentMediaType(static_cast<UINT32>(MF_SOURCE_READER_FIRST_AUDIO_STREAM), 0, mediaType.Get())
        );

    // Get the completeWAVEFORMAT from the Media Type.
    Microsoft::WRL::ComPtr<IMFMediaType> outputMediaType;
    DirectX::ThrowIfFailed(
        reader->GetCurrentMediaType(static_cast<UINT32>(MF_SOURCE_READER_FIRST_AUDIO_STREAM), &outputMediaType)
        );

    UINT32 size = 0;
    WAVEFORMATEX* waveFormat;
    DirectX::ThrowIfFailed(
        MFCreateWaveFormatExFromMFMediaType(outputMediaType.Get(), &waveFormat, &size)
        );

    CopyMemory(&m_waveFormat, waveFormat, sizeof(m_waveFormat));
    CoTaskMemFree(waveFormat);

    PROPVARIANT propVariant;
    DirectX::ThrowIfFailed(
        reader->GetPresentationAttribute(static_cast<UINT32>(MF_SOURCE_READER_MEDIASOURCE), MF_PD_DURATION, &propVariant)
        );
    // 'duration' is in 100ns units; convert to seconds, and round up
    // to the nearest whole byte.
    LONGLONG duration = propVariant.uhVal.QuadPart;
    unsigned int maxStreamLengthInBytes =
        static_cast<unsigned int>(
            ((duration * static_cast<ULONGLONG>(m_waveFormat.nAvgBytesPerSec)) + 10000000) /
            10000000
            );

    Platform::Array<BYTE>^ fileData = ref new Platform::Array<BYTE>(maxStreamLengthInBytes);

    ComPtr<IMFSample> sample;
    ComPtr<IMFMediaBuffer> mediaBuffer;
    DWORD flags = 0;

    int positionInData = 0;
    bool done = false;
    while (!done)
    {
        DirectX::ThrowIfFailed(
            reader->ReadSample(static_cast<UINT32>(MF_SOURCE_READER_FIRST_AUDIO_STREAM), 0, nullptr, &flags, nullptr, &sample)
            );

        if (sample != nullptr)
        {
            DirectX::ThrowIfFailed(
                sample->ConvertToContiguousBuffer(&mediaBuffer)
                );

            BYTE* audioData = nullptr;
            DWORD sampleBufferLength = 0;
            DirectX::ThrowIfFailed(
                mediaBuffer->Lock(&audioData, nullptr, &sampleBufferLength)
                );

            for (DWORD i = 0; i < sampleBufferLength; i++)
            {
                fileData[positionInData++] = (BYTE)audioData[i];
            }
        }
        if (flags & MF_SOURCE_READERF_ENDOFSTREAM)
        {
            done = true;
        }
    }

    return fileData;
}