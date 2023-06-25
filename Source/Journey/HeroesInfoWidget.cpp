// Fill out your copyright notice in the Description page of Project Settings.


#include "HeroesInfoWidget.h"
#include "GameManager.h"

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

    ClassText->SetText(FText::FromString("HERO"));
   // TextWidget->SetText(FText::FromString(Text));

}

void UHeroesInfoWidget::OnSkillBtnClicked()
{
    if (SkillBG != nullptr)
    {
        SkillBG->SetVisibility(ESlateVisibility::Visible);
    }

    if (EquipBG != nullptr)
    {
        EquipBG->SetVisibility(ESlateVisibility::Hidden);
    }
}

void UHeroesInfoWidget::OnEquipBtnClicked()
{
    if (SkillBG != nullptr)
    {
        SkillBG->SetVisibility(ESlateVisibility::Hidden);
    }

    if (EquipBG != nullptr)
    {
        EquipBG->SetVisibility(ESlateVisibility::Visible);
    }
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
}
