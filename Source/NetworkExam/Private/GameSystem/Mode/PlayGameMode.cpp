// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSystem/Mode/PlayGameMode.h"
#include "GameSystem/State/PickupGameState.h"

void APlayGameMode::PostLogin(APlayerController* NewPlayer)
{
	int32 currentPlayer = GetNumPlayers();

	APickupGameState* State = GetGameState<APickupGameState>();
	if (State)
	{
		State->ChangeState(EGameState::Waiting);
	}

	if (currentPlayer == 2)
	{
		//서버 UI에 시작버튼 활성화
		//시작 누르면 카운팅
		//카운팅 종료되면 플레이로 상태변경...
	}
}

void APlayGameMode::Logout(AController* Exiting)
{
	//서버 UI에 시작 버튼 비활성
	//시작중이면 취소
}
