// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Data/Enums.h"
#include "UIData.generated.h"

/**
 * 
 */
UCLASS()
class NETWORKEXAM_API UUIData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<EUIType, TSubclassOf<UUserWidget>> Data;

};
