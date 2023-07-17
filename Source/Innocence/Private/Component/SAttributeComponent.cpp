// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/SAttributeComponent.h"

// Sets default values for this component's properties
USAttributeComponent::USAttributeComponent()
{
	Health = 100;
	HealthMax = 100;
}

bool USAttributeComponent::ApplyHealthChange(AActor* InstigatordActor, float Delta)
{
	float OldHealth = Health;
	float NewHealth = FMath::Clamp(Health + Delta, 0.0f, HealthMax);
	float ActualDelta = NewHealth - OldHealth;

	Health = NewHealth;
	if (ActualDelta != 0)
	{
		OnHealthChanged.Broadcast(InstigatordActor, this, NewHealth, Delta);
	}

	UE_LOG(LogTemp, Log, TEXT("Health Has Change, NewHealth = %f, Delta = %f."), NewHealth, ActualDelta);

	return ActualDelta > 0;

}

bool USAttributeComponent::IsAlive() const
{
	return Health > 0.0f;
}

bool USAttributeComponent::IsFullHealth() const
{
	return Health == HealthMax;
}

float USAttributeComponent::GetHealth()
{
	return Health;
}

float USAttributeComponent::GetHealthMax()
{
	return HealthMax;
}

USAttributeComponent* USAttributeComponent::GetAttributes(AActor* FromActor)
{
	if (FromActor)
	{
		return Cast<USAttributeComponent>(FromActor->GetComponentByClass(USAttributeComponent::StaticClass()));
	}

	return nullptr;
}
