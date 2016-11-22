///////////////////////////////////////////////////////////////////////////////
/// @file VisiteurCollision.h
/// @author Loïc Sauvageau
/// @date 2014-08-01
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#ifndef __Visiteur_COLLISION_H__
#define __Visiteur_COLLISION_H__

#include "VisiteurAbstrait.h"
#include "AideCollision.h"
#include "QuadTree.h"
#include "NoeudBille.h"
#include "NoeudButoirCirculaire.h"
#include "NoeudCible.h"
#include "../ArbreRenduINF2990.h"

class VisiteurCollision : public VisiteurAbstrait
{
public:
	VisiteurCollision(){ ; }
	void dectectionCollisionGlobale();
	void visite(NoeudAbstrait* objet);
	void traiterCollision(NoeudAbstrait* noeud1, NoeudAbstrait* noeud2);
	void dectectionCollision(std::vector<NoeudAbstrait*> listeNoeud);

private:
	void dectectionCollisionQuadTree(QuadTree* quad);
	std::list<NoeudAbstrait*>aEffacer;
	NoeudAbstrait* noeudEnContact_;
	aidecollision::DetailsCollision details_;
};

#endif