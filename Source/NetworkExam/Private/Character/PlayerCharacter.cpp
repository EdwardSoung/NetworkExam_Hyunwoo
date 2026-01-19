// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlayerCharacter.h"
#include "GameFramework/PlayerState.h"
#include "GameSystem/State/PickupPlayerState.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void APlayerCharacter::AddScore(int InPoint)
{
	if (IsLocallyControlled())
	{
		Server_AddScore(InPoint);
	}
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlayerCharacter::Server_AddScore_Implementation(int32 InPoint)
{
	APickupPlayerState* PS = GetPlayerState<APickupPlayerState>();
	if (PS)
	{
		PS->AddMyScore(InPoint);
	}
}

void APlayerCharacter::Server_SetName_Implementation(const FString& InName)
{
	APickupPlayerState* PS = GetPlayerState<APickupPlayerState>();
	if (PS)
	{
		PS->SetMyName(InName);
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

