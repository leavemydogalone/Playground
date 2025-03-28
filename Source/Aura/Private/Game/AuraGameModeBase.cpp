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
		for (int i = 0; i < 2; i++)
		{
			FVector PawnLocation = PlayerPawn->GetActorLocation();
			FVector SpawnLocation = GetSpawnLocationForPlayer(Player, i);
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = Player;
			SpawnParams.Instigator = nullptr;

			AUnitCharacterBase* NewUnit = World->SpawnActor<AUnitCharacterBase>(DefaultUnitPawn, SpawnLocation, FRotator::ZeroRotator, SpawnParams);
			if (NewUnit)
			{
				//NewUnit->InitializeUnit(PlayerState, StatsArray[i]);
				NewUnit->SetOwner(Player);
			}

			//create random vector spawn location within 200 units of pawn
			SpawnLocation += FMath::VRand() * 200.f;
		}
	}
}

FVector AAuraGameModeBase::GetSpawnLocationForPlayer(APlayerController* Player, int Index)
{
	FVector BaseSpawnLocation = FVector(0.0f, Index * 200.0f, 100.0f); // Adjust for formation
	return BaseSpawnLocation;
}