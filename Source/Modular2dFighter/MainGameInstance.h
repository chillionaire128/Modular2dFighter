// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MainGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class MODULAR2DFIGHTER_API UMainGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	// Override the Init function from UGameInstance
	virtual void Init() override;

private:
	void ScanCharactersDirectory();
};
