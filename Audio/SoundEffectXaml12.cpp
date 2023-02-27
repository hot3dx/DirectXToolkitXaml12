//// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//// PARTICULAR PURPOSE.
////
//// Copyright (c) Microsoft Corporation. All rights reserved

#include "pch.h"
#include "AudioXaml12_22.h"
#include "SoundEffectXaml12.h"
#include "Graphics\PlatformHelpersXaml12.h"

SoundEffect::SoundEffect() :
    m_audioAvailable(false)
{
}

//----------------------------------------------------------------------

void SoundEffect::Initialize(
    _In_ IXAudio2* masteringEngine,
    _In_ WAVEFORMATEX* sourceFormat,
    _In_ Platform::Array<byte>^ soundData)
{
    m_soundData = soundData;

    if (masteringEngine == nullptr)
    {
        // Audio is not available so just return.
        m_audioAvailable = false;
        return;
    }

    // Create a source voice for this sound effect.
    DirectX::DXTKXAML12::ThrowIfFailed(
        masteringEngine->CreateSourceVoice(
            &m_sourceVoice,
            sourceFormat
            )
        );
    m_audioAvailable = true;
}

//----------------------------------------------------------------------

void SoundEffect::PlaySound(_In_ float volume)
{
    XAUDIO2_BUFFER buffer = { 0 };

    if (!m_audioAvailable)
    {
        // Audio is not available so just return.
        return;
    }

    // Interrupt sound effect if it is currently playing.
    DirectX::DXTKXAML12::ThrowIfFailed(
        m_sourceVoice->Stop()
        );
    DirectX::DXTKXAML12::ThrowIfFailed(
        m_sourceVoice->FlushSourceBuffers()
        );

    // Queue the memory buffer for playback and start the voice.
    buffer.AudioBytes = m_soundData->Length;
    buffer.pAudioData = m_soundData->Data;
    buffer.Flags = XAUDIO2_END_OF_STREAM;

    DirectX::DXTKXAML12::ThrowIfFailed(
        m_sourceVoice->SetVolume(volume)
        );
    DirectX::DXTKXAML12::ThrowIfFailed(
        m_sourceVoice->SubmitSourceBuffer(&buffer)
        );
    DirectX::DXTKXAML12::ThrowIfFailed(
        m_sourceVoice->Start()
        );
}

//----------------------------------------------------------------------
