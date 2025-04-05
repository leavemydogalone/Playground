// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/AuraPlayerState.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Character/UnitCharacterBase.h"
#include "Net/UnrealNetwork.h"


AAuraPlayerState::AAuraPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");

	NetUpdateFrequency = 100.f;
}

void AAuraPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AAuraPlayerState, Level);
	DOREPLIFETIME(AAuraPlayerState, SelectedUnit);
}

UAbilitySystemComponent* AAuraPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AAuraPlayerState::SetSelectedUnit(AActor* NewUnit)
{
	if (HasAuthority())
	{
		if (AUnitCharacterBase* UnitCharacter = Cast<AUnitCharacterBase>(NewUnit))
		{
			SelectedUnit = UnitCharacter;
			UE_LOG(LogTemp, Warning, TEXT("Selected Unit: %s"), *GetNameSafe(SelectedUnit));
		}
		/*SelectedUnit = NewUnit;
		UE_LOG(LogTemp, Warning, TEXT("Selected Unit: %s"), *GetNameSafe(SelectedUnit));*/
	}
}

void AAuraPlayerState::OnRep_SelectedUnit()
{
	//write a debug message on screen of the new selected unit
	
		UE_LOG(LogTemp, Warning, TEXT("Client Selected Unit: %s"), *GetNameSafe(SelectedUnit));
	
}

void AAuraPlayerState::OnRep_Level(int32 OldLevel)
{
}