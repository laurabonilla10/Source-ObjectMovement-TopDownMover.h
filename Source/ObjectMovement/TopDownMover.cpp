// Fill out your copyright notice in the Description page of Project Settings.

#include "TopDownMover.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
ATopDownMover::ATopDownMover()
{
    PrimaryActorTick.bCanEverTick = true;

    // CORRECTO: Solo usar esto
    AutoPossessPlayer = EAutoReceiveInput::Player0;

    // Mesh
    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    RootComponent = MeshComponent;

    // Cargar cubo
    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
    if (CubeMeshAsset.Succeeded())
    {
        MeshComponent->SetStaticMesh(CubeMeshAsset.Object);
    }

    // Valores iniciales
    Velocity = 400.0f;
    MoveDirection = EMoveDirection::Right;
    bIsMoving = false;
}

// Called when the game starts or when spawned
void ATopDownMover::BeginPlay()
{
    Super::BeginPlay();

    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(
            -1,
            5.0f,
            FColor::Yellow,
            TEXT("Starting the game")
        );
    }

    UE_LOG(LogTemp, Warning, TEXT("Starting the game"));
}

// Called every frame
void ATopDownMover::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (bIsMoving)
    {
        FVector CurrentLocation = GetActorLocation();
        FVector MovementStep = FVector::ZeroVector;

        switch (MoveDirection)
        {
        case EMoveDirection::Up:
            MovementStep.X = 1.0f;
            break;

        case EMoveDirection::Down:
            MovementStep.X = -1.0f;
            break;

        case EMoveDirection::Right:
            MovementStep.Y = 1.0f;
            break;

        case EMoveDirection::Left:
            MovementStep.Y = -1.0f;
            break;

            // Diagonales
        case EMoveDirection::UpRight:
            MovementStep.X = 1.0f;
            MovementStep.Y = 1.0f;
            break;

        case EMoveDirection::UpLeft:
            MovementStep.X = 1.0f;
            MovementStep.Y = -1.0f;
            break;

        case EMoveDirection::DownRight:
            MovementStep.X = -1.0f;
            MovementStep.Y = 1.0f;
            break;

        case EMoveDirection::DownLeft:
            MovementStep.X = -1.0f;
            MovementStep.Y = -1.0f;
            break;
        }

        // Normalizar para evitar velocidad mayor en diagonal
        MovementStep = MovementStep.GetSafeNormal();

        CurrentLocation += MovementStep * Velocity * DeltaTime;
        SetActorLocation(CurrentLocation);
    }
}

// INPUT (ÚNICO LUGAR CORRECTO)
void ATopDownMover::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAction(
        "ToggleMove",
        IE_Pressed,
        this,
        &ATopDownMover::ToggleMovement
    ).bConsumeInput = false;
}

void ATopDownMover::ToggleMovement()
{
    bIsMoving = !bIsMoving;

    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(
            -1,
            5.0f,
            FColor::Yellow,
            FString::Printf(TEXT("bIsMoving: %s"), bIsMoving ? TEXT("TRUE") : TEXT("FALSE"))
        );
    }

    UE_LOG(LogTemp, Warning, TEXT("Toggle pressed"));
}
