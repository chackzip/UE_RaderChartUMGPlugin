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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
	FSlateBrush Brush;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Appearance")
	TArray<float> ValueArray;

	UFUNCTION(BlueprintCallable, Category = "Appearance")
	void SetValueArray(TArray<float>& InValueArray);

#if WITH_EDITOR
	virtual const FText GetPaletteCategory() override;
#endif

protected:
	virtual TSharedRef<SWidget> RebuildWidget() override;
	TSharedPtr<SRaderChart> MyRaderChart;
};