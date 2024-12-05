// Fill out your copyright notice in the Description page of Project Settings.

#include "TowerBase.h"


#include "TowerUpgradeWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"

ATowerBase::ATowerBase()
{
	PrimaryActorTick.bCanEverTick = true;
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	RootComponent = StaticMeshComponent;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	BoxComponent->SetupAttachment(StaticMeshComponent);
	
	BoxComponent->OnBeginCursorOver.AddDynamic(this, &ATowerBase::OnCursorOver);
	BoxComponent->OnEndCursorOver.AddDynamic(this, &ATowerBase::EndCursorOver);
	BoxComponent->OnClicked.AddDynamic(this, &ATowerBase::OnClick);

	DetectionRangeMesh = CreateDefaultSubobject<UStaticMeshComponent>("DetectionRangeMesh");
	DetectionRangeMesh->SetupAttachment(StaticMeshComponent);
	
	DetectionSphere = CreateDefaultSubobject<USphereComponent>("DetectionSphere");
	DetectionSphere->SetupAttachment(RootComponent);
	DetectionSphere->OnComponentBeginOverlap.AddDynamic(this, &ATowerBase::OnEnemyEnterRadius);
	DetectionSphere->OnComponentEndOverlap.AddDynamic(this, &ATowerBase::OnEnemyExitRadius);
	
}

#if WITH_EDITOR
void ATowerBase::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	FName PropertyName = (PropertyChangedEvent.Property != nullptr) ? PropertyChangedEvent.Property->GetFName() : NAME_None;

	if (PropertyName != GET_MEMBER_NAME_CHECKED(ATowerBase, DetectionRadius)) return;

	if (!DetectionSphere) return;

	DetectionSphere->SetSphereRadius(DetectionRadius);
	UpdateCylinderScale();
	
}
#endif

void ATowerBase::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = UGameplayStatics::GetPlayerController(this, 0);

	DetectionRangeMesh->SetVisibility(false);
}



void ATowerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	Timer += DeltaTime;

	float AttackInterval = AttackIntervalBase / TowerUpgrades[CurrentUpgradeIndex].AttackSpeed;

	if (Timer >= AttackInterval)
	{
		Attack();
		Timer = 0.0f;
	}
}


void ATowerBase::OnCursorOver(UPrimitiveComponent* Component) 
{
	if (!StaticMeshComponent || !HoverMaterial) return;

	StaticMeshComponent->SetMaterial(0, HoverMaterial);

	if (!PlayerController) return;

	DetectionRangeMesh->SetVisibility(true);
	
	PlayerController->CurrentMouseCursor = EMouseCursor::Hand;
}


void ATowerBase::EndCursorOver(UPrimitiveComponent* Component)
{
	if (!StaticMeshComponent || !TowerMaterial) return;

	StaticMeshComponent->SetMaterial(0, TowerMaterial);
	
	if (!PlayerController) return;
	
	DetectionRangeMesh->SetVisibility(false);
	PlayerController->CurrentMouseCursor = EMouseCursor::Default;
}

void ATowerBase::OnClick(UPrimitiveComponent* Component,  FKey InKey)
{
	if(!TowerUpgradeWidget) GetUpgradeWidgetReference();
	
	DetectionRangeMesh->SetVisibility(false);
	
	TowerUpgradeWidget->OpenUI(TowerUpgrades, this);
}

void ATowerBase::GetUpgradeWidgetReference()
{
	if (!PlayerController) return;

	TArray<UUserWidget*> FoundWidgets;
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(this, FoundWidgets, UTowerUpgradeWidget::StaticClass(), false);
	
	if (FoundWidgets.Num() <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("No widgets found for tower %s"), *GetName());
		return;
	}

	TowerUpgradeWidget = Cast<UTowerUpgradeWidget>(FoundWidgets[0]);
}

void ATowerBase::OnEnemyEnterRadius(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor || !OtherActor->IsA(AEnemyBase::StaticClass())) return;

	AEnemyBase* Enemy = Cast<AEnemyBase>(OtherActor);
	
	if (!Enemy) return;
	
	EnemiesInRange.Add(Enemy);
}

void ATowerBase::OnEnemyExitRadius(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!OtherActor) return;

	AEnemyBase* Enemy = Cast<AEnemyBase>(OtherActor);
	
	if (!Enemy) return;

	EnemiesInRange.Remove(Enemy);
}

void ATowerBase::Attack()
{
	if (CurrentUpgradeIndex <= 0 || EnemiesInRange.Num() <= 0) return;

	AEnemyBase* Enemy = EnemiesInRange[0];
	
	if (!Enemy) return;
	
	Enemy->DecreaseHealth(TowerUpgrades[CurrentUpgradeIndex].AttackDamage);
}

void ATowerBase::UpgradeTowerMesh(UStaticMesh* UpgradedMesh)
{
	StaticMeshComponent->SetStaticMesh(UpgradedMesh);
}

void ATowerBase::UpdateCylinderScale()
{
	if (!DetectionRangeMesh || !DetectionSphere) return;

	float ScaleFactor = DetectionSphere->GetScaledSphereRadius() / SphereRadiusDivider;
	DetectionRangeMesh->SetWorldScale3D(FVector(ScaleFactor, ScaleFactor, 1.0f));
}
