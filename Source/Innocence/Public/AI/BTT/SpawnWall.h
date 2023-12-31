// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "SpawnWall.generated.h"

/**
 * 
 */
UCLASS()
class INNOCENCE_API USpawnWall : public UBTTaskNode
{
	GENERATED_BODY()

private:

	// 在这个行为树节点中传入一个子弹类
	UPROPERTY(EditAnywhere, Category = "AI")
		TSubclassOf<AActor> WallClass;

	UPROPERTY(EditAnywhere, Category = "Attack")
		float MaxBulleSpread;

	// 重载执行函数
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

public:

	USpawnWall();
};
