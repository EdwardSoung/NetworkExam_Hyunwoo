// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Play/PlayHUD_Widget.h"
#include "Components/Button.h"
#include "GameSystem/State/PickupGameState.h"

void UPlayHUD_Widget::NativeConstruct()
{
	Super::NativeConstruct();

	if (StartButton)
	{
		StartButton->OnClicked.AddDynamic(this, &UPlayHUD_Widget::OnClickStart);
	}
}

void UPlayHUD_Widget::OnClickStart()
{
	UWorld* World = GetWorld();
	if (World)
	{
		APickupGameState* State = World->GetGameState<APickupGameState>();
		if (State)
		{
			State->ChangeState(EGameState::OnReady);
		}
	}
}

void UPlayHUD_Widget::SetStartButton(bool bIsVisible)
{
	if (StartButton)
	{
		StartButton->SetVisibility(bIsVisible ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
	}
}
