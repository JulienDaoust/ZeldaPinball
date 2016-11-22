///////////////////////////////////////////////////////////////////////////
/// @file VisiteurAbstyrait.h
/// @author ToLoFr
/// @date 2014-09-19
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __VISITEUR_ABSTRAIT_H__
#define __VISITEUR_ABSTRAIT_H__

#include "../Noeuds/NoeudAbstrait.h"

class NoeudAbstrait;

class VisiteurAbstrait
{
public:
	VisiteurAbstrait() {}
	virtual ~VisiteurAbstrait() {}

	virtual void Visite(NoeudAbstrait* objet) = 0;

};

#endif