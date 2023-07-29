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
    NowHP->SetText(FText::FromString(FString::FromInt(hero->nowHP)));
    MaxHP->SetText(FText::FromString(FString::FromInt(hero->maxHP)));
    NowMP->SetText(FText::FromString(FString::FromInt(hero->nowMP)));
    MaxMP->SetText(FText::FromString(FString::FromInt(hero->maxMP)));

    HPBar->SetPercent(maze->nowHP / maze->maxHP);
    MPBar->SetPercent(maze->nowMP / maze->maxMP);
    setArmour(0);
    Power->SetText(FText::FromString(FString::FromInt(hero->power)));
}

void UHeroesInfoWidget::SetItems()
{
    HelmetThum->SetBrushFromTexture(Thumnail);
    VestThum->SetBrushFromTexture(Thumnail);
    WeaponeThum->SetBrushFromTexture(Thumnail);
    ShoesThum->SetBrushFromTexture(Thumnail);
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
        {
            hero->EquipItems[0]= item;
            item->Owner = hero;
            item->bEquip = true;
            //hero->Armour += item->Armour;
            Armour->SetText(FText::FromString(FString::FromInt(hero->Armour)));
        }
        if(count == 1)
        {
            maze->EquipItems[0] = item;
            item->Owner = maze;
            item->bEquip = true;
            //maze->Armour += item->Armour;
            Armour->SetText(FText::FromString(FString::FromInt(maze->Armour)));
        }
        if(count == 2)
        {
            archer->EquipItems[0] = item;
            item->Owner = archer;
            item->bEquip = true;
            //archer->Armour += item->Armour;
            Armour->SetText(FText::FromString(FString::FromInt(archer->Armour)));
        }
        break;
    case 1:
        if(count == 0)
        {
            hero->EquipItems[1] = item;
            item->Owner = hero;
            item->bEquip = true;
            //hero->Armour += item->Armour;
            Armour->SetText(FText::FromString(FString::FromInt(hero->Armour)));
        }
        if(count == 1)
        {
            maze->EquipItems[1] = item;
            item->Owner = maze;
            item->bEquip = true;
            //maze->Armour += item->Armour;
            Armour->SetText(FText::FromString(FString::FromInt(maze->Armour)));
        }
        if(count == 2)
        {
            archer->EquipItems[1] = item;
            item->Owner = archer;
            item->bEquip = true;
            //archer->Armour += item->Armour;
            Armour->SetText(FText::FromString(FString::FromInt(archer->Armour)));
        }
        break;
    case 2:
        if(count == 0 && item->ItemDisplayName.ToString() == "Sword")
        {
            hero->EquipItems[2] = item;
            item->Owner = hero;
            item->bEquip = true;
            //hero->Armour += item->Armour;
            Power->SetText(FText::FromString(FString::FromInt(hero->power)));
        }
        if(count == 1 && item->ItemDisplayName.ToString() == "Staff")
        {
            maze->EquipItems[2] = item;
            item->Owner = maze;
            item->bEquip = true;
            //maze->Armour += item->Armour;
            Power->SetText(FText::FromString(FString::FromInt(maze->power)));
        }
        if(count == 2 && item->ItemDisplayName.ToString() == "Arrow")
        {
            archer->EquipItems[2] = item;
            item->Owner = archer;
            item->bEquip = true;
            //archer->Armour += item->Armour;
            Power->SetText(FText::FromString(FString::FromInt(archer->power)));
        }
        break;
    case 3:
        if(count == 0)
        {
            hero->EquipItems[3] = item;
            item->Owner = hero;
            item->bEquip = true;
            //hero->Armour += item->Armour;
            Armour->SetText(FText::FromString(FString::FromInt(hero->Armour)));
        }
        if(count == 1)
        {
            maze->EquipItems[3] = item;
            item->Owner = maze;
            item->bEquip = true;
            //maze->Armour += item->Armour;
            Armour->SetText(FText::FromString(FString::FromInt(maze->Armour)));
        }
        if(count == 2)
        {
            archer->EquipItems[3] = item;
            item->Owner = archer;
            item->bEquip = true;
            //archer->Armour += item->Armour;
            Armour->SetText(FText::FromString(FString::FromInt(archer->Armour)));
        }
        break;
    }
    if(item->bEquip)
    {
        item->OwingInventory->RemoveItem(item);
        setArmour(count);
    }
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


    setArmour(count);
    if (count == 0)
    {
        hero->SetActorLocation((FVector(-51560.0, 1330.0, 88.0)));
        maze->SetActorLocation((FVector(-51560.0, 500, 88.0)));
        archer->SetActorLocation((FVector(-51560.0, 600, 88.0)));
       // mesh = hero;

        NameText->SetText(FText::FromString("JAMES"));
        ClassText->SetText(FText::FromString("HERO"));
        NowHP->SetText(FText::FromString(FString::FromInt(hero->nowHP)));
        MaxHP->SetText(FText::FromString(FString::FromInt(hero->maxHP)));
        NowMP->SetText(FText::FromString(FString::FromInt(hero->nowMP)));
        MaxMP->SetText(FText::FromString(FString::FromInt(hero->maxMP)));
        
        HPBar->SetPercent(hero->nowHP / hero->maxHP);
        MPBar->SetPercent(hero->nowMP / hero->maxMP);
        Armour->SetText(FText::FromString(FString::FromInt(hero->Armour)));
        Power->SetText(FText::FromString(FString::FromInt(hero->power)));
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
        NowHP->SetText(FText::FromString(FString::FromInt(maze->nowHP)));
        MaxHP->SetText(FText::FromString(FString::FromInt(maze->maxHP)));
        NowMP->SetText(FText::FromString(FString::FromInt(maze->nowMP)));
        MaxMP->SetText(FText::FromString(FString::FromInt(maze->maxMP)));
        Armour->SetText(FText::FromString(FString::FromInt(maze->Armour)));

        HPBar->SetPercent(maze->nowHP / maze->maxHP);
        MPBar->SetPercent(maze->nowMP / maze->maxMP);
        Power->SetText(FText::FromString(FString::FromInt(maze->power)));
    }
    else if (count == 2)
    {
        hero->SetActorLocation((FVector(-51560.0, 600, 88.0)));
        maze->SetActorLocation((FVector(-51560.0, 500, 88.0)));
        archer->SetActorLocation((FVector(-51560.0, 1330.0, 88.0)));
        //mesh = maze;

        NameText->SetText(FText::FromString("Alice"));
        ClassText->SetText(FText::FromString("ARCHER"));

        NowHP->SetText(FText::FromString(FString::FromInt(archer->nowHP)));
        MaxHP->SetText(FText::FromString(FString::FromInt(archer->maxHP)));
        NowMP->SetText(FText::FromString(FString::FromInt(archer->nowMP)));
        MaxMP->SetText(FText::FromString(FString::FromInt(archer->maxMP)));

        HPBar->SetPercent(archer->nowHP / archer->maxHP);
        MPBar->SetPercent(archer->nowMP / archer->maxMP);
        Armour->SetText(FText::FromString(FString::FromInt(archer->Armour)));
        Power->SetText(FText::FromString(FString::FromInt(archer->power)));
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
    setArmour(count);
    if (count == 0)
    {
        hero->SetActorLocation((FVector(-51560.0, 1330.0, 88.0)));
        maze->SetActorLocation((FVector(-51560.0, 500, 88.0)));
        archer->SetActorLocation((FVector(-51560.0, 600, 88.0)));
        // mesh = hero;

        NameText->SetText(FText::FromString("JAMES"));
        ClassText->SetText(FText::FromString("HERO"));
        NowHP->SetText(FText::FromString(FString::FromInt(hero->nowHP)));
        MaxHP->SetText(FText::FromString(FString::FromInt(hero->maxHP)));
        NowMP->SetText(FText::FromString(FString::FromInt(hero->nowMP)));
        MaxMP->SetText(FText::FromString(FString::FromInt(hero->maxMP)));
        
        HPBar->SetPercent(hero->nowHP / hero->maxHP);
        MPBar->SetPercent(hero->nowMP / hero->maxMP);
        Armour->SetText(FText::FromString(FString::FromInt(hero->Armour)));
        Power->SetText(FText::FromString(FString::FromInt(hero->power)));
    }
    else if (count == 1)
    {
        hero->SetActorLocation((FVector(-51560.0, 500, 88.0)));
        maze->SetActorLocation((FVector(-51560.0, 1330.0, 88.0)));
        archer->SetActorLocation((FVector(-51560.0, 600, 88.0)));

        NameText->SetText(FText::FromString("Edgar"));
        ClassText->SetText(FText::FromString("MAGE"));
        NowHP->SetText(FText::FromString(FString::FromInt(maze->nowHP)));
        MaxHP->SetText(FText::FromString(FString::FromInt(maze->maxHP)));
        NowMP->SetText(FText::FromString(FString::FromInt(maze->nowMP)));
        MaxMP->SetText(FText::FromString(FString::FromInt(maze->maxMP)));

        HPBar->SetPercent(maze->nowHP / maze->maxHP);
        MPBar->SetPercent(maze->nowMP / maze->maxMP);
        Armour->SetText(FText::FromString(FString::FromInt(maze->Armour)));
        Power->SetText(FText::FromString(FString::FromInt(maze->power)));
        //mesh = archer;
    }
    else if (count == 2)
    {
        hero->SetActorLocation((FVector(-51560.0, 600, 88.0)));
        maze->SetActorLocation((FVector(-51560.0, 500, 88.0)));
        archer->SetActorLocation((FVector(-51560.0, 1330.0, 88.0)));


        NameText->SetText(FText::FromString("Alice"));
        ClassText->SetText(FText::FromString("ARCHER"));
        NowHP->SetText(FText::FromString(FString::FromInt(archer->nowHP)));
        MaxHP->SetText(FText::FromString(FString::FromInt(archer->maxHP)));
        NowMP->SetText(FText::FromString(FString::FromInt(archer->nowMP)));
        MaxMP->SetText(FText::FromString(FString::FromInt(archer->maxMP)));

        HPBar->SetPercent(archer->nowHP / archer->maxHP);
        MPBar->SetPercent(archer->nowMP / archer->maxMP);
        Armour->SetText(FText::FromString(FString::FromInt(archer->Armour)));
        Power->SetText(FText::FromString(FString::FromInt(archer->power)));
        //mesh = maze;
    }
    UGameDataSingleton* singleton = UGameDataSingleton::GetInstance();
    if(singleton!=nullptr)
        singleton->AddUIUnitNum();
    SetItems();
}

