// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyPath.h"

AEnemyPath::AEnemyPath()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AEnemyPath::BeginPlay()
{
	Super::BeginPlay();
}

bool AEnemyPath::GetPointPosition(int8 CurrentPoint, FVector& OutVector)
{
    if (PathPoints.IsValidIndex(CurrentPoint))
    {
        OutVector = PathPoints[CurrentPoint];
        return true;
    }

    OutVector = GetActorLocation();
    return false;
}