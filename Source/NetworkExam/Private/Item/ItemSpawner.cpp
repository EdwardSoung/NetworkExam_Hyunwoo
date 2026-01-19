// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/ItemSpawner.h"
#include "Item/PickupItem.h"
#include "Components/BoxComponent.h"
#include "GameSystem/State/PickupGameState.h"

#include <Kismet/GameplayStatics.h>

// Sets default values
AItemSpawner::AItemSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnArea = CreateDefaultSubobject<UBoxComponent>(TEXT("Spawn Area"));
	SetRootComponent(SpawnArea);
}

// Called when the game starts or when spawned
void AItemSpawner::BeginPlay()
{
	Super::BeginPlay();
}

void AItemSpawner::Spawn()
{
    if (!SpawnItem) return;

    FVector Origin = SpawnArea->GetComponentLocation();
    FVector BoxExtent = SpawnArea->GetScaledBoxExtent();

    float RandomX = FMath::RandRange(Origin.X - BoxExtent.X, Origin.X + BoxExtent.X);
    float RandomY = FMath::RandRange(Origin.Y - BoxExtent.Y, Origin.Y + BoxExtent.Y);

    FVector TraceStart = FVector(RandomX, RandomY, Origin.Z + BoxExtent.Z);
    FVector TraceEnd = FVector(RandomX, RandomY, Origin.Z - BoxExtent.Z - 1000.f);


    FHitResult HitResult;
    FCollisionQueryParams Params;
    //자기자신은 무시
    Params.AddIgnoredActor(this);

    bool bHit = GetWorld()->LineTraceSingleByChannel(
        HitResult,
        TraceStart,
        TraceEnd,
        ECC_GameTraceChannel1,
        Params
    );

    if (bHit)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,
            FString::Printf(TEXT("Hit Actor: %s"), *HitResult.GetActor()->GetName()));
        //회전값 설정
        FRotator SpawnRotation = FRotator::ZeroRotator;

        AActor* NewActor = GetWorld()->SpawnActor<AActor>(SpawnItem, HitResult.Location, SpawnRotation);

        if (NewActor)
        {
            NewActor->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
        }
    }
}

// Called every frame
void AItemSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (!CachedGameState.IsValid())
    {
        CachedGameState = Cast<APickupGameState>(UGameplayStatics::GetGameState(this));
    }

    if (CachedGameState.IsValid())
    {
        FTimerManager& TimerManager = GetWorld()->GetTimerManager();
        if (CachedGameState->GetCurrent() == EGameState::Playing && !TimerManager.IsTimerActive(SpawnTimerHandle))
        {
            TimerManager.SetTimer(
                SpawnTimerHandle,
                this, &AItemSpawner::Spawn,
                SpawnInterval, true
            );
        }

        if (CachedGameState->GetCurrent() == EGameState::Finished && TimerManager.IsTimerActive(SpawnTimerHandle))
        {
            TimerManager.ClearTimer(SpawnTimerHandle);
        }
    }
    
}

