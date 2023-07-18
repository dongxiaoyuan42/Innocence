// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SAttributeComponent.generated.h"

// 属性改变事件
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnAttributeChanged, AActor*, InstigatordActor, USAttributeComponent*, OwningComp, float, NewValue, float, Delta);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class INNOCENCE_API USAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USAttributeComponent();

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	static USAttributeComponent* GetAttributes(AActor* FromActor);

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
	float Health; // 生命值

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
	float HealthMax; // 最大生命值

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
	float Energy; // 精力值

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
	float EnergyMax; // 最大精力值

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
	float EnergyRecoverySpeed; // 精力回复速度

public:

	void BeginPlay();

	FTimerHandle MemberTimerHandle;

	/*生命值*/
	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool IsAlive() const; // 是否活着

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool IsFullHealth() const; // 是否满血

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	float GetHealth(); // 生命值获取

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	float GetHealthMax(); // 最大生命值获取

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool ApplyHealthChange(AActor* InstigatordActor, float Delta); // 生命值改变

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChanged OnHealthChanged; // 生命值改变事件

	/*精力值*/
	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool IsEmptyEnergy() const; // 精力是否为空

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool IsFullEnergy() const; // 精力是否已满

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	float GetEnergy(); // 精力值获取

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	float GetEnergyMax(); // 最大精力值获取

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool ApplyEnergyChange(float Delta); // 精力值改变

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	void EnergyRecovery(); // 精力值自动回复

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChanged OnEnergyChanged; // 精力值改变事件
};
