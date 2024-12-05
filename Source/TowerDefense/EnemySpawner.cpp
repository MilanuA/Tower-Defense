// EnemySpawner.cpp

#include "EnemySpawner.h"
#include "EnemyPath.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"

AEnemySpawner::AEnemySpawner(): TimeBetweenWaves(0), CurrentWaveIndex(0), EnemiesSpawnedInWave(0), TimeSinceLastWave(0),
                                bIsSpawningWave(false)
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(LevelUICheckTimerHandle, this, &AEnemySpawner::GetLevelUIReference, 0.1f, true);
}

void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	TimeSinceLastWave += DeltaTime;

	if (!bIsSpawningWave && CurrentWaveIndex < Waves.Num() && TimeSinceLastWave >= TimeBetweenWaves)
	{
		TimeSinceLastWave = 0.0f;

		bIsSpawningWave = true;
		
		SpawnWaves();
	}
}

void AEnemySpawner::SpawnWaves()
{
	if (CurrentWaveIndex >= Waves.Num()) return;
	
	LevelUI->IncreaseWave();
	
	EnemiesSpawnedInWave = 0;
	
	const FWaveStruct& Wave = Waves[CurrentWaveIndex];
	
	GetWorld()->GetTimerManager().SetTimer(EnemySpawnTimerHandle, [this, Wave]() {
		SpawnEnemyWithInterval(Wave);
	}, Wave.SpawnInterval, true);

}

void AEnemySpawner::SpawnEnemyWithInterval(const FWaveStruct& Wave)
{
	if (EnemiesSpawnedInWave >= Wave.Amount || CurrentWaveIndex >= Waves.Num())
	{
		GetWorld()->GetTimerManager().ClearTimer(EnemySpawnTimerHandle);
		
		TimeSinceLastWave = 0.0f;
		EnemiesSpawnedInWave = 0;

		CurrentWaveIndex++;

		bIsSpawningWave = false;
		return;
	}
	
	SpawnEnemy(Wave);
}

void AEnemySpawner::SpawnEnemy(const FWaveStruct& Wave)
{
	if (!Wave.EnemyBP)
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid EnemyBP for wave %i"), CurrentWaveIndex);
		return;
	}
	
	UWorld* World = GetWorld();
	
	if (!World) return;;
	
	FActorSpawnParameters SpawnParams;
	AEnemyBase* SpawnedEnemy = World->SpawnActor<AEnemyBase>(Wave.EnemyBP, GetActorLocation(), FRotator::ZeroRotator, SpawnParams);

	if (!SpawnedEnemy) return;
	
	SpawnedEnemy->AssignInfo( EnemyPath.Get());
	
	EnemiesSpawnedInWave++;
}


void AEnemySpawner::GetLevelUIReference()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);

	if (!PlayerController) return;

	TArray<UUserWidget*> FoundWidgets;
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(this, FoundWidgets, ULevelUI::StaticClass(), false);

	if (FoundWidgets.Num() <= 0) return;

	LevelUI = Cast<ULevelUI>(FoundWidgets[0]);
		
	if (!LevelUI) return;
	
	GetWorld()->GetTimerManager().ClearTimer(LevelUICheckTimerHandle);
	
	CheckWaveCount();
}

/// <summary> Checks if the number of waves in the LevelUI matches the number of waves in the EnemySpawner </summary>
void AEnemySpawner::CheckWaveCount()
{
	if (Waves.Num() != LevelUI->MaxWaves)
	{
		FString Message = FString::Printf(TEXT("Number of waves in EnemySpawner %s does not match number of waves in LevelUI %s"), *GetName(), *LevelUI->GetName());
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, Message);
	}
}