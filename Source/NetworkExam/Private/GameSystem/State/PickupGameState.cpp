// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSystem/State/PickupGameState.h"
#include "GameSystem/Instance/GameManager.h"
#include "GameSystem/Instance/UIManager.h"
#include "Net/UnrealNetwork.h"

APickupGameState::APickupGameState()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APickupGameState::BeginPlay()
{
	GameRemainingTime = GameDuration;
	GameElapsedTime = 0.0f;
	PendingElapsedTime = 0.0f;
}

void APickupGameState::Tick(float DeltaTime)
{
	if (HasAuthority() && GameState == EGameState::Playing)
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
}

void APickupGameState::ChangeState(EGameState InState)
{
	GameState = InState;
	
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

		break;

	case EGameState::Playing:
		//오브젝트 스폰 시작
		UE_LOG(LogTemp, Log, TEXT("플레이 시작!!"));
		break;
	}
}
