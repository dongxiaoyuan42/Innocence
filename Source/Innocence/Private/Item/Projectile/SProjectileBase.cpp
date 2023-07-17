// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Projectile/SProjectileBase.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Component/SAttributeComponent.h"

// Sets default values
ASProjectileBase::ASProjectileBase()
{

	//设置球形组件为根组件
	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetCollisionProfileName("Projectile");
	RootComponent = SphereComp;

	//粒子效果组件的实例化
	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	EffectComp->SetupAttachment(RootComponent);

	//粒子运动组件
	MoveComp = CreateDefaultSubobject<UProjectileMovementComponent>("MoveComp");
	MoveComp->bRotationFollowsVelocity = true;
	MoveComp->bInitialVelocityInLocalSpace = true;
	MoveComp->ProjectileGravityScale = 0.0f;
	MoveComp->InitialSpeed = 4000;

	//默认伤害10点
	ProjectileDamage = -10.0f;

	//默认子弹存在最多十秒会自我销毁
	DestoryPrjDelay = 10.0f;

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	//忽略发射者
	SphereComp->IgnoreActorWhenMoving(GetInstigator(), true);
	//设置自我销毁计时器
	GetWorldTimerManager().SetTimer(FTimerHandle_DestoryPrjDelay, this, &ASProjectileBase::DestoryPrj, DestoryPrjDelay);
}

// Called every frame
void ASProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASProjectileBase::DestoryPrj()
{
	GetWorldTimerManager().ClearTimer(FTimerHandle_DestoryPrjDelay);
	Destroy();
}

void ASProjectileBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	//注册组件碰撞事件处理函数
	SphereComp->OnComponentHit.AddDynamic(this, &ASProjectileBase::OnActorHit);
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ASProjectileBase::OnActorOverlap);
}

void ASProjectileBase::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Explode();
}

void ASProjectileBase::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != GetInstigator())
	{

		Explode();
		USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(OtherActor->GetComponentByClass(USAttributeComponent::StaticClass()));
		if (AttributeComp)
		{
			AttributeComp->ApplyHealthChange(GetInstigator(), ProjectileDamage);
			Destroy();
		}
	}
}

void ASProjectileBase :: Explode_Implementation()
{
	if (ensure(!IsPendingKill())) {
		UGameplayStatics::SpawnEmitterAtLocation(this, ImpactVFX, GetActorLocation(), GetActorRotation());
		DestoryPrj();
	}
}


