///////////////////////////////////////////////////////////////////////////////
/// @file NoeudTrou.cpp
/// @author Tommy Sagala
/// @date 2014-09-17
/// @version 1.0
///////////////////////////////////////////////////////////////////////////////
#include "NoeudTrou.h"
#include "Utilitaire.h"

#include <windows.h>
#include <GL/gl.h>
#include <cmath>

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudTrou::NoeudTrou(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par défaut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudTrou::NoeudTrou(const std::string& typeNoeud)
: NoeudComposite{ typeNoeud }
{
	/// Charger le modèle 3D
	modele_.charger("media/trou.obj");

	// Création d'une liste d'affichage.  ATTENTION, CECI N'EST PAS UN
	// USAGE CORRECT DES LISTES D'AFFICHAGE, puisque la même liste serait
	// recréée pour chaque instance d'un noeud, alors que la même pourrait
	// être partagée par toutes les instances d'un même type de noeud.
	liste_ = modele::opengl_storage::OpenGL_Liste{ &modele_ };
	liste_.storageCharger();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudTrou::~NoeudTrou()
///
/// Ce destructeur désallouee la liste d'affichage du cube.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudTrou::~NoeudTrou()
{
	liste_.storageRelacher();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudTrou::afficherConcret() const
///
/// Cette fonction effectue le véritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudTrou::afficherConcret() const
{
	// Appel à la version de la classe de base pour l'affichage des enfants.
	NoeudComposite::afficherConcret();

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
void NoeudTrou::animer(float temps)
{
	
	//NoeudComposite::chercher(NoeudAbstrait* bille);
	//std::vector<NoeudAbstrait*> vectNoeud = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->o;
	//std::vector<NoeudAbstrait*>::iterator it;
	//NoeudPaletteJoueur2Droite* noeudPalette;
	//for (it = vectNoeud.begin(); it < vectNoeud.end(); it++)
	//{
	//	noeudPalette = (NoeudPaletteJoueur2Droite*)(*it);
	//	noeudPalette->setAnimation();
	//}
	////NoeudComposite::effacer(bille);
}


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
