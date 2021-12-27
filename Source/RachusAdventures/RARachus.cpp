#include "RARachus.h"

#include "DrawDebugHelpers.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

ARARachus::ARARachus()
{
	BaseSetup();
}

void ARARachus::BeginPlay()
{
	Super::BeginPlay();

	InitialGameplaySetup();
}

void ARARachus::Tick(float DeltaSeconds)
{
	CheckIfMustJump();
}

void ARARachus::BaseSetup()
{
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->AirControl = 0.2f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
}

void ARARachus::InitialGameplaySetup()
{
	GetCharacterMovement()->MaxWalkSpeed = BaseMovementSpeed;
	GetCharacterMovement()->JumpZVelocity = BaseJumpSpeed;
}

void ARARachus::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ARARachus::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ARARachus::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ARARachus::TurnRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ARARachus::LookUpRate);
}

void ARARachus::MoveForward(float Value)
{
	if (Controller == nullptr || Value == 0.f) return;

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}

void ARARachus::MoveRight(float Value)
{
	if (Controller == nullptr || Value == 0.f) return;

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}

void ARARachus::TurnRate(float Value)
{
	AddControllerYawInput(Value * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ARARachus::LookUpRate(float Value)
{
	AddControllerPitchInput(Value * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ARARachus::CheckIfMustJump()
{
	const bool IsFalling = GetCharacterMovement()->IsFalling();
	const FVector Velocity = GetCharacterMovement()->Velocity;

	if (IsFalling) return;
	if (abs(Velocity.X) < 300 && abs(Velocity.Y) < 300) return;

	const FVector StartTracePoint = GetActorLocation() + GetActorForwardVector() * 50.f;
	const FVector EndTracePoint = StartTracePoint - FVector(0.f, 0.f, 150.f);

	FHitResult Hit;
	FCollisionQueryParams TraceParams;
	GetWorld()->LineTraceSingleByChannel(Hit, StartTracePoint, EndTracePoint, ECC_Visibility, TraceParams);
	// DrawDebugLine(GetWorld(), StartTracePoint, EndTracePoint, FColor::Red, false, 5.f);

	if (Hit.bBlockingHit) return;

	Jump();
}

bool ARARachus::Roll()
{
	const FVector Velocity = GetCharacterMovement()->Velocity;

	if (Velocity != FVector::ZeroVector)
		return true;

	return false;
}
