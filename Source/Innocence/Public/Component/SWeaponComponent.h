// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SWeaponComponent.generated.h"

// 注册子弹切换改变事件
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBulletChanged, int32, NewBullet);

class UStaticMeshComponent; // 静态网格体

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INNOCENCE_API USWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USWeaponComponent();

	// 返回Actor上的USWeaponComponent
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	static USWeaponComponent* GetWeaponComp(AActor* FromActor);

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	TSubclassOf<AActor> Fire(); // 开火

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void AddBullet(TSubclassOf<AActor> ProjectileClass); // 装弹

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	bool CanFire();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void BulletTypeRight(); // 向右旋转

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void BulletTypeLeft(); // 向左旋转

	TSubclassOf<AActor> GetDefaultBullet();

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	UStaticMeshComponent* WeaponMesh; // 枪械网格体

	UPROPERTY(BlueprintReadOnly, Category = "Weapon")
	TSubclassOf<AActor> DefaultBullet; // 默认子弹

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	int32 BulletNumMax; // 子弹上限

	UPROPERTY(BlueprintReadOnly, Category = "Weapon")
	TArray<TSubclassOf<AActor>> BulletInGun; // 枪械中现存子弹

	int32 NowBulletType;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TArray<TSubclassOf<AActor>> BulletType;

	UFUNCTION(BlueprintCallable)
	void AddAll(); // 装满

	TSubclassOf<AActor> BulletPop();

	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable)
	FOnBulletChanged OnBulletChangedRight; // 子弹种类改变事件

	UPROPERTY(BlueprintAssignable)
	FOnBulletChanged OnBulletChangedLeft; // 子弹种类改变事件

		
};
