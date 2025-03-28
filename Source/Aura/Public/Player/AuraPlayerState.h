// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "AuraPlayerState.generated.h"

class UAbilitySystemComponent;
class AUnitCharacterBase;
class UAttributeSet;

/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	AAuraPlayerState();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifeTimeProps) const override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const { return AttributeSet; };

	FORCEINLINE int32 GetPlayerLevel() const { return Level; }

	UPROPERTY(ReplicatedUsing = OnRep_ControlledUnits)
	TArray<AUnitCharacterBase*> ControlledUnits;

	UPROPERTY(ReplicatedUsing = OnRep_SelectedUnits)
	TArray<AUnitCharacterBase*> SelectedUnits;

	UFUNCTION(Server, Reliable)
	void ServerRegisterUnit(AUnitCharacterBase* Unit);

	UFUNCTION(Server, Reliable)
	void ServerSelectUnit(AUnitCharacterBase* Unit);

	UFUNCTION()
	void OnRep_ControlledUnits();

	UFUNCTION()
	void OnRep_SelectedUnits();

protected:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;


private:

	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_Level)
	int32 Level = 1;

	UFUNCTION()
	void OnRep_Level(int32 OldLevel);
};
