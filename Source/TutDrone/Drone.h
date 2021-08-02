// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Drone.generated.h"

UCLASS()//������ñ༭������һЩģ���ļ�
class TUTDRONE_API ADrone : public APawn
{
	GENERATED_BODY()
		//�����֮����û�����ɵ������滻�����λ��

public:
	// Sets default values for this pawn's properties
	ADrone();

	/*
	UObject ���������뵽UE4����ϵͳ�Ļ����������Ҫ�����뵽UE4����ϵͳ�Ķ��󶼱���̳���UObject,
	�̳���UObject���ᱻUE4���ü����������������������ա�UClass���ڲ���һ������������Ժͷ���,
	������Ϊ��һ�����Ԫ���ݽṹ�����Ԫ���ݽṹ�ṩ�������ڻ��һ��������Ժͷ���������Ϣ��
	һ���������Ԫ���ݣ��Ϳ��Խ�һ��������Ժͷ�����¶���༭�����ͼ��
	ʹ��c++�ͱ༭������ͼͨ�ţ�c++����ͼ������ñ�ɿ��ܡ�
	��������Ժͷ��������ѡ���Ե�ͨ�����������Ƿ�Ҫ�������Ժͷ������뷴�䣬�����뵽��������Խ����ᱻUE4���ü�����������ָ����ԣ��ǱȽ�Σ�յĲ�����
	UE4Ҳ�ṩ���Լ�������ָ��ϵͳ����û�����뵽���������Ҳ�����ձ�ϵͳ���ա�
	���㴴����ÿ�����ͷ�ļ������4�����generate.hͷ�ļ����������ÿ���̳���UObject ���ͷ�ļ������ɵĶ�Ӧ�ĺ����
	*/

	UPROPERTY(VisibleAnywhere)
		class UBoxComponent* OutCollision;//��ײ��

	UPROPERTY(VisibleAnywhere)//1.UPROPERTY �ṩ�Զ�GC 2.���л�����
		class UStaticMeshComponent* Mesh;//ǰ������ �������һ��ʹ�������ķ�ʽ���õ�class����ķ���ʱ��include��ͷ�ļ�


	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent* Paddle1;

	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent* Paddle2;

	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent* Paddle3;

	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent* Paddle4;

	UPROPERTY(VisibleAnywhere)
		class UPhysicsThrusterComponent* UpThruster;//���������ƽ���	�����Ķ�һ������ʩ����

	UPROPERTY(VisibleAnywhere)
		class UPhysicsThrusterComponent* ForwarThruster;//��ǰ�����ƽ���

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
