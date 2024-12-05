// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "TowerUpgradeElementWidget.h"
#include "TowerUpgradeStruct.h"
#include "Blueprint/UserWidget.h"
#include "TowerUpgradeWidget.generated.h"

/**
 * 
 */
class ULevelUI;
class ATowerBase;

UCLASS()
class TOWERDEFENSE_API UTowerUpgradeWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void OpenUI(TArray<FTowerUpgradeStruct> &TowerUpgrades, ATowerBase* TowerBase);
	void CheckElements(int CurrentCoins);
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnOpenUI();

protected:
	UPROPERTY(meta = (BindWidget))
	UTowerUpgradeElementWidget* Element1;

	UPROPERTY(meta = (BindWidget))
	UTowerUpgradeElementWidget* Element2;

	UPROPERTY(meta = (BindWidget))
	UTowerUpgradeElementWidget* Element3;

private:
	bool UpdateElements(TArray<FTowerUpgradeStruct> &TowerUpgrades, ATowerBase* TowerBase);
	ULevelUI* LevelUI;

	void GetLevelUI();
};
