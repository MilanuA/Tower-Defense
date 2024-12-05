// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyHealthWidget.h"
#include "Components/ActorComponent.h"
#include "EnemyHealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOWERDEFENSE_API UEnemyHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UEnemyHealthComponent();
	void DecreaseHealth(float Damage);
	void SetInfo(UEnemyHealthWidget* Widget);

	float GetCurrentHealth() const { return CurrentHealth; }
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Health")
	float MaxHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	UEnemyHealthWidget* HealthWidget;
	
private:
	float CurrentHealth;
	void DestroyEnemy() const;
		
};
