// Fill out your copyright notice in the Description page of Project Settings.


#include "HeroesInfoWidget.h"
#include "GameManager.h"
#include"GameDataSingleton.h"

void UHeroesInfoWidget::NativeConstruct()
{
	Super::NativeConstruct();
    
    SkillBtn->OnClicked.AddDynamic(this, &UHeroesInfoWidget::OnSkillBtnClicked);
    EquipBtn->OnClicked.AddDynamic(this, &UHeroesInfoWidget::OnEquipBtnClicked);

    LeftChangeBtn->OnClicked.AddDynamic(this, &UHeroesInfoWidget::OnLeftBtnClicked);
    RightChangeBtn->OnClicked.AddDynamic(this, &UHeroesInfoWidget::OnRightBtnClicked);

    for (TActorIterator<AGameManager> It(GetWorld()); It; ++It)
    {
        AGameManager* GM = *It;
        archer = GM->archer;
        hero = GM->hero;
        maze = GM->maze;
       
    }
    hero->SetActorLocation((FVector(-51560.0, 1330.0, 88.0)));
    maze->SetActorLocation((FVector(-51560.0, 500, 88.0)));
    archer->SetActorLocation((FVector(-51560.0, 600, 88.0)));
    count = 0;
    UIcharcatercnt = 0;
    ClassText->SetText(FText::FromString("HERO"));
   // TextWidget->SetText(FText::FromString(Text));

}

void UHeroesInfoWidget::SetItems()
{
    HelmetThum->SetBrushFromTexture(NULL);
    VestThum->SetBrushFromTexture(NULL);
    WeaponeThum->SetBrushFromTexture(NULL);
    ShoesThum->SetBrushFromTexture(NULL);
    switch (count)
    {
    case 0:
        if(hero->EquipItems[0]!=nullptr && hero->EquipItems[0]->Thumbnail!= nullptr)
            HelmetThum->SetBrushFromTexture(hero->EquipItems[0]->Thumbnail);
        if(hero->EquipItems[1]!=nullptr && hero->EquipItems[1]->Thumbnail != nullptr)
            VestThum->SetBrushFromTexture(hero->EquipItems[1]->Thumbnail);
        if(hero->EquipItems[2]!=nullptr && hero->EquipItems[2]->Thumbnail!= nullptr)
            WeaponeThum->SetBrushFromTexture(hero->EquipItems[2]->Thumbnail);
        if(hero->EquipItems[3]!=nullptr && hero->EquipItems[3]->Thumbnail!= nullptr)
            ShoesThum->SetBrushFromTexture(hero->EquipItems[3]->Thumbnail);
        break;
    case 1:
        if(maze->EquipItems[0]!=nullptr && maze->EquipItems[0]->Thumbnail!= nullptr)
            HelmetThum->SetBrushFromTexture(maze->EquipItems[0]->Thumbnail);
        if(maze->EquipItems[1]!=nullptr && maze->EquipItems[1]->Thumbnail != nullptr)
            VestThum->SetBrushFromTexture(maze->EquipItems[1]->Thumbnail);
        if(maze->EquipItems[2]!=nullptr && maze->EquipItems[2]->Thumbnail!= nullptr)
            WeaponeThum->SetBrushFromTexture(maze->EquipItems[2]->Thumbnail);
        if(maze->EquipItems[3]!=nullptr && maze->EquipItems[3]->Thumbnail!= nullptr)
            ShoesThum->SetBrushFromTexture(maze->EquipItems[3]->Thumbnail);
        break;
    case 2:
        if(archer->EquipItems[0]!=nullptr && archer->EquipItems[0]->Thumbnail!= nullptr)
            HelmetThum->SetBrushFromTexture(archer->EquipItems[0]->Thumbnail);
        if(archer->EquipItems[1]!=nullptr && archer->EquipItems[1]->Thumbnail != nullptr)
            VestThum->SetBrushFromTexture(archer->EquipItems[1]->Thumbnail);
        if(archer->EquipItems[2]!=nullptr && archer->EquipItems[2]->Thumbnail!= nullptr)
            WeaponeThum->SetBrushFromTexture(archer->EquipItems[2]->Thumbnail);
        if(archer->EquipItems[3]!=nullptr && archer->EquipItems[3]->Thumbnail!= nullptr)
            ShoesThum->SetBrushFromTexture(archer->EquipItems[3]->Thumbnail);
        break;
    }
}

