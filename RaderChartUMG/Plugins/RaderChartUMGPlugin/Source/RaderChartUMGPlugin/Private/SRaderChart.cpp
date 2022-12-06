#include "SRaderChart.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SRaderChart::Construct(const FArguments& InArgs)
{
	Brush = FInvalidatableBrushAttribute(InArgs._Brush);
	ValueArray = InArgs._ValueArray;
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

int32 SRaderChart::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect,
	FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle,
	bool bParentEnabled) const
{
	if (ValueArray.Num() < 3)
	{
		return LayerId;
	}

	const FVector2D Pos = AllottedGeometry.GetAbsolutePosition();
	const FVector2D Size = AllottedGeometry.GetAbsoluteSize();
	const FVector2f Center = FVector2f(Pos.X, Pos.Y) + (0.5f * FVector2f(Size.X,Size.Y));
	const float Radius = FMath::Min(Size.X, Size.Y) * 0.5f;
	const float Deg = 360 / ValueArray.Num();

	const FSlateBrush* SlateBrush = Brush.GetImage().Get();
	FLinearColor LinearColor = /*ColorAndOpacity.Get() * */InWidgetStyle.GetColorAndOpacityTint() * SlateBrush->GetTint(InWidgetStyle);
	FColor FinalColorAndOpacity = LinearColor.ToFColor(true);

	TArray<FSlateVertex> Vertices;
	Vertices.Reserve(ValueArray.Num() + 1);

	// Add center vertex
	Vertices.AddZeroed();
	FSlateVertex& CenterVertex = Vertices.Last();

	CenterVertex.Position = FVector2f(Center.X, Center.Y);
	CenterVertex.Color = FinalColorAndOpacity;

	// Add edge vertices
	for (int i = 0; i < ValueArray.Num(); i++)
	{
		const float CurrentRad = FMath::DegreesToRadians(Deg * i + 90);
		FVector2f VertPos(FMath::Cos(CurrentRad), -FMath::Sin(CurrentRad));

		Vertices.AddZeroed();
		FSlateVertex& OuterVert = Vertices.Last();

		OuterVert.Position = Center + VertPos * Radius * ValueArray[i];
		OuterVert.Color = FinalColorAndOpacity;
	}

	TArray<SlateIndex> Indices;
	for (int i = 1; i <= ValueArray.Num(); i++)
	{
		Indices.Add(0);
		Indices.Add(i);

		if (ValueArray.Num() < i + 1)
		{
			Indices.Add(1);
		}
		else
		{
			Indices.Add(i + 1);
		}
	}

	const FSlateResourceHandle Handle = FSlateApplication::Get().GetRenderer()->GetResourceHandle(*SlateBrush);
	FSlateDrawElement::MakeCustomVerts(
		OutDrawElements,
		LayerId,
		Handle,
		Vertices,
		Indices,
		nullptr,
		0,
		0
	);
	return LayerId;
}

void SRaderChart::SetBrush(FSlateBrush* InBrush)
{
	Brush.SetImage(*this, InBrush);
}

void SRaderChart::SetValueArray(TArray<float>& InValueArray)
{
	ValueArray = InValueArray;
}