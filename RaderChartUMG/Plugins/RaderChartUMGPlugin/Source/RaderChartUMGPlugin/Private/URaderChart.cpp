#include "URaderChart.h"

#define LOCTEXT_NAMESPACE "UMG"

void URaderChart::SynchronizeProperties()
{
	Super::SynchronizeProperties();
	MyRaderChart->SetBrush(&Brush);
	MyRaderChart->SetValueArray(ValueArray);
	MyRaderChart->SetOutlineBrush(&OutlineBrush);
	MyRaderChart->SetOutlineWidth(OutlineWidth);
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

void URaderChart::SetOutlineWidth(float InOutlineWidth)
{
	OutlineWidth = InOutlineWidth;
	if (MyRaderChart)
	{
		MyRaderChart->SetOutlineWidth(OutlineWidth);
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
		.ValueArray(ValueArray)
		.OutlineWidth(OutlineWidth)
		.OutlineBrush(&OutlineBrush);

	return MyRaderChart.ToSharedRef();
}