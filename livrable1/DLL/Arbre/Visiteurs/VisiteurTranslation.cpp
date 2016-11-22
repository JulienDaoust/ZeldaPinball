////////////////////////////////////////////////
/// @file   VisiteurTranslation.cpp
/// @author Tommy Sagala
/// @date   2014-10-03
///
/// @{
////////////////////////////////////////////////

#include "VisiteurTranslation.h"
#include "Utilitaire.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurTranslation::visite(NoeudAbstrait* objet);
///
/// @param[in] NoeudAbstrait* objet : objet a visiter
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurTranslation::visite(NoeudAbstrait* objet)
{
	objet->assignerPositionRelative(objet->obtenirPositionRelative() + mouvement_);

}
////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurTranslation::visiteAll(glm::dvec3 nouveauCentre);
///
/// @param[in] glm::dvec3 : nouveau centre des objets.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurTranslation::visiteAll(glm::dvec3 translation)
{
	mouvement_ = translation;
	mouvementTotal_ += translation;
	for each(NoeudAbstrait* noeuds in noeudsSelectionnes_)
	{
		noeuds->accepte(this);
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurTranslation::Revert();
///
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurTranslation::revert()
{
	mouvement_ = mouvementTotal_ / std::sqrt(mouvementTotal_[0] * mouvementTotal_[0] + mouvementTotal_[1] * mouvementTotal_[1]);
	mouvement_ *= -1;

	for each(NoeudAbstrait* noeuds in noeudsSelectionnes_)
	{
		noeuds->accepte(this);
	}
}
