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
	DOREPLIFETIME(AAuraPlayerState, ControlledUnits);
	DOREPLIFETIME(AAuraPlayerState, SelectedUnits);
}

UAbilitySystemComponent* AAuraPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AAuraPlayerState::OnRep_Level(int32 OldLevel)
{
}

void AAuraPlayerState::ServerRegisterUnit_Implementation(AUnitCharacterBase* Unit)
{
	if (Unit && !ControlledUnits.Contains(Unit))
	{
		ControlledUnits.Add(Unit);
		Unit->SetOwner(this);
	}
}

void AAuraPlayerState::ServerSelectUnit_Implementation(AUnitCharacterBase* Unit)
{
	if (Unit && ControlledUnits.Contains(Unit))
	{
		SelectedUnits.AddUnique(Unit);
	}
}


void AAuraPlayerState::OnRep_ControlledUnits()
{
}

void AAuraPlayerState::OnRep_SelectedUnits()
{
}
