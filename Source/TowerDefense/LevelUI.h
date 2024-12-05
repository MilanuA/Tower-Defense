// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "LevelUI.generated.h"

class UTowerUpgradeWidget;

UCLASS()
class TOWERDEFENSE_API ULevelUI : public UUserWidget
{
	GENERATED_BODY()

	UTowerUpgradeWidget* TowerUpgradeWidget;
	
public:
	UPROPERTY(BlueprintReadWrite)
	int CurrentCoins;

	UPROPERTY(BlueprintReadWrite)
	int MaxWaves;
	
protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* CoinsText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* WavesText;
	
	UPROPERTY(BlueprintReadWrite)
	int CurrentWave = -1;
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnLevelFinished();
	
public:
	UFUNCTION(BlueprintImplementableEvent)
	/// <summary> Updates the health bar in BLUEPRINT</summary>
	void OnUpdateHealthBar(float HealthDecrease);
	
	UFUNCTION(BlueprintCallable)
	void CheckUpgradeButtons();

	
	void DecreaseCoins(int CoinsAmount);

	UFUNCTION(BlueprintCallable)
	void IncreaseWave();
	
private:
	/// <summary> Reference to the upgrade UI </summary>
	void GetUpgradeUIReference();
};
