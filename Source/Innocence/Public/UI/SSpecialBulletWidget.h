// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SSpecialBulletWidget.generated.h"

class USWeaponComponent;
class UMaterialInstanceDynamic; // 动态材质接口

/**
 * 
 */
UCLASS()
class INNOCENCE_API USSpecialBulletWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	USSpecialBulletWidget(const FObjectInitializer& ObjectInitializer); // 构造函数

protected:

	UPROPERTY(BlueprintReadOnly, Category = "SpecialBullet")
	int32 SectorNum; // 扇形数量

	UPROPERTY(BlueprintReadOnly, Category = "SpecialBullet")
	float SectorSize; // 扇形大小

	UPROPERTY(BlueprintReadOnly, Category = "SpecialBullet")
	float CurrentArea; // 当前区域角度

	UPROPERTY(BlueprintReadOnly, Category = "SpecialBullet")
	float OffsetAngle; // 偏移角度

	UPROPERTY(BlueprintReadWrite, Category = "SpecialBullet")
	UMaterialInstanceDynamic* BulletSelectMaterial; // 扇形选择材质

protected:

	// UI构造完成时绑定相关事件
	virtual void NativeConstruct() override;

	// 切换武器子弹时更新UI
	UFUNCTION(BlueprintCallable)
	void SwitchWeaponBullet(int32 NewBullet);
};
