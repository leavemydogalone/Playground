// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AuraAbilitySystemComponent.h"

void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComponent::EffectApplied);
}

void UAuraAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);
	for (FGameplayTag Tag : TagContainer)
	{
		const FString Msg = FString::Printf(TEXT("GE Tag: %s"), *Tag.ToString());
		//TODO: broadcast the tag to the widget controller
		GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Blue, Msg);
	}
}
