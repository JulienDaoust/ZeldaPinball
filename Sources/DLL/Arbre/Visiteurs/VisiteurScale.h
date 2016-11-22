///////////////////////////////////////////////////////////////////////////////
/// @file VisiteurScale.h
/// @author Loïc Sauvageau
/// @date 2014-08-01
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#ifndef __Visiteur_SCALE_H__
#define __Visiteur_SCALE_H__

#include "VisiteurMouvement.h"
#include <vector>
#include <map>


class VisiteurScale : public VisiteurMouvement
{
public:
	VisiteurScale(glm::dvec3 point, std::vector<NoeudAbstrait*> noeuds) { pointPrecedent_ = point; noeudsSelectionnes_ = noeuds; type_ = "SCALE"; }
	void visite(NoeudAbstrait* objet);
	void visiteAll(glm::dvec3 point);
	void revert();
	void setInitialScales();
private:
	glm::dvec3 pointPrecedent_;
	glm::dvec3 scale_;
	std::map<NoeudAbstrait*, glm::dvec3> initialScales_;
	bool upordown = true;
};

#endif