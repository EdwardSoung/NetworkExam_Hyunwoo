// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Lobby/LobbyHUD_Widget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "GameSystem/Instance/GameManager.h"

void ULobbyHUD_Widget::NativeConstruct()
{
	Super::NativeConstruct();

	if (CreateServerButton)
	{
		CreateServerButton->OnClicked.AddDynamic(this, &ULobbyHUD_Widget::OnCreateServer);
	}	
	if (JoinServerButton)
	{
		JoinServerButton->OnClicked.AddDynamic(this, &ULobbyHUD_Widget::OnJoinServer);
	}
}

void ULobbyHUD_Widget::OnCreateServer()
{
	UGameManager* GI = Cast<UGameManager>(GetGameInstance());
	if (GI)
	{
		GI->CreateServer();
	}
}

void ULobbyHUD_Widget::OnJoinServer()
{
	UGameManager* GI = Cast<UGameManager>(GetGameInstance());
	if (GI)
	{
		GI->JoinServer(FString(TEXT("127.0.0.1")));
	}
}
