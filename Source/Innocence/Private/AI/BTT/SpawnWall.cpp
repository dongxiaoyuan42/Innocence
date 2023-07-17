// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/BTT/SpawnWall.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "GameFramework/Actor.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Engine/World.h"
#include "Component/SAttributeComponent.h"

USpawnWall::USpawnWall()
{
	MaxBulleSpread = 8.0f;
}

EBTNodeResult::Type USpawnWall::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// 获取AIController
	AAIController* MyController = OwnerComp.GetAIOwner();

	if (ensure(MyController))
	{
		// 获取AICharacter
		ACharacter* AICharacter = Cast<ACharacter>(MyController->GetPawn());
		if (AICharacter == nullptr)
		{
			return EBTNodeResult::Failed;
		}
		// 获取墙结束的位置
		FVector WallEndLocation = AICharacter->GetMesh()->GetSocketLocation("EndOfWall");
		// 获取攻击对象
		AActor* TargetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("TargetActor"));
		if (TargetActor == nullptr)
		{
			return EBTNodeResult::Failed;
		}
		ACharacter* PlayerCharacter = Cast<ACharacter>(TargetActor);

		FVector PlayerLocation = TargetActor->GetActorLocation();

		// 攻击对象应该活着
		//if (!USAttributeComponent::IsAlive(TargetActor))
		//{
		//	return EBTNodeResult::Failed;
		//}

		// 设置墙攻击朝向，指向目标现在所处位置
		FVector Direction = WallEndLocation - PlayerLocation;
		FRotator WallRotator = Direction.Rotation();
		FVector WallStartLocation = PlayerLocation - WallRotator.Vector() * 1000.f;
		// 添加一些扰动
		//WallRotator.Pitch += FMath::RandRange(0.0f, MaxBulleSpread);
		//WallRotator.Yaw += FMath::RandRange(-MaxBulleSpread, MaxBulleSpread);

		//UE_LOG(LogTemp, Log, TEXT("---------------"));
		//UE_LOG(LogTemp, Log, TEXT("Location: %s"), *WallEndLocation.ToString());
		//UE_LOG(LogTemp, Log, TEXT("Rotator: %s"), *WallRotator.ToString());

		// 设置生成抛射物的碰撞信息与抛射物所有者信息
		FActorSpawnParameters Params;
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		Params.Instigator = AICharacter;

		// 生成墙
		AActor* NewWall = GetWorld()->SpawnActor<AActor>(WallClass, WallStartLocation, WallRotator, Params);
		// 返回生成结果
		return NewWall ? EBTNodeResult::Succeeded : EBTNodeResult::Failed;
	}

	return EBTNodeResult::Failed;;
}

