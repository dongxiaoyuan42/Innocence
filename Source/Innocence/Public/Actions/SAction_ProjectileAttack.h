// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "SAction_ProjectileAttack.generated.h"

/**
 * 
 */
UCLASS()
class INNOCENCE_API USAction_ProjectileAttack : public UGameplayAbility
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> ProjectileBaseClass; // 发射物

	UPROPERTY(EditAnywhere, Category = "Attack")
	FName HandSocketName; // 发射抛射物插槽名称

	// 实施攻击
	UFUNCTION()
	void AttackDelay_Elapsed(ACharacter* InstigatorCharacter);

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData);
	
};
