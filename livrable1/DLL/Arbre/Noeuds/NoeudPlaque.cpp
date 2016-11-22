///////////////////////////////////////////////////////////////////////////////
/// @file NoeudPlaque.cpp
/// @author Tommy Sagala
/// @date 2014-09-17
/// @version 1.0
///////////////////////////////////////////////////////////////////////////////
#include "NoeudPlaque.h"
#include "Utilitaire.h"

#include <windows.h>
#include <GL/gl.h>
#include <cmath>


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudPlaque::NoeudPlaque(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par défaut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudPlaque::NoeudPlaque(const std::string& typeNoeud)
: NoeudComposite{ typeNoeud }
{
	/// Charger le modèle 3D
	modele_.charger("media/fond.obj");

	estBoiter = false;

	// Création d'une liste d'affichage.  ATTENTION, CECI N'EST PAS UN
	// USAGE CORRECT DES LISTES D'AFFICHAGE, puisque la même liste serait
	// recréée pour chaque instance d'un noeud, alors que la même pourrait
	// être partagée par toutes les instances d'un même type de noeud.
	assignerScale(90, 160, 90);
	liste_ = modele::opengl_storage::OpenGL_Liste{ &modele_ };
	liste_.storageCharger();
	assignerEstSelectionnable(false);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudPlaque::~NoeudPlaque()
///
/// Ce destructeur désallouee la liste d'affichage du cube.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudPlaque::~NoeudPlaque()
{
	liste_.storageRelacher();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudPlaque::afficherConcret() const
///
/// Cette fonction effectue le véritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudPlaque::afficherConcret() const
{
	// Appel à la version de la classe de base pour l'affichage des enfants.
	NoeudComposite::afficherConcret();

	// Sauvegarde de la matrice.
	glPushMatrix();
	// Révolution autour du centre.
	//glTranslatef(81, 0, 0);
	glScalef(scale_[0], scale_[1], scale_[2]);
	glRotatef(90, 1, 0, 0);
	// Affichage du modèle.
	liste_.dessiner();
	// Restauration de la matrice.
	glPopMatrix();
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
void NoeudPlaque::animer(float temps)
{
	// Appel à la version de la classe de base pour l'animation des enfants.
	//NoeudComposite::animer(temps);

	// L'araignée oscille selon une période de 4 secondes.
	//angle_ = fmod(angle_ + temps / 4.0f * 360.0f, 360.0f);
	//positionRelative_[0] = 5 * cos(utilitaire::DEG_TO_RAD(angle_));
	//positionRelative_[1] = 40 * sin(utilitaire::DEG_TO_RAD(angle_));
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::calculBoiteEnglobante( glm::dvec3& coinHG, glm::dvec3& coinBG, glm::dvec3& coinHD, glm::dvec3& coinBD )
///
/// Cette fonction calcule la boite englobant un noeud (hitbox)
///
/// @param [in,out] coinHG  : point contenant le coin superieur gauche
/// @param [in,out] coinBG  : point contenant le coin inferieur gauche
/// @param [in,out] coinHD  : point contenant le coin superieur droite
/// @param [in,out] coinBD  : point contenant le coin inferieur droite
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudPlaque::calculBoiteEnglobante()
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
	double hauteur = abs(boite.coinMax[2] - boite.coinMin[2]) * scale_[2];
	boiteEnglobante.coinHG = { longueur / 2 * -1, hauteur / 2, 0 };
	boiteEnglobante.coinBG = { longueur / 2 * -1, hauteur / 2 * -1, 0 };
	boiteEnglobante.coinHD = { longueur / 2, hauteur / 2, 0 };
	boiteEnglobante.coinBD = { longueur / 2, hauteur / 2 * -1, 0 };
}

////////////////////////////////////////////////////////////////////////
///
/// @fn virtual  BoiteEnglobante NoeudAbstrait::obtenirBoiteEnglobante( NoeudAbstrait* parent )
///
/// Cette fonction retourne la boite englobante
///
/// @return BoiteEnglobante
///
////////////////////////////////////////////////////////////////////////
BoiteEnglobante NoeudPlaque::obtenirBoiteEnglobante()
{
	BoiteEnglobante boitePositionnee = boiteEnglobante;
	glm::dvec3 translation = obtenirPositionRelative();

	if (!estBoiter)
		calculBoiteEnglobante();
	
	boitePositionnee.coinHG = { translation[0] + boitePositionnee.coinHG[0], translation[1] + boitePositionnee.coinHG[1], 0 };
	boitePositionnee.coinBG = { translation[0] + boitePositionnee.coinBG[0], translation[1] + boitePositionnee.coinBG[1], 0 };
	boitePositionnee.coinHD = { translation[0] + boitePositionnee.coinHD[0], translation[1] + boitePositionnee.coinHD[1], 0 };
	boitePositionnee.coinBD = { translation[0] + boitePositionnee.coinBD[0], translation[1] + boitePositionnee.coinBD[1], 0 };
	
	return boitePositionnee;
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////