// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/PickupItem.h"
#include "Components/SphereComponent.h"

// Sets default values
APickupItem::APickupItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	SetRootComponent(Collision);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Item Mesh"));
	Mesh->SetupAttachment(Collision);

	OnActorBeginOverlap.AddDynamic(this, &APickupItem::OnBeginOverlap);
}

// Called when the game starts or when spawned
void APickupItem::BeginPlay()
{
	Super::BeginPlay();
	
}

void APickupItem::OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	//점수 처리...

	Destroy();
}

// Called every frame
void APickupItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

