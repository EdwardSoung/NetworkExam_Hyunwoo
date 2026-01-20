// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSystem/Instance/LobbyManager.h"
#include "GameSystem/Instance/UIManager.h"

bool ULobbyManager::ShouldCreateSubsystem(UObject* Outer) const
{
	if (!Super::ShouldCreateSubsystem(Outer))
	{
		return false;
	}

	UWorld* World = Cast<UWorld>(Outer);
	if (!World) return false;

	return World->GetMapName().Contains(TEXT("Lobby"));
}

void ULobbyManager::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
	
	UGameInstance* GI = InWorld.GetGameInstance();
	if (GI)
	{
		UUIManager* UIManager = GI->GetSubsystem<UUIManager>();
		if (UIManager)
		{
			UIManager->ShowWidget(EUIType::LobbyHUD);

			if (InWorld.GetFirstPlayerController())
			{
				InWorld.GetFirstPlayerController()->bShowMouseCursor = true;
			}
		}
	}
}
