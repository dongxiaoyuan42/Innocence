// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Projectile/GravitationalProjectile.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Components/SphereComponent.h"
AGravitationalProjectile::AGravitationalProjectile()
{
	// 添加径向力组件
	ForceComp = CreateDefaultSubobject<URadialForceComponent>("ForceComp");
	ForceComp->SetupAttachment(RootComponent);
	ForceComp->ForceStrength = -8000000.0f;
	ForceComp->Radius = 500.0f;
}

void AGravitationalProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	/*if (OtherComp->IsSimulatingPhysics("None"))
	{
		OtherActor->Destroy();
	}*/
}//引力子弹碰到非static类型的物体不做任何修改，也不调用摧毁函数。
