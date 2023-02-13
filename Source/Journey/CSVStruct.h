#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "CSVStruct.generated.h"

USTRUCT(BlueprintType)
struct FCSVStruct : public FTableRowBase
{
public:
	GENERATED_BODY()

	UPROPERTY()
	string fName;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float HP;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float MP;
};