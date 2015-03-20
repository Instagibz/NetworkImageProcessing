#include "StdAfx.h"
#include <conio.h>

GlobalStore			GlobalData;
AudioBufferStore	AudioStore;

void main()
{
	LoadSettingsFromFile( "../VideoEncodeOverNetworkEncoder/Config.txt" );

	AudioStore.SetCacheDuration( 10 );
//	AudioStore.DebugForceStopRecordSeconds = 20;

	ClientNetwork *NetworkReader = new ClientNetwork( GlobalData.AudioNetworkIP, GlobalData.AudioNetworkPort );

	if( NetworkReader->ConnectSocket == INVALID_SOCKET )
	{
		printf("could not connect to server\n");
		return;
	}

	GlobalData.ThreadIsRunning = 1;

	printf("Started network reader\n");
	StartDataFeederThread( NetworkReader, &AudioStore );

	printf("Started playback\n");
	int AntiDeadLock = 10;
	while( AudioStore.GetAvailableFrames() == 0 && AntiDeadLock > 0 )
	{
		Sleep( 10 );
		AntiDeadLock--;
	}
	if( AudioStore.GetAvailableFrames() > 0 )
	{
		printf("Received initial packets. Forcing latency %d \n", GlobalData.ForcedAudioLatency);
		Sleep( GlobalData.ForcedAudioLatency );	//to be able to make it echo echo echo echo
		_beginthread( PlayAudioStream, 0, (void*)NULL );
	}

	printf("press any key to exit\n");
	_getch();
	GlobalData.ThreadIsRunning = 2;
	NetworkReader->CloseConnection();
	Sleep( 100 );

	AntiDeadLock = 10;
	while( GlobalData.ThreadsAliveCount > 0 && AntiDeadLock > 0 )
	{
		Sleep( 1000 );
		AntiDeadLock--;
	}

	printf("Done recv / playback\n");

	delete NetworkReader;
}