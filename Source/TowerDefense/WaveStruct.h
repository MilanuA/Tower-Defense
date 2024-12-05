#pragma once
#include "CoreMinimal.h"
#include "EnemyBase.h"
#include "WaveStruct.generated.h"

USTRUCT(BlueprintType)
struct FWaveStruct
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave")
	int32 SpawnInterval;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave")
	int32 Amount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave")
	TSubclassOf<AEnemyBase> EnemyBP;
};
