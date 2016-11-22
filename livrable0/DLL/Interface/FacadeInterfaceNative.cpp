////////////////////////////////////////////////
/// @file   FacadeInterfaceNative.cpp
/// @author INF2990
/// @date   2014-08-16
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////
#include "FacadeInterfaceNative.h"
#include "FacadeModele.h"

#include "glm\glm.hpp"
#include "FacadeModele.h"
#include "AideGL.h"
#include "Vue.h"
#include "ArbreRenduINF2990.h"
#include "NoeudPlaque.h"
#include "CompteurAffichage.h"
#include <iostream>

#include "BancTests.h"

extern "C"
{
	////////////////////////////////////////////////////////////////////////
	///
	/// __declspec(dllexport) void __cdecl initialiserOpenGL(int* handle)
	///
	/// Cette fonction initialise un contexte OpenGL dans la fenêtre
	/// identifiée par le handle passé en paramètre.  Cette fonction doit
	/// être la première à être appelée, car la création de l'objet du modèle
	/// C++ s'attend à avoir un contexte OpenGL valide.
	///
	/// @param[in] handle : Le handle.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl initialiserOpenGL(int* handle)
	{
		if (handle == nullptr)
			return;

		FacadeModele::obtenirInstance()->initialiserOpenGL((HWND) handle);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl libererOpenGL()
	///
	/// Cette fonction libère le contexte OpenGL. Cette fonction doit être la
	/// dernière à être appelée, car elle libère également l'objet du modèle
	/// C++.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl libererOpenGL()
	{
		FacadeModele::obtenirInstance()->libererOpenGL();

		// Désinitialisation de la façade.  Le fait de le faire après la
		// désinitialisation du contexte OpenGL aura pour conséquence que la
		// libération des listes d'affichages, par exemple, sera faite une fois que
		// le contexte n'existera plus, et sera donc sans effet.
		FacadeModele::libererInstance();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl dessinerOpenGL()
	///
	/// Cette fonction affiche la scène.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl dessinerOpenGL()
	{
		// Affiche la scène.
		FacadeModele::obtenirInstance()->afficher();

		// Temporaire: pour détecter les erreurs OpenGL
		aidegl::verifierErreurOpenGL();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// __declspec(dllexport) void __cdecl redimensionnerFenetre(int largeur, int hauteur)
	///
	/// Cette fonction doit être appelée lorsque la fenêtre est
	/// redimensionnée afin d'ajuster les paramètres de la machine à états
	/// d'OpenGL pour correspondre aux nouvelles dimensions de la fenêtre.
	///
	/// @param[in] largeur : La nouvelle largeur de la fenêtre.
	/// @param[in] hauteur : La nouvelle hauteur de la fenêtre.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl redimensionnerFenetre(int largeur, int hauteur)
	{
		FacadeModele::obtenirInstance()->obtenirVue()->redimensionnerFenetre(
			glm::ivec2{ 0, 0 },
			glm::ivec2{ largeur, hauteur }
		);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl animer(double temps)
	///
	/// Cette fonction effectue les différents calculs d'animations
	/// nécessaires pour le mode jeu, tel que les différents calculs de
	/// physique du jeu.
	///
	/// @param[in] temps : Intervalle de temps sur lequel effectuer le calcul.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl animer(double temps)
	{
		FacadeModele::obtenirInstance()->animer((float) temps);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl zoomIn()
	///
	/// Cette fonction applique un zoom avant sur le présent volume de vision.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl zoomIn()
	{
		FacadeModele::obtenirInstance()->obtenirVue()->zoomerIn();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl zoomOut()
	///
	/// Cette fonction applique un zoom arrière sur le présent volume de vision.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl zoomOut()
	{
		FacadeModele::obtenirInstance()->obtenirVue()->zoomerOut();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) int __cdecl obtenirAffichagesParSeconde()
	///
	/// Cette fonction permet d'obtenir le nombre d'affichages par seconde.
	///
	/// @return Le nombre d'affichage par seconde.
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) int __cdecl obtenirAffichagesParSeconde()
	{
		return utilitaire::CompteurAffichage::obtenirInstance()->obtenirAffichagesSeconde();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) bool __cdecl executerTests()
	///
	/// Cette fonction permet d'exécuter l'ensemble des tests unitaires
	///
	/// @return 0 si tous les tests ont réussi, 1 si au moins un test a échoué
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) bool __cdecl executerTests()
	{
		bool reussite = BancTests::obtenirInstance()->executer();
		return reussite ? 0 : 1;
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl ajouterNoeud(std::string nom)
	///
	/// Cette fonction permet ajouter un noeud a l'arbre de rendu
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl ajouterNoeud(char* nom,int x, int y)
	{
		std::string type(nom);
		glm::dvec3 point;
		FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x, y, point);
		FacadeModele::obtenirInstance()->ajouterNoeud(nom,point);
		
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl ajouterMur(int x1, int y1, int x2, int y2)
	///
	/// Cette fonction permet ajouter un noeud a l'arbre de rendu
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl ajouterNoeudMur(int x1, int y1, int x2, int y2)
	{
		glm::dvec3 point1;
		glm::dvec3 point2;
		FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x1, y1, point1);
		FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x2, y2, point2);
		FacadeModele::obtenirInstance()->ajouterNoeudMur(point1, point2);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl selectionSimple(int x, int y)
	///
	/// Cette fonction permet de selectionner un objet
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl selectionSimple(int x, int y)
	{
		glm::dvec3 point;
		FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x, y, point);
		FacadeModele::obtenirInstance()->selectionSimple(point);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl selectionMultiple(int gauche, int haut, int droite, int bas)
	///
	/// Cette fonction permet de selectionner un ou plusieurs objets
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl selectionMultiple(int gauche, int haut, int droite, int bas)
	{
		glm::dvec3 min;
		glm::dvec3 max;
		FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(gauche, bas, min);
		FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(droite, haut, max);
		FacadeModele::obtenirInstance()->selectionMultiple(min, max);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl deselectionnerTout()
	///
	/// Cette fonction permet de deselectionner tout lesobjets de l'arbre
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl deselectionnerTout()
	{
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->deselectionnerTout();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl RetournerPosition(int x, int y)
	///
	/// Cette fonction permet de retourner une position sur linterface en position sur la cloture virtuelle
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl RetournerPosition(int x, int y)
	{
		glm::dvec3 point;
		FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x, y, point);
		
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn __declspec(dllexport) void __cdecl RetournerPosition(int x, int y)
	///
	/// Cette fonction permet de retourner une position sur linterface en position sur la cloture virtuelle
	///
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) bool __cdecl survolPlaque(int x, int y)
	{
		glm::dvec3 point;
		NoeudAbstrait* noeudPlaque;
		BoiteEnglobante boitePlaque;

		FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x, y, point);
		noeudPlaque = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->chercher("plaque");

		boitePlaque = noeudPlaque->obtenirBoiteEnglobante();
		return utilitaire::DANS_LIMITESXY(point[0], boitePlaque.coinBG[0], boitePlaque.coinBD[0], point[1], boitePlaque.coinBG[1],boitePlaque.coinHG[1]);

	}
}


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////