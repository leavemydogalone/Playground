// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AuraGameModeBase.generated.h"

class UCharacterClassInfo;
class AAuraPlayerController;
class AUnitCharacterBase;
/**
 * 
 */
UCLASS()
class AURA_API AAuraGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "Character Class Defaults")
	TObjectPtr<UCharacterClassInfo> CharacterClassInfo;

	virtual void PostLogin(APlayerController* NewPlayer) override;

	void SpawnUnitsForPlayer(APlayerController* Player);

	FVector GetSpawnLocationForPlayer(FVector PawnLocation, int Index);

protected:
	//create a default unit pawn variable that can be assigned in blueprint, and will be used in the spawn unit function
	UPROPERTY(EditDefaultsOnly, Category = "Character Class Defaults")
	TSubclassOf<AUnitCharacterBase> DefaultUnitPawn;
};
