// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Tickable.h"
#include "TimerManager.h"
#include "Components/TimelineComponent.h"
#include "SAction_Dash.generated.h"

/**
 * 
 */
UCLASS()
class INNOCENCE_API USAction_Dash : public UGameplayAbility, public FTickableGameObject
{
	GENERATED_BODY()

public:

	USAction_Dash();

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData);

public:
	// 抽象类FTickableGameObject必须重载的函数
	virtual TStatId GetStatId() const override
	{
		RETURN_QUICK_DECLARE_CYCLE_STAT(MyBPObject, STATGROUP_Tickables);
	}
	virtual bool IsTickable() const override { return !this->IsDefaultSubobject(); }
	virtual void Tick(float DeltaTime) override;

protected:

	// Timeline相关
	bool HasInit;
	FTimeline CurveTimeline;
	UPROPERTY(EditDefaultsOnly, Category = "Action")
	UCurveFloat* Curve;

	UPROPERTY(EditDefaultsOnly, Category = "Action")
	float DashLength; // 冲刺距离
	UPROPERTY()
	FVector StartPos;
	UPROPERTY()
	FVector NowPos;
	UPROPERTY()
	FVector EndPos;

	UPROPERTY()
	AActor* DashActor;

	UFUNCTION()
	void SetupTimeline();

	UFUNCTION()
	void TimelineProgressFunction(float Value);

	UFUNCTION()
	void TimelineCallbackFunction();
	
};
