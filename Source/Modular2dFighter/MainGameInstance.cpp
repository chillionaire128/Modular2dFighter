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
                UE_LOG(LogTemp, Warning, TEXT("Found character settings: %s"), *SettingsFilePath);

                // Now, let's read and parse the JSON file
                FString JsonRaw;
                if (FFileHelper::LoadFileToString(JsonRaw, *SettingsFilePath))
                {
                    TSharedPtr<FJsonObject> JsonObject;
                    TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonRaw);

                    if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
                    {
                        FCharacterInfo CharInfo;

                        CharInfo.Name = JsonObject->GetStringField("name");
                        CharInfo.Health = JsonObject->GetIntegerField("health");
                        CharInfo.SelectIconPath = CharacterDir + TEXT("/ArtAssets/") + JsonObject->GetStringField("selectIcon");

                        LoadedCharacters.Add(CharInfo);

                        UE_LOG(LogTemp, Warning, TEXT("Character Name: %s, Health: %d, Select Icon: %s"), *CharInfo.Name, CharInfo.Health, *CharInfo.SelectIconPath);
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

