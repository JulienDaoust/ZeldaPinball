///////////////////////////////////////////////////////////////////////////////
/// @file NoeudButoirCirculaire.cpp
/// @author Tommy Sagala
/// @date 2014-09-17
///////////////////////////////////////////////////////////////////////////////
#include "NoeudButoirCirculaire.h"
#include "ArbreRenduINF2990.h"

#include <windows.h>
#include <GL/gl.h>
#include <cmath>


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudButoirCirculaire::NoeudButoirCirculaire(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par défaut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudButoirCirculaire::NoeudButoirCirculaire(const std::string& typeNoeud)
: NoeudAbstrait{ typeNoeud }
{
	/// Charger le modèle 3D
	modele_.charger("media/butoir_circulaire.obj");

	// Création d'une liste d'affichage.  ATTENTION, CECI N'EST PAS UN
	// USAGE CORRECT DES LISTES D'AFFICHAGE, puisque la même liste serait
	// recréée pour chaque instance d'un noeud, alors que la même pourrait
	// être partagée par toutes les instances d'un même type de noeud.
	liste_ = modele::opengl_storage::OpenGL_Liste{ &modele_ };
	liste_.storageCharger();
	calculBoiteEnglobante();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudButoirCirculaire::~NoeudButoirCirculaire()
///
/// Ce destructeur désallouee la liste d'affichage du cube.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudButoirCirculaire::~NoeudButoirCirculaire()
{
	liste_.storageRelacher();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudButoirCirculaire::afficherConcret() const
///
/// Cette fonction effectue le véritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudButoirCirculaire::afficherConcret() const
{
	// Sauvegarde de la matrice.
	glPushMatrix();
	glRotated(angleRotation, 0, 0, 1);
	glScaled(scale_[0] * multiplicateurScale_, scale_[1] * multiplicateurScale_, scale_[2] * multiplicateurScale_);
	// Affichage du modèle.
	liste_.dessiner();
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
void NoeudButoirCirculaire::animer(float temps)
{
	if (touche_ && multiplicateurScale_ < hitScaling_)
	{
		double increment = (hitScaling_ - 1) / scalingTime_;
		multiplicateurScale_ += increment * temps;
	}
	else if (touche_)
	{
		touche_ = false;
	}
	else if (!touche_ && multiplicateurScale_ > 1)
	{
		double increment = (hitScaling_ - 1) / scalingTime_ *-1;
		multiplicateurScale_ += increment * temps;
	}
	calculBoiteEnglobante();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudButoirCirculaire::assignerCollision() 
///
/// Cette fonction change l'état de la collision
///
/// @param aucun.
///
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
void NoeudButoirCirculaire::assignerCollision()
{
	touche_ = true;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn virtual  aidecollision::DetailsCollision NoeudButoirCirculaire::collision(NoeudAbstrait* noeud) const
///
/// Cette fonction retourne les informations de collisions
///
/// @return aidecollision::DetailsCollision
///
////////////////////////////////////////////////////////////////////////
aidecollision::DetailsCollision NoeudButoirCirculaire::collision(NoeudAbstrait* noeud)
{
	aidecollision::DetailsCollision details;
	details.type = aidecollision::COLLISION_AUCUNE;

	if (noeud->obtenirType() == ArbreRenduINF2990::NOM_BILLE)
	{
		double rayon = noeud->calculerRayon();
		glm::dvec3 pos2 = noeud->obtenirPositionRelative();
		details = aidecollision::calculerCollisionCercle(glm::dvec2(noeud->obtenirPositionRelative().x, noeud->obtenirPositionRelative().y), rayon, glm::dvec2(positionRelative_.x, positionRelative_.y), calculerRayon());
	}
	return details;
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
