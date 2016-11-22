///////////////////////////////////////////////////////
/// @file Son.h
/// @author Tommy Sagala
/// @date 2014-11-21
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#ifndef __SONS_H__
#define __SONS_H__

#include <iostream>
#include "../../../Commun/Externe/FMOD/include/fmod.hpp"
#include "../../../Commun/Externe/FMOD/include/fmod_errors.h"

class Son
{
public:
	Son();
	~Son();
	void FMODErrorCheck(FMOD_RESULT result);
	void sonPortail();
	void sonBilleBonus();
	void sonBilleDestruction();
	void sonBilleCreation();
	void sonCollision();
	void sonCollisionCible();
	void sonPalette();
	void sonSpringUp();
	void sonSpringDown();
	void sonWin();
	void initialiser();
	void mute();
	void pause();

private:
	FMOD::System *system;
	FMOD::Channel *channel0, *channel1, *channel2, *channel3, *channel4, *channel5, *channel6, *channel7;
	FMOD_RESULT fmodResult;
	FMOD::Sound *backgroundSound, *collision, *collisionCible, *billeBonus, *portail, *billeDestruction, *billeCreation, *palette, *springUp, *springDown, *win;
};
#endif // __SONS_H__

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
