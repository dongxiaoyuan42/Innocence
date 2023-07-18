// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Projectile/SHealingProjectile.h"
#include "Item/Projectile/SProjectileBase.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"  // 用于调用 ApplyRadialDamageWithFalloff 和 GetPlayerCharacter
#include "Player/SCharacter.h"            
#include "GameFramework/Actor.h"
#include "Item/Projectile/SHealingSphere.h"
#include "Components/CapsuleComponent.h"

ASHealingProjectile::ASHealingProjectile()
{
	MoveComp->ProjectileGravityScale = 1.0f;

}



void ASHealingProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != GetInstigator())
	{
		//生成一个球形场
		FVector ProjectileLocation = GetActorLocation();
		float FieldRadius = 100.f;
		AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(HealingClass, ProjectileLocation, FRotator::ZeroRotator);
		ASHealingSphere* HealingSphere = Cast<ASHealingSphere>(SpawnedActor);

		if (HealingSphere)
		{
			HealingSphere->SetRadius(FieldRadius);
		}

	}
}



void ASHealingProjectile::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor && OtherActor != GetInstigator())
	{
		//生成一个球形场
		FVector ProjectileLocation = GetActorLocation();
		float FieldRadius = 100.f;
		AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(HealingClass, ProjectileLocation, FRotator::ZeroRotator);
		ASHealingSphere* HealingSphere = Cast<ASHealingSphere>(SpawnedActor);

		if (HealingSphere)
		{
			HealingSphere->SetRadius(FieldRadius);
		}

	}

}

