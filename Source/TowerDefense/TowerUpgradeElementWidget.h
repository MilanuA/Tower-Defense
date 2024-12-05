// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LevelUI.h"

#include "TowerUpgradeStruct.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "TowerUpgradeElementWidget.generated.h"

/**
 * 
 */

class ATowerBase;

UCLASS()
class TOWERDEFENSE_API UTowerUpgradeElementWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TB_DamageValue;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TB_AttacKSpeedValue;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TB_UpgradeCostValue;
	
	UPROPERTY(meta = (BindWidget))
	UButton* BT_Buy;

private:
	FTowerUpgradeStruct UpgradeInfo;
	ATowerBase* GetTowerBase;
	ULevelUI* GetLevelUI;
	int8 CurrentElementIndex;
	
	UFUNCTION()
	void BuyUpgrade();
	
public:
	void SetElementInfo(const FTowerUpgradeStruct& PassedUpgradeInfo, ULevelUI* LevelUI, ATowerBase* TowerBase, int8 ElementIndex);
	void CheckBuyButton(int CurrentCoins);
};
