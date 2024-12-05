// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyHealthComponent.h"

UEnemyHealthComponent::UEnemyHealthComponent(): MaxHealth(100), CurrentHealth(0)
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UEnemyHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
}

void UEnemyHealthComponent::DecreaseHealth(float Damage)
{
	CurrentHealth -= Damage;
	HealthWidget->UpdateHealthBar(CurrentHealth, MaxHealth);

	if (CurrentHealth > 0) return;

	DestroyEnemy();
}

void UEnemyHealthComponent::SetInfo(UEnemyHealthWidget* Widget)
{
	HealthWidget = Widget;
}

void UEnemyHealthComponent::DestroyEnemy() const
{
	AActor* EnemyActor = GetOwner();
	EnemyActor->Destroy();
}

