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
	UJourneySaveGame* JSaveGame = Cast<UJourneySaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0));
	if (nullptr == JSaveGame)
	{
		JSaveGame = GetMutableDefault<UJourneySaveGame>(); // Gets the mutable default object of a class.
	}

	SetPlayerName(JSaveGame->PlayerName);
	//SetCharacterLevel(JSaveGame->Level);
	GameHighScore = JSaveGame->HighScore;
	Exp = JSaveGame->Exp;

	SavePlayerData();
}

void AJourneyPlayerState::SavePlayerData()
{
	// SpawnActor도 결국엔 NewObject를 사용한다.
	UJourneySaveGame* NewPlayerData = NewObject<UJourneySaveGame>(); // 가비지 컬렉터 덕분에 Delete 안써도 됨.
	NewPlayerData->PlayerName = GetPlayerName();
	NewPlayerData->Level = CharacterLevel;
	NewPlayerData->Exp = Exp;
	NewPlayerData->HighScore = GameHighScore;

	if (false == UGameplayStatics::SaveGameToSlot(NewPlayerData, SaveSlotName, 0))
	{
		UE_LOG(LogClass, Warning, TEXT("SaveGame Error!"));
	}
}

void AJourneyPlayerState::AddExp()
{

	// 다른 코드는 생략.
	// 데이터가 변할 때마다 저장.
	SavePlayerData();
}

void AJourneyPlayerState::AddGameScore()
{
	// 최고 점수가 바뀌면 교체하기.
	GameScore++;
	if (GameScore >= GameHighScore)
	{
		GameHighScore = GameScore;
	}
	// 데이터가 변할 때마다 저장.
	SavePlayerData();
}
