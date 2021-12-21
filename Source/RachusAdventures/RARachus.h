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

public:
	ARARachus();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void InitialSetup();
	void MoveForward(float Value);
	void MoveRight(float Value);
};
