// Fill out your copyright notice in the Description page of Project Settings.


#include "MinimapWidget.h"
#include "HeroCharacter.h"

void UMinimapWidget::NativeConstruct()
{
	Super::NativeConstruct();
    UImage* BackgroundImage = NewObject<UImage>(this);
    BackgroundImage->SetColorAndOpacity(FLinearColor::Black * 0.5f); 
    RootPanel->AddChild(BackgroundImage);

    
    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(),AProceduralNoiseGenerator::StaticClass(),FoundActors);
    AHeroCharacter* player = Cast<AHeroCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), AHeroCharacter::StaticClass()));
    FVector2D playerPos = FVector2D(player->GetActorLocation().X / 180, player->GetActorLocation().Y / 150);

    AProceduralNoiseGenerator* townmap = Cast<AProceduralNoiseGenerator>(FoundActors[TownNum]);
    vector<vector<int32>> TownMapData = townmap->height;

    for (int i = 0; i < townmap->XSize; ++i)
    {
        for (int j = 0; j < townmap->YSize; ++j)
        {
            if (j == 0 || j == townmap->YSize - 1  || i == 0 || i == townmap->XSize - 1)
                continue;
            
            UImage* Image = NewObject<UImage>(this);
            if (TownMapData[i][j] == 3) //집
            {
                Image->SetBrushFromTexture(HouseTexture);
            }
            else if(TownMapData[i][j] == 9) // 상점
            {
                Image->SetBrushFromTexture(ShopTexture);
            }
            else if (TownMapData[i][j] == 10)//모텔
            {
                Image->SetBrushFromTexture(MotelTexture);
            }
            else if(TownMapData[i][j] == 1)
            {
                Image->SetBrushFromTexture(LandTexture);
            }
            else
            {
                Image->SetBrushFromTexture(WallTexture);
            }
            //Image->SetBrushSize(FVector2D(ImageWidth, ImageHeight));

            //Image->SetBrushSize(FVector2D(j, i));

            GridPanel->AddChildToGrid(Image, j, i);
        }
    }


    UImage* Image = NewObject<UImage>(this);
    Image->SetBrushFromTexture(PlayerTexture);
    GridPanel->AddChildToGrid(Image, playerPos.Y, playerPos.X);

}

void UMinimapWidget::OnVillageButtonClicked()
{
}
