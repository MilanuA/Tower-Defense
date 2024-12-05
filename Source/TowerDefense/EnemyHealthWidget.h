// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "EnemyHealthWidget.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UEnemyHealthWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* HealthBar;


public:
	void UpdateHealthBar(float CurrentHealth, float MaxHealth);
};
