//////////////////////////////////////////////////////////////////////////////
/// @file FacadeModele.h
/// @author Loic Sauvageau
/// @date 2014-11-01
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////

#include "VisiteurScale.h"
#include "Utilitaire.h"
#include <iostream>

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurScale::visite(NoeudAbstrait* objet);
///
/// @param[in] NoeudAbstrait* objet : objet a visiter
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurScale::visite(NoeudAbstrait* objet)
{
	if (objet->estScaleable())
	objet->scale(upordown);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurScale::visiteAll(glm::dvec3 point);
///
/// @param[in] glm::dvec3 point : position de la souris
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurScale::visiteAll(glm::dvec3 point)
{
	if (point.y > pointPrecedent_.y)
		upordown = true;
	else
		upordown = false;
	if (point.y != pointPrecedent_.y)
	{
		for each(NoeudAbstrait* noeuds in noeudsSelectionnes_)
		{
			noeuds->accepte(this);
		}
		pointPrecedent_ = point;
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurScale::revert(glm::dvec3 centreActuel);
///
/// @param[in] glm::dvec3 centreActuel : centre de l'objet
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurScale::revert()
{
	upordown = false;
	for each(NoeudAbstrait* noeuds in noeudsSelectionnes_)
	{
		noeuds->accepte(this);
	}
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurScale::setInitialScales();
///
/// Cette fonction assigne les valeurs initiales de scale pour chaque object
/// de la sélection
///
/// @param[in] Aucun.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurScale::setInitialScales()
{
	for each(NoeudAbstrait* noeuds in noeudsSelectionnes_)
	{
		initialScales_.insert(std::pair<NoeudAbstrait*, glm::dvec3>(noeuds, noeuds->obtenirTailleRelative()));
	}
}