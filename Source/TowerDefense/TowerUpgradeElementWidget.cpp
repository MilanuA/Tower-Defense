// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerUpgradeElementWidget.h"

#include "TowerBase.h"

void UTowerUpgradeElementWidget::SetElementInfo(const FTowerUpgradeStruct& PassedUpgradeInfo, ULevelUI* LevelUI, ATowerBase* TowerBase, int8 ElementIndex)
{
	UpgradeInfo = PassedUpgradeInfo;
	GetLevelUI = LevelUI;
	GetTowerBase = TowerBase;

	CurrentElementIndex = ElementIndex;
	
	TB_DamageValue->SetText(FText::AsNumber(PassedUpgradeInfo.AttackDamage));
	TB_AttacKSpeedValue->SetText(FText::AsNumber(PassedUpgradeInfo.AttackSpeed));
	TB_UpgradeCostValue->SetText(FText::AsNumber(PassedUpgradeInfo.UpgradeCost));
	
	CheckBuyButton(GetLevelUI->CurrentCoins);
	
	BT_Buy->OnClicked.Clear();
	BT_Buy->OnClicked.AddDynamic(this, &UTowerUpgradeElementWidget::BuyUpgrade);
}

/// <summary>
/// Checks if the upgrade button can be enabled
/// </summary>
void UTowerUpgradeElementWidget::CheckBuyButton(int CurrentCoins)
{
	BT_Buy->SetIsEnabled(UpgradeInfo.UpgradeCost <= CurrentCoins && GetTowerBase->CurrentUpgradeIndex < CurrentElementIndex);
}

void UTowerUpgradeElementWidget::BuyUpgrade()
{
	GetTowerBase->CurrentUpgradeIndex = CurrentElementIndex;
	
	GetLevelUI->DecreaseCoins(UpgradeInfo.UpgradeCost);
	GetTowerBase->UpgradeTowerMesh(UpgradeInfo.TowerMesh);
}