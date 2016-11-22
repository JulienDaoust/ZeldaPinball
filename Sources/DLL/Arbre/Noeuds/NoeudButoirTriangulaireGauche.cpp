///////////////////////////////////////////////////////////////////////////////
/// @file NoeudButoirTriangulaireGauche.cpp
/// @author Tommy Sagala
/// @date 2014-09-17
///////////////////////////////////////////////////////////////////////////////
#include "NoeudButoirTriangulaireGauche.h"

#include <windows.h>
#include <GL/gl.h>
#include <cmath>
#include "ArbreRenduINF2990.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudButoirTriangulaireGauche::NoeudButoirTriangulaireGauche(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par défaut aux variables membres.
///
/// @param[in] typeNoeud : Le typtoire du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudButoirTriangulaireGauche::NoeudButoirTriangulaireGauche(const std::string& typeNoeud)
: NoeudAbstrait{ typeNoeud }
{
	/// Charger le modèle 3D
	modele_.charger("media/butoirTriangulaire.obj");

	// Création d'une liste d'affichage.  ATTENTION, CECI N'EST PAS UN
	// USAGE CORRECT DES LISTES D'AFFICHAGE, puisque la même liste serait
	// recréée pour chaque instance d'un noeud, alors que la même pourrait
	// être partagée par toutes les instances d'un même type de noeud.
	liste_ = modele::opengl_storage::OpenGL_Liste{ &modele_ };
	liste_.storageCharger();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudButoirTriangulaireGauche::~NoeudButoirTriangulaireGauche()
///
/// Ce destructeur désallouee la liste d'affichage du cube.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudButoirTriangulaireGauche::~NoeudButoirTriangulaireGauche()
{
	liste_.storageRelacher();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudButoirTriangulaireGauche::afficherConcret() const
///
/// Cette fonction effectue le véritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudButoirTriangulaireGauche::afficherConcret() const
{
	// Sauvegarde de la matrice.
	glPushMatrix();
	// Révolution autour du centre.
	glRotated(angleRotation, 0, 0, 1);
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
void NoeudButoirTriangulaireGauche::animer(float temps)
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudButoirTriangulaireGauche::calculBoiteEnglobante()
///
/// Cette fonction calcule la boite englobant un noeud (hitbox)
///
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudButoirTriangulaireGauche::calculBoiteEnglobante()
{
	if (scale_[0] == 0 && scale_[1] == 0 && scale_[2] == 0)
	{
		scale_[0] = 1;
		scale_[1] = 1;
		scale_[2] = 1;
	}
	utilitaire::BoiteEnglobante boite;
	boite = utilitaire::calculerBoiteEnglobante(modele_);
	double longueur = abs(boite.coinMax[0] - boite.coinMin[0]) * scale_[0];
	double hauteur = abs(boite.coinMax[1] - boite.coinMin[1]) * scale_[1];
	glm::dvec3 HG = { boite.coinMin[0] * scale_[0], boite.coinMax[1] * scale_[1], 0 };
	glm::dvec3 BG = { boite.coinMin[0] * scale_[0], boite.coinMin[1] * scale_[1], 0 };
	glm::dvec3 HD = { boite.coinMax[0] * scale_[0], boite.coinMax[1] * scale_[1], 0 };
	glm::dvec3 BD = { boite.coinMax[0] * scale_[0], boite.coinMin[1] * scale_[1], 0 };

	double radAngle = (angleRotation * 3.141592 / 180);


	boiteEnglobante.coinHG[0] = HG[0] * std::cos(radAngle) - HG[1] * std::sin(radAngle);
	boiteEnglobante.coinHG[1] = HG[0] * std::sin(radAngle) + HG[1] * std::cos(radAngle);

	boiteEnglobante.coinBG[0] = BG[0] * std::cos(radAngle) - BG[1] * std::sin(radAngle);
	boiteEnglobante.coinBG[1] = BG[0] * std::sin(radAngle) + BG[1] * std::cos(radAngle);

	boiteEnglobante.coinHD[0] = HD[0] * std::cos(radAngle) - HD[1] * std::sin(radAngle);
	boiteEnglobante.coinHD[1] = HD[0] * std::sin(radAngle) + HD[1] * std::cos(radAngle);

	boiteEnglobante.coinBD[0] = BD[0] * std::cos(radAngle) - BD[1] * std::sin(radAngle);
	boiteEnglobante.coinBD[1] = BD[0] * std::sin(radAngle) + BD[1] * std::cos(radAngle);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn virtual  aidecollision::DetailsCollision NoeudButoirTriangulaireGauche::collision(NoeudAbstrait* noeud)
///
/// Cette fonction retourne les informations de collisions
///
/// @return aidecollision::DetailsCollision
///
////////////////////////////////////////////////////////////////////////
aidecollision::DetailsCollision NoeudButoirTriangulaireGauche::collision(NoeudAbstrait* noeud)
{
	aidecollision::DetailsCollision details;
	details.type = aidecollision::COLLISION_AUCUNE;
	return details;
}
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
