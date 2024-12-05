// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "TowerUpgradeStruct.h"
#include "TowerUpgradeWidget.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "EnemyBase.h"
#include "TowerBase.generated.h"

UCLASS()
class TOWERDEFENSE_API ATowerBase : public AActor
{
	GENERATED_BODY()

public:	
	ATowerBase();
	
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
	
protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Upgrades")
	TArray<FTowerUpgradeStruct> TowerUpgrades;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Upgrades")
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBoxComponent* BoxComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USphereComponent* DetectionSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* DetectionRangeMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials")
	UMaterialInterface* TowerMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials")
	UMaterialInterface* HoverMaterial;
	
	UFUNCTION()
	void OnEnemyEnterRadius(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	UFUNCTION()
	void OnEnemyExitRadius(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void OnCursorOver(UPrimitiveComponent* Component);

	UFUNCTION()
	void EndCursorOver(UPrimitiveComponent* Component);

	UFUNCTION()
	void OnClick(UPrimitiveComponent* Component,  FKey InKey);

	UPROPERTY(VisibleAnywhere)
	UTowerUpgradeWidget* TowerUpgradeWidget;

	UPROPERTY(EditAnywhere, Category = "Tower Settings")
	float DetectionRadius = 200.f;

	UPROPERTY(EditAnywhere, Category = "Tower Settings")
	float SphereRadiusDivider = 50.f;
	
	UPROPERTY(EditAnywhere, Category = "Attack Settings")
	float AttackIntervalBase = 20.0f;
	
	UPROPERTY(VisibleAnywhere)
	int8 AttackWavesAmount;
	
private:
	APlayerController* PlayerController;
	
	UPROPERTY()
	TArray<AEnemyBase*> EnemiesInRange;

	void Attack();

	float Timer;
	
	void GetUpgradeWidgetReference();
	void UpdateCylinderScale();

public:
	int8 CurrentUpgradeIndex = 0;
	virtual void Tick(float DeltaTime) override;

	void UpgradeTowerMesh(UStaticMesh* UpgradedMesh);
};
