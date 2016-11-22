///////////////////////////////////////////////////////////////////////////////
/// @file VisiteurTranslation.h
/// @author Loïc Sauvageau
/// @date 2014-08-01
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#ifndef __Visiteur_TRANSLATION_H__
#define __Visiteur_TRANSLATION_H__

#include "VisiteurMouvement.h"
#include <vector>


class VisiteurTranslation : public VisiteurMouvement
{
public:
	VisiteurTranslation(std::vector<NoeudAbstrait*> noeuds) { mouvementTotal_ = glm::dvec3(); noeudsSelectionnes_ = noeuds; type_ = "TRANSLATION"; }
	void visite(NoeudAbstrait* objet);
	void visiteAll(glm::dvec3 translation);
	void revert();
};

#endif