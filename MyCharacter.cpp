// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Components/CapsuleComponent.h"
// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UAnimSequence> idle_Anim(TEXT("AnimSequence'/Game/Character/Animations/Idle.Idle'"));
	IdleAnim = idle_Anim.Object;

	static ConstructorHelpers::FObjectFinder<UAnimComposite> duck_standing_Anim(TEXT("AnimComposite'/Game/Character/Animations/Duck_and_Stand.Duck_and_Stand'"));
	Duck_StandingUpAnim = duck_standing_Anim.Object;

}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetMesh()->PlayAnimation(IdleAnim, true);

	brain.InitialiseWeights();

}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isDuckingAnimationStarted == true)
	{
		if (GetMesh()->IsPlaying() == false)
		{
			isDuckingAnimationStarted = false;
			enableCollision(true);
			GetMesh()->PlayAnimation(IdleAnim, true);
		}
	}
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMyCharacter::runDuckingAnimation()
{
	enableCollision(false);
	GetMesh()->PlayAnimation(Duck_StandingUpAnim, false);
	isDuckingAnimationStarted = true;
}

void AMyCharacter::enableCollision(bool collide)
{
	if (collide == true)
	{
		GetCapsuleComponent()->SetCollisionResponseToChannel(
			ECollisionChannel::ECC_GameTraceChannel1,
			ECollisionResponse::ECR_Block
		);
	}
	else
	{
		GetCapsuleComponent()->SetCollisionResponseToChannel(
			ECollisionChannel::ECC_GameTraceChannel1,
			ECollisionResponse::ECR_Ignore
		);
	}
}

void AMyCharacter::resetTrainingSet()
{
	brain.InitialiseWeights();
	brain.ts.Empty();
}

void AMyCharacter::SendInput(float i1, float i2, float out)
{
	//react
	double result = brain.CalcOutput(i1, i2);
	if (result == 0) //duck for cover
	{
		runDuckingAnimation();
	}
	else
	{
		enableCollision(true);
	}

	//learn from it for next time
	TrainingSet s;
	s.input.Add(i1);
	s.input.Add(i2);
	s.output = out;
	brain.ts.Add(s);
	brain.Train();
}


