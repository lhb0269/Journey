// Fill out your copyright notice in the Description page of Project Settings.


#include "HeroesInfoWidget.h"

void UHeroesInfoWidget::NativeConstruct()
{
	Super::NativeConstruct();
    
    SkillBtn->OnClicked.AddDynamic(this, &UHeroesInfoWidget::OnSkillBtnClicked);
    EquipBtn->OnClicked.AddDynamic(this, &UHeroesInfoWidget::OnEquipBtnClicked);

    LeftChangeBtn->OnClicked.AddDynamic(this, &UHeroesInfoWidget::OnLeftBtnClicked);
    RightChangeBtn->OnClicked.AddDynamic(this, &UHeroesInfoWidget::OnRightBtnClicked);


    //TextWidget->SetText(FText::FromString(Text));
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
}

void UHeroesInfoWidget::OnRightBtnClicked()
{
}
