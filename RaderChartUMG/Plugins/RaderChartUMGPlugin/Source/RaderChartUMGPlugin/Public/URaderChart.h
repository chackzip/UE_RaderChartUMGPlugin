#pragma once

#include "CoreMinimal.h"


#include "SRaderChart.h"
#include "Components/Widget.h"
#include "URaderChart.generated.h"

UCLASS()
class RADERCHARTUMGPLUGIN_API URaderChart : public UWidget
{
	GENERATED_BODY()
public:
	virtual void SynchronizeProperties() override;
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RaderChart")
	FSlateBrush Brush;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RaderChart")
	FSlateBrush OutlineBrush;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RaderChart")
	TArray<float> ValueArray;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RaderChart")
	float OutlineWidth;

	UFUNCTION(BlueprintCallable, Category = "RaderChart")
	void SetValueArray(TArray<float>& InValueArray);

	UFUNCTION(BlueprintCallable, Category = "RaderChart")
	void SetOutlineWidth(float InOutlineWidth);


#if WITH_EDITOR
	virtual const FText GetPaletteCategory() override;
#endif

protected:
	virtual TSharedRef<SWidget> RebuildWidget() override;
	TSharedPtr<SRaderChart> MyRaderChart;
};