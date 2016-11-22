//////////////////////////////////////////////////////////////////////////////
/// @file FacadeModele.h
/// @author Loic Sauvageau
/// @date 2014-11-01
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////

#include "VisiteurRotation.h"
#include "Utilitaire.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurRotation::visite(NoeudAbstrait* objet);
///
/// @param[in] NoeudAbstrait* objet : objet a visiter.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurRotation::visite(NoeudAbstrait* objet)
{
	objet->rotation(mouvement_[0], centre_);
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurRotation::visiteAll(glm::dvec3 angle);
///
/// @param[in] glm::dvec3 angle : angle de la rotation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurRotation::visiteAll(glm::dvec3 angle)
{
	mouvementTotal_[0] += angle[0];
	mouvement_[0] = angle[0];
		for each(NoeudAbstrait* noeuds in noeudsSelectionnes_)
		{
			noeuds->accepte(this);
		}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurRotation::Revert(glm::dvec3 centreActuel);
///
/// @param[in] glm::dvec3 centreActuel: nouveau centre des objets.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurRotation::revert()
{
	mouvement_[0] = -0.01 * mouvementTotal_[0];
	
	for each(NoeudAbstrait* noeuds in noeudsSelectionnes_)
	{
		noeuds->accepte(this);
	}
}
