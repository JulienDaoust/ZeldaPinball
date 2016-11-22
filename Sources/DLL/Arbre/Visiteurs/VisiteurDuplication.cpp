//////////////////////////////////////////////////////////////////////////////
/// @file FacadeModele.h
/// @author Loic Sauvageau
/// @date 2014-11-01
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////

#include "VisiteurDuplication.h"
#include "Utilitaire.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurDuplication::visite(NoeudAbstrait* objet);
///
/// @param[in] NoeudAbstrait* objet : objet a visiter
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurDuplication::visite(NoeudAbstrait* objet)
{
	if (etat == "creation")
	{
		NoeudAbstrait* noeud1 = arbre_->ajouterNouveauNoeud(objet->obtenirParent()->obtenirType(), objet->obtenirType());
		noeud1->assignerTailleRelative(objet->obtenirTailleRelative());
		noeud1->assignerAngleRotation(objet->obtenirAngleRotation());
		noeud1->assignerPositionRelative(objet->obtenirPositionRelative() + mouvement_ - centre_);
		if (objet->obtenirType() == "portail")
		{
			((NoeudPortail*)noeud1)->assignerId(portalId);
		}
		copies_.push_back(noeud1);
	}
	else if (etat == "positionnement")
	{
		objet->assignerPositionRelative(objet->obtenirPositionRelative() + mouvement_- centre_);
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurDuplication::visiteAll(glm::dvec3 nouveauCentre);
///
/// @param[in] glm::dvec3 : nouveau centre des objets.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurDuplication::visiteAll(glm::dvec3 nouveauCentre)
{
	mouvement_ = nouveauCentre;
	if (etat == "creation")
	{
		std::vector<NoeudPortail*> portals = std::vector<NoeudPortail*>();
		for each(NoeudAbstrait* noeud in noeudsSelectionnes_)
		{
			if (noeud->obtenirType() == "portail")
			{
				std::vector<NoeudAbstrait*>::iterator it;
				for (it = noeudsSelectionnes_.begin(); it != noeudsSelectionnes_.end(); it++)
				{
					if ((*it) != noeud && (*it)->obtenirType() == "portail" && ((NoeudPortail*)*it)->obtenirId() == ((NoeudPortail*)noeud)->obtenirId()
						&& std::find(portals.begin(), portals.end(), (*it)) == portals.end())
					{
						portals.push_back((NoeudPortail*)noeud);
						portals.push_back((NoeudPortail*)*it);
					}
				}
			}
			else
			{
				noeud->accepte(this);
			}
		}
		bool refreshNumber = true;
		for (std::vector<NoeudPortail*>::iterator it = portals.begin(); it != portals.end(); it++)
		{
			if (refreshNumber)
				portalId = arbre_->obtenirIdPortail();
			(*it)->accepte(this);

			refreshNumber = !refreshNumber;
		}

		etat = "positionnement";
	}
	else if (etat == "positionnement")
	{
		for each(NoeudAbstrait* noeuds in copies_)
		{
			noeuds->accepte(this);
		}
	}
	centre_ = mouvement_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurDuplication::Revert();
///
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurDuplication::revert()
{
}
