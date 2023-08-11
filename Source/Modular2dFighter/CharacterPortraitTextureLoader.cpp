// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterPortraitTextureLoader.h"
#include "Engine/Texture2D.h"
#include "IImageWrapperModule.h"
#include "Modules/ModuleManager.h"
#include "IImageWrapper.h"
#include "Misc/FileHelper.h"

UTexture2D* UCharacterPortraitTextureLoader::LoadTextureFromPath(const FString& Path)
{
    IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>("ImageWrapper");
    TSharedPtr<IImageWrapper> ImageWrapper = ImageWrapperModule.CreateImageWrapper(EImageFormat::PNG);

    // Ensure the Image Wrapper is valid
    if (!ImageWrapper.IsValid())
    {
        return nullptr;
    }

    TArray<uint8> RawFileData;
    if (!FFileHelper::LoadFileToArray(RawFileData, *Path))
    {
        return nullptr;
    }

    TArray<uint8> UncompressedBGRA;
    if (ImageWrapper->GetRaw(RenderCore::ERGBFormat::BGRA8, 8, RawFileData, UncompressedBGRA))
    {
        UTexture2D* Texture = UTexture2D::CreateTransient(ImageWrapper->GetWidth(), ImageWrapper->GetHeight(), PF_B8G8R8A8);

        if (!Texture)
        {
            return nullptr;
        }

        void* TextureData = Texture->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
        FMemory::Memcpy(TextureData, UncompressedBGRA.GetData(), UncompressedBGRA.Num());
        Texture->PlatformData->Mips[0].BulkData.Unlock();

        Texture->UpdateResource();

        return Texture;
    }

    return nullptr;
}