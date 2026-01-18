// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayHUD_Widget.generated.h"

class UButton;

/**
 * 
 */
UCLASS()
class NETWORKEXAM_API UPlayHUD_Widget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnClickStart();

public:
	void SetStartButton(bool bIsVisible);

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> StartButton = nullptr;
};
