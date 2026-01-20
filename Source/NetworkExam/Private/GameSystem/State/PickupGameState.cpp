// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSystem/State/PickupGameState.h"
#include "GameSystem/Instance/GameManager.h"
#include "GameSystem/Instance/UIManager.h"
#include "Widget/Play/PlayResultWidget.h"
#include "Widget/Play/PlayHUD_Widget.h"
#include "Net/UnrealNetwork.h"

APickupGameState::APickupGameState()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APickupGameState::BeginPlay()
{
	GameRemainingTime = GameDuration;
	PendingRemainingTime = PendingDuration;
	GameElapsedTime = 0.0f;
	PendingElapsedTime = 0.0f;
	TotalPoint = 0;
}

void APickupGameState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority())
	{
		if (GameState == EGameState::Playing)
		{
			GameElapsedTime += DeltaTime;

			GameRemainingTime -= DeltaTime;

			if (GameRemainingTime < 0.0f)
			{
				GameRemainingTime = 0.0f;
				ChangeState(EGameState::Finished);
			}
		}

		if (GameState == EGameState::OnReady)
		{
			PendingElapsedTime += DeltaTime;
			PendingRemainingTime -= DeltaTime;

			if (PendingRemainingTime < 0.0f)
			{
				PendingRemainingTime = 0.0f;
				ChangeState(EGameState::Playing);
			}
		}
	}
}

void APickupGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APickupGameState, GameElapsedTime);
	DOREPLIFETIME(APickupGameState, GameRemainingTime);
	DOREPLIFETIME(APickupGameState, GameState);
	DOREPLIFETIME(APickupGameState, PendingElapsedTime);
	DOREPLIFETIME(APickupGameState, PendingRemainingTime);
	DOREPLIFETIME(APickupGameState, TotalPoint);
}

void APickupGameState::ChangeState(EGameState InState)
{
	if (HasAuthority())
	{
		GameState = InState;

		OnRep_StateChanged();
	}
}

void APickupGameState::OnRep_StateChanged()
{
	UGameManager* Manager = Cast<UGameManager>(GetGameInstance());

	switch (GameState)
	{
	case EGameState::Lobby:
		if (Manager)
		{
			Manager->DisconnectServer();
		}
		break;
	case EGameState::Waiting:
		//게임 시작하기를 대기중

		break;

	case EGameState::OnReady:
		//Pending타이머 시작
		UE_LOG(LogTemp, Log, TEXT("게임 시작 눌림!! 3초후 시작"));
		if (Manager)
		{
			UUIManager* UIManager = Manager->GetSubsystem<UUIManager>();
			if (UIManager)
			{
				auto Widget = UIManager->GetCurrentWidget();
				auto PlayWidget = Cast<UPlayHUD_Widget>(Widget);
				if (PlayWidget)
				{
					PlayWidget->SetExitButton(false);
				}
			}
		}
		break;

	case EGameState::Playing:
		//오브젝트 스폰 시작
		UE_LOG(LogTemp, Log, TEXT("플레이 시작!!"));
		//위젯에서 종료버튼 꺼줌		

		break;
	case EGameState::Finished:
		//결과 화면
		if (Manager)
		{
			UUIManager* UIManager = Manager->GetSubsystem<UUIManager>();
			if (UIManager)
			{
				auto Widget = UIManager->ShowWidget(EUIType::ResultUI);
				if (Widget)
				{
					Widget->Initialize();
				}
			}
		}
		break;
	}
}

void APickupGameState::OnRep_TotalPointChanged()
{
	UGameManager* Manager = Cast<UGameManager>(GetGameInstance());
	if (Manager)
	{
		UUIManager* UIManager = Manager->GetSubsystem<UUIManager>();
		if (UIManager)
		{
			auto Widget = UIManager->GetCurrentWidget();
			auto PlayWidget = Cast<UPlayHUD_Widget>(Widget);
			if (PlayWidget)
			{
				PlayWidget->UpdateUITotalPoint(TotalPoint);
			}
		}
	}
}

void APickupGameState::AddToTotal(int32 InPoint)
{
	if (HasAuthority())
	{
		TotalPoint += InPoint;

		OnRep_TotalPointChanged();
	}
}
