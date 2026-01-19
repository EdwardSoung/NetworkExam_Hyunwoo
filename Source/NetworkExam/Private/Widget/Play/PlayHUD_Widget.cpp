// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Play/PlayHUD_Widget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"

#include "GameSystem/State/PickupGameState.h"
#include "GameSystem/Instance/GameManager.h"
#include <Kismet/GameplayStatics.h>

void UPlayHUD_Widget::NativeConstruct()
{
	Super::NativeConstruct();

	if (StartButton)
	{
		StartButton->OnClicked.AddDynamic(this, &UPlayHUD_Widget::OnClickStart);
		ExitButton->OnClicked.AddDynamic(this, &UPlayHUD_Widget::OnClickExit);

		SetStartButton(false);
	}

	if (ServerPointBar)
		ServerPointBar->SetPercent(0.0f);
	if (ServerPointText)
		ServerPointText->SetText(FText::FromString(TEXT("0")));
	if (ClientPointBar)
		ClientPointBar->SetPercent(0.0f);
	if (ClientPointText)
		ClientPointText->SetText(FText::FromString(TEXT("0")));
}

void UPlayHUD_Widget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (!CachedGameState.IsValid())
	{
		CachedGameState = Cast<APickupGameState>(UGameplayStatics::GetGameState(this));
	}

	UpdateRemainTimer();
	UpdateRemainTimerText();
	UpdateReadyTimer();
	UpdateReadyTimerText();
}

void UPlayHUD_Widget::OnClickStart()
{
	if (!CachedGameState.IsValid())
	{
		CachedGameState = Cast<APickupGameState>(UGameplayStatics::GetGameState(this));
	}

	if (CachedGameState.IsValid())
	{
		CachedGameState->ChangeState(EGameState::OnReady);
		SetStartButton(false);
	}
}

void UPlayHUD_Widget::OnClickExit()
{
	UGameManager* Manager = Cast<UGameManager>(GetGameInstance());
	if (Manager)
	{
		Manager->DisconnectServer();
	}
}

void UPlayHUD_Widget::UpdateReadyTimerText()
{
	if (CachedGameState.IsValid())
	{
		if (CachedGameState->GetCurrent() == EGameState::OnReady && ReadyTimerText)
		{
			float RemainTime = CachedGameState->GetPendingRemainingTime();
			if (RemainTime > 0.3f)
			{
				int32 Time = FMath::FloorToInt(RemainTime);

				ReadyTimerText->SetText(FText::FromString(FString::Printf(TEXT("%01d"), Time + 1)));
			}
			else
			{
				ReadyTimerText->SetText(FText::FromString(TEXT("START!")));
			}			
		}
	}
}

void UPlayHUD_Widget::UpdateReadyTimer()
{
	if (CachedGameState.IsValid())
	{
		if (ReadyTimerText)
		{
			ReadyTimerText->SetVisibility(CachedGameState->GetCurrent() == EGameState::OnReady ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
		}
	}
}

void UPlayHUD_Widget::UpdateRemainTimerText()
{
	if (CachedGameState.IsValid())
	{
		if (CachedGameState->GetCurrent() == EGameState::Playing && RemainTimerText)
		{
			int32 Total = FMath::FloorToInt(CachedGameState->GetGameRemainingTime());
			int32 Minutes = Total / 60;
			int32 Seconds = Total % 60;
			RemainTimerText->SetText(FText::FromString(FString::Printf(TEXT("%02d:%02d"), Minutes, Seconds)));
		}
	}
}

void UPlayHUD_Widget::UpdateRemainTimer()
{
	if (CachedGameState.IsValid())
	{
		if (ReadyTimerText)
		{
			ReadyTimerText->SetVisibility(CachedGameState->GetCurrent() == EGameState::Playing ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
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

void UPlayHUD_Widget::UpdateScore(int32 InPoint, bool bIsHost)
{
	if (bIsHost)
	{
		if (ServerPointText)
		{
			ServerPointText->SetText(FText::AsNumber(InPoint));
		}
	}
	else
	{
		if (ClientPointText)
		{
			ClientPointText->SetText(FText::AsNumber(InPoint));
		}
	}
}
