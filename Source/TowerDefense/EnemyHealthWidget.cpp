// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyHealthWidget.h"

void UEnemyHealthWidget::UpdateHealthBar(float CurrentHealth, float MaxHealth)
{
	HealthBar->SetPercent(CurrentHealth / MaxHealth);
}
