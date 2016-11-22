///////////////////////////////////////////////////////////////////////////////
/// @file NoeudBille.cpp
/// @author Tommy Sagala
/// @date 2014-09-17
/// @version 1.0
///////////////////////////////////////////////////////////////////////////////
#include "NoeudBille.h"
#include "Utilitaire.h"

#include <windows.h>
#include <GL/gl.h>
#include <cmath>

#include <iostream>
#include "ArbreRenduINF2990.h"
#include "NoeudCible.h"
#include "FTGL/ftgl.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudBille::NoeudBille(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par défaut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudBille::NoeudBille(const std::string& typeNoeud)
	: NoeudComposite{ typeNoeud }
{
	/// Charger le modèle 3D
	modele_.charger("media/bille.obj");

	// Création d'une liste d'affichage.  ATTENTION, CECI N'EST PAS UN
	// USAGE CORRECT DES LISTES D'AFFICHAGE, puisque la même liste serait
	// recréée pour chaque instance d'un noeud, alors que la même pourrait
	// être partagée par toutes les instances d'un même type de noeud.
	liste_ = modele::opengl_storage::OpenGL_Liste{ &modele_ };
	liste_.storageCharger();
	dynamique_ = true;
	portailDesactives_ = std::list<NoeudPortail*>();
	scale_ = { 2, 2, 2 };
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudBille::~NoeudBille()
///
/// Ce destructeur désallouee la liste d'affichage du cube.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudBille::~NoeudBille()
{
	liste_.storageRelacher();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudBille::afficherConcret() const
///
/// Cette fonction effectue le véritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudBille::afficherConcret() const
{
	// Appel à la version de la classe de base pour l'affichage des enfants.
	NoeudComposite::afficherConcret();
	// Sauvegarde de la matrice.
	glPushMatrix();
	// Révolution autour du centre.
	glRotated(vitesseAngulaireX_, 0, 1, 0);
	glRotated(vitesseAngulaireY_, 1, 0, 0);
	// Rotation autour de l'axe des z
	glScaled(scale_[0], scale_[1], scale_[2]);
	// Affichage du modèle.
	liste_.dessiner();
	// Restauration de la matrice.
	glPopMatrix();

	dessinerBoiteEnglobante();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCube::animer(float temps)
///
/// Cette fonction effectue l'animation du noeud pour un certain
/// intervalle de temps.
///
/// @param[in] temps : Intervalle de temps sur lequel faire l'animation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudBille::animer(float temps)
{
	// Appel à la version de la classe de base pour l'animation des enfants.
	NoeudComposite::animer(temps);

	vitesseY_ += accelerationY_ * temps;

	if (vitesseY_ > vitesseMax) vitesseY_ = vitesseMax;
	else if (vitesseY_ < -1 * vitesseMax) vitesseY_ = -1 * vitesseMax;

	positionRelative_[0] += vitesseX_ * temps;
	positionRelative_[1] += vitesseY_ * temps;

	/// Calcul de la rotation
	vitesseAngulaireX_ += -vitesseX_  * temps *180.0 / 3.1416 ;
	vitesseAngulaireY_ += -vitesseY_  * temps *180.0 / 3.1416;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudBille::assignerVitesse(double x, double y) 
///
/// Cette fonction change lavitesse de deplacement
///
/// @param[in] x,y : nouvelle vitesse
///
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
void NoeudBille::assignerVitesse(double x, double y) 
{
	if (x > vitesseMax) x = vitesseMax;
	else if (x < -1 * vitesseMax) x = -1 * vitesseMax;

	if (y > vitesseMax) y = vitesseMax;
	else if (y < -1 * vitesseMax) y = -1 * vitesseMax;

	vitesseX_ = x;
	vitesseY_ = y;

	vitesseAngulaireX_ = 0;
	vitesseAngulaireY_ = 0;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn double NoeudBille::obtenirVitesseX() const
///
/// Cette fonction retourne la vitesse de deplacement en x
///
/// @return double.
///
////////////////////////////////////////////////////////////////////////
double NoeudBille::obtenirVitesseX() const
{
	return vitesseX_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn double NoeudBille::obtenirVitesseY() const
///
/// Cette fonction retourne la vitesse de deplacement en y
///
/// @return double.
///
////////////////////////////////////////////////////////////////////////
double NoeudBille::obtenirVitesseY() const
{
	return vitesseY_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudBille::affecterParPortail(NoeudPortail* portail) const
///
/// Cette fonction permet de savoir si la bille est affectée par les portails
///
/// @return bool.
///
////////////////////////////////////////////////////////////////////////
bool NoeudBille::affecterParPortail(NoeudPortail* portail) const
{
	if(!portailDesactives_.empty())
		return false;
	for (std::list<NoeudPortail*>::const_iterator it = portailDesactives_.begin(); it != portailDesactives_.end(); it++)
	{
		if ((*it)->obtenirId() == portail->obtenirId() && (*it)->obtenirPositionRelative() == portail->obtenirPositionRelative())
			return false;
	}
	return true;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudBille::assignerAffecterParPortail(NoeudPortail* portail)
///
/// Cette fonction permet d'activer les interactions avec les portails
///
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
void NoeudBille::assignerAffecterParPortail(NoeudPortail* portail)
{
	if (portailDesactives_.size() > 0)
	{
		std::list<NoeudPortail*>::iterator it = std::find(portailDesactives_.begin(), portailDesactives_.end(), portail);
		if (it != portailDesactives_.end())
			portailDesactives_.erase(it);
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudBille::assignerNonAffecterParPortail(NoeudPortail* portail)
///
/// Cette fonction permet de desactiver les interactions avec les portails
///
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
void NoeudBille::assignerNonAffecterParPortail(NoeudPortail* portail)
{
	if (portailDesactives_.size() == 0 || std::find(portailDesactives_.begin(), portailDesactives_.end(), portail) == portailDesactives_.end())
		portailDesactives_.push_back(portail);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn virtual  aidecollision::DetailsCollision NoeudBille::collision(NoeudAbstrait* noeud) const
///
/// Cette fonction retourne les informations de collisions
///
/// @return aidecollision::DetailsCollision
///
////////////////////////////////////////////////////////////////////////
aidecollision::DetailsCollision NoeudBille::collision(NoeudAbstrait* noeud)
{
	aidecollision::DetailsCollision details;
	details.type = aidecollision::COLLISION_AUCUNE;
	glm::dvec3 pos1 = this->obtenirPositionRelative();
	double rayon1 = calculerRayon();

	if (noeud->obtenirType() == ArbreRenduINF2990::NOM_GENERATEUR_BILLE)
	{
		return details;
	}
	/// cas du contact avec un mur
	else if (noeud->obtenirType() == ArbreRenduINF2990::NOM_MUR || noeud->obtenirType() == ArbreRenduINF2990::NOM_PLAQUE)
	{
		BoiteEnglobante boiteMur = noeud->obtenirBoiteEnglobante();
		/// 1er mur
		details = aidecollision::calculerCollisionSegment(boiteMur.coinHD, boiteMur.coinHG, pos1, rayon1, false);
		if (details.type != aidecollision::COLLISION_AUCUNE)
		{
			return details;
		}
		/// 2e mur
		details = aidecollision::calculerCollisionSegment(boiteMur.coinBD, boiteMur.coinBG, pos1, rayon1, false);
		if (details.type != aidecollision::COLLISION_AUCUNE)
			return details;

		/// 3e mur
		details = aidecollision::calculerCollisionSegment(boiteMur.coinHD, boiteMur.coinBD, pos1, rayon1, false);
		if (details.type != aidecollision::COLLISION_AUCUNE)
			return details;

		/// 4e mur
		details = aidecollision::calculerCollisionSegment(boiteMur.coinHG, boiteMur.coinBG, pos1, rayon1, false);
		return details;
	}
	else if (noeud->obtenirType() == ArbreRenduINF2990::NOM_RESSORT)
	{
		BoiteEnglobante boiteRessort = noeud->obtenirBoiteEnglobante();
		/// 1er mur
		details = aidecollision::calculerCollisionSegment(boiteRessort.coinHD, boiteRessort.coinHG, pos1, rayon1, false);
		if (details.type != aidecollision::COLLISION_AUCUNE)
		{
			collisionRessort_ = true;
			return details;
		}
		/// 2e mur
		details = aidecollision::calculerCollisionSegment(boiteRessort.coinBD, boiteRessort.coinBG, pos1, rayon1, false);
		if (details.type != aidecollision::COLLISION_AUCUNE)
			return details;

		/// 3e mur
		details = aidecollision::calculerCollisionSegment(boiteRessort.coinHD, boiteRessort.coinBD, pos1, rayon1, false);
		if (details.type != aidecollision::COLLISION_AUCUNE)
			return details;

		/// 4e mur
		details = aidecollision::calculerCollisionSegment(boiteRessort.coinHG, boiteRessort.coinBG, pos1, rayon1, false);
		return details;

	}
	/// cas du butoir circulaire
	else if (noeud->obtenirType() == ArbreRenduINF2990::NOM_BUTOIR_CIRCULAIRE)
	{
		double rayon2 = noeud->calculerRayon();
		glm::dvec3 pos2 = noeud->obtenirPositionRelative();
		details = aidecollision::calculerCollisionCercle(glm::dvec2(noeud->obtenirPositionRelative().x, noeud->obtenirPositionRelative().y), rayon2, glm::dvec2(positionRelative_.x, positionRelative_.y), rayon1);
		if (details.type != aidecollision::COLLISION_AUCUNE)
			assignerEffetButoir(true);
	}
	/// cas du butoir triangulaire gauche
	else if (noeud->obtenirType() == ArbreRenduINF2990::NOM_BUTOIR_TRIANGULAIRE_GAUCHE)
	{
		
		/// Calcul du point 
		BoiteEnglobante boiteMur = noeud->obtenirBoiteEnglobante();
		glm::dvec3 point(boiteMur.coinHG.x, boiteMur.coinHG.y - (boiteMur.coinHG.y - boiteMur.coinBG.y) * 2 / 3, 0);
		
		/// 1er mur qui donne un boost
		details = aidecollision::calculerCollisionSegment(boiteMur.coinHG, boiteMur.coinBD, pos1, rayon1, false);
		if (details.type != aidecollision::COLLISION_AUCUNE)
		{
			assignerEffetButoir(true);
			return details;
		}
		/// 2e mur
		details = aidecollision::calculerCollisionSegment(boiteMur.coinHG, point, pos1, rayon1, false);
		if (details.type != aidecollision::COLLISION_AUCUNE)
			return details;

		/// 3e mur
		details = aidecollision::calculerCollisionSegment(point, boiteMur.coinBD, pos1, rayon1, false);
		if (details.type != aidecollision::COLLISION_AUCUNE)
			return details;
	}
	/// cas du butoir triangulaire droit
	else if (noeud->obtenirType() == ArbreRenduINF2990::NOM_BUTOIR_TRIANGULAIRE_DROIT)
	{

		/// Calcul du point 
		BoiteEnglobante boiteMur = noeud->obtenirBoiteEnglobante();
		glm::dvec3 point(boiteMur.coinHD.x, boiteMur.coinHD.y - (boiteMur.coinHD.y - boiteMur.coinBD.y) * 2 / 3, 0);

		/// 1er mur qui donne un boost
		details = aidecollision::calculerCollisionSegment(boiteMur.coinHD, boiteMur.coinBG, pos1, rayon1, false);
		if (details.type != aidecollision::COLLISION_AUCUNE)
		{
			assignerEffetButoir(true);
			return details;
		}
		/// 2e mur
		details = aidecollision::calculerCollisionSegment(boiteMur.coinHD, point, pos1, rayon1, false);
		if (details.type != aidecollision::COLLISION_AUCUNE)
			return details;

		/// 3e mur
		details = aidecollision::calculerCollisionSegment(point, boiteMur.coinBG, pos1, rayon1, false);
		if (details.type != aidecollision::COLLISION_AUCUNE)
			return details;
	}
	/// cas de la palette gauche
	else if (noeud->obtenirType() == ArbreRenduINF2990::NOM_PALETTE_JOUEUR1_GAUCHE || noeud->obtenirType() == ArbreRenduINF2990::NOM_PALETTE_JOUEUR2_GAUCHE
		|| noeud->obtenirType() == ArbreRenduINF2990::NOM_PALETTE_JOUEUR1_DROITE || noeud->obtenirType() == ArbreRenduINF2990::NOM_PALETTE_JOUEUR2_DROITE)
	{

		/// Calcul du point 
		BoiteEnglobante boiteMur = noeud->obtenirBoiteEnglobante();

		/// 1er segment
		details = aidecollision::calculerCollisionSegment(boiteMur.coinHD, boiteMur.coinHG, pos1, rayon1, false);
		if (details.type != aidecollision::COLLISION_AUCUNE)
		{
			return details;
		}
		/// 2e segment
		details = aidecollision::calculerCollisionSegment(boiteMur.coinBD, boiteMur.coinBG, pos1, rayon1, false);
		if (details.type != aidecollision::COLLISION_AUCUNE)
			return details;

		/// sphère de gauche
		details = aidecollision::calculerCollisionSphere(boiteMur.coinHG - (boiteMur.coinHG - boiteMur.coinBG) / 2.0, (boiteMur.coinHG.y - boiteMur.coinBG.y) / 2.0,pos1, rayon1);
		if (details.type != aidecollision::COLLISION_AUCUNE)
			return details;

		/// sphère de droite
		details = aidecollision::calculerCollisionSphere(boiteMur.coinHD - (boiteMur.coinHD - boiteMur.coinBD) / 2.0, (boiteMur.coinHD.y - boiteMur.coinBD.y) / 2.0, pos1, rayon1);
		if (details.type != aidecollision::COLLISION_AUCUNE)
			return details;
	}
	else if (noeud->obtenirType() != ArbreRenduINF2990::NOM_CIBLE || ((NoeudCible*)noeud)->obtenirEtatCible())
	{
		double rayon2 = noeud->calculerRayon();
		glm::dvec3 pos2 = noeud->obtenirPositionRelative();
		details = aidecollision::calculerCollisionCercle(glm::dvec2(noeud->obtenirPositionRelative().x, noeud->obtenirPositionRelative().y), rayon2, glm::dvec2(positionRelative_.x, positionRelative_.y), rayon1);
	}
	return details;

}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
