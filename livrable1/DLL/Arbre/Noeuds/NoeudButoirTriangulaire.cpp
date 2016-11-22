///////////////////////////////////////////////////////////////////////////////
/// @file NoeudButoirTriangulaire.cpp
/// @author Tommy Sagala
/// @date 2014-09-17
///////////////////////////////////////////////////////////////////////////////
#include "NoeudButoirTriangulaire.h"

#include <windows.h>
#include <GL/gl.h>
#include <cmath>


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudButoirTriangulaire::NoeudButoirTriangulaire(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par défaut aux variables membres.
///
/// @param[in] typeNoeud : Le typtoire du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudButoirTriangulaire::NoeudButoirTriangulaire(const std::string& typeNoeud)
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
/// @fn NoeudButoirTriangulaire::~NoeudButoirTriangulaire()
///
/// Ce destructeur désallouee la liste d'affichage du cube.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudButoirTriangulaire::~NoeudButoirTriangulaire()
{
	liste_.storageRelacher();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudButoirTriangulaire::afficherConcret() const
///
/// Cette fonction effectue le véritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudButoirTriangulaire::afficherConcret() const
{
	// Sauvegarde de la matrice.
	glPushMatrix();
	// Révolution autour du centre.
	glRotatef(angleRotation, 0, 0, 1);
	// Translation.
	//glTranslatef(40, 0, 0);
	// Rotation autour de l'axe des X.
	//glRotatef(angleX_, 1, 0, 0);
	// Rotation autour de l'axe des Y.
	//glRotatef(angleY_, 0, 1, 0);
	// Recentrage du cube.
	//glTranslatef(0, 0, -10);
	glScaled(multiplicateurScale_, multiplicateurScale_, 1);
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
void NoeudButoirTriangulaire::animer(float temps)
{
}


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
