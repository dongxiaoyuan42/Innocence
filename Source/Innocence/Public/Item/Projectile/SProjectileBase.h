// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SProjectileBase.generated.h"


class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystemComponent;
UCLASS()
class INNOCENCE_API ASProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASProjectileBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	float ProjectileDamage;

	//粒子效果
	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	UParticleSystem* ImpactVFX;

	//球形组件
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USphereComponent* SphereComp;

	//移动组件
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UProjectileMovementComponent* MoveComp;

	//粒子效果组件(控制)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UParticleSystemComponent* EffectComp;

	//自我销毁计时器
	FTimerHandle FTimerHandle_DestoryPrjDelay;
	float DestoryPrjDelay;

	//自我销毁函数
	virtual void DestoryPrj();

	//注册事件回调函数
	virtual void PostInitializeComponents() override;

	//碰撞事件处理函数
	UFUNCTION()
	virtual void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	virtual void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//作用函数
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Explode();

public:
	//蓄力子弹函数
	//UFUNCTION()
	//void EnhancedProjectile(float ChargeTime);

};
