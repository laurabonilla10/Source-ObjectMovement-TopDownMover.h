// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TopDownMover.generated.h"

// UENUM(BlueprintType) makes it visible in the Editor dropdowns
UENUM(BlueprintType)
enum class EMoveDirection : uint8
{
	Up          UMETA(DisplayName = "Up"),
	Down        UMETA(DisplayName = "Down"),
	Left        UMETA(DisplayName = "Left"),
	Right       UMETA(DisplayName = "Right"),
	UpRight     UMETA(DisplayName = "Up Right"),
	UpLeft      UMETA(DisplayName = "Up Left"),
	DownRight   UMETA(DisplayName = "Down Right"),
	DownLeft    UMETA(DisplayName = "Down Left")
};

UCLASS()
class OBJECTMOVEMENT_API ATopDownMover : public APawn
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATopDownMover();

protected:
	virtual void BeginPlay() override;
	// A visual mesh so we can actually see the object in the editor
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UStaticMeshComponent* MeshComponent;
	// Called when the game starts or when spawned
	

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// 2. Variables exposed to the Visual Editor
	UPROPERTY(EditAnywhere, Category = "Movement Settings")
	float Velocity;

	UPROPERTY(EditAnywhere, Category = "Movement Settings")
	EMoveDirection MoveDirection;
	UPROPERTY(EditAnywhere, Category = "Movement Settings")
	bool bIsMoving;

private:
	// 3. Boolean to control the action state
	//bool bIsMoving;

	// Function to listen to the Spacebar
	void ToggleMovement();

};