void UHeroesInfoWidget::setArmour(int num)
{
    switch (num)
    {
    case 0://hero
        {
            int armour=0;
            hero->Armour = 15;//basic armour
            hero->power = 10 + hero->Upgrade; //basic power;
            for(int i=0;i<4;++i)
            {
                if(hero->EquipItems[i] != nullptr && i != 2)
                {
                    armour += hero->EquipItems[i]->Armour;
                }
                if(hero->EquipItems[i] != nullptr && i == 2)
                {
                    hero->power+=hero->EquipItems[i]->Armour;
                }
            }
            armour+= hero->Armour;
            Armour->SetText(FText::FromString(FString::FromInt(armour)));
            Power->SetText(FText::FromString(FString::FromInt(hero->power)));
            hero->Armour = armour;
        }
        break;
    case 1://maze
        {
            int armour=0;
            maze->Armour = 5;//basic armour
            maze->power = 10 + maze->Upgrade; //basic power;
            for(int i=0;i<4;++i)
            {
                if(maze->EquipItems[i] != nullptr && i != 2)
                {
                    armour += maze->EquipItems[i]->Armour;
                }
                if(maze->EquipItems[i] != nullptr && i == 2)
                {
                    maze->power+=maze->EquipItems[i]->Armour;
                }
            }
            armour+= maze->Armour;
            Armour->SetText(FText::FromString(FString::FromInt(armour)));
            Power->SetText(FText::FromString(FString::FromInt(maze->power)));
            maze->Armour = armour;
        }
        break;
    case 2://archer
        {
            int armour=0;
            archer->Armour = 3;//basic armour
            archer->power = 10 + archer->Upgrade; //basic power;
            for(int i=0;i<4;++i)
            {
                if(archer->EquipItems[i] != nullptr && i != 2)
                {
                    armour += archer->EquipItems[i]->Armour;
                }
                if(archer->EquipItems[i] != nullptr && i == 2)
                {
                    archer->power+=archer->EquipItems[i]->Armour;
                }
            }
            armour+= archer->Armour;
            Armour->SetText(FText::FromString(FString::FromInt(armour)));
            Power->SetText(FText::FromString(FString::FromInt(archer->power)));
            archer->Armour = armour;
        }
        break;
    }
}

bool UHeroesInfoWidget::UsePotion()
{
    switch (count)
    {
    case 0://hero
        {
            if(hero->nowHP >= hero->maxHP)
                return false;
           hero->nowHP += 10;
            HPBar->SetPercent(hero->nowHP / hero->maxHP);
            NowHP->SetText(FText::FromString(FString::FromInt(hero->nowHP)));
        }
        break;
    case 1://maze
        {
            if(maze->nowHP >= maze->maxHP)
                return false;
            maze->nowHP += 10;
            HPBar->SetPercent(maze->nowHP / maze->maxHP);
            NowHP->SetText(FText::FromString(FString::FromInt(maze->nowHP)));
        }
        break;
    case 2://archer
        {
            if(archer->nowHP >= archer->maxHP)
                return false;
            archer->nowHP += 10;
            HPBar->SetPercent(archer->nowHP / archer->maxHP);
            NowHP->SetText(FText::FromString(FString::FromInt(archer->nowHP)));
        }
        break;
    }
    return true;
}
