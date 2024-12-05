// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBase.h"

AEnemyBase::AEnemyBase():  Speed(20), Tolerance(2), PathToFollow(nullptr)
{
	PrimaryActorTick.bCanEverTick = true;
	
	HealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthWidgetComponent"));

	EnemyMesh = CreateDefaultSubobject<UStaticMeshComponent>("EnemyMesh");
	RootComponent = EnemyMesh;

	HealthWidgetComponent->SetupAttachment(RootComponent);
	HealthWidgetComponent->SetWidgetClass(HealthWidgetClass);

	HealthComponent = CreateDefaultSubobject<UEnemyHealthComponent>("HealthComponent");
	
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();

	HealthWidget = Cast<UEnemyHealthWidget>(HealthWidgetComponent->GetWidget());
	HealthComponent->SetInfo(HealthWidget);
}

void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	MoveToPoint(DeltaTime);
}


void AEnemyBase::AssignInfo(AEnemyPath* EnemyPath)
{
	PathToFollow = EnemyPath;

	if (!PathToFollow) return;
	
	if(PathToFollow->GetPointPosition(CurrentPathPointIndex, CurrentTargetPoint))
	{
		CurrentPathPointIndex++;
	}
}

void AEnemyBase::DecreaseHealth(float Damage)
{
	HealthComponent->DecreaseHealth(Damage);
}

///<summary>Moves the enemy towards the next point in the path</summary>
void AEnemyBase::MoveToPoint(float DeltaTime)
{
	if (!PathToFollow) 	return;
	
	const FVector WorldTargetPoint = PathToFollow->GetActorTransform().TransformPosition(CurrentTargetPoint); 
	FVector Direction = WorldTargetPoint - GetActorLocation();
	
	float DistanceToTarget = Direction.Size();

	if (DistanceToTarget <= Tolerance)
	{
		if(PathToFollow->GetPointPosition(CurrentPathPointIndex, CurrentTargetPoint))
		{
			CurrentPathPointIndex++;
		}
		
		return;
	}

	Direction.Normalize();
	AddActorWorldOffset(Direction * Speed * DeltaTime, true);
}
