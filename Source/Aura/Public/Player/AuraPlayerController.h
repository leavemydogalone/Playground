// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTagContainer.h"
#include "AuraPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class IEnemyInterface;
class IUnitInterface;
class UAuraInputConfig;
class UDamageTextComponent;
class UAuraAbilitySystemComponent;
class USplineComponent;
class MinionCharacterBase;

/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AAuraPlayerController();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void PlayerTick(float DeltaTime) override;

	//Client RPCs are great for things that only the owning player should see or hear, especially for cosmetic or UI-related effects.
	UFUNCTION(Client, Reliable)
	void ShowDamageNumber(float DamageAmount, ACharacter* TargetCharacter, bool bBlockedHit, bool bCriticalHit);


protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	UPROPERTY(ReplicatedUsing = OnRep_SelectedUnit)
	AActor* SelectedUnit;

	UFUNCTION()
	void OnRep_SelectedUnit(); // Called when SelectedUnit is updated

	UFUNCTION(Server, Reliable)
	void ServerSelectUnit();
	void ServerSelectUnit_Implementation();

private:
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputMappingContext> AuraContext;

	UPROPERTY(Editanywhere, Category="Input");
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(Editanywhere, Category = "Input");
	TObjectPtr<UInputAction> ShiftAction;

	void Move(const FInputActionValue& InputActionValue);

	void ShiftPressed(const FInputActionValue& InputActionValue) { bShiftKeyDown = true; };
	void ShiftReleased(const FInputActionValue& InputActionValue) { bShiftKeyDown = false; };
	bool bShiftKeyDown = false;

	void CursorTrace();
	IUnitInterface* LastActor;
	IUnitInterface* ThisActor;
	FHitResult CursorHit;

	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UAuraInputConfig> InputConfig;

	UPROPERTY()
	TObjectPtr<UAuraAbilitySystemComponent> AuraAbilitySystemComponent;

	UAuraAbilitySystemComponent* GetASC();

	FVector CachedDestination = FVector::ZeroVector;
	float FollowTime = 0.f;
	float ShortPressThreshold = 0.5f;
	bool bAutoRunning = false;
	bool bTargeting = false;

	UPROPERTY(EditDefaultsOnly)
	float AutoRunAcceptanceRadius = 50.f;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USplineComponent> Spline;

	void AutoRun();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDamageTextComponent> DamageTextComponentClass;


};
