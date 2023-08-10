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

    // Array to hold found directories (character folders)
    TArray<FString> CharacterDirectories;

    // Find subdirectories (individual character folders)
    PlatformFile.FindFiles(CharacterDirectories, *CharacterFolderPath, nullptr);

    for (FString CharacterDir : CharacterDirectories)
    {
        FString SettingsFilePath = CharacterDir + TEXT("/Settings/settings.json");

        // Check if the settings file exists
        if (PlatformFile.FileExists(*SettingsFilePath))
        {
            // Print the path to the settings file for the character (or log it)
            UE_LOG(LogTemp, Warning, TEXT("Found character settings: %s"), *SettingsFilePath);
        }
    }
}