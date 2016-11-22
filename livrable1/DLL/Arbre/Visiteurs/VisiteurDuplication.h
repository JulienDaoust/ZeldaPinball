///////////////////////////////////////////////////////////////////////////
/// @file VisiteurDuplication.h
/// @author Tommy Sagala
/// @date 2014-10-08
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __Visiteur_DUPLICATION_H__
#define __Visiteur_DUPLICATION_H__

#include "VisiteurMouvement.h"
#include "ArbreRenduINF2990.h"
#include "NoeudPortail.h"
#include <vector>


class VisiteurDuplication : public VisiteurMouvement
{
public:
	VisiteurDuplication(ArbreRenduINF2990* arbre, glm::dvec3 centre, std::vector<NoeudAbstrait*> noeuds) { arbre_ = arbre; centre_ = centre; mouvementTotal_ = glm::dvec3(0, 0, 0); noeudsSelectionnes_ = noeuds; type_ = "DUPLICATION"; copies_ = std::vector<NoeudAbstrait*>(); }
	void visite(NoeudAbstrait* objet);
	void visiteAll(glm::dvec3 point);
	void revert();
	std::vector<NoeudAbstrait*> getCopies() { return copies_; }
private:
	int portalId = 0;
	glm::dvec3 centre_;
	std::vector<NoeudAbstrait*> copies_;
	ArbreRenduINF2990* arbre_;
	std::string etat = "creation";
};

#endif