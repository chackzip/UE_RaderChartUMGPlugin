#include "URaderChart.h"

#define LOCTEXT_NAMESPACE "UMG"

void URaderChart::SynchronizeProperties()
{
	Super::SynchronizeProperties();
	MyRaderChart->SetBrush(&Brush);
	MyRaderChart->SetValueArray(ValueArray);
}

void URaderChart::ReleaseSlateResources(bool bReleaseChildren)
{
	MyRaderChart.Reset();
}

void URaderChart::SetValueArray(TArray<float>& InValueArray)
{
	ValueArray = InValueArray;
	if (MyRaderChart)
	{
		MyRaderChart->SetValueArray(ValueArray);
	}
}


#if WITH_EDITOR
const FText URaderChart::GetPaletteCategory()
{
	return LOCTEXT("CustomPaletteCategory", "ExtensionWidget");
}
#endif

TSharedRef<SWidget> URaderChart::RebuildWidget()
{
	MyRaderChart = SNew(SRaderChart)
		.Brush(&Brush)
		.ValueArray(ValueArray);

	return MyRaderChart.ToSharedRef();
}