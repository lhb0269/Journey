// Fill out your copyright notice in the Description page of Project Settings.


#include "JourneyController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

AJourneyController::AJourneyController()
{
    bClickRightMouse = false;
   /* bShowMouseCursor = true;
    SetInputMode(FInputModeGameAndUI());*/
    
}

void AJourneyController::SetupInputComponent()
{
	InputComponent->BindAction(TEXT("RightClick"), IE_Pressed, this, &AJourneyController::InputRightMouseButtonPressed);
	InputComponent->BindAction(TEXT("RightClick"), IE_Released, this, &AJourneyController::InputRightMouseButtonReleased);
}

void AJourneyController::PlayerTick(float DeletaTime)
{
    Super::PlayerTick(DeletaTime);
    if (bClickRightMouse)
    {
        MoveToMouseCursur();
    }
}

void AJourneyController::SetNewDestination(const FVector Dest)
{
    APawn* const MyPawn = GetPawn();

    if (MyPawn)
    {
        float const Distance = FVector::Dist(Dest, MyPawn->GetActorLocation());
        if (Distance > 120.0f)
        {
            UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, Dest);
        }
    }
}

//void AJourneyController::OnRightMouseClicked()
//{
//    FVector2D ScreenPosition;
//    if (GetMousePosition(ScreenPosition.X, ScreenPosition.Y))
//    {
//        FVector WorldLocation;
//        FVector WorldDirection;
//        if (DeprojectScreenPositionToWorld(ScreenPosition.X, ScreenPosition.Y, WorldLocation, WorldDirection))
//        {
//            // TODO: Implement movement to the clicked location
//        }
//    }
//}

void AJourneyController::InputRightMouseButtonPressed()
{
    bClickRightMouse = true;
}

void AJourneyController::InputRightMouseButtonReleased()
{
    bClickRightMouse = false;
}

void AJourneyController::MoveToMouseCursur()
{
    FHitResult Hit;
    GetHitResultUnderCursor(ECC_Visibility, false, Hit);

    if (Hit.bBlockingHit)
    {
        SetNewDestination(Hit.ImpactPoint);
    }
}
