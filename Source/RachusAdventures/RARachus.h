#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RARachus.generated.h"

UCLASS()
class RACHUSADVENTURES_API ARARachus : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	virtual void BeginPlay() override;

public:
	ARARachus();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rachus")
	float BaseMovementSpeed = 600.f;
	
	UFUNCTION(BlueprintCallable, Category = "Rachus")
	void MoveForward(float Value);

	UFUNCTION(BlueprintCallable, Category = "Rachus")
	void MoveRight(float Value);

private:
	void BaseSetup();
	void InitialGameplaySetup();
};
