///////////////////////////////////////////////////////////////////////////
/// @file VisiteurAbstyrait.h
/// @author ToLoFr
/// @date 2014-09-19
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __VISITEUR_TEST_H__
#define __VISITEUR_TEST_H__


#include "VisiteurAbstrait.h"
#include <iostream>

class VisiteurTest : public VisiteurAbstrait
{
public:
	VisiteurTest() {}
	virtual ~VisiteurTest() {}

	virtual void visite(NoeudAbstrait* objet);

};

inline void Visite(NoeudAbstrait* objet)
{
	std::cout << objet->obtenirType() << std::endl;
}

#endif