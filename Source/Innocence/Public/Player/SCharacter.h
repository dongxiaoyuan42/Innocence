// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h" 
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "SCharacter.generated.h"

class USpringArmComponent; // 弹簧臂组件
class UCameraComponent; // 摄像机组件
class USAttributeComponent; // 属性组件
class USWeaponComponent; // 武器组件
class USActionComponent; // 行动组件

// 输入相关
class UInputMappingContext;
class UInputAction;
class UInputComponent;

UCLASS()
class INNOCENCE_API ASCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASCharacter();

protected:

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp; // 弹簧臂组件

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp; // 摄像机组件

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	USAttributeComponent* AttributeComp; // 属性组件

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	USWeaponComponent* WeaponComp; // 武器组件

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	USActionComponent* AbilityComp; // ASC


protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext; // 输入映射

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction; // 跳跃

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction; // 移动

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction; // 角色视角

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* PrimaryAttackAction; // 左键普通攻击

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* PrimaryDashAction; // 冲刺

	// 移动
	void Move(const FInputActionValue& Value);

	// 角色视角
	void Look(const FInputActionValue& Value);

	// 普通攻击
	void PrimaryAttack();

	// 冲刺
	void PrimaryDash();

protected:

	// 死亡判断
	UFUNCTION()
	void GetHealthChange(AActor* InstigatordActor, USAttributeComponent* OwningComp, float NewHealth, float Delta);
	void SpawnProjectile(TSubclassOf<AActor> ClassToSpawn);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// 注册事件绑定函数
	virtual void PostInitializeComponents() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
