// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SEnergyWidget.h"
#include "Component/SAttributeComponent.h"
#include "Materials/MaterialInstanceDynamic.h"

// 构造函数
USEnergyWidget::USEnergyWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	MaxEnergy = 100.0f;
	EnergyChangeCommon(100.0f);
}

// UI构造完成时绑定相关事件
void USEnergyWidget::NativeConstruct()
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
			MaxEnergy = AttributeComp->GetEnergyMax();
			EnergyChangeCommon(AttributeComp->GetEnergy());
			// 绑定玩家属性组件 OnHealthChanged 到 GetHealthChange
			AttributeComp->OnEnergyChanged.AddDynamic(this, &USEnergyWidget::GetEnergyChange); //
		}
		// 开始时UI初始化
		EnergyChangeCommon(Energy); //
		EnergyMaterial->SetScalarParameterValue("PrograssAlpha", EnergyRate);
	}
}

// 精力改变时更新UI
void USEnergyWidget::GetEnergyChange(AActor* InstigatordActor, USAttributeComponent* OwningComp, float NewEnergy, float Delta)
{
	EnergyChangeCommon(NewEnergy);
	// 血条材质更新（已经设置好了，只需要PrograssAlpha与HealthRate）
	EnergyMaterial->SetScalarParameterValue("PrograssAlpha", EnergyRate);
}

// 普通更新精力值函数
bool USEnergyWidget::EnergyChangeCommon(float NewEnergy)
{
	Energy = NewEnergy;
	TEnergy = FText::FromString(FString::Printf(TEXT("%.2f"), Energy));
	EnergyRate = Energy / MaxEnergy;

	return true;
}
