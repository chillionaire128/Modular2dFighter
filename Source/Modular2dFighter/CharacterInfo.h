#pragma once

#include "CoreMinimal.h"
#include "CharacterInfo.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FCharacterInfo
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadOnly)
    FString Name;

    UPROPERTY(BlueprintReadOnly)
    int32 Health;

    UPROPERTY(BlueprintReadOnly)
    FString SelectIconPath;
};