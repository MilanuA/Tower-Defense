// Fill out your copyright notice in the Description page of Project Settings.

#include "LevelUI.h"

#include "TowerUpgradeWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"

void ULevelUI::CheckUpgradeButtons()
{
	if (TowerUpgradeWidget == nullptr)
		GetUpgradeUIReference();
	
	if (!TowerUpgradeWidget->IsVisible()) return;

	TowerUpgradeWidget->CheckElements(CurrentCoins);
}

/// <summary>
/// Decreases the amount of coins, updates the UI and checks if the upgrade buttons can be enabled
/// </summary>
void ULevelUI::DecreaseCoins(int CoinsAmount)
{
	CurrentCoins -= CoinsAmount;
	
	CoinsText->SetText(FText::FromString("Coins: " + FString::FromInt(CurrentCoins)));

	CheckUpgradeButtons();
}

void ULevelUI::IncreaseWave()
{
	CurrentWave++;
	
	WavesText->SetText(FText::FromString("Wave: " + FString::FromInt(CurrentWave) + " / " + FString::FromInt(MaxWaves)));

	if (CurrentWave == MaxWaves)
	{
		OnLevelFinished();	
	}
}

void ULevelUI::GetUpgradeUIReference()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	
	if (!PlayerController) return;

	TArray<UUserWidget*> FoundWidgets;
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(this, FoundWidgets, UTowerUpgradeWidget::StaticClass(), false);
	
	if (FoundWidgets.Num() <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("No widgets found for destroyer %s"), *GetName());
		return;
	}

	TowerUpgradeWidget = Cast<UTowerUpgradeWidget>(FoundWidgets[0]);
}
