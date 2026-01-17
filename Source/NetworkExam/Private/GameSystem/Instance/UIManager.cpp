// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSystem/Instance/UIManager.h"
#include "GameSystem/Instance/GameManager.h"
#include <Kismet/GameplayStatics.h>

void UUIManager::InitUI()
{
	CreatedWidgets.Empty();
}

UUserWidget* UUIManager::ShowWidget(EUIType InUIType)
{
	UUserWidget* TargetUI = nullptr;
	if (CreatedWidgets.Contains(InUIType))
	{
		TargetUI = *CreatedWidgets.Find(InUIType);
	}
	else
	{
		auto GI = Cast<UGameManager>(GetGameInstance());
		if (GI)
		{
			auto UIData = GI->UIData.Get();
			if (UIData)
			{
				auto WidgetClass = *UIData->Data.Find(InUIType);
				if (WidgetClass)
				{
					UWorld* World = GetWorld();
					if (!World) return nullptr;

					APlayerController* PC = UGameplayStatics::GetPlayerController(World, 0);

					TargetUI = CreateWidget<UUserWidget>(PC, WidgetClass);
					if (TargetUI)
					{
						TargetUI->AddToViewport();
						CreatedWidgets.Add(InUIType, TargetUI);
					}
				}							
			}
		}
	}

	if (TargetUI)
	{
		if (OpenedUI != EUIType::None)
		{
			auto PrevUI = *CreatedWidgets.Find(OpenedUI);
			if (PrevUI)
			{
				PrevUI->SetVisibility(ESlateVisibility::Collapsed);
			}
		}

		TargetUI->SetVisibility(ESlateVisibility::Visible);
		OpenedUI = InUIType;

		return TargetUI;
	}

	return nullptr;
}
