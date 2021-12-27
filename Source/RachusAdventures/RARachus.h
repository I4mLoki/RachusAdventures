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
	virtual void Tick(float DeltaSeconds) override;

public:
	ARARachus();

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Rachus")
	float BaseMovementSpeed = 600.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Rachus")
	float BaseJumpSpeed = 300.f;

	UFUNCTION(BlueprintCallable, Category = "Rachus")
	bool Roll();

private:
	float BaseTurnRate = 45.f;
	float BaseLookUpRate = 45.f;

	void BaseSetup();
	void InitialGameplaySetup();
	void MoveForward(float Value);
	void MoveRight(float Value);
	void TurnRate(float Value);
	void LookUpRate(float Value);
	void CheckIfMustJump();
};
