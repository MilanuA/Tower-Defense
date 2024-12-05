// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerUpgradeWidget.h"
#include "TowerBase.h"
#include "LevelUI.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"

void UTowerUpgradeWidget::OpenUI(TArray<FTowerUpgradeStruct> &TowerUpgrades, ATowerBase* TowerBase)
{
	bool bSuccesfullyUpdated = UpdateElements(TowerUpgrades, TowerBase);

	if (!bSuccesfullyUpdated) return;
	
	OnOpenUI();
}

void UTowerUpgradeWidget::CheckElements(int CurrentCoins)
{
	Element1->CheckBuyButton(CurrentCoins);
	Element2->CheckBuyButton(CurrentCoins);
	Element3->CheckBuyButton(CurrentCoins);
}

bool UTowerUpgradeWidget::UpdateElements(TArray<FTowerUpgradeStruct>& TowerUpgrades, ATowerBase* TowerBase)
{
	if (TowerUpgrades.Num() <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("No tower upgrades found for tower %s"), *GetName());
		return false;
	}

	if (TowerUpgrades.Num() > 3)
	{
		UE_LOG(LogTemp, Warning, TEXT("Too many tower upgrades found for tower %s"), *GetName());
		return false;
	}

	if(LevelUI == nullptr) GetLevelUI();
	
	//funny way how to do it, but hey, its never gonna be more than 3 upgrades :D

	Element1->SetElementInfo(TowerUpgrades[0], LevelUI, TowerBase,1);
	Element2->SetElementInfo(TowerUpgrades[1], LevelUI, TowerBase, 2);
	Element3->SetElementInfo(TowerUpgrades[2], LevelUI, TowerBase, 3);

	return true;
}

void UTowerUpgradeWidget::GetLevelUI()
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

	LevelUI = Cast<ULevelUI>(FoundWidgets[0]);
}
