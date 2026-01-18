// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Data/Enums.h"
#include "Blueprint/UserWidget.h"
#include "UIManager.generated.h"

/**
 * 
 */
UCLASS()
class NETWORKEXAM_API UUIManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	//전체 초기화
	void InitUI();

	UUserWidget* ShowWidget(EUIType InUIType);


protected:
	//생성된 UI 데이터
	TMap<EUIType, UUserWidget*> CreatedWidgets;

};
