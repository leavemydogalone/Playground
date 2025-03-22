// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "ExecCalc_Damage.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UExecCalc_Damage : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
	//NOTE: Exec calcs cannot be used for infinite duration effects. They are only for instant or periodic effects. So if the enemy has an infinite effect for attribute values, you cannot capture them.
public:
	UExecCalc_Damage();

	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,  FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
