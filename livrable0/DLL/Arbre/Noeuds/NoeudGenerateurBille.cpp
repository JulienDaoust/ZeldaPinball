///////////////////////////////////////////////////////////////////////////////
/// @file NoeudGenerateurBille.cpp
/// @author Tommy Sagala
/// @date 2014-09-17
/// @version 1.0
///////////////////////////////////////////////////////////////////////////////
#include "NoeudGenerateurBille.h"
#include "Utilitaire.h"

#include <windows.h>
#include <GL/gl.h>
#include <cmath>


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudGenerateurBille::NoeudGenerateurBille(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par d�faut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudGenerateurBille::NoeudGenerateurBille(const std::string& typeNoeud)
: NoeudComposite{ typeNoeud }
{
	/// Charger le mod�le 3D
	modele_.charger("media/bille.obj");

	// Cr�ation d'une liste d'affichage.  ATTENTION, CECI N'EST PAS UN
	// USAGE CORRECT DES LISTES D'AFFICHAGE, puisque la m�me liste serait
	// recr��e pour chaque instance d'un noeud, alors que la m�me pourrait
	// �tre partag�e par toutes les instances d'un m�me type de noeud.
	liste_ = modele::opengl_storage::OpenGL_Liste{ &modele_ };
	liste_.storageCharger();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudGenerateurBille::~NoeudGenerateurBille()
///
/// Ce destructeur d�sallouee la liste d'affichage du cube.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudGenerateurBille::~NoeudGenerateurBille()
{
	liste_.storageRelacher();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudGenerateurBille::afficherConcret() const
///
/// Cette fonction effectue le v�ritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudGenerateurBille::afficherConcret() const
{
	// Appel � la version de la classe de base pour l'affichage des enfants.
	NoeudComposite::afficherConcret();

	// Sauvegarde de la matrice.
	glPushMatrix();
	// R�volution autour du centre.
	glRotatef(35, sqrtf(2), sqrtf(2), 0);
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
void NoeudGenerateurBille::animer(float temps)
{
	// Appel � la version de la classe de base pour l'animation des enfants.
	NoeudComposite::animer(temps);

	// L'araign�e oscille selon une p�riode de 4 secondes.
	angle_ = fmod(angle_ + temps / 4.0f * 360.0f, 360.0f);
	positionRelative_[0] = 5 * cos(utilitaire::DEG_TO_RAD(angle_));
	positionRelative_[1] = 40 * sin(utilitaire::DEG_TO_RAD(angle_));
}


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
