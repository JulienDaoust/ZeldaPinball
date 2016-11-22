///////////////////////////////////////////////////////////////////////////////
/// @file NoeudMur.cpp
/// @author Tommy Sagala
/// @date 2014-09-17
/// @version 1.0
///////////////////////////////////////////////////////////////////////////////
#include "NoeudMur.h"
#include "Utilitaire.h"

#include <windows.h>
#include <GL/gl.h>
#include <cmath>
#include <iostream>


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudMur::NoeudMur(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par défaut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudMur::NoeudMur(const std::string& typeNoeud)
: NoeudComposite{ typeNoeud }
{
	/// Charger le modèle 3D
	modele_.charger("media/cube.obj");

	// Création d'une liste d'affichage.  ATTENTION, CECI N'EST PAS UN
	// USAGE CORRECT DES LISTES D'AFFICHAGE, puisque la même liste serait
	// recréée pour chaque instance d'un noeud, alors que la même pourrait
	// être partagée par toutes les instances d'un même type de noeud.
	liste_ = modele::opengl_storage::OpenGL_Liste{ &modele_ };
	liste_.storageCharger();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudMur::~NoeudMur()
///
/// Ce destructeur désallouee la liste d'affichage du cube.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudMur::~NoeudMur()
{
	liste_.storageRelacher();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudMur::afficherConcret() const
///
/// Cette fonction effectue le véritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudMur::afficherConcret() const
{
	// Appel à la version de la classe de base pour l'affichage des enfants.
	NoeudComposite::afficherConcret();

	// Sauvegarde de la matrice.
	glPushMatrix();
	
	glRotatef(angleRotation, 0, 0, 1);
	glScalef(multiplicateurScale_ * scale_[0], scale_[1], scale_[2]);

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
void NoeudMur::animer(float temps)
{
	// Appel à la version de la classe de base pour l'animation des enfants.
	NoeudComposite::animer(temps);

	// L'araignée oscille selon une période de 4 secondes.
	angle_ = fmod(angle_ + temps / 4.0f * 360.0f, 360.0f);
	positionRelative_[0] = 5 * cos(utilitaire::DEG_TO_RAD(angle_));
	positionRelative_[1] = 40 * sin(utilitaire::DEG_TO_RAD(angle_));
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
