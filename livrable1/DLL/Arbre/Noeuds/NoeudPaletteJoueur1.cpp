///////////////////////////////////////////////////////////////////////////////
/// @file NoeudPaletteJoueur1.cpp
/// @author Tommy Sagala
/// @date 2014-09-17
///////////////////////////////////////////////////////////////////////////////
#include "NoeudPaletteJoueur1.h"

#include <windows.h>
#include <GL/gl.h>
#include <cmath>


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudPaletteJoueur1::NoeudPaletteJoueur1(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par d�faut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudPaletteJoueur1::NoeudPaletteJoueur1(const std::string& typeNoeud)
: NoeudAbstrait{ typeNoeud }
{
	/// Charger le mod�le 3D
	modele_.charger("media/palette1.obj");

	// Cr�ation d'une liste d'affichage.  ATTENTION, CECI N'EST PAS UN
	// USAGE CORRECT DES LISTES D'AFFICHAGE, puisque la m�me liste serait
	// recr��e pour chaque instance d'un noeud, alors que la m�me pourrait
	// �tre partag�e par toutes les instances d'un m�me type de noeud.
	liste_ = modele::opengl_storage::OpenGL_Liste{ &modele_ };
	liste_.storageCharger();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudPalette::~NoeudPalette()
///
/// Ce destructeur d�sallouee la liste d'affichage du cube.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudPaletteJoueur1::~NoeudPaletteJoueur1()
{
	liste_.storageRelacher();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudPalette::afficherConcret() const
///
/// Cette fonction effectue le v�ritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudPaletteJoueur1::afficherConcret() const
{
	// Sauvegarde de la matrice.
	glPushMatrix();
	// R�volution autour du centre.
	//glRotatef(angleRotation_, 0, 0, 1);
	// Translation.
	//glTranslatef(40, 0, 0);
	// Rotation autour de l'axe des z.
	glRotatef(90, 1, 0, 0);
	glRotatef(angleRotation, 0, 1, 0);
	// Rotation autour de l'axe des Y.
	//glRotatef(90, 0, 1, 0);
	// Recentrage du cube.
	//glTranslatef(0, 0, -10);
	// resize
	//glScaled(2, 2, 2);
	// Affichage du mod�le.
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
void NoeudPaletteJoueur1::animer(float temps)
{
	//// Le cube effectue un tour � toutes les 7 secondes sur l'axe des X.
	//angleX_ = fmod(angleX_ + temps / 7.0f * 360.0f, 360.0f);
	//// Le cube effectue un tour � toutes les 3 secondes sur l'axe des Y.
	//angleY_ = fmod(angleY_ + temps / 3.0f * 360.0f, 360.0f);
	//// Le cube effectue une r�volution � toutes les 15 secondes.
	//angleRotation_ = fmod(angleRotation_ + temps / 15.0f * 360.0f, 360.0f);
}


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
