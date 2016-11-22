///////////////////////////////////////////////////////////////////////////////
/// @file VisiteurTest.h
/// @author Loïc Sauvageau
/// @date 2014-08-01
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#ifndef __Visiteur_TEST_H__
#define __Visiteur_TEST_H__


#include "VisiteurAbstrait.h"
#include <iostream>

class VisiteurTest : public VisiteurAbstrait
{
public:
	VisiteurTest() {}
	virtual ~VisiteurTest() {}

	virtual void visite(NoeudAbstrait* objet);

};

inline void visite(NoeudAbstrait* objet)
{
	std::cout << objet->obtenirType() << std::endl;
}

#endif