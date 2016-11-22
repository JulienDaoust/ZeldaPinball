///////////////////////////////////////////////////////////////////////////////
/// @file NoeudCible.cpp
/// @author Tommy Sagala
/// @date 2014-09-17
///////////////////////////////////////////////////////////////////////////////
#include "NoeudCible.h"
#include "Utilitaire.h"

#include <iostream>
#include <windows.h>
#include <GL/gl.h>
#include <cmath>


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudCible::NoeudCible(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par défaut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudCible::NoeudCible(const std::string& typeNoeud)
: NoeudAbstrait{ typeNoeud }
{
	/// Charger le modèle 3D
	modele_.charger("media/cibleFinal.obj");

	// Création d'une liste d'affichage.  ATTENTION, CECI N'EST PAS UN
	// USAGE CORRECT DES LISTES D'AFFICHAGE, puisque la même liste serait
	// recréée pour chaque instance d'un noeud, alors que la même pourrait
	// être partagée par toutes les instances d'un même type de noeud.
	liste_ = modele::opengl_storage::OpenGL_Liste{ &modele_ };
	liste_.storageCharger();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudCible::~NoeudCible()
///
/// Ce destructeur désallouee la liste d'affichage du cube.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudCible::~NoeudCible()
{
	liste_.storageRelacher();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCible::afficherConcret() const
///
/// Cette fonction effectue le véritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudCible::afficherConcret() const
{
	// Sauvegarde de la matrice.
	glPushMatrix();
	glTranslated(0, 0, cibleDisp);
	glScaled(scale_[0], scale_[1], scale_[2]);
	glRotated(90, 0, 1, 0);
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
void NoeudCible::animer(float temps)
{
	if (touche_)
	{
		//positionRelative_.y -= 0.3;
		positionRelative_.z -= 0.3;

		if (positionRelative_.z <= -10)
		{
			touche_ = false;
			etat_ = false;
			
		}
	}
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
void NoeudCible::assignerCollision()
{
	touche_ = true;
	etat_ = false;
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
bool NoeudCible::obtenirEtatCible() const
{
	return etat_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn virtual  void NoeudAbstrait::reinitialiserObjet()
///
/// Cette fonction réinitialise l'état de l'objet
///
/// @return double
///
////////////////////////////////////////////////////////////////////////
void NoeudCible::reinitialiserCible()
{
	touche_ = false;
	etat_ = true;
	positionRelative_.z += 0.03;
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
