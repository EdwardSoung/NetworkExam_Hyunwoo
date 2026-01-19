// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PickupPlayerController.h"
#include "GameSystem/State/PickupGameState.h"
#include "GameSystem/Instance/GameManager.h"
#include "GameSystem/Instance/UIManager.h"

void APickupPlayerController::BeginPlay()
{
	if (HasAuthority())
	{
		auto State = GetWorld()->GetGameState<APickupGameState>();
		if (State)
		{
			State->ChangeState(EGameState::Waiting);
		}
	}
	
	if (IsLocalController())
	{
		UGameManager* Manager = Cast<UGameManager>(GetGameInstance());
		if (Manager)
		{
			auto UIManager = Manager->GetSubsystem<UUIManager>();
			if (UIManager)
			{
				auto HUD = UIManager->ShowWidget(EUIType::GameHUD);
				FInputModeGameAndUI InputMode;
				SetInputMode(InputMode);
				bShowMouseCursor = true;
			}
		}
	}
	
}
