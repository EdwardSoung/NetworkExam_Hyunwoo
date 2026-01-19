// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

UENUM()
enum class EGameState : uint8
{
	Lobby,
	Waiting,
	OnReady,
	Playing,
	Finished,
};

UENUM()
enum class EUIType : uint8
{
	None,
	LobbyHUD,
	GameHUD,
	ResultUI,
};