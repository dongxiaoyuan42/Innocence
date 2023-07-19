// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SSpecialBulletWidget.generated.h"

class USWeaponComponent;
class UMaterialInstanceDynamic; // ��̬���ʽӿ�

/**
 * 
 */
UCLASS()
class INNOCENCE_API USSpecialBulletWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	USSpecialBulletWidget(const FObjectInitializer& ObjectInitializer); // ���캯��

protected:

	UPROPERTY(BlueprintReadOnly, Category = "SpecialBullet")
	int32 SectorNum; // ��������

	UPROPERTY(BlueprintReadOnly, Category = "SpecialBullet")
	float SectorSize; // ���δ�С

	UPROPERTY(BlueprintReadOnly, Category = "SpecialBullet")
	float CurrentArea; // ��ǰ����Ƕ�

	UPROPERTY(BlueprintReadOnly, Category = "SpecialBullet")
	float OffsetAngle; // ƫ�ƽǶ�

	UPROPERTY(BlueprintReadWrite, Category = "SpecialBullet")
	UMaterialInstanceDynamic* BulletSelectMaterial; // ����ѡ�����

protected:

	// UI�������ʱ������¼�
	virtual void NativeConstruct() override;

	// �л������ӵ�ʱ����UI
	UFUNCTION(BlueprintCallable)
	void SwitchWeaponBullet(int32 NewBullet);
};
