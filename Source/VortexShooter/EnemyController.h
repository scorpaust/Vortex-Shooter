// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyController.generated.h"

/**
 * 
 */
UCLASS()
class VORTEXSHOOTER_API AEnemyController : public AAIController
{
	GENERATED_BODY()

public:

	AEnemyController();

	virtual void OnPossess(APawn* InPawn) override;

private:

	/** Blackboard component for this enemy */
	UPROPERTY(BlueprintReadWrite, Category = "AI Behavior", meta = (AllowPrivateAccess = true ))
	class UBlackboardComponent* BlackboardComponent;

	/** Behavior Tree component for this enemy */
	UPROPERTY(BlueprintReadWrite, Category = "AI Behavior", meta = (AllowPrivateAccess = true))
	class UBehaviorTreeComponent* BehaviorTreeComponent;

public:

	FORCEINLINE UBlackboardComponent* GetBlackboardComponent() const { return BlackboardComponent; }
	
};
