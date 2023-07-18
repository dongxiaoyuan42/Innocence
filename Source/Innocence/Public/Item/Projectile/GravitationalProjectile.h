// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/Projectile/SProjectileBase.h"
#include "GravitationalProjectile.generated.h"

class URadialForceComponent;

UCLASS()
class INNOCENCE_API AGravitationalProjectile : public ASProjectileBase
{
	GENERATED_BODY()

public:
	AGravitationalProjectile();
	
protected:

	//径向力组件
	UPROPERTY(VisibleAnywhere)
	URadialForceComponent* ForceComp;

	//组件碰撞事件处理函数
	virtual void  OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
