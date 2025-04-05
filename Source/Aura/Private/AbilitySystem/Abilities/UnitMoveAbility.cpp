// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/UnitMoveAbility.h"
#include "DrawDebugHelpers.h"

void UUnitMoveAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UUnitMoveAbility::MoveToLocation(const FVector& TargetLocation)
{
	DrawDebugSphere(GetWorld(), TargetLocation, 20.f, 12, FColor::Red, false, 5.f);

	//if (const AActor* TargetActor = GetAvatarActorFromActorInfo())
	//{
	//	FAIMoveRequest MoveRequest;
	//	MoveRequest.SetGoalLocation(TargetLocation);
	//	MoveRequest.SetAcceptanceRadius(5.f);
	//	const FNavPathSharedPtr NavPath = UAuraAbilitySystemLibrary::GetNavPath(TargetActor, MoveRequest);
	//	if (NavPath.IsValid())
	//	{
	//		UAuraAbilitySystemLibrary::MoveToLocation(TargetActor, MoveRequest);
	//	}
	//}
}