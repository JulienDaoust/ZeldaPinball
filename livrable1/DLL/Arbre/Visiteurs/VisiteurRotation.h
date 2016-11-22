///////////////////////////////////////////////////////////////////////////
/// @file VisiteurRotation.h
/// @author Tommy Sagala
/// @date 2014-10-03
/// @{
///////////////////////////////////////////////////////////////////////////
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