//////////////////////////////////////////////////////////////////////////////
/// @file VisiteurCollision.cpp
/// @author Loic Sauvageau
/// @date 2014-11-01
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////

#include "FacadeModele.h"
#include "VisiteurCollision.h"
#include "Utilitaire.h"
#include "NoeudPortail.h"
#include "NoeudRessort.h"
#include "NoeudPaletteJoueur2Gauche.h"
#include "NoeudPaletteJoueur2Droite.h"
#include <algorithm>
#include "glm\gtx\norm.hpp"
#include "glm\gtx\projection.hpp"


////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurCollision::visite(NoeudAbstrait* objet);
///
/// @param[in] NoeudAbstrait* objet : objet a visiter
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurCollision::visite(NoeudAbstrait* objet)
{
	if (objet->obtenirType() == ArbreRenduINF2990::NOM_BILLE)
	{
		FacadeModele::obtenirInstance()->incrementPoints(FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->obtenirPointsCollision(noeudEnContact_->obtenirType()));

		if (noeudEnContact_->obtenirType() == ArbreRenduINF2990::NOM_TROU)
		{
			aEffacer.push_back(objet);
			FacadeModele::obtenirInstance()->obtenirSon()->sonBilleDestruction();
		}
		else
		{
			glm::dvec3 direction{ ((NoeudBille*)objet)->obtenirVitesseX(), ((NoeudBille*)objet)->obtenirVitesseY(), 0 };

			double vitesse = sqrt(direction[0] * direction[0] + direction[1] * direction[1]);
			glm::dvec3 normale = details_.direction;
			normale = normale / sqrt((normale.x*normale.x + normale.y*normale.y));

			if (noeudEnContact_->obtenirType() == ArbreRenduINF2990::NOM_BILLE)
			{
				details_ = noeudEnContact_->collision(objet);
				glm::dvec3 direction2{ ((NoeudBille*)noeudEnContact_)->obtenirVitesseX(), ((NoeudBille*)noeudEnContact_)->obtenirVitesseY(), 0 };
				glm::dvec3 normale2 = details_.direction;
				normale2 = normale2 / sqrt((normale.x*normale.x + normale.y*normale.y));	
				double vitesse2 = sqrt(direction2[0] * direction2[0] + direction2[1] * direction2[1]);
				if (((NoeudBille*)objet)->collisionRessort())
				{
					if(details_.enfoncement > 0)
					{
						glm::dvec3 nouvellePos = noeudEnContact_->obtenirPositionRelative();
						nouvellePos += details_.enfoncement * normale2;
						noeudEnContact_->assignerPositionRelative(nouvellePos);
					}
					direction2 = -(2.0 * (normale2.x * direction2.x + normale2.y * direction2.y) * normale2 - direction2) / vitesse2 * vitesse;
					((NoeudBille*)noeudEnContact_)->assignerVitesse(direction2.x, direction2.y);
					FacadeModele::obtenirInstance()->sortieConsoleVitesse((NoeudBille*)noeudEnContact_);
				}
				else if (((NoeudBille*)noeudEnContact_)->collisionRessort())
				{
					details_ = objet->collision(noeudEnContact_);
					if (details_.enfoncement > 0)
					{
						glm::dvec3 nouvellePos = objet->obtenirPositionRelative();
						nouvellePos += details_.enfoncement * normale2;
						objet->assignerPositionRelative(nouvellePos);
					}
					direction = -(2.0 * (normale.x * direction.x + normale.y * direction.y) * normale - direction) / vitesse * vitesse2;
				}
				else
				{
					if (details_.enfoncement > 0)
					{
						glm::dvec3 nouvellePos = noeudEnContact_->obtenirPositionRelative();
						nouvellePos += details_.enfoncement * normale2;
						noeudEnContact_->assignerPositionRelative(nouvellePos);
					}

					direction = -(2.0 * (normale.x * direction.x + normale.y * direction.y) * normale - direction) / vitesse * vitesse2;
					direction2 = -(2.0 * (normale2.x * direction2.x + normale2.y * direction2.y) * normale2 - direction2) / vitesse2 * vitesse;
					((NoeudBille*)noeudEnContact_)->assignerVitesse(direction2.x, direction2.y);
					FacadeModele::obtenirInstance()->sortieConsoleVitesse((NoeudBille*)noeudEnContact_);
				}
			}
			else if (noeudEnContact_->obtenirType() == ArbreRenduINF2990::NOM_PORTAIL)
			{
				double rayonPortail = ((NoeudPortail*)noeudEnContact_)->calculerRayonPortail();
				if (details_.enfoncement > 0 && details_.enfoncement <= 2 * rayonPortail && ((NoeudBille*)objet)->affecterParPortail((NoeudPortail*)noeudEnContact_))
				{
					direction[0] += normale.x * (2.0 * rayonPortail - details_.enfoncement) * -0.2;
					direction[1] += normale.y * (2.0 * rayonPortail - details_.enfoncement) * -0.2;
				}
			}
			else if (noeudEnContact_->obtenirType() == ArbreRenduINF2990::NOM_RESSORT)
			{
				if (details_.enfoncement > 0)
				{
					glm::dvec3 nouvellePos = objet->obtenirPositionRelative();
					nouvellePos += details_.enfoncement * normale * 1.5;
					objet->assignerPositionRelative(nouvellePos);
				}
				if (((NoeudRessort*)noeudEnContact_)->auRepos() || (((NoeudRessort*)noeudEnContact_)->enRetraction() && ((NoeudRessort*)noeudEnContact_)->obtenirFacteurCollision() == 1)
					|| (!((NoeudRessort*)noeudEnContact_)->enRetraction() && ((NoeudRessort*)noeudEnContact_)->obtenirFacteurRetraction() < 1.0))
				{
					direction.x = 0;
					direction.y = 0;
				}
				else if (((NoeudRessort*)noeudEnContact_)->enRetraction())
				{
					direction = -(2.0 * (normale.x * direction.x + normale.y * direction.y) * normale - direction);
					direction *= 10;
					direction *= 1 / (1 - ((NoeudRessort*)noeudEnContact_)->obtenirFacteurRetraction());
					((NoeudBille*)objet)->assignerCollisionRessort(false);
				}
				else
				{
					direction = -(2.0 * (normale.x * direction.x + normale.y * direction.y) * normale - direction);
					direction *= 4.0;
					direction *= pow(10, ((NoeudRessort*)noeudEnContact_)->obtenirFacteurCollision());
					((NoeudBille*)objet)->assignerCollisionRessort(false);
				}
			}
			else if (noeudEnContact_->obtenirType() == ArbreRenduINF2990::NOM_PALETTE_JOUEUR1_GAUCHE || noeudEnContact_->obtenirType() == ArbreRenduINF2990::NOM_PALETTE_JOUEUR2_GAUCHE
				|| noeudEnContact_->obtenirType() == ArbreRenduINF2990::NOM_PALETTE_JOUEUR1_DROITE || noeudEnContact_->obtenirType() == ArbreRenduINF2990::NOM_PALETTE_JOUEUR2_DROITE)
			{

				if (details_.enfoncement > 0)
				{
					glm::dvec3 nouvellePos = objet->obtenirPositionRelative();
					nouvellePos += details_.enfoncement * normale * 1.5;
					objet->assignerPositionRelative(nouvellePos);
				}

				if (noeudEnContact_->estAscension())
				{
					BoiteEnglobante boitePalette = noeudEnContact_->obtenirBoiteEnglobante();
					const glm::dvec3 segment{ boitePalette.coinHD - boitePalette.coinHG };
					double ratio;

					if (noeudEnContact_->obtenirType() == ArbreRenduINF2990::NOM_PALETTE_JOUEUR1_GAUCHE || noeudEnContact_->obtenirType() == ArbreRenduINF2990::NOM_PALETTE_JOUEUR2_GAUCHE)
					{
						const glm::dvec3 segment{ boitePalette.coinHD - boitePalette.coinHG };
						ratio = glm::dot(objet->obtenirPositionRelative() - boitePalette.coinHG, segment) / glm::length2(segment);
					}
					else
					{
						const glm::dvec3 segment{ boitePalette.coinHG - boitePalette.coinHD };
						ratio = 1.0 - glm::dot(objet->obtenirPositionRelative() - boitePalette.coinHD, segment) / glm::length2(segment);
					}

					direction.x = ratio*std::sqrt(glm::length2(segment)) * 10 * normale.x;
					direction.y = ratio*std::sqrt(glm::length2(segment)) * 10 * normale.y;
				}
				else
				{
					direction = -(2.0 * (normale.x * direction.x + normale.y * direction.y) * normale - direction);
				}
				FacadeModele::obtenirInstance()->obtenirSon()->sonCollision();
			}
			else if (noeudEnContact_->obtenirType() != ArbreRenduINF2990::NOM_CIBLE || ((NoeudCible*)noeudEnContact_)->obtenirEtatCible())
			{
				if (details_.enfoncement > 0)
				{
					glm::dvec3 nouvellePos = objet->obtenirPositionRelative();
					nouvellePos += details_.enfoncement * normale * 1.5;
					objet->assignerPositionRelative(nouvellePos);
				}

				if (noeudEnContact_->obtenirType() == ArbreRenduINF2990::NOM_BUTOIR_CIRCULAIRE)
				{
					((NoeudButoirCirculaire*)noeudEnContact_)->assignerCollision();
				}

				direction = -(2.0 * (normale.x * direction.x + normale.y * direction.y) * normale - direction);

				if (((NoeudBille*)objet)->estAffectButoir())
				{
					direction *= 2.0;
					((NoeudBille*)objet)->assignerEffetButoir(false);
				}

				if (noeudEnContact_->obtenirType() == ArbreRenduINF2990::NOM_CIBLE)
					((NoeudCible*)noeudEnContact_)->assignerCollision();
			}
			if (((NoeudBille*)objet)->obtenirVitesseX() != direction.x || ((NoeudBille*)objet)->obtenirVitesseY() != direction.y)
			{
				((NoeudBille*)objet)->assignerVitesse(direction.x, direction.y);
				FacadeModele::obtenirInstance()->sortieConsoleVitesse((NoeudBille*)objet);
			}
			if (noeudEnContact_->obtenirType() == ArbreRenduINF2990::NOM_CIBLE)
				FacadeModele::obtenirInstance()->obtenirSon()->sonCollisionCible();
			else
				FacadeModele::obtenirInstance()->obtenirSon()->sonCollision();
		}
	}
	else if (objet->obtenirType() == ArbreRenduINF2990::NOM_PORTAIL && noeudEnContact_->obtenirType() == ArbreRenduINF2990::NOM_BILLE)
	{
		double rayonPortail = ((NoeudPortail*)objet)->calculerRayonPortail();
		//bille entre dans le portail
		if (details_.enfoncement > 2 * rayonPortail && ((NoeudBille*)noeudEnContact_)->affecterParPortail((NoeudPortail*)objet))
		{
			NoeudPortail* noeudFrere = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->obtenirNoeudFrere((NoeudPortail*)objet);
			glm::dvec3 nouvellePosition = noeudFrere->obtenirPositionRelative();
			noeudEnContact_->assignerPositionRelative(nouvellePosition);
			((NoeudBille*)noeudEnContact_)->assignerNonAffecterParPortail(noeudFrere);
			FacadeModele::obtenirInstance()->obtenirSon()->sonPortail();
		}
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurCollision::dectectionCollisionGlobale();
///
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurCollision::dectectionCollisionGlobale()
{
	QuadTree* quad = FacadeModele::obtenirInstance()->obtenirQuadTree();

	dectectionCollisionQuadTree(quad);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurCollision::dectectionCollisionQuadTree(QuadTree* quad);
///
/// @param[in] QuadTree* objet : quadTree a visiter
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurCollision::dectectionCollisionQuadTree(QuadTree* quad)
{
	/*if (quad->obtenirQuartier(0) != nullptr)
	{
	dectectionCollisionQuadTree(quad->obtenirQuartier(0));
	dectectionCollisionQuadTree(quad->obtenirQuartier(1));
	dectectionCollisionQuadTree(quad->obtenirQuartier(2));
	dectectionCollisionQuadTree(quad->obtenirQuartier(3));
	}
	else
	{
	dectectionCollision(quad->obtenirListeNoeud());
	}*/

	//std::list<NoeudAbstrait*>::iterator it;

	///// traverse des noeuds dans le quad
	//for (it = listeNoeud.begin(); it != listeNoeud.end();)
	//{
	//	NoeudAbstrait* noeud1 = *it;
	//	it++;

	//	for (it2 = it; it2 != listeNoeud.end(); it2++)
	//	{
	//		NoeudAbstrait* noeud2 = *it2;

	//		/// vérification d'une collision possible
	//		if (!(!noeud1->estDynamique() && !noeud2->estDynamique()))
	//			traiterCollision(noeud1, noeud2);
	//	}
	//}
	//if (!aEffacer.empty())
	//{
	//	for (std::list<NoeudAbstrait*>::iterator it = aEffacer.begin(); it != aEffacer.end(); it++)
	//		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->effacer(*it);
	//}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurCollision::dectectionCollision(std::list<NoeudAbstrait*> listeNoeud);
///
/// @param[in] NoeudAbstrait* objet : objet a visiter
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurCollision::dectectionCollision(std::vector<NoeudAbstrait*> listeNoeud)
{
	std::vector<NoeudAbstrait*>::iterator it;
	std::vector<NoeudAbstrait*>::iterator it2;
	QuadTree * quad = FacadeModele::obtenirInstance()->obtenirQuadTree();
	std::vector<NoeudAbstrait*> listeCollision;

	/// traverse des noeuds dans le quad
	for (it = listeNoeud.begin(); it != listeNoeud.end();)
	{
		NoeudAbstrait* noeud1 = *it;
		it++;
		glm::dvec3 posNoeud = noeud1->obtenirPositionRelative();
		BoiteEnglobante boite = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->chercher(ArbreRenduINF2990::NOM_PLAQUE)->obtenirBoiteEnglobante();
		if (utilitaire::DANS_LIMITESXY(posNoeud.x, boite.coinBG.x, boite.coinBD.x, posNoeud.y, boite.coinBG.y, boite.coinHG.y))
		{
			// vérifie que le noeud est dynamique
			if (noeud1->estDynamique())
			{
				listeCollision.clear();
				quad->obtenirListeCollision(listeCollision, noeud1);
				/// vérification d'une collision possible
				for (it2 = listeCollision.begin(); it2 != listeCollision.end();)
				{
					NoeudAbstrait* noeud2 = *it2;
					it2++;

					/// vérifier que l'on ne compare pas un noeud à lui-même
					if (noeud1 != noeud2)
						traiterCollision(noeud1, noeud2);
				}
			}
		}
		else if (noeud1->obtenirType() == ArbreRenduINF2990::NOM_BILLE)
		{
			aEffacer.push_back(noeud1);
		}
	}

	/// supression des noeuds
	if (!aEffacer.empty())
	{
		for (std::list<NoeudAbstrait*>::iterator it = aEffacer.begin(); it != aEffacer.end(); it++)
		{
			FacadeModele::obtenirInstance()->decrementerBilleSurLaTable();
			FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->effacer(*it);
		}
		aEffacer.clear();
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurCollision::traiterCollision(NoeudAbstrait* noeud1, NoeudAbstrait* noeud2);
///
/// @param[in] NoeudAbstrait* objet : objet a visiter
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurCollision::traiterCollision(NoeudAbstrait* noeud1, NoeudAbstrait* noeud2)
{
	if (noeud1->obtenirType() == ArbreRenduINF2990::NOM_BILLE || noeud1->obtenirType() == ArbreRenduINF2990::NOM_PORTAIL)
	{
		details_ = noeud1->collision(noeud2);

		if (details_.type != aidecollision::COLLISION_AUCUNE)
		{

			noeudEnContact_ = noeud2;
			noeud1->accepte(this);
		}
	}
	if ((noeud2->obtenirType() == ArbreRenduINF2990::NOM_BILLE && noeud1->obtenirType() != ArbreRenduINF2990::NOM_BILLE) || noeud2->obtenirType() == ArbreRenduINF2990::NOM_PORTAIL)
	{
		details_ = noeud2->collision(noeud1);

		if (details_.type != aidecollision::COLLISION_AUCUNE)
		{
			noeudEnContact_ = noeud1;
			noeud2->accepte(this);
		}
	}

	if (noeud1->obtenirType() == ArbreRenduINF2990::NOM_BILLE && noeud2->obtenirType() == ArbreRenduINF2990::NOM_PORTAIL && details_.type == aidecollision::COLLISION_AUCUNE)
	{
		((NoeudBille*)noeud1)->assignerAffecterParPortail((NoeudPortail*)noeud2);
	}
	else if (noeud2->obtenirType() == ArbreRenduINF2990::NOM_BILLE && noeud1->obtenirType() == ArbreRenduINF2990::NOM_PORTAIL && details_.type == aidecollision::COLLISION_AUCUNE)
	{
		((NoeudBille*)noeud2)->assignerAffecterParPortail((NoeudPortail*)noeud1);
	}

	///////////////////////////////////////// Code de merde pour le AI /////////////////////////////////////////////

	if (FacadeModele::obtenirInstance()->obtenirJoueurVirtuel())
	{
		// cas bille - palette gauche
		if (noeud1->obtenirType() == ArbreRenduINF2990::NOM_BILLE && noeud2->obtenirType() == ArbreRenduINF2990::NOM_PALETTE_JOUEUR2_GAUCHE)
		{
			// vérifie si la palette n'est pas activé
			if (!((NoeudPaletteJoueur2Gauche*)noeud2)->estAscension())
			{
				BoiteEnglobante boitePalette = noeud2->obtenirBoiteEnglobante();
				BoiteEnglobante boiteContact;
				double radAngle = 60.0 * 3.1416 / 180.0;

				glm::dvec3 pointLimite = boitePalette.coinHD;
				glm::dvec3 pointTemp;
				pointLimite -= noeud2->obtenirPositionRelative();

				pointTemp[0] = pointLimite[0] * std::cos(radAngle) - pointLimite[1] * std::sin(radAngle);
				pointTemp[1] = pointLimite[0] * std::sin(radAngle) + pointLimite[1] * std::cos(radAngle);

				pointLimite = pointTemp + noeud2->obtenirPositionRelative();

				double maxX = std::max(std::max(boitePalette.coinHG.x, boitePalette.coinHD.x), pointLimite.x);
				double minX = std::min(std::min(boitePalette.coinHG.x, boitePalette.coinHD.x), pointLimite.x);

				double maxY = std::max(std::max(boitePalette.coinHG.y, boitePalette.coinHD.y), pointLimite.y);
				double minY = std::min(std::min(boitePalette.coinHG.y, boitePalette.coinHD.y), pointLimite.y);

				if (utilitaire::DANS_LIMITESXY(noeud1->obtenirPositionRelative().x, minX - 1, maxX + 1, noeud1->obtenirPositionRelative().y, minY, maxY))
				{
					std::vector<NoeudAbstrait*> vectNoeud = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->obtenirNoeudPaletteGJ2();
					std::vector<NoeudAbstrait*>::iterator it;
					NoeudPaletteJoueur2Gauche* noeudPalette;
					for (it = vectNoeud.begin(); it < vectNoeud.end(); it++)
					{
						noeudPalette = (NoeudPaletteJoueur2Gauche*)(*it);
						noeudPalette->setAnimation();
					}
				}
			}
		}
		// cas palette - bille
		else if (noeud1->obtenirType() == ArbreRenduINF2990::NOM_PALETTE_JOUEUR2_GAUCHE && noeud2->obtenirType() == ArbreRenduINF2990::NOM_BILLE)
		{
			// vérifie si la palette n'est pas activé
			if (!((NoeudPaletteJoueur2Gauche*)noeud1)->estAscension())
			{
				BoiteEnglobante boitePalette = noeud1->obtenirBoiteEnglobante();
				BoiteEnglobante boiteContact;
				double radAngle = 60.0 * 3.1416 / 180.0;

				glm::dvec3 pointLimite = boitePalette.coinHD;
				glm::dvec3 pointTemp;
				pointLimite -= noeud1->obtenirPositionRelative();

				pointTemp[0] = pointLimite[0] * std::cos(radAngle) - pointLimite[1] * std::sin(radAngle);
				pointTemp[1] = pointLimite[0] * std::sin(radAngle) + pointLimite[1] * std::cos(radAngle);

				pointLimite = pointTemp + noeud2->obtenirPositionRelative();

				double maxX = std::max(std::max(boitePalette.coinHG.x, boitePalette.coinHD.x), pointLimite.x);
				double minX = std::min(std::min(boitePalette.coinHG.x, boitePalette.coinHD.x), pointLimite.x);

				double maxY = std::max(std::max(boitePalette.coinHG.y, boitePalette.coinHD.y), pointLimite.y);
				double minY = std::min(std::min(boitePalette.coinHG.y, boitePalette.coinHD.y), pointLimite.y);

				if (utilitaire::DANS_LIMITESXY(noeud2->obtenirPositionRelative().x, minX - 1, maxX + 1, noeud2->obtenirPositionRelative().y, minY, maxY))
				{
					std::vector<NoeudAbstrait*> vectNoeud = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->obtenirNoeudPaletteGJ2();
					std::vector<NoeudAbstrait*>::iterator it;
					NoeudPaletteJoueur2Gauche* noeudPalette;
					for (it = vectNoeud.begin(); it < vectNoeud.end(); it++)
					{
						noeudPalette = (NoeudPaletteJoueur2Gauche*)(*it);
						noeudPalette->setAnimation();
					}
				}
			}
		}
		// cas bille - palette droite
		else if (noeud1->obtenirType() == ArbreRenduINF2990::NOM_BILLE && noeud2->obtenirType() == ArbreRenduINF2990::NOM_PALETTE_JOUEUR2_DROITE)
		{
			// vérifie si la palette n'est pas activé
			if (!((NoeudPaletteJoueur2Droite*)noeud2)->estAscension())
			{
				BoiteEnglobante boitePalette = noeud2->obtenirBoiteEnglobante();
				BoiteEnglobante boiteContact;
				double radAngle = 60.0 * 3.1416 / 180.0;

				glm::dvec3 pointLimite = boitePalette.coinHG;
				glm::dvec3 pointTemp;
				pointLimite -= noeud2->obtenirPositionRelative();

				pointTemp[0] = pointLimite[0] * std::cos(radAngle) - pointLimite[1] * std::sin(radAngle);
				pointTemp[1] = pointLimite[0] * std::sin(radAngle) + pointLimite[1] * std::cos(radAngle);

				pointLimite = pointTemp + noeud2->obtenirPositionRelative();

				double maxX = std::max(std::max(boitePalette.coinHG.x, boitePalette.coinHD.x), pointLimite.x);
				double minX = std::min(std::min(boitePalette.coinHG.x, boitePalette.coinHD.x), pointLimite.x);

				double maxY = std::max(std::max(boitePalette.coinHG.y, boitePalette.coinHD.y), pointLimite.y);
				double minY = std::min(std::min(boitePalette.coinHG.y, boitePalette.coinHD.y), pointLimite.y);

				if (utilitaire::DANS_LIMITESXY(noeud1->obtenirPositionRelative().x, minX - 1, maxX + 1, noeud1->obtenirPositionRelative().y, minY, maxY))
				{
					std::vector<NoeudAbstrait*> vectNoeud = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->obtenirNoeudPaletteDJ2();
					std::vector<NoeudAbstrait*>::iterator it;
					NoeudPaletteJoueur2Droite* noeudPalette;
					for (it = vectNoeud.begin(); it < vectNoeud.end(); it++)
					{
						noeudPalette = (NoeudPaletteJoueur2Droite*)(*it);
						noeudPalette->setAnimation();
					}
				}
			}
		}
		// cas palette - bille
		else if (noeud1->obtenirType() == ArbreRenduINF2990::NOM_PALETTE_JOUEUR2_DROITE && noeud2->obtenirType() == ArbreRenduINF2990::NOM_BILLE)
		{
			// vérifie si la palette n'est pas activé
			if (!((NoeudPaletteJoueur2Droite*)noeud1)->estAscension())
			{
				BoiteEnglobante boitePalette = noeud1->obtenirBoiteEnglobante();
				BoiteEnglobante boiteContact;
				double radAngle = 60.0 * 3.1416 / 180.0;

				glm::dvec3 pointLimite = boitePalette.coinHG;
				glm::dvec3 pointTemp;
				pointLimite -= noeud1->obtenirPositionRelative();

				pointTemp[0] = pointLimite[0] * std::cos(radAngle) + pointLimite[1] * std::sin(radAngle);
				pointTemp[1] = pointLimite[0] * std::sin(radAngle) - pointLimite[1] * std::cos(radAngle);

				pointLimite = pointTemp + noeud2->obtenirPositionRelative();

				double maxX = std::max(std::max(boitePalette.coinHG.x, boitePalette.coinHD.x), pointLimite.x);
				double minX = std::min(std::min(boitePalette.coinHG.x, boitePalette.coinHD.x), pointLimite.x);

				double maxY = std::max(std::max(boitePalette.coinHG.y, boitePalette.coinHD.y), pointLimite.y);
				double minY = std::min(std::min(boitePalette.coinHG.y, boitePalette.coinHD.y), pointLimite.y);

				if (utilitaire::DANS_LIMITESXY(noeud2->obtenirPositionRelative().x, minX -1, maxX +1, noeud2->obtenirPositionRelative().y, minY, maxY))
				{
					std::vector<NoeudAbstrait*> vectNoeud = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->obtenirNoeudPaletteDJ2();
					std::vector<NoeudAbstrait*>::iterator it;
					NoeudPaletteJoueur2Droite* noeudPalette;
					for (it = vectNoeud.begin(); it < vectNoeud.end(); it++)
					{
						noeudPalette = (NoeudPaletteJoueur2Droite*)(*it);
						noeudPalette->setAnimation();
					}
				}
			}
		}
	}
}

