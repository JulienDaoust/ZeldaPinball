///////////////////////////////////////////////////////////////////////////////
/// @file VisiteurRotation.h
/// @author Loïc Sauvageau
/// @date 2014-08-01
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#ifndef __Visiteur_ROTATION_H__
#define __Visiteur_ROTATION_H__

#include "VisiteurMouvement.h"
#include <vector>


class VisiteurRotation : public VisiteurMouvement
{
public:
	VisiteurRotation(glm::dvec3 centre, std::vector<NoeudAbstrait*> noeuds) { centre_ = centre; mouvementTotal_ = glm::dvec3(0,0,0); noeudsSelectionnes_ = noeuds; type_ = "ROTATION"; }
	void visite(NoeudAbstrait* objet);
	void visiteAll(glm::dvec3 angle);
	void revert();
private:
	glm::dvec3 centre_;
};

#endif