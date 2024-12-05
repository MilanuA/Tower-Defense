// EnemySpawner.h

#pragma once

#include "CoreMinimal.h"
#include "LevelUI.h"
#include "GameFramework/Actor.h"
#include "WaveStruct.h"
#include "EnemySpawner.generated.h"

UCLASS()
class TOWERDEFENSE_API AEnemySpawner : public AActor
{
	GENERATED_BODY()

public:
	AEnemySpawner();

protected:
	virtual void BeginPlay() override;


	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Wave")
	TSoftObjectPtr<AEnemyPath> EnemyPath;
	
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Wave")
	TArray<FWaveStruct> Waves;
	
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Wave Control")
	float TimeBetweenWaves;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Wave Control")
	int32 CurrentWaveIndex;
	
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Wave Control")
	int32 EnemiesSpawnedInWave;
	
private:
	float TimeSinceLastWave;

	ULevelUI* LevelUI;
	
	void SpawnWaves();
	
	void SpawnEnemyWithInterval(const FWaveStruct& Wave);
	
	void SpawnEnemy(const FWaveStruct& Wave);
	void GetLevelUIReference();
	void CheckWaveCount();
	
	FTimerHandle EnemySpawnTimerHandle;
	FTimerHandle LevelUICheckTimerHandle;

	
	bool bIsSpawningWave; 
};
