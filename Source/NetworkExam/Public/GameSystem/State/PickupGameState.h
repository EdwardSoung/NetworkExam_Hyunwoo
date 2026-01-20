// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Data/Enums.h"
#include "PickupGameState.generated.h"

/**
 * 
 */
UCLASS()
class NETWORKEXAM_API APickupGameState : public AGameStateBase
{
	GENERATED_BODY()
public:
	APickupGameState();
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	inline float GetGameElapsedTime() const { return GameElapsedTime; }
	inline float GetGameRemainingTime() const { return GameRemainingTime; }
	inline float GetPendingRemainingTime() const { return PendingRemainingTime; }
	inline bool IsGameOver() const { return GameState == EGameState::Finished; }
	inline EGameState GetCurrent() { return GameState; }
	inline int32 GetTotalPoint() { return TotalPoint; }

	void ChangeState(EGameState InState);

	UFUNCTION()
	void OnRep_StateChanged();

	UFUNCTION()
	void OnRep_TotalPointChanged();

	void AddToTotal(int32 InPoint);

protected:
	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Game Data")
	float GameElapsedTime = 0.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game Data")
	float GameDuration = 60.0f;	// 게임 1판 시간. GameMode에 추가하는 것이 적합함(지금은 테스트용)

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Game Data")
	float GameRemainingTime = 0.0f;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Game Data")
	float PendingElapsedTime = 0.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game Data")
	float PendingDuration = 3.0f;	// 게임 시작 후 플레이 대기시간

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Game Data")
	float PendingRemainingTime = 0.0f;

	UPROPERTY(ReplicatedUsing = OnRep_StateChanged, BlueprintReadOnly, Category = "Game Data")
	EGameState GameState = EGameState::Lobby;

	UPROPERTY(ReplicatedUsing = OnRep_TotalPointChanged, BlueprintReadOnly, Category = "Game Data")
	int32 TotalPoint = 0;

};
