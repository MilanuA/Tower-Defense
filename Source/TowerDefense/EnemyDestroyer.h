#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyDestroyer.generated.h"

class ULevelUI;
UCLASS()
class TOWERDEFENSE_API AEnemyDestroyer : public AActor
{
	GENERATED_BODY()
	
public:	
	AEnemyDestroyer();

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	ULevelUI* EventBasedUI;

	UPROPERTY(EditAnywhere)
	float HealthDecreaser;
	
	void GetUIReference();
public:	
	UFUNCTION()
	void OnTriggerEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* TriggerBox;
};
