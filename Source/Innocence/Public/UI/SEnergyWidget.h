// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SEnergyWidget.generated.h"

class USAttributeComponent; // 属性组件
class UMaterialInstanceDynamic; // 动态材质接口

UCLASS()
class INNOCENCE_API USEnergyWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	// 构造函数
	USEnergyWidget(const FObjectInitializer& ObjectInitializer);

protected:

	UPROPERTY(BlueprintReadOnly, Category = "Player Energy")
	FText TEnergy; // 精力值

	UPROPERTY(BlueprintReadOnly, Category = "Player Energy")
	float Energy; // 精力值

	UPROPERTY(BlueprintReadOnly, Category = "Player Energy")
	float MaxEnergy; // 最大精力值

	UPROPERTY(BlueprintReadOnly, Category = "Player Energy")
	float EnergyRate; // 精力值百分比

	UPROPERTY(BlueprintReadWrite, Category = "Player Energy")
	UMaterialInstanceDynamic* EnergyMaterial; // 精力条材质

protected:
	
	virtual void NativeConstruct() override; // UI构造完成时绑定相关事件

	UFUNCTION(BlueprintCallable)
	void GetEnergyChange(AActor* InstigatordActor, USAttributeComponent* OwningComp, float NewEnergy, float Delta); // 精力改变时更新UI
	
	bool EnergyChangeCommon(float Energy); // 普通更新精力值函数
};

