////////////////////////////////////////////////
/// @file   Son.cpp
/// @author Tommy Sagala
/// @date   2014-11-21
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////

#include "Son.h"	

////////////////////////////////////////////////////////////////////////
///
/// @fn Son::Son()
///
/// constructeur de la classe son. 
///
/// @retourne aucun(constructuer).
///
////////////////////////////////////////////////////////////////////////
Son::Son() {
	char name[256];
	int carteSon;
	unsigned int version;
	FMOD_SPEAKERMODE speakerMode;
	FMOD_CAPS caps;

	fmodResult = FMOD::System_Create(&system);
	FMODErrorCheck(fmodResult);

	fmodResult = system->getVersion(&version);
	FMODErrorCheck(fmodResult);

	if (version < FMOD_VERSION)
	{
		std::cout << "Error! You are using an old version of FMOD " << version << ". This program requires " << FMOD_VERSION << std::endl;
		return;
	}

	fmodResult = system->getNumDrivers(&carteSon);
	FMODErrorCheck(fmodResult);

	if (carteSon == 0)
	{
		fmodResult = system->setOutput(FMOD_OUTPUTTYPE_NOSOUND);
		FMODErrorCheck(fmodResult);
	}
	else
	{
		fmodResult = system->getDriverCaps(0, &caps, 0, &speakerMode);
		FMODErrorCheck(fmodResult);

		fmodResult = system->setSpeakerMode(speakerMode);
		FMODErrorCheck(fmodResult);

		if (caps & FMOD_CAPS_HARDWARE_EMULATED)
		{
			fmodResult = system->setDSPBufferSize(1024, 10);
			FMODErrorCheck(fmodResult);
		}

		fmodResult = system->getDriverInfo(0, name, 256, 0);
		FMODErrorCheck(fmodResult);

		if (strstr(name, "SigmaTel"))
		{
			fmodResult = system->setSoftwareFormat(48000, FMOD_SOUND_FORMAT_PCMFLOAT, 0, 0, FMOD_DSP_RESAMPLER_LINEAR);
			FMODErrorCheck(fmodResult);
		}
	}

	// Initialise FMOD
	fmodResult = system->init(100, FMOD_INIT_NORMAL, 0);

	if (fmodResult == FMOD_ERR_OUTPUT_CREATEBUFFER)
	{
		fmodResult = system->setSpeakerMode(FMOD_SPEAKERMODE_STEREO);
		FMODErrorCheck(fmodResult);

		fmodResult = system->init(100, FMOD_INIT_NORMAL, 0);
	}
	FMODErrorCheck(fmodResult);
	fmodResult = system->createStream(".//Son/background.wav", FMOD_LOOP_NORMAL, 0, &backgroundSound);
	FMODErrorCheck(fmodResult);
	fmodResult = system->createStream(".//Son/collision.wav", FMOD_DEFAULT, 0, &collision);
	FMODErrorCheck(fmodResult);
	fmodResult = system->createStream(".//Son/collisionCible.wav", FMOD_DEFAULT, 0, &collisionCible);
	FMODErrorCheck(fmodResult);
	fmodResult = system->createStream(".//Son/bonus.wav", FMOD_DEFAULT, 0, &billeBonus);
	FMODErrorCheck(fmodResult);
	fmodResult = system->createStream(".//Son/portal.wav", FMOD_DEFAULT, 0, &portail);
	FMODErrorCheck(fmodResult);
	fmodResult = system->createStream(".//Son/trou.wav", FMOD_DEFAULT, 0, &billeDestruction);
	FMODErrorCheck(fmodResult);
	fmodResult = system->createStream(".//Son/creation.wav", FMOD_DEFAULT, 0, &billeCreation);
	FMODErrorCheck(fmodResult);
	fmodResult = system->createStream(".//Son/palette.wav", FMOD_DEFAULT, 0, &palette);
	FMODErrorCheck(fmodResult);
	fmodResult = system->createStream(".//Son/springUp.wav", FMOD_DEFAULT, 0, &springUp);
	FMODErrorCheck(fmodResult);
	fmodResult = system->createStream(".//Son/springDown.wav", FMOD_DEFAULT, 0, &springDown);
	FMODErrorCheck(fmodResult);
	fmodResult = system->createStream(".//Son/win.wav", FMOD_DEFAULT, 0, &win);
	FMODErrorCheck(fmodResult);


	channel0->setVolume(0.1f);
	channel1->setVolume(0.5f);
	channel2->setVolume(1.0f);
	channel3->setVolume(0.5f);
	channel4->setVolume(0.5f);
	channel5->setVolume(1.0f);
	channel6->setVolume(1.0f);
	channel7->setVolume(1.5f);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn Son::~Son()
///
/// destructeur de son
///
/// @retourne aucun(destructeur).
///
////////////////////////////////////////////////////////////////////////
Son::~Son() {
	FMODErrorCheck(backgroundSound->release());
	FMODErrorCheck(collision->release());
	FMODErrorCheck(billeBonus->release());
	FMODErrorCheck(portail->release());
	FMODErrorCheck(collisionCible->release());
	FMODErrorCheck(billeDestruction->release());
	FMODErrorCheck(billeCreation->release());
	FMODErrorCheck(palette->release());
	FMODErrorCheck(springUp->release());
	FMODErrorCheck(springDown->release());
	FMODErrorCheck(win->release());
	FMODErrorCheck(system->release());
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Son::initialiser()
///
/// initialise la musique de background 
///
/// @retourne aucun.
///
////////////////////////////////////////////////////////////////////////
void Son::initialiser() {
	channel0->setMode(FMOD_LOOP_NORMAL);
	fmodResult = system->playSound(FMOD_CHANNEL_FREE, backgroundSound, false, &channel0);
	FMODErrorCheck(fmodResult);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Son::FMODErrorCheck(FMOD_fmodResult fmodResult)
///
/// verifie si une erreur s'est produite lorsd'un operation de FMODE. 
///
/// @retourne aucun.
///
////////////////////////////////////////////////////////////////////////
void Son::FMODErrorCheck(FMOD_RESULT result)
{
	if (fmodResult != FMOD_OK)
	{
		std::cout << "FMOD error! (" << fmodResult << ") " << FMOD_ErrorString(fmodResult) << std::endl;
		exit(-1);
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Son::mute()
///
/// coupe les sons. 
///
/// @retourne aucun.
///
////////////////////////////////////////////////////////////////////////
void Son::mute() {
	channel0->stop();
	channel1->stop();
	channel2->stop();
	channel3->stop();
	channel4->stop();
	channel5->stop();
	channel6->stop();
	channel7->stop();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Son::sonPortail()
///
/// active le son du portail. 
///
/// @retourne aucun.
///
////////////////////////////////////////////////////////////////////////
void Son::sonPortail() {
	fmodResult = system->playSound(FMOD_CHANNEL_FREE, portail, false, &channel2);
	FMODErrorCheck(fmodResult);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Son::sonBilleBonus()
///
/// active le son de la bille bonus. 
///
/// @retourne aucun.
///
////////////////////////////////////////////////////////////////////////
void Son::sonBilleBonus() {
	fmodResult = system->playSound(FMOD_CHANNEL_FREE, billeBonus, false, &channel2);
	FMODErrorCheck(fmodResult);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Son::sonBilleDestruction()
///
/// active le son de la destruction de bille (collision ave le trou). 
///
/// @retourne aucun.
///
////////////////////////////////////////////////////////////////////////
void Son::sonBilleDestruction() {
	fmodResult = system->playSound(FMOD_CHANNEL_FREE, billeDestruction, false, &channel6);
	FMODErrorCheck(fmodResult);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void Son::sonBilleCreation()
///
/// active le son de la Creation de bille. 
///
/// @retourne aucun.
///
////////////////////////////////////////////////////////////////////////
void Son::sonBilleCreation() {
	fmodResult = system->playSound(FMOD_CHANNEL_FREE, billeCreation, false, &channel7);
	FMODErrorCheck(fmodResult);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Son::sonCollision()
///
/// active le son de collision par default. 
///
/// @retourne aucun.
///
////////////////////////////////////////////////////////////////////////
void Son::sonCollision() {
	fmodResult = system->playSound(FMOD_CHANNEL_FREE, collision, false, &channel1);
	FMODErrorCheck(fmodResult);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Son::sonCollisionCible()
///
/// active le son de collision des cibles 
///
/// @retourne aucun.
///
////////////////////////////////////////////////////////////////////////
void Son::sonCollisionCible() {
	fmodResult = system->playSound(FMOD_CHANNEL_FREE, collisionCible, false, &channel1);
	FMODErrorCheck(fmodResult);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Son::sonPalette()
///
/// active le son de mouvement de palette. 
///
/// @retourne aucun.
///
////////////////////////////////////////////////////////////////////////
void Son::sonPalette() {
	fmodResult = system->playSound(FMOD_CHANNEL_FREE, palette, false, &channel3);
	FMODErrorCheck(fmodResult);
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void Son::sonSpringUp()
///
/// active le son de décompression du ressort. 
///
/// @retourne aucun.
///
////////////////////////////////////////////////////////////////////////
void Son::sonSpringUp() {
	channel4->stop();
	fmodResult = system->playSound(FMOD_CHANNEL_FREE, springUp, false, &channel4);
	FMODErrorCheck(fmodResult);
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void Son::sonSpringDown()
///
/// active le son de compression du ressort. 
///
/// @retourne aucun.
///
////////////////////////////////////////////////////////////////////////
void Son::sonSpringDown() {
	channel4->stop();
	fmodResult = system->playSound(FMOD_CHANNEL_FREE, springDown, false, &channel4);
	FMODErrorCheck(fmodResult);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Son::sonWin()
///
/// active le son de victoire. 
///
/// @retourne aucun.
///
////////////////////////////////////////////////////////////////////////
void Son::sonWin() {
	fmodResult = system->playSound(FMOD_CHANNEL_FREE, win, false, &channel5);
	FMODErrorCheck(fmodResult);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Son::pause()
///
/// met les sons en pause. 
///
/// @retourne aucun.
///
////////////////////////////////////////////////////////////////////////
void Son::pause() {
	bool isPaused;
	channel0->getPaused(&isPaused);
	channel0->setPaused(!isPaused);
	channel1->getPaused(&isPaused);
	channel1->setPaused(!isPaused);
	channel2->getPaused(&isPaused);
	channel2->setPaused(!isPaused);
	channel3->getPaused(&isPaused);
	channel3->setPaused(!isPaused);
	channel4->getPaused(&isPaused);
	channel4->setPaused(!isPaused);
	channel5->getPaused(&isPaused);
	channel5->setPaused(!isPaused);
	channel6->getPaused(&isPaused);
	channel6->setPaused(!isPaused);
	channel7->getPaused(&isPaused);
	channel7->setPaused(!isPaused);
}
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////