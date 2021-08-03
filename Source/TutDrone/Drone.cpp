// Fill out your copyright notice in the Description page of Project Settings.


#include "Drone.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "PhysicsEngine/PhysicsThrusterComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ADrone::ADrone()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	OutCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("OutCollision"));
	RootComponent = OutCollision;
	OutCollision->SetBoxExtent(FVector(100.0f, 100.0f, 100.f));
	OutCollision->SetSimulatePhysics(true);//设置启用模拟物理
	OutCollision->BodyInstance.bLockXRotation = true;
	OutCollision->BodyInstance.bLockYRotation = true;//锁定旋转

	//Mesh->SetupAttachment(RootComponent);
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(OutCollision);
	Paddle1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Paddle1"));
	Paddle2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Paddle2"));
	Paddle3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Paddle3"));
	Paddle4 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Paddle4"));
	Paddle1->SetupAttachment(Mesh, TEXT("Paddle1"));
	Paddle2->SetupAttachment(Mesh, TEXT("Paddle2"));
	Paddle3->SetupAttachment(Mesh, TEXT("Paddle3"));
	Paddle4->SetupAttachment(Mesh, TEXT("Paddle4"));

	Paddles.Add(Paddle1);
	Paddles.Add(Paddle2);
	Paddles.Add(Paddle3);
	Paddles.Add(Paddle4);


	UpThruster = CreateDefaultSubobject<UPhysicsThrusterComponent>(TEXT("UpThruster"));
	UpThruster->SetupAttachment(RootComponent);
	UpThruster->ThrustStrength = 980.0f;//重力加速度
	UpThruster->SetAutoActivate(true);
	UpThruster->SetWorldRotation(UKismetMathLibrary::MakeRotFromX(-this->GetActorUpVector())); //设置当前物体朝下时候的rotation

	ForwarThruster = CreateDefaultSubobject<UPhysicsThrusterComponent>(TEXT("ForwarThruster"));
	ForwarThruster->SetupAttachment(RootComponent);
	ForwarThruster->ThrustStrength = 0.0f;
	ForwarThruster->SetAutoActivate(true);
	ForwarThruster->SetWorldRotation(UKismetMathLibrary::MakeRotFromX(-this->GetActorForwardVector()));

	//AttachToComponent不能放到构造函数里面执行
}

// Called when the game starts or when spawned
void ADrone::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ADrone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TempDeltaTime = DeltaTime;

	if (GetInputAxisValue(TEXT("Lift")) == 0)
	{
		UpThruster->ThrustStrength = 980.0f;
	}

	if (GetInputAxisValue(TEXT("Forward")) == 0)
	{
		ForwarThruster->ThrustStrength = 0.0f;

		float currentPitch = Mesh->GetRelativeRotation().Pitch;
		if (currentPitch != 0)
		{
			if (FMath::Abs(currentPitch) <= KINDA_SMALL_NUMBER)
			{
				Mesh->SetRelativeRotation(FRotator::ZeroRotator);
			}
			else
			{
				//负号 进行与原方向相反的偏移
				Mesh->AddRelativeRotation(FRotator(-currentPitch * DeltaTime, .0f, .0f));
			}
		}
	}

	RotatePaddle(DeltaTime);
}

// Called to bind functionality to input
void ADrone::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Lift"), this, &ADrone::Lift);
	PlayerInputComponent->BindAxis(TEXT("Forward"), this, &ADrone::Forward);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ADrone::Turn);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ADrone::Fire);
}

void ADrone::Lift(float value)
{
	//每一帧都不断的给这个力增加
	//涉及到和每一帧有关的，应考虑不同帧率对它的影响

	/*this->GetWorld()->DeltaTimeSeconds <==> TempDeltaTime*/
	UpThruster->ThrustStrength += (LiftAcc * value * TempDeltaTime);
	UpThruster->ThrustStrength = FMath::Clamp(UpThruster->ThrustStrength, -LiftThrustMax, LiftThrustMax);
}

void ADrone::Forward(float value)
{
	ForwarThruster->ThrustStrength += (ForwardAcc * value * TempDeltaTime);
	ForwarThruster->ThrustStrength = FMath::Clamp(ForwarThruster->ThrustStrength, -ForwardThrustMax, ForwardThrustMax);

	float pitch = Mesh->GetRelativeRotation().Pitch;
	if (FMath::Abs(pitch) < 30)
	{
		Mesh->AddRelativeRotation(FRotator(value * TempDeltaTime * -MeshRotationSpeed, .0f, .0f));
	}
}

void ADrone::Turn(float value)
{
	//auto t = FString::Printf(TEXT("%f %f % f"), value, TempDeltaTime, TurnStrength);
	//GEngine->AddOnScreenDebugMessage(0, 10, FColor::Red, t);

	OutCollision->AddTorqueInDegrees(-this->GetActorUpVector() * value * TurnStrength);
}

void ADrone::Fire()
{
	FTransform firingScoket = Mesh->GetSocketTransform(TEXT("FiringScoket"));
	this->GetWorld()->SpawnActor<AMissle>(Bullet, firingScoket);
}

void ADrone::RotatePaddle(float deltatime)
{
	for (auto paddle : Paddles)
	{
		paddle->AddRelativeRotation(FRotator(.0f, deltatime * PaddleRotationSpeed, .0f));
	}
}

