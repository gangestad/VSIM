// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Perceptron.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/Classes/Animation/AnimSequence.h"
#include "Engine/Classes/Animation/AnimComposite.h"


#include "MyCharacter.generated.h"



UCLASS()
class DOGBALL_PERCEPTRON_1_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UAnimSequence *IdleAnim;
	UAnimComposite *Duck_StandingUpAnim;

	bool isDuckingAnimationStarted;

	void enableCollision(bool collide);

	void runDuckingAnimation();

	Perceptron brain;
	UFUNCTION(BlueprintCallable, Category = "Perception")
		void resetTrainingSet();

	UFUNCTION(BlueprintCallable, Category = "Perception")
		void SendInput(float i1, float i2, float out);

};
