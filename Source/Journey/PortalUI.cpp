// Fill out your copyright notice in the Description page of Project Settings.


#include "PortalUI.h"

void UPortalUI::NativeConstruct()
{
	Super::NativeConstruct();
}

void UPortalUI::AddVillage(const FString& VillageName,const FVector& pos,const FVector& savedpos)
{
	VillageInfo = CreateWidget<UVillageInfo>(GetWorld(), VillageInfoClass);
	VillageInfo->SetUpText(VillageName,pos,savedpos);
	
	VillageBox->AddChildToWrapBox(VillageInfo);
}
