// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "SHealingSphere.generated.h"



UCLASS()
class INNOCENCE_API ASHealingSphere : public AActor
{
	GENERATED_BODY()

public:

	ASHealingSphere();

	//添加球形区的半径
	void SetRadius(float Radius);

	//球形区的碰撞组件
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	USphereComponent* SphereComp;

	//粒子效果组件(控制)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UParticleSystemComponent* EffectComp;

	//进入球形区的触发事件
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


protected:

	virtual void BeginPlay() override;

public:

	virtual void Tick(float DeltaTime) override;

};
