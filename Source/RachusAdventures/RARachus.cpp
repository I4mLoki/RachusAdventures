// Fill out your copyright notice in the Description page of Project Settings.


#include "RARachus.h"

// Sets default values
ARARachus::ARARachus()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARARachus::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARARachus::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARARachus::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

