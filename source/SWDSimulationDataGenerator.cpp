#include "SWDSimulationDataGenerator.h"
#include "SWDAnalyzerSettings.h"

#include <AnalyzerHelpers.h>

SWDSimulationDataGenerator::SWDSimulationDataGenerator()
{
}

SWDSimulationDataGenerator::~SWDSimulationDataGenerator()
{
}

void SWDSimulationDataGenerator::Initialize( U32 simulation_sample_rate, SWDAnalyzerSettings* settings )
{
	mSimulationSampleRateHz = simulation_sample_rate;
	mSettings = settings;

	mSWDIOData = mSimulationGroup.Add(settings->mSWDIOChannel, mSimulationSampleRateHz, BIT_LOW);
	mSWCLKData = mSimulationGroup.Add(settings->mSWCLKChannel, mSimulationSampleRateHz, BIT_LOW);
}

U32 SWDSimulationDataGenerator::GenerateSimulationData( U64 largest_sample_requested, U32 sample_rate, SimulationChannelDescriptor** simulation_channel )
{
	U64 adjusted_largest_sample_requested = AnalyzerHelpers::AdjustSimulationTargetSample( largest_sample_requested, sample_rate, mSimulationSampleRateHz );

	// TODO: generate actual data
	mSWDIOData->Advance(adjusted_largest_sample_requested - mSWDIOData->GetCurrentSampleNumber());
	mSWCLKData->Advance(adjusted_largest_sample_requested - mSWCLKData->GetCurrentSampleNumber());

	*simulation_channel = mSimulationGroup.GetArray();
	return mSimulationGroup.GetCount();
}

#if 0
void SWDSimulationDataGenerator::CreateSerialByte()
{
	U32 samples_per_bit = mSimulationSampleRateHz / mSettings->mBitRate;

	U8 byte = mSerialText[ mStringIndex ];
	mStringIndex++;
	if( mStringIndex == mSerialText.size() )
		mStringIndex = 0;

	//we're currenty high
	//let's move forward a little
	mSerialSimulationData.Advance( samples_per_bit * 10 );

	mSerialSimulationData.Transition();  //low-going edge for start bit
	mSerialSimulationData.Advance( samples_per_bit );  //add start bit time

	U8 mask = 0x1 << 7;
	for( U32 i=0; i<8; i++ )
	{
		if( ( byte & mask ) != 0 )
			mSerialSimulationData.TransitionIfNeeded( BIT_HIGH );
		else
			mSerialSimulationData.TransitionIfNeeded( BIT_LOW );

		mSerialSimulationData.Advance( samples_per_bit );
		mask = mask >> 1;
	}

	mSerialSimulationData.TransitionIfNeeded( BIT_HIGH ); //we need to end high

	//lets pad the end a bit for the stop bit:
	mSerialSimulationData.Advance( samples_per_bit );
}
#endif
