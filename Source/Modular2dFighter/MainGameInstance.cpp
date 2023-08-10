// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameInstance.h"

void UMainGameInstance::Init()
{
    Super::Init();
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Executing ScanCharactersDirectory..."));
    ScanCharactersDirectory();
}

void UMainGameInstance::ScanCharactersDirectory()
{
    IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

    // Assuming characters are stored in a "Characters" directory under the Content directory
    FString CharacterFolderPath = FPaths::ProjectContentDir() + TEXT("Characters/");

    // Print debug message indicating function execution
    UE_LOG(LogTemp, Warning, TEXT("Executing ScanCharactersDirectory..."));

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
            // Print debug message for each folder being checked
            UE_LOG(LogTemp, Warning, TEXT("Checking folder: %s"), *CharacterDir);

            FString SettingsFilePath = CharacterDir + TEXT("/settings/settings.txt");

            // Check if the settings file exists
            UE_LOG(LogTemp, Warning, TEXT("Checking for file: %s"), *SettingsFilePath);
            if (FPaths::FileExists(SettingsFilePath))
            {
                // Print the path to the settings file for the character
                UE_LOG(LogTemp, Warning, TEXT("Found character settings: %s"), *SettingsFilePath);
            }
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("No directories found in: %s"), *CharacterFolderPath);
    }
}

