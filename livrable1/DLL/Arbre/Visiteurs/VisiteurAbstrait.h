///////////////////////////////////////////////////////////////////////////
/// @file VisiteurAbstrait.h
/// @author TommySagala
/// @date 2014-09-19
/// @{
///////////////////////////////////////////////////////////////////////////
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