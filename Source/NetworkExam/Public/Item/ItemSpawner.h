// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemSpawner.generated.h"

UCLASS()
class NETWORKEXAM_API AItemSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Spawn();
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item|Spanwer")
	TObjectPtr<class UBoxComponent> SpawnArea = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Spanwer")
	TSubclassOf<class APickupItem> SpawnItem;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Spanwer")
	float SpawnInterval = 3.0f;

private:
	FTimerHandle SpawnTimerHandle;
	TWeakObjectPtr<class APickupGameState> CachedGameState = nullptr;
};
