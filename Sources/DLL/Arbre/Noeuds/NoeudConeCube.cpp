///////////////////////////////////////////////////////////////////////////////
/// @file NoeudConeCube.cpp
/// @author Julien Gascon-Samson
/// @date 2011-05-19
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "NoeudConeCube.h"

#include <windows.h>
#include <GL/gl.h>
#include <cmath>


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudConeCube::NoeudConeCube(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par d�faut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudConeCube::NoeudConeCube(const std::string& typeNoeud)
: NoeudAbstrait{ typeNoeud }
{
	/// Charger le mod�le 3D
	modele_.charger("media/cubecone.obj");

	// Cr�ation d'une liste d'affichage.  ATTENTION, CECI N'EST PAS UN
	// USAGE CORRECT DES LISTES D'AFFICHAGE, puisque la m�me liste serait
	// recr��e pour chaque instance d'un noeud, alors que la m�me pourrait
	// �tre partag�e par toutes les instances d'un m�me type de noeud.
	liste_ = modele::opengl_storage::OpenGL_Liste{ &modele_ };
	liste_.storageCharger();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudConeCube::~NoeudConeCube()
///
/// Ce destructeur d�sallouee la liste d'affichage du cube.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudConeCube::~NoeudConeCube()
{
	liste_.storageRelacher();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudConeCube::afficherConcret() const
///
/// Cette fonction effectue le v�ritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudConeCube::afficherConcret() const
{
	// Sauvegarde de la matrice.
	glPushMatrix();
	// R�volution autour du centre.
	glRotated(angleRotation, 0, 0, 1);
	// Translation.
	glTranslated(40, 0, 0);
	// Recentrage du cube.
	glTranslated(0, 0, -10);
	// Affichage du mod�le.
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
void NoeudConeCube::animer(float temps)
{
}


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
