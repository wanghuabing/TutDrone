// Fill out your copyright notice in the Description page of Project Settings.


#include "Drone.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "PhysicsEngine/PhysicsThrusterComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Drone.h"

// Sets default values
ADrone::ADrone()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	OutCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("OutCollision"));
	RootComponent = OutCollision;
	OutCollision->SetBoxExtent(FVector(100.0f, 100.0f, 100.f));
	OutCollision->SetSimulatePhysics(true);//��������ģ������
	OutCollision->BodyInstance.bLockXRotation = true;
	OutCollision->BodyInstance.bLockYRotation = true;//������ת

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

	UpThruster = CreateDefaultSubobject<UPhysicsThrusterComponent>(TEXT("UpThruster"));
	UpThruster->SetupAttachment(RootComponent);
	UpThruster->ThrustStrength = 980.0f;//�������ٶ�
	UpThruster->SetAutoActivate(true);
	UpThruster->SetWorldRotation(UKismetMathLibrary::MakeRotFromX(-this->GetActorUpVector())); //���õ�ǰ���峯��ʱ���rotation

	ForwarThruster = CreateDefaultSubobject<UPhysicsThrusterComponent>(TEXT("ForwarThruster"));
	ForwarThruster->SetupAttachment(RootComponent);
	ForwarThruster->ThrustStrength = 0.0f;
	ForwarThruster->SetAutoActivate(true);
	ForwarThruster->SetWorldRotation(UKismetMathLibrary::MakeRotFromX(this->GetActorForwardVector()));

	//AttachToComponent���ܷŵ����캯������ִ��
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

}

// Called to bind functionality to input
void ADrone::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Lift"), this, &ADrone::Lift);
	PlayerInputComponent->BindAxis(TEXT("Forward"), this, &ADrone::Forward);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ADrone::Turn);
}

void ADrone::Lift(float value)
{
	//ÿһ֡�����ϵĸ����������
	//�漰����ÿһ֡�йصģ�Ӧ���ǲ�ͬ֡�ʶ�����Ӱ��
	UpThruster->ThrustStrength += (LiftAcc * value * GetWord()->DeltaTimeSeconds);
	UpThruster->ThrustStrength = FMath::Clamp(UpThruster->ThrustStrength, -LiftThrustMax, LiftThrustMax);
}

void ADrone::Forward(float value)
{

}

void ADrone::Turn(float value)
{

}

