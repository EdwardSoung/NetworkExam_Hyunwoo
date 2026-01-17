// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LobbyHUD_Widget.generated.h"

class UButton;
class UTextBlock;

/**
 * 
 */
UCLASS()
class NETWORKEXAM_API ULobbyHUD_Widget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> CreateServerButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> JoinServerButton;

};
