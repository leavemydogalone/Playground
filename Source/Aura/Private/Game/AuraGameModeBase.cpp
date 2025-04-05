// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/AuraGameModeBase.h"
#include "Character/UnitCharacterBase.h"

void AAuraGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if (HasAuthority() && NewPlayer)
	{		
			SpawnUnitsForPlayer(NewPlayer);
	}
}

void AAuraGameModeBase::SpawnUnitsForPlayer(APlayerController* Player)
{
	if (!HasAuthority() || !Player) return;

	UWorld* World = GetWorld();

	check(DefaultUnitPawn);

	if (APawn* PlayerPawn = Player->GetPawn())
	{
		FVector PawnLocation = PlayerPawn->GetActorLocation();
		for (int i = 0; i < 2; i++)
		{
			FVector SpawnLocation = GetSpawnLocationForPlayer(PawnLocation, i);
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = Player;
			SpawnParams.Instigator = nullptr;

			AUnitCharacterBase* NewUnit = World->SpawnActor<AUnitCharacterBase>(DefaultUnitPawn, SpawnLocation, FRotator::ZeroRotator, SpawnParams);
			if (NewUnit)
			{
				//NewUnit->InitializeUnit(PlayerState, StatsArray[i]);
				NewUnit->SetOwner(Player);
				NewUnit->SetAutonomousProxy(true);
			}
		}
	}
}

FVector AAuraGameModeBase::GetSpawnLocationForPlayer(FVector PawnLocation, int Index)
{

	FVector RandomLocation = FVector(Index * 200, 0.f, 0.f);
	FVector BaseSpawnLocation = PawnLocation + RandomLocation;// Adjust for formation
	return BaseSpawnLocation;
}