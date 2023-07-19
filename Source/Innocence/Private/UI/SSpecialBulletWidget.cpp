// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SSpecialBulletWidget.h"
#include "Component/SWeaponComponent.h"
#include "Materials/MaterialInstanceDynamic.h"

// ���캯��
USSpecialBulletWidget::USSpecialBulletWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	SectorNum = 24;
	SectorSize = 360 / SectorNum;
	OffsetAngle = 7.5;
	CurrentArea = 12 * SectorSize - OffsetAngle;
}

// UI�������ʱ������¼�
void USSpecialBulletWidget::NativeConstruct()
{
	// ��ȡ���
	APawn* PlayerPawn = GetOwningPlayerPawn();
	if (PlayerPawn)
	{
		// ��ȡ����������
		USWeaponComponent* WeaponComp = Cast<USWeaponComponent>(PlayerPawn->GetComponentByClass(USWeaponComponent::StaticClass()));
		if (ensureAlways(WeaponComp))
		{
			// �󶨺��� SwitchWeaponBullet �� OnBulletChangedLeft�¼�
			WeaponComp->OnBulletChangedLeft.AddDynamic(this, &USSpecialBulletWidget::SwitchWeaponBullet);
			// �󶨺��� SwitchWeaponBullet �� OnBulletChangedRight�¼�
			WeaponComp->OnBulletChangedRight.AddDynamic(this, &USSpecialBulletWidget::SwitchWeaponBullet);
		}
		// ��ʼʱUI��ʼ��
		BulletSelectMaterial->SetScalarParameterValue("OuterRotate", CurrentArea);
		BulletSelectMaterial->SetScalarParameterValue("MiddleRotate", CurrentArea);
		BulletSelectMaterial->SetScalarParameterValue("InnerRotate", CurrentArea);
	}
	
}

// �л������ӵ�ʱ����UI
void USSpecialBulletWidget::SwitchWeaponBullet(int32 NewBullet)
{
	CurrentArea = (12 - NewBullet) * SectorSize - OffsetAngle;
	BulletSelectMaterial->SetScalarParameterValue("OuterRotate", CurrentArea);
	BulletSelectMaterial->SetScalarParameterValue("MiddleRotate", CurrentArea);
	BulletSelectMaterial->SetScalarParameterValue("InnerRotate", CurrentArea);

}
