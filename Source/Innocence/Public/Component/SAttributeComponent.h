// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SAttributeComponent.generated.h"

// 属性改变事件
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnAttributeChanged, AActor*, InstigatordActor, USAttributeComponent*, OwningComp, float, NewValue, float, Delta);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
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

public:	

	// 是否活着
	UFUNCTION(BlueprintCallable, Category = "Attributes")
		bool IsAlive() const;

	// 是否满血
	UFUNCTION(BlueprintCallable, Category = "Attributes")
		bool IsFullHealth() const;

	// 生命值改变
	UFUNCTION(BlueprintCallable, Category = "Attributes")
		bool ApplyHealthChange(AActor* InstigatordActor, float Delta);

	// 生命值获取
	UFUNCTION(BlueprintCallable, Category = "Attributes")
		float GetHealth();

	// 最大生命值获取
	UFUNCTION(BlueprintCallable, Category = "Attributes")
		float GetHealthMax();

	// 生命值改变事件
	UPROPERTY(BlueprintAssignable)
		FOnAttributeChanged OnHealthChanged;

		
};
