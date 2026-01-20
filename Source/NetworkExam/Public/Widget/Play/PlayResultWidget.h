// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayResultWidget.generated.h"

class UTextBlock;
class UButton;
/**
 * 
 */
UCLASS()
class NETWORKEXAM_API UPlayResultWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ResultText = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> HostScoreText = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ClientScoreText = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ExitButton = nullptr;

	bool IsHost = false;

protected:
	UFUNCTION()
	void OnClickExit();

public:

	virtual bool Initialize() override;

	virtual void NativeConstruct() override;

	void SetResult();

};
