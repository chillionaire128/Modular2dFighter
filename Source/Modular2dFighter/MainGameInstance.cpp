// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameInstance.h"

void UMainGameInstance::Init()
{
    Super::Init();
    ScanCharactersDirectory();
}

void UMainGameInstance::ScanCharactersDirectory()
{
    IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

    // Assuming characters are stored in a "Characters" directory under the Content directory
    FString CharacterFolderPath = FPaths::ProjectContentDir() + TEXT("Characters/");

    // Array to hold found directory entries (both files and directories)
    TArray<FString> CharacterDirectories;

    // Using IterateDirectory to get directories
    bool bFoundDirs = PlatformFile.IterateDirectory(*CharacterFolderPath, [&CharacterDirectories](const TCHAR* FilenameOrDirectory, bool bIsDirectory) -> bool
        {
            if (bIsDirectory)
            {
                CharacterDirectories.Add(FilenameOrDirectory);
            }
            return true;  // Continue iteration
        });

    if (bFoundDirs)
    {
        for (FString CharacterDir : CharacterDirectories)
        {
            FString SettingsFilePath = CharacterDir + TEXT("/settings/settings.txt");
            if (FPaths::FileExists(SettingsFilePath))
            {
                //parse the JSON file
                FString JsonRaw;
                if (FFileHelper::LoadFileToString(JsonRaw, *SettingsFilePath))
                {
                    TSharedPtr<FJsonObject> JsonObject;
                    TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonRaw);

                    if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
                    {
                        FString CharName = JsonObject->GetStringField("name");
                        int32 CharHealth = JsonObject->GetIntegerField("health");
                        FString IconFileName = JsonObject->GetStringField("selectIcon");

                        // Assembling the icon path
                        FString FullIconPath = CharacterDir + TEXT("/ArtAssets/") + IconFileName;

                        UE_LOG(LogTemp, Warning, TEXT("Character Name: %s, Health: %d, Select Icon: %s"), *CharName, CharHealth, *FullIconPath);

                        // Check if the selectIcon file exists
                        if (PlatformFile.FileExists(*FullIconPath))
                        {
                            UE_LOG(LogTemp, Warning, TEXT("Icon found at: %s"), *FullIconPath);
                        }
                        else
                        {
                            UE_LOG(LogTemp, Warning, TEXT("Icon NOT found at: %s"), *FullIconPath);
                        }
                    }
                    else
                    {
                        UE_LOG(LogTemp, Error, TEXT("Failed to parse JSON from: %s"), *SettingsFilePath);
                    }
                }
            }
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("No directories found in: %s"), *CharacterFolderPath);
    }
}

