    // Both the class ScreenGrab and the cdecl functions work!
    // DirectXPage Example
 /*
 ```
         #include <\DirectXToolKitXaml12\Graphics\ScreenGrabXaml12.h>
         #include <guiddef.h>
     void DirectXPage::OnKeyDown(Windows::UI::Core::CoreWindow^ /*window*/, Windows::UI::Core::KeyEventArgs^ args)
     {
         auto Key = args->VirtualKey;
	     switch (Key)
	     {
  case VirtualKey::O:
	{
		
		
		FileSavePicker^ pick = ref new  FileSavePicker();
		pick->SuggestedStartLocation = PickerLocationId::PicturesLibrary;

		auto plainTextExtensions = ref new Platform::Collections::Vector<Platform::String^>();
		Platform::String^ type = ref new Platform::String(L"Windows Bitmap");
		plainTextExtensions->Append(".bmp");
		pick->FileTypeChoices->Insert(type, plainTextExtensions);

		auto plainTextExtensions1 = ref new Platform::Collections::Vector<Platform::String^>();
		Platform::String^ type1 = ref new Platform::String(L"PNG");
		plainTextExtensions1->Append(".png");
		pick->FileTypeChoices->Insert(type1, plainTextExtensions1);

		auto plainTextExtensions2 = ref new Platform::Collections::Vector<Platform::String^>();
		Platform::String^ type2 = ref new Platform::String(L"JPEG");
		plainTextExtensions2->Append(".jpg");
		pick->FileTypeChoices->Insert(type2, plainTextExtensions2);

		auto plainTextExtensions3 = ref new Platform::Collections::Vector<Platform::String^>();
		Platform::String^ type3 = ref new Platform::String(L"TIFF");
		plainTextExtensions3->Append(".tiff");
		pick->FileTypeChoices->Insert(type3, plainTextExtensions3);

		auto plainTextExtensions4 = ref new Platform::Collections::Vector<Platform::String^>();
		Platform::String^ type4 = ref new Platform::String(L"GIF");
		plainTextExtensions4->Append(".gif");
		pick->FileTypeChoices->Insert(type4, plainTextExtensions4);

		auto plainTextExtensions5 = ref new Platform::Collections::Vector<Platform::String^>();
		Platform::String^ type6 = ref new Platform::String(L"Direct Draw Surface");
		plainTextExtensions5->Append(".dds");
		pick->FileTypeChoices->Insert(type6, plainTextExtensions5);

		pick->SuggestedFileName = ref new Platform::String(L"RotoDrawScreenShot");
		Platform::String^ fileNameS = ref new Platform::String();
		Platform::String^ s = ref new Platform::String(L"C:\\Hot3dxRotoDraw\\x64\\Release\\Hot3dxRotoDraw\\AppX\\Assets\\Textures\\");
		//s = L"Assets\\Textures\\";//GetProgramDirPathDXP();
		Platform::String^ sfile = ref new Platform::String(s->Data());
		sfile = sfile->Concat(sfile, fileNameS);


		create_task(pick->PickSaveFileAsync()).then([this](StorageFile^ file)
			{
				if (file != nullptr)
				{
					D3D12_RESOURCE_STATES beforeState = D3D12_RESOURCE_STATE_RENDER_TARGET;
					D3D12_RESOURCE_STATES afterState = D3D12_RESOURCE_STATE_RENDER_TARGET;
					std::function<void(IPropertyBag2*)> setCustomProps = nullptr;
					GUID guidContainerFormat;
					bool forceSRGB = false;
					const GUID* targetFormat = (const GUID*)NULL;
					unsigned int guidFormat = m_Scene11Vars->GetGuidFormatForScreenGrabVars();
					switch (guidFormat)
					{
					case 0:
					{
						guidContainerFormat = GUID_ContainerFormatBmp;
						SaveWICTextureToFile(
							m_deviceResources->GetCommandQueue(),
							m_deviceResources->GetRenderTarget(),
							guidContainerFormat,
							file->Path->Data(),
							beforeState,
							afterState,
							targetFormat,
							setCustomProps,
							forceSRGB
						);
					}break;
					case 1:
					{
						guidContainerFormat = GUID_ContainerFormatPng;
						SaveWICTextureToFile(
							m_deviceResources->GetCommandQueue(),
							m_deviceResources->GetRenderTarget(),
							guidContainerFormat,
							file->Path->Data(),
							beforeState,
							afterState,
							targetFormat,
							setCustomProps,
							forceSRGB
						);
					}break;
					case 2:
					{
						guidContainerFormat = GUID_ContainerFormatIco;
						SaveWICTextureToFile(
							m_deviceResources->GetCommandQueue(),
							m_deviceResources->GetRenderTarget(),
							guidContainerFormat,
							file->Path->Data(),
							beforeState,
							afterState,
							targetFormat,
							setCustomProps,
							forceSRGB
						);
					}break;
					case 3:
					{
						guidContainerFormat = GUID_ContainerFormatJpeg;
						SaveWICTextureToFile(
							m_deviceResources->GetCommandQueue(),
							m_deviceResources->GetRenderTarget(),
							guidContainerFormat,
							file->Path->Data(),
							beforeState,
							afterState,
							targetFormat,
							setCustomProps,
							forceSRGB
						);
					}break;
					case 4:
					{
						guidContainerFormat = GUID_ContainerFormatTiff;
						SaveWICTextureToFile(
							m_deviceResources->GetCommandQueue(),
							m_deviceResources->GetRenderTarget(),
							guidContainerFormat,
							file->Path->Data(),//fileNameW,
							beforeState,
							afterState,
							targetFormat,
							setCustomProps,
							forceSRGB
						);
						forceSRGB = true;
					}break;
					case 5:
					{
						//const wchar_t* fileNameW = L"C:\\Users\\hot3d\\Pictures\\ScreenShots\\ScreenGrab.gif";
						guidContainerFormat = GUID_ContainerFormatGif;
						SaveWICTextureToFile(
							m_deviceResources->GetCommandQueue(),
							m_deviceResources->GetRenderTarget(),
							guidContainerFormat,
							file->Path->Data(),//fileNameW,
							beforeState,
							afterState,
							targetFormat,
							setCustomProps,
							forceSRGB
						);
					}	break;
					case 6:
					{
						//const wchar_t* fileNameW = L"C:\\Users\\hot3d\\Pictures\\ScreenShots\\ScreenGrab.wmp";
						guidContainerFormat = GUID_ContainerFormatWmp;
						SaveWICTextureToFile(
							m_deviceResources->GetCommandQueue(),
							m_deviceResources->GetRenderTarget(),
							guidContainerFormat,
							file->Path->Data(),//fileNameW,
							beforeState,
							afterState,
							targetFormat,
							setCustomProps,
							forceSRGB
						);
					}break;
					default:
					{
						guidContainerFormat = GUID_ContainerFormatDds;
						DirectX::SaveDDSTextureToFile(
							m_deviceResources->GetCommandQueue(),
							m_deviceResources->GetRenderTarget(),
							file->Path->Data(),//fileNameW,fileName->Data(),
							beforeState,
							afterState);
					}break;
				}


					NotifyUser(L"ScreenGrab File Saved" + file->Path, NotifyType::StatusMessage);
				}// eo if create_task
				else
				{
					NotifyUser(L"ScreenGrab File Save Failure Error" + file->Path, NotifyType::StatusMessage);
				}
			});
			
					
		ScreenGrab* grab = new ScreenGrab();
		    grab->SaveDDSTextureToFile(
			m_deviceResources->GetCommandQueue(),
			m_deviceResources->GetRenderTarget(),
			fileName,
			beforeState,
			afterState);// noexcept

		grab->SaveWICTextureToFile(
			m_deviceResources->GetCommandQueue(),
			m_deviceResources->GetRenderTarget(),
			guidContainerFormat,
			fileNameW,
			beforeState,
			afterState,
			targetFormat,
			setCustomProps,
			forceSRGB
		);
		
	}break; // eo VirtualKey O
	}
}

*/