// Fill out your copyright notice in the Description page of Project Settings.


#include "JourneyPlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "JourneySaveGame.h"

AJourneyPlayerState::AJourneyPlayerState()
{
	GameHighScore = 0;
	Exp = 0;
	CharacterLevel = 0;
	GameScore = 0;
	SaveSlotName = TEXT("Player1");
}

int32 AJourneyPlayerState::GetGameHighScore() const
{
	return GameHighScore;
}

void AJourneyPlayerState::InitPlayerData()
{
	//UJourneySaveGame* JSaveGame = Cast<UJourneySaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0));
	//if (nullptr == JSaveGame)
	//{
	//	JSaveGame = GetMutableDefault<UJourneySaveGame>(); // Gets the mutable default object of a class.
	//}

	//SetPlayerName(JSaveGame->PlayerName);
	////SetCharacterLevel(JSaveGame->Level);
	//GameHighScore = JSaveGame->HighScore;
	//Exp = JSaveGame->Exp;

	//SavePlayerData();
}

void AJourneyPlayerState::SavePlayerData()
{
	// SpawnActor�� �ᱹ�� NewObject�� ����Ѵ�.
	//UJourneySaveGame* NewPlayerData = NewObject<UJourneySaveGame>(); // ������ �÷��� ���п� Delete �Ƚᵵ ��.
	//NewPlayerData->PlayerName = GetPlayerName();
	//NewPlayerData->Level = CharacterLevel;
	//NewPlayerData->Exp = Exp;
	//NewPlayerData->HighScore = GameHighScore;

	//if (false == UGameplayStatics::SaveGameToSlot(NewPlayerData, SaveSlotName, 0))
	//{
	//	UE_LOG(LogClass, Warning, TEXT("SaveGame Error!"));
	//}
}

void AJourneyPlayerState::AddExp()
{

	// �ٸ� �ڵ�� ����.
	// �����Ͱ� ���� ������ ����.
	SavePlayerData();
}

void AJourneyPlayerState::AddGameScore()
{
	// �ְ� ������ �ٲ�� ��ü�ϱ�.
	GameScore++;
	if (GameScore >= GameHighScore)
	{
		GameHighScore = GameScore;
	}
	// �����Ͱ� ���� ������ ����.
	SavePlayerData();
}
