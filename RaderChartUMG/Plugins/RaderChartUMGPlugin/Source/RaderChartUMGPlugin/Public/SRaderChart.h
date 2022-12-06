#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

class RADERCHARTUMGPLUGIN_API SRaderChart : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SRaderChart)
	{}
	SLATE_ARGUMENT(FSlateBrush*, Brush)
	SLATE_ARGUMENT(TArray<float>, ValueArray)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
	virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect,
	FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle,
	bool bParentEnabled) const override;

	void SetValueArray(TArray<float>& InValueArray);
	void SetBrush(FSlateBrush* InBrush);

protected:
	FInvalidatableBrushAttribute Brush;
	TArray<float> ValueArray;
};