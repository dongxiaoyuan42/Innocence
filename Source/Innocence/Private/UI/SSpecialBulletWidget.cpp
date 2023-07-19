// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SSpecialBulletWidget.h"
#include "Component/SWeaponComponent.h"
#include "Materials/MaterialInstanceDynamic.h"

// 构造函数
USSpecialBulletWidget::USSpecialBulletWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	SectorNum = 24;
	SectorSize = 360 / SectorNum;
	OffsetAngle = 7.5;
	CurrentArea = 12 * SectorSize - OffsetAngle;
}

// UI构造完成时绑定相关事件
void USSpecialBulletWidget::NativeConstruct()
{
	// 获取玩家
	APawn* PlayerPawn = GetOwningPlayerPawn();
	if (PlayerPawn)
	{
		// 获取玩家属性组件
		USWeaponComponent* WeaponComp = Cast<USWeaponComponent>(PlayerPawn->GetComponentByClass(USWeaponComponent::StaticClass()));
		if (ensureAlways(WeaponComp))
		{
			// 绑定函数 SwitchWeaponBullet 到 OnBulletChangedLeft事件
			WeaponComp->OnBulletChangedLeft.AddDynamic(this, &USSpecialBulletWidget::SwitchWeaponBullet);
			// 绑定函数 SwitchWeaponBullet 到 OnBulletChangedRight事件
			WeaponComp->OnBulletChangedRight.AddDynamic(this, &USSpecialBulletWidget::SwitchWeaponBullet);
		}
		// 开始时UI初始化
		BulletSelectMaterial->SetScalarParameterValue("OuterRotate", CurrentArea);
		BulletSelectMaterial->SetScalarParameterValue("MiddleRotate", CurrentArea);
		BulletSelectMaterial->SetScalarParameterValue("InnerRotate", CurrentArea);
	}
	
}

// 切换武器子弹时更新UI
void USSpecialBulletWidget::SwitchWeaponBullet(int32 NewBullet)
{
	CurrentArea = (12 - NewBullet) * SectorSize - OffsetAngle;
	BulletSelectMaterial->SetScalarParameterValue("OuterRotate", CurrentArea);
	BulletSelectMaterial->SetScalarParameterValue("MiddleRotate", CurrentArea);
	BulletSelectMaterial->SetScalarParameterValue("InnerRotate", CurrentArea);

}
