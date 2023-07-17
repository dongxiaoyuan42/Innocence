// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SHealthWidget.h"
#include "Component/SAttributeComponent.h"
#include "Materials/MaterialInstanceDynamic.h"

// 构造函数
USHealthWidget::USHealthWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	MaxHealth = 100.0f;
	HealthChangeCommon(100.0f);
}

// UI构造完成时绑定相关事件
void USHealthWidget::NativeConstruct()
{
	// 获取玩家
	APawn* PlayerPawn = GetOwningPlayerPawn();
	if (PlayerPawn)
	{
		// 获取玩家属性组件
		USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(PlayerPawn->GetComponentByClass(USAttributeComponent::StaticClass()));
		if (ensureAlways(AttributeComp))
		{
			// 根据属性组件更新UI参数
			MaxHealth = AttributeComp->GetHealthMax();
			HealthChangeCommon(AttributeComp->GetHealth());
			// 绑定玩家属性组件 OnHealthChanged 到 GetHealthChange
			AttributeComp->OnHealthChanged.AddDynamic(this, &USHealthWidget::GetHealthChange); //
		}
		// 开始时UI初始化
		HealthChangeCommon(Health); //
		HealthMaterial->SetScalarParameterValue("PrograssAlpha", HealthRate);
	}
}

// 生命值改变时更新UI
void USHealthWidget::GetHealthChange(AActor* InstigatordActor, USAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	HealthChangeCommon(NewHealth);
	// 血条材质更新（已经设置好了，只需要PrograssAlpha与HealthRate）
	HealthMaterial->SetScalarParameterValue("PrograssAlpha", HealthRate);
}

// 普通更新生命值函数
bool USHealthWidget::HealthChangeCommon(float NewHealth)
{
	Health = NewHealth;
	THealth = FText::FromString(FString::Printf(TEXT("%.2f"), Health));
	HealthRate = Health / MaxHealth;

	return true;
}
