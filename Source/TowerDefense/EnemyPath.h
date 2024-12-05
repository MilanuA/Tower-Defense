// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyPath.generated.h"

UCLASS()
class TOWERDEFENSE_API AEnemyPath : public AActor
{
	GENERATED_BODY()
	
public:	
	AEnemyPath();
	
	bool GetPointPosition(int8 CurrentPoint, FVector& OutVector);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Path", Meta = (MakeEditWidget = true))
	TArray<FVector> PathPoints;
};
