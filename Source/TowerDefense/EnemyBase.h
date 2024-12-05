// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyHealthComponent.h"
#include "EnemyHealthWidget.h"
#include "EnemyPath.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Actor.h"
#include "EnemyBase.generated.h"

UCLASS()
class TOWERDEFENSE_API AEnemyBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AEnemyBase();

protected:
	virtual void BeginPlay() override;

	void MoveToPoint(float DeltaTime);

public:	
	virtual void Tick(float DeltaTime) override;
    void AssignInfo(AEnemyPath* EnemyPath);
	void DecreaseHealth(float Damage);

	float GetCurrentHealth() const { return HealthComponent->GetCurrentHealth(); }
	
protected:

	UPROPERTY(EditAnywhere)
	float Speed;

	UPROPERTY(EditAnywhere)
	float Tolerance;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	UWidgetComponent* HealthWidgetComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UEnemyHealthWidget> HealthWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	UEnemyHealthWidget* HealthWidget;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* EnemyMesh;

	UPROPERTY(VisibleAnywhere)
	UEnemyHealthComponent* HealthComponent;
	
private:
	int8 CurrentPathPointIndex;
	AEnemyPath *PathToFollow;

	FVector CurrentTargetPoint;

};
