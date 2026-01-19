// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSystem/Mode/PlayGameMode.h"
#include "GameSystem/State/PickupGameState.h"
#include "GameSystem/Instance/GameManager.h"
#include "GameSystem/Instance/UIManager.h"
#include "Widget/Play/PlayHUD_Widget.h"

void APlayGameMode::StartPlay()
{
	Super::StartPlay();
}

void APlayGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	int32 currentPlayer = GetNumPlayers();

	APickupGameState* State = GetGameState<APickupGameState>();
	if (State)
	{
		State->ChangeState(EGameState::Waiting);
	}

	if (currentPlayer == 2)
	{
		UGameManager* Manager = Cast<UGameManager>(GetGameInstance());
		if (Manager)
		{
			auto UIManager = Manager->GetSubsystem<UUIManager>();
			if (UIManager)
			{
				auto HUD = UIManager->GetCurrentWidget();
				if (HUD)
				{
					UPlayHUD_Widget* Widget = Cast<UPlayHUD_Widget>(HUD);
					if (Widget)
					{
						Widget->SetStartButton(true);
					}
				}
			}
		}
		//서버 UI에 시작버튼 활성화
		//시작 누르면 카운팅
		//카운팅 종료되면 플레이로 상태변경...
	}
}

void APlayGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);
	//서버 UI에 시작 버튼 비활성
	//시작중이면 취소
	if (GetNumPlayers() < 2)
	{
		UGameManager* Manager = Cast<UGameManager>(GetGameInstance());
		if (Manager)
		{
			auto UIManager = Manager->GetSubsystem<UUIManager>();
			if (UIManager)
			{
				auto HUD = UIManager->GetCurrentWidget();
				if (HUD)
				{
					UPlayHUD_Widget* Widget = Cast<UPlayHUD_Widget>(HUD);
					if (Widget)
					{
						Widget->SetStartButton(false);
					}
				}
			}
		}
	}
}
