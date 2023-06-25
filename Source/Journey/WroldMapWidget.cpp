// Fill out your copyright notice in the Description page of Project Settings.


#include "WroldMapWidget.h"
#include "HeroCharacter.h"


void UWroldMapWidget::NativeConstruct()
{
    Super::NativeConstruct();

    UImage* BackgroundImage = NewObject<UImage>(this);
    BackgroundImage->SetColorAndOpacity(FLinearColor::Black * 0.5f); 
    RootPanel->AddChild(BackgroundImage);

  
    AProceduralWorldMapGenerator* worldMap = Cast<AProceduralWorldMapGenerator>(UGameplayStatics::GetActorOfClass(GetWorld(), AProceduralWorldMapGenerator::StaticClass()));
    AHeroCharacter* player = Cast<AHeroCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), AHeroCharacter::StaticClass()));
    FVector2D playerPos = FVector2D(player->GetActorLocation().X / 180, player->GetActorLocation().Y / 150);

    TArray<TArray<FWTile>> WorldMapData = worldMap->heightMap;

    for (int i = 0; i < 50; ++i)
    {
        for (int j = 0; j < 50; ++j)
        {
            if (j == 0 || j == 49 || i == 0 || i == 49)
                continue;

            if (WorldMapData[i][j].isTown)
            {
                UButton* VillageButton = NewObject<UButton>(this);
                // 마을을 나타내는 버튼에 클릭 이벤트 핸들러를 추가합니다.
                VillageButton->OnClicked.AddDynamic(this, &UWroldMapWidget::OnVillageButtonClicked);
                VillageButton->WidgetStyle.Normal.SetResourceObject(nullptr);
                UImage* ButtonImage = NewObject<UImage>(this);
                ButtonImage->SetBrushFromTexture(TownTexture); 
                ButtonImage->SetBrushFromTexture(TownTexture); 


                VillageButton->AddChild(ButtonImage);

                 GridPanel->AddChildToGrid(VillageButton, j, i);
           

            }

            UImage* Image = NewObject<UImage>(this);
            if (WorldMapData[i][j].isWater)
            {
                Image->SetBrushFromTexture(WaterTexture);
            }
            else
            {
                Image->SetBrushFromTexture(LandTexture);
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

void UWroldMapWidget::OnVillageButtonClicked()
{
}
