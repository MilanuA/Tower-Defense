// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyDestroyer.h"
#include "Components/BoxComponent.h"
#include "EnemyBase.h"  // Include your enemy base class
#include "LevelUI.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemyDestroyer::AEnemyDestroyer() : HealthDecreaser(10.f)
{
	PrimaryActorTick.bCanEverTick = false;
	
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(RootComponent);
	
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AEnemyDestroyer::OnTriggerEnter);
}

void AEnemyDestroyer::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemyDestroyer::OnTriggerEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{	
	if (!OtherActor || !OtherActor->IsA(AEnemyBase::StaticClass())) return;

	float currentHealth = Cast<AEnemyBase>(OtherActor)->GetCurrentHealth();
	
	OtherActor->Destroy();
	
	if (!EventBasedUI)
		GetUIReference();
	
	EventBasedUI->OnUpdateHealthBar(currentHealth / HealthDecreaser);
}

void AEnemyDestroyer::GetUIReference()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	
	if (!PlayerController) return;

	TArray<UUserWidget*> FoundWidgets;
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(this, FoundWidgets, ULevelUI::StaticClass(), false);
	
	if (FoundWidgets.Num() <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("No widgets found for destroyer %s"), *GetName());
		return;
	}

	EventBasedUI = Cast<ULevelUI>(FoundWidgets[0]);
}