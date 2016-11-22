///////////////////////////////////////////////////////////////////////////////
/// @file VisiteurAbstrait.h
/// @author Loïc Sauvageau
/// @date 2014-08-01
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#ifndef __Visiteur_ABSTRAIT_H__
#define __Visiteur_ABSTRAIT_H__

#include "../Noeuds/NoeudAbstrait.h"

class NoeudAbstrait;

class VisiteurAbstrait
{
public:
	VisiteurAbstrait() {}
	virtual ~VisiteurAbstrait() {}

	virtual void visite(NoeudAbstrait* objet) = 0;

};

#endif