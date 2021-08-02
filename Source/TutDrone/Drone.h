// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Drone.generated.h"

UCLASS()//告诉虚幻编辑器生成一些模板文件
class TUTDRONE_API ADrone : public APawn
{
	GENERATED_BODY()
		//编译的之后虚幻会把生成的内容替换到这个位置

public:
	// Sets default values for this pawn's properties
	ADrone();

	/*
	UObject 是所有纳入到UE4反射系统的基类对象，所有要被纳入到UE4反射系统的对象都必须继承自UObject,
	继承自UObject将会被UE4引用计数，并最终用于垃圾回收。UClass用于捕获一个类的所有属性和方法,
	可以认为是一个类的元数据结构。这个元数据结构提供在运行期获得一个类的属性和方法基本信息，
	一旦有了类的元数据，就可以将一个类的属性和方法暴露到编辑器里，蓝图。
	使得c++和编辑器，蓝图通信，c++和蓝图互相调用变成可能。
	在类的属性和方法里可以选择性的通过宏来声明是否要将该属性和方法纳入反射，不纳入到反射的属性将不会被UE4引用计数，对于裸指针而言，是比较危险的操作。
	UE4也提供了自己的智能指针系统，对没有纳入到反射的属性也能最终被系统回收。
	在你创建的每个类的头文件，虚幻4会添加generate.h头文件，这个就是每个继承自UObject 类的头文件里生成的对应的宏代码
	*/

	UPROPERTY(VisibleAnywhere)
		class UBoxComponent* OutCollision;//碰撞体

	UPROPERTY(VisibleAnywhere)//1.UPROPERTY 提供自动GC 2.序列化变量
		class UStaticMeshComponent* Mesh;//前向声明 虚幻里面一般使用这样的方式，用的class里面的方法时在include其头文件


	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent* Paddle1;

	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent* Paddle2;

	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent* Paddle3;

	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent* Paddle4;

	UPROPERTY(VisibleAnywhere)
		class UPhysicsThrusterComponent* UpThruster;//向上物理推进器	持续的对一个物体施加力

	UPROPERTY(VisibleAnywhere)
		class UPhysicsThrusterComponent* ForwarThruster;//向前物理推进器

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Init")
		float LiftAcc = 10000;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Init")
		float LiftThrustMax = 2000;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Init")
		float ForwardAcc = 500;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Init")
		float ForwardThrustMax = 2000;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Init")
		float TurnStrength = 500000;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Init")
		float PaddleRotationSpeed = 1000;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Init")
		float MeshRotationSpeed = 20;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UFUNCTION()
		void Lift(float value);
	UFUNCTION()
		void Forward(float value);
	UFUNCTION()
		void Turn(float value);

	float TempDeltaTime;


	TArray<UStaticMeshComponent*> Paddles;

	void RotatePaddle(float deltatime);
};
