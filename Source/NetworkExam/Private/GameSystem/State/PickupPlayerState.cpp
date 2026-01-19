// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSystem/State/PickupPlayerState.h"
#include "Net/UnrealNetwork.h"

//점수를 Playing 상태에서만 추가되어야함

void APickupPlayerState::AddMyScore(int32 Point)
{
	if (HasAuthority())
	{
		MyScore += Point;
		OnRep_MyScore();	// 서버는 리플리케이션이 없으니 수동으로 호출
	}

}

void APickupPlayerState::SetMyName(const FString& NewName)
{
	if (HasAuthority())
	{
		if (NewName.IsEmpty())
		{
			MyName = TEXT("MyPlayer");
		}
		else
		{
			MyName = NewName;
		}
		OnRep_MyName();
	}
}

void APickupPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APickupPlayerState, MyScore);	// 모든 클라이언트에 리플리케이션
	DOREPLIFETIME(APickupPlayerState, MyName);
}

void APickupPlayerState::OnRep_MyScore()
{
	UE_LOG(LogTemp, Log, TEXT("[%d]Score : %d"), GetPlayerId(), MyScore);

}

void APickupPlayerState::OnRep_MyName()
{
}