void UHeroesInfoWidget::AddItemsInCharacter(UEquipItem* item)
{
    switch (item->E_Case)
    {
    case 0:
        if(count == 0)
            hero->EquipItems[0]= item;
        if(count == 1)
            maze->EquipItems[0] = item;
        if(count == 2)
            archer->EquipItems[0] = item;
        break;
    case 1:
        if(count == 0)
            hero->EquipItems[1] = item;
        if(count == 1)
            maze->EquipItems[1] = item;
        if(count == 2)
            archer->EquipItems[1] = item;
        break;
    case 2:
        if(count == 0)
            hero->EquipItems[2] = item;
        if(count == 1)
            maze->EquipItems[2] = item;
        if(count == 2)
            archer->EquipItems[2] = item;
        break;
    case 3:
        if(count == 0)
            hero->EquipItems[3] = item;
        if(count == 1)
            maze->EquipItems[3] = item;
        if(count == 2)
            archer->EquipItems[3] = item;
        break;
    }
    item->OwingInventory->RemoveItem(item);
}

void UHeroesInfoWidget::OnSkillBtnClicked()
{
    
}

void UHeroesInfoWidget::OnEquipBtnClicked()
{
   
}

void UHeroesInfoWidget::OnLeftBtnClicked()
{
    count -= 1;
    if (count <= 0)
    {
        count = 0;
    }



    if (count == 0)
    {
        hero->SetActorLocation((FVector(-51560.0, 1330.0, 88.0)));
        maze->SetActorLocation((FVector(-51560.0, 500, 88.0)));
        archer->SetActorLocation((FVector(-51560.0, 600, 88.0)));
       // mesh = hero;

        NameText->SetText(FText::FromString("JAMES"));
        ClassText->SetText(FText::FromString("HERO"));

        //ClassText = "123";
    }
    else if (count == 1)
    {
        hero->SetActorLocation((FVector(-51560.0, 500, 88.0)));
        maze->SetActorLocation((FVector(-51560.0, 1330.0, 88.0)));
        archer->SetActorLocation((FVector(-51560.0, 600, 88.0)));
        //mesh = archer;

        NameText->SetText(FText::FromString("Edgar"));
        ClassText->SetText(FText::FromString("MAGE"));
    }
    else if (count == 2)
    {
        hero->SetActorLocation((FVector(-51560.0, 600, 88.0)));
        maze->SetActorLocation((FVector(-51560.0, 500, 88.0)));
        archer->SetActorLocation((FVector(-51560.0, 1330.0, 88.0)));
        //mesh = maze;

        NameText->SetText(FText::FromString("Alice"));
        ClassText->SetText(FText::FromString("ARCHER"));
    }
    UGameDataSingleton* singleton = UGameDataSingleton::GetInstance();
    if(singleton!=nullptr)
        singleton->MinusUIUnitNum();
    SetItems();
}

void UHeroesInfoWidget::OnRightBtnClicked()
{
    count += 1;
    if (count >= 2)
    {
        count = 2;
    }
    if (count == 0)
    {
        hero->SetActorLocation((FVector(-51560.0, 1330.0, 88.0)));
        maze->SetActorLocation((FVector(-51560.0, 500, 88.0)));
        archer->SetActorLocation((FVector(-51560.0, 600, 88.0)));
        // mesh = hero;

        NameText->SetText(FText::FromString("JAMES"));
        ClassText->SetText(FText::FromString("HERO"));

    }
    else if (count == 1)
    {
        hero->SetActorLocation((FVector(-51560.0, 500, 88.0)));
        maze->SetActorLocation((FVector(-51560.0, 1330.0, 88.0)));
        archer->SetActorLocation((FVector(-51560.0, 600, 88.0)));

        NameText->SetText(FText::FromString("Edgar"));
        ClassText->SetText(FText::FromString("MAGE"));
        //mesh = archer;
    }
    else if (count == 2)
    {
        hero->SetActorLocation((FVector(-51560.0, 600, 88.0)));
        maze->SetActorLocation((FVector(-51560.0, 500, 88.0)));
        archer->SetActorLocation((FVector(-51560.0, 1330.0, 88.0)));


        NameText->SetText(FText::FromString("Alice"));
        ClassText->SetText(FText::FromString("ARCHER"));
        //mesh = maze;
    }
    UGameDataSingleton* singleton = UGameDataSingleton::GetInstance();
    if(singleton!=nullptr)
        singleton->AddUIUnitNum();
    SetItems();
}
