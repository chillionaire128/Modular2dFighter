// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine/Texture2D.h"
#include "CharacterPortraitTextureLoader.generated.h"


/**
 * 
 */
UCLASS()
class MODULAR2DFIGHTER_API UCharacterPortraitTextureLoader : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = "Custom Texture Loader")
	static UTexture2D* LoadTextureFromPath(const FString& Path);
};
