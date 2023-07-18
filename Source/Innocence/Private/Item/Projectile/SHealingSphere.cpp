


#include "Item/Projectile/SHealingSphere.h"
#include "Player/SCharacter.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ASHealingSphere::ASHealingSphere()
{
	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetCollisionProfileName("OverlapAllDynamic");
	SphereComp->SetSphereRadius(100.f);

	//事件绑定
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ASHealingSphere::OnOverlapBegin);

	RootComponent = SphereComp;

	//粒子效果组件的实例化
	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	EffectComp->SetupAttachment(RootComponent);

	PrimaryActorTick.bCanEverTick = true;

}

void ASHealingSphere::SetRadius(float Radius)
{
	if (SphereComp)
	{
		SphereComp->SetSphereRadius(Radius);
	}
}

void ASHealingSphere::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherComp && OtherActor->IsA<ASCharacter>())
	{
		ASCharacter* MyCharacter = Cast<ASCharacter>(OtherActor);
		if (MyCharacter)
		{
			UE_LOG(LogTemp, Log, TEXT("In the Healing area!!!"));
			//这里写治疗函数




			//↑
		}
	}
}

// Called when the game starts or when spawned
void ASHealingSphere::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ASHealingSphere::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

