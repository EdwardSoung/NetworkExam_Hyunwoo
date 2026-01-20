// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSystem/Instance/UIManager.h"
#include "GameSystem/Instance/GameManager.h"
#include <Kismet/GameplayStatics.h>

void UUIManager::InitUI()
{
	//CreatedWidgets.Empty();
}

UUserWidget* UUIManager::ShowWidget(EUIType InUIType)
{
	UUserWidget* TargetUI = nullptr;
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

				if (CurrentWidget)
				{
					CurrentWidget->RemoveFromParent();
					CurrentWidget = nullptr;
				}

				CurrentWidget = CreateWidget<UUserWidget>(PC, WidgetClass);
				if (CurrentWidget)
				{
					CurrentWidget->AddToViewport();
					//CreatedWidgets.Add(InUIType, TargetUI);
					return CurrentWidget;
				}
			}
		}
	}

	//레벨 전환 시 삭제됨...

	return nullptr;
}

UUserWidget* UUIManager::GetCurrentWidget()
{
	return CurrentWidget;
}
