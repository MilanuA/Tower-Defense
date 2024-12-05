#pragma once

#include "CoreMinimal.h"
#include "TowerUpgradeStruct.generated.h"

USTRUCT(BlueprintType)
struct FTowerUpgradeStruct
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Upgrade")
	float AttackSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Upgrade")
	float AttackDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Upgrade")
	float UpgradeCost;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Upgrade")
	TObjectPtr<UStaticMesh> TowerMesh;
	
};
