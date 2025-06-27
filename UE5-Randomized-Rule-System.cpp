#include "RulesGameMode.h"

void ARulesGameMode::GetRules()
{
	FVector SpawnLoc = FVector(-2830.0f, 0.0f, 110.0f);
	FRotator SpawnRot = FRotator::ZeroRotator;

	int MaxDifficultyRating = 0;
	int CurrentDifficultyRating = 0;
	int GMDifficulty = 4; // Scale of 10; if changed, update the Threshold Difficulty Calculation
	int RulesSlots = 6;
	int ThresholdRange = 0;
	int DifficultyMinValue = 0;
	float DifficultyThreshold = 0.0f;
	float ThresholdDifficultyScale = 10.0f - GMDifficulty;

	// Calculate minimum difficulty value, clamped between 1 and GMDifficulty
	DifficultyMinValue = FMath::Clamp(FMath::FloorToInt(GMDifficulty * 0.8f), 1, GMDifficulty);

	// Calculate difficulty threshold for even GMDifficulty values
	if (GMDifficulty % 2 == 0)
	{
		DifficultyThreshold = ((ThresholdDifficultyScale / 2.0f) * 5.0f) / 100.0f;
	}

	if (RulesData)
	{
		// Calculate max possible difficulty rating
		MaxDifficultyRating = (GMDifficulty * RulesSlots) / 2;

		// Lambda: randomize and process rules, assigning aggression and occurrence values
		auto ProcessRules = [&]() {
			CurrentDifficultyRating = 0;
			RulesList.Empty();

			for (FRulesStruct& Rule : RulesData->Items)
			{
				if (Rule.object)
				{
					Rule.Aggression = FMath::RandRange(DifficultyMinValue, GMDifficulty);
					Rule.Occurrence = FMath::RandRange(DifficultyMinValue, GMDifficulty);
					CurrentDifficultyRating += Rule.Aggression + Rule.Occurrence;
					RulesList.Add(Rule);

					if (RulesList.Num() >= RulesSlots)
					{
						break;
					}
				}
			}
			};

		// Lambda: shuffle rules in RulesData
		auto ShuffleRules = [&]() {
			if (RulesData->Items.Num() > 1)
			{
				const int32 LastIndex = RulesData->Items.Num() - 1;
				for (int32 i = LastIndex; i > 0; --i)
				{
					int32 SwapIndex = FMath::RandRange(0, i);
					if (i != SwapIndex)
					{
						RulesData->Items.Swap(i, SwapIndex);
					}
				}
			}
			};

		ThresholdRange = FMath::RoundToInt(DifficultyThreshold * MaxDifficultyRating);

		// Repeat until the total difficulty rating falls within the desired range
		while (!(CurrentDifficultyRating >= (MaxDifficultyRating - ThresholdRange) && CurrentDifficultyRating <= MaxDifficultyRating))
		{
			ShuffleRules();
			ProcessRules();
		}

		// Spawn selected rules into the world
		for (const FRulesStruct& Rule : RulesList)
		{
			GetWorld()->SpawnActor<AActor>(Rule.object, SpawnLoc, SpawnRot);
		}
	}
}
