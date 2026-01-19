// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayHUD_Widget.generated.h"

class UButton;
class UProgressBar;
class UTextBlock;

/**
 * 
 */
UCLASS()
class NETWORKEXAM_API UPlayHUD_Widget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UFUNCTION()
	void OnClickStart();
	UFUNCTION()
	void OnClickExit();

	void UpdateReadyTimerText();
	void UpdateReadyTimer();

	void UpdateRemainTimerText();
	void UpdateRemainTimer();
public:
	void SetStartButton(bool bIsVisible);

	void UpdateScore(int32 InPoint, bool bIsHost);

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> StartButton = nullptr;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ExitButton = nullptr;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ReadyTimerText = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> RemainTimerText = nullptr;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> ServerPointBar = nullptr;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ServerPointText= nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> ClientPointBar = nullptr;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ClientPointText = nullptr;


private:
	TWeakObjectPtr<class APickupGameState> CachedGameState = nullptr;
};
