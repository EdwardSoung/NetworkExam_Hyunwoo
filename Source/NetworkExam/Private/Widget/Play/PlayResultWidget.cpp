// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Play/PlayResultWidget.h"
#include "GameSystem/State/PickupGameState.h"
#include "GameSystem/State/PickupPlayerState.h"
#include "GameSystem/Instance/GameManager.h"

#include "Components/TextBlock.h"
#include "Components/Button.h"

bool UPlayResultWidget::Initialize()
{
	SetResult();

	return Super::Initialize();
}

void UPlayResultWidget::NativeConstruct()
{
	if (ExitButton)
	{
		ExitButton->OnClicked.AddDynamic(this, &UPlayResultWidget::OnClickExit);
	}
}

void UPlayResultWidget::OnClickExit()
{
	UGameManager* Manager = Cast<UGameManager>(GetGameInstance());
	if (Manager)
	{
		Manager->DisconnectServer();
	}
}

void UPlayResultWidget::SetResult()
{
	AGameStateBase* GS = GetWorld()->GetGameState();
	if (GS)
	{
		int32 hostScore = 0;
		int32 clientScore = 0;
		for (APlayerState* BS : GS->PlayerArray)
		{
			APickupPlayerState* PS = Cast<APickupPlayerState>(BS);
			if (PS)
			{				
				if (PS->bIsHost)
				{
					hostScore = PS->GetMyScore();					
				}
				else
				{
					clientScore = PS->GetMyScore();					
				}
			}
		}

		IsHost = GetOwningPlayer()->HasAuthority();
		FSlateColor HostScoreColor = FSlateColor(FLinearColor::White);
		FSlateColor ClientScoreColor = FSlateColor(FLinearColor::White);

		if (hostScore != clientScore)
		{
			if (IsHost)
			{
				if (hostScore > clientScore)
					HostScoreColor = FSlateColor(FLinearColor::Green);
				else
					HostScoreColor = FSlateColor(FLinearColor::Red);
			}
			else
			{
				if (hostScore < clientScore)
					ClientScoreColor = FSlateColor(FLinearColor::Green);
				else
					ClientScoreColor = FSlateColor(FLinearColor::Red);
			}
		}	

		if (HostScoreText)
		{
			HostScoreText->SetText(FText::AsNumber(hostScore));
			HostScoreText->SetColorAndOpacity(HostScoreColor);
		}
		if (ClientScoreText)
		{
			ClientScoreText->SetText(FText::AsNumber(clientScore));
			ClientScoreText->SetColorAndOpacity(ClientScoreColor);
		}
		
		FText ResultTextValue;
		FSlateColor ResultColor = FSlateColor(FLinearColor::White);
		if (hostScore == clientScore)
		{
			ResultTextValue = FText::FromString(TEXT("DRAW"));
		}
		else
		{
			APlayerController* PC = GetOwningPlayer();

			if ((PC->HasAuthority() && hostScore > clientScore) || (!PC->HasAuthority() && hostScore < clientScore))
			{
				ResultTextValue = FText::FromString(TEXT("VICTORY"));

				//승리 텍스트 컬러 파랑
				ResultColor = FSlateColor(FLinearColor(0.0f, 0.35f, 1.0f));
			}
			else
			{
				ResultTextValue = FText::FromString(TEXT("LOSE"));
				ResultColor = FSlateColor(FLinearColor::Gray);
			}			
		}

		if (ResultText)
		{
			ResultText->SetText(ResultTextValue);
			ResultText->SetColorAndOpacity(ResultColor);
		}


		//점수

	}
}
